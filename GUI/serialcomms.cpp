#include "stdafx.h"
#include "states.h"
#include "serialcomms.h"


using namespace System::IO::Ports;
using namespace System::Windows::Forms;

void SerialComms::sendSerialByte(unsigned char byte)
{
	array<unsigned char>^ sendArray = gcnew array<unsigned char>(1);
	sendArray[0] = byte;
	sp->Write(sendArray, 0, 1);
}

void SerialComms::sendChange(unsigned char comm_code, unsigned char st_code, unsigned char ack_code) 
{
	if (serialChange)
		return;

	// Loop until return statement is hit (ack received)
	while (true)
	{
		unsigned int timeout = SERIAL_TIMEOUT_GUI;
		sendSerialByte(comm_code);
		if (st_code != 0xFF) sendSerialByte(st_code);

		// Wait for ack
		while (--timeout)
		{
			if (ack == ack_code)
			{
				ack = 0;
				return;
			}
		}

		// If this code is reached, the ack was not received.
		if (MessageBox::Show("The scales did not respond to the request."
			+ " Press Retry to try again or Cancel to close the program",
			"Lost connection to scales",
			MessageBoxButtons::RetryCancel, MessageBoxIcon::Error)
				== System::Windows::Forms::DialogResult::Cancel)
		{
			closeAll = true;
			Application::Exit();
			break;
		}
	}
	ack = 0;
}

void SerialComms::sendChange(unsigned char comm_code, unsigned char ack_code)
{
	sendChange(comm_code, 0xFF, ack_code);
}

void SerialComms::timeout(unsigned char ack_code)
{

}