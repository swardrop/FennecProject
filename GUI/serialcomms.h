#pragma once

#include "commscodes.h"

public ref class SerialComms
{
public:
	SerialComms(System::IO::Ports::SerialPort ^port)
	{
		sp = port;
		waiting = false;
	}

	~SerialComms()
	{
	}

	void sendSerialByte(unsigned char byte);
	void sendChange(unsigned char comm_code, unsigned char st_code, unsigned char ack_code);
	void sendChange(unsigned char comm_code, unsigned char ack_code);

	void timeout(unsigned char ack_code);

	bool waiting;
private:
	System::IO::Ports::SerialPort ^sp;
};

//void _sendSerialByte(System::IO::Ports::SerialPort ^sp, char byte);
//void _sendChange(System::IO::Ports::SerialPort ^sp, unsigned char comm_code, unsigned char st_code, unsigned char ack_code);