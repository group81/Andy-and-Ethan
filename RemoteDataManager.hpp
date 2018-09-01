#ifndef MTRN3500_REMOTEDATAMANAGER_H
#define MTRN3500_REMOTEDATAMANAGER_H

//
// The RemoteDataManager class handles communication of one message type between two machines using a serial interface.  
//   This class is designed for the use of a simple "polling" strategy, and may not be very robust to errors.  Please
//   let us know immediately if you are having problems with serial port communication between your laptop and the
//   PC104 using this class.
//

#include <iostream>
#include <string>
#include <vector>

struct RemoteMessage
{
	char			type;
	std::string		payload;
};

class RemoteDataManager {
public:
	static const int MAX_RESPONSE_SIZE = 10000;
	
	// Send data from source buffer [buff] of length [len] down the pipe with a trailing [checksum] value. 
	//
	//        [buff] is the pointer that indicates what data to be written out.
	//         [len] is the amount of bytes to write.
	//    [checksum] is the validity byte used to check for data corruption.
	//
	static void Write(const std::string & msg);

	
	// Receive data to buffer [buff] of length [len] from the pipe with a trailing [checksum] value.
	// Returns true if all requested bytes were successfully read into the specified target buffer.
	//
	//        [buff] is the pointer to the data to be overwritten with fresh data.
	//         [len] is the amount of bytes to read.
	//    [checksum] is the pointer to where the validity byte should be written to.
	//
	static std::vector<RemoteMessage> Read();

	
	// Connect to port at [address] for communication, returns true if successful.  If the address
	// "Emulator" is given, the RemoteDataManager will Read using the provided emulation function. 
	// If no emulation function is provided, a default is used (see DefaultEmulationFill in the .cpp file).
	//
	//    On Windows,
	//          Use "COM1" for serial port 1, "COM2" for 2, etc...
	//    On Linux and OSX, 
	//          Pass the device address as listed by the operating system.  You can use the
	//          "dmesg" console command to help identify what the USB serial interface
	//          cable may be registered as.  Example: "/dev/tty.usbserial-2232ftdi". 
	//
	//	   [baudRate] is the baud rate of which the device operates.
	//		 [parity] is the parity scheme used.  The value can be 0 for none, 1 for odd, or 2 for even.
	//	   [stopBits] is the number of stop bits used.  The value can be 1 or 2.
	//
	static bool Connect(const std::string & address, const std::string & port);

	
	// Closes any opened ports, causing all reads and writes to fail.
	//
	static void Disconnect();

	
	// Returns true if an active port exists.
	//
	static bool IsConnected();
private:
	static bool			mIsConnected;

	RemoteDataManager();
	~RemoteDataManager();
};

#endif // for MTRN3500_REMOTEDATAMANAGER_H
