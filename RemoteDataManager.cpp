#include "RemoteDataManager.hpp"

#include <math.h>

#define FILLING_BUFFER 1

#define MESSAGE_HEADER_SIZE 8
#define MESSAGE_FOOTER_SIZE 2

// ---- operating system specific code STARTS here ----
#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)

static SOCKET		ConnectSocket  = INVALID_SOCKET;
static WSAEVENT		ahEvents[1]; 
static bool			inited = false;

bool OSinit()
{
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return false;
	}

	// Create event 
	ahEvents[0] = WSACreateEvent(); 
	return true;
}

void OSclose()
{
	closesocket(ConnectSocket);
	ConnectSocket = INVALID_SOCKET;
}

bool OSopen(const char * szHostName, const char * szPortName)
{
	if(!inited)
		OSinit();

	addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	int iResult = getaddrinfo(szHostName, szPortName, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed for %s: %d\n", szHostName, iResult);
		// WSACleanup();
		return false;
	}

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr=result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		return false;
	}

	// Connect to server.
	iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	// Should really try the next address returned by getaddrinfo
	// if the connect call failed
	// But for this simple example we just free the resources
	// returned by getaddrinfo and print an error message

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		return false;
	}

	return true;
}
bool OSwrite(const char * lpBuf, DWORD dwToWrite)
{
	// Send an initial buffer
	int iResult = send(ConnectSocket, (const char*) lpBuf, dwToWrite, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		return false;
	}
	return true;
}
DWORD OSread(char * lpBuf, DWORD dwToRead)
{
	DWORD dwRead;
	
#if FILLING_BUFFER
	int totRead = 0;
	bool ok = true;
	while(ok && (dwToRead - totRead) > 0) {
		dwRead = recv(ConnectSocket, (char*) lpBuf + totRead, dwToRead - totRead, 0);
		//ReadFile(hComm, lpBuf + totRead, dwToRead - totRead, &dwRead, NULL);
		if(dwRead <= 0 || dwRead == SOCKET_ERROR)
			ok = false;
		else
			totRead += dwRead;
	}
	return totRead;
#else
	dwRead = recv(ConnectSocket, (char*) lpBuf, dwToRead, 0);
	//ReadFile(hComm, lpBuf, dwToRead, &dwRead, NULL);
	return dwRead;
#endif

}

#else
//#include <fcntl.h>   /* File control definitions */
//#include <termios.h> /* POSIX terminal control definitions */
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

static int sock;
void OSclose()
{
	close(sock);
}


bool OSopen(const char * szHostName, const char * szPortName)
{
    // server address
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    
	addrinfo *result = NULL, *ptr = NULL, hints;
    
	memset( &hints, 0, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
    
	// Resolve the server address and port
	int iResult = getaddrinfo(szHostName, szPortName, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed for %s: %d\n", szHostName, iResult);
		return false;
	}
    
    // Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr=result;
 
    sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    
	if (sock == -1) {
        perror("Socket creation");
        return false;
	}
    
	// Connect to server.
	iResult = connect( sock, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == -1) {
        perror("Connection error");
        return false;
	}
    
    return true;
}
bool OSwrite(const char * buff, size_t len)
{
	return write(sock, buff, len) != -1;
}
size_t OSread(char * buff, size_t len)
{
	return read(sock, buff, len);
}

#endif
// ---- operating system specific code ENDS here ----

// ----------------------------------------------------
// ------ RemoteDataManager class implementation ------
// ----------------------------------------------------


bool RemoteDataManager::mIsConnected = false;

void RemoteDataManager::Write(const std::string & msg)
{
	bool ok = true;
	if(IsConnected()) {
		std::string request = msg + "\n";

		ok = OSwrite(request.c_str(), request.length());
	}

	if(!ok)
		Disconnect();
}


std::vector<RemoteMessage> RemoteDataManager::Read()
{
	std::vector<RemoteMessage> ret;
	int totRead = 0;
	bool ok = true;
	if(IsConnected()) {
		char header[MESSAGE_HEADER_SIZE + 1];
		char footer[MESSAGE_FOOTER_SIZE + 1];
		memset(header, 0, sizeof(header));

		// read the response header
		size_t hlen = OSread(header, MESSAGE_HEADER_SIZE);
		totRead += hlen;
		ok = ok && (hlen == MESSAGE_HEADER_SIZE);

		char rcode;
		int rlen;
		size_t flen;

		// validate header
		if(ok && sscanf(header, "-%c-%d", &rcode, &rlen) == 2 && rcode == 'R') {
			if(rlen > 0) {

				// read messages until we've read the entire response
				while(ok && (totRead < rlen + MESSAGE_HEADER_SIZE)) {

					// read the message header
					char mcode;
					int mlen;
					hlen = OSread(header, MESSAGE_HEADER_SIZE);
					totRead += hlen;
					ok = ok && (hlen == MESSAGE_HEADER_SIZE);

					// validate header
					if(ok && sscanf(header, "-%c-%d", &mcode, &mlen) == 2) {
						char msgbuff[MAX_RESPONSE_SIZE];
						memset(msgbuff, 0, sizeof(msgbuff));

						// read the message text
						size_t mdlen = OSread(msgbuff, mlen);
						totRead += mdlen;
						ok = ok && (mdlen == mlen);

						RemoteMessage msg;
						msg.type = mcode;
						msg.payload = msgbuff;

						// add to vector
						ret.push_back(msg);

						if(ok) {
							// read message separator
							flen = OSread(footer, MESSAGE_FOOTER_SIZE);
							totRead += flen;
							ok = ok && (flen == MESSAGE_FOOTER_SIZE);
						}
					}
				}

			}

			if(ok) {
				// read message separator
				flen = OSread(footer, MESSAGE_FOOTER_SIZE);
				totRead += flen;
				ok = ok && (flen == MESSAGE_FOOTER_SIZE);
			}
		}
	}

	if(!ok)
		Disconnect();

	return ret;
}


bool RemoteDataManager::Connect(const std::string & address, const std::string & port)
{
	if(IsConnected())
		Disconnect();

	mIsConnected = OSopen(address.c_str(), port.c_str());

	return mIsConnected;
}

void RemoteDataManager::Disconnect()
{
	if(IsConnected())
		OSclose();

	mIsConnected = false;
}

bool RemoteDataManager::IsConnected()
{
	return mIsConnected;
}

RemoteDataManager::RemoteDataManager() {}
RemoteDataManager::~RemoteDataManager() {}
