#pragma once

#include "FrmUsrRemote.h"
#include "FrmFactoryMode.h"
#include "states.h"
#include "commscodes.h"

bool serialChange = false;
bool weightReady = true;
short weightData = 0;
unsigned char ack = 0;
unsigned char init_statesRxd = 0;
unsigned char receivedCount = 0;
unsigned int weightPer1000Items;
unsigned short count_serial;
unsigned short mean, variance;
unsigned short weightReadings[ADC_BUFSIZE];
unsigned char numReadings;
unsigned char numSamples;

namespace FennecScalesGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();

			port = gcnew SerialPort("COM1", 9600, Parity::None, 8, StopBits::One);
			port->Open();
			port->Encoding = System::Text::Encoding::UTF8;
			comms = gcnew SerialComms(port);

			form1SerialHandler = gcnew SerialDataReceivedEventHandler(this, &Form1::port_DataReceived);
			port->DataReceived += form1SerialHandler;

			usrRemoteForm = gcnew FrmUsrRemote(this, comms);
			factoryForm = gcnew FrmFactoryMode(usrRemoteForm, comms);

			cur_state.state = WEIGH; // TODO: replace with proper init?
			cur_state.units = GRAMS;
			cur_state.outputs = LCD_TTS;
			cur_state.isFactory = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
	private: System::Windows::Forms::PictureBox^  pictureBox1;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  State;

	private: System::Windows::Forms::RadioButton^  radioCount;
	private: System::Windows::Forms::RadioButton^  radioWeigh;
	private: System::Windows::Forms::CheckBox^  checkFactory;
	private: System::Windows::Forms::GroupBox^  warningsBox;
	private: System::Windows::Forms::CheckBox^  overWarningCB;
	private: System::Windows::Forms::CheckBox^  evWarningCB;
			 
			 FrmFactoryMode^ factoryForm;
			 FrmUsrRemote^ usrRemoteForm;

			 SerialPort^ port;
			 SerialComms^ comms;
			 SerialDataReceivedEventHandler^ form1SerialHandler;
	private: System::Windows::Forms::Button^  facButton;

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->State = (gcnew System::Windows::Forms::GroupBox());
			this->checkFactory = (gcnew System::Windows::Forms::CheckBox());
			this->radioCount = (gcnew System::Windows::Forms::RadioButton());
			this->radioWeigh = (gcnew System::Windows::Forms::RadioButton());
			this->warningsBox = (gcnew System::Windows::Forms::GroupBox());
			this->overWarningCB = (gcnew System::Windows::Forms::CheckBox());
			this->evWarningCB = (gcnew System::Windows::Forms::CheckBox());
			this->facButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->State->SuspendLayout();
			this->warningsBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->ImageLocation = L"";
			this->pictureBox1->Location = System::Drawing::Point(70, 46);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(327, 217);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(99, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(267, 31);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Fennec Scales GUI";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(70, 284);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(327, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Proceed to remote scale control";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// State
			// 
			this->State->Controls->Add(this->checkFactory);
			this->State->Controls->Add(this->radioCount);
			this->State->Controls->Add(this->radioWeigh);
			this->State->Location = System::Drawing::Point(5, 101);
			this->State->Name = L"State";
			this->State->Size = System::Drawing::Size(59, 100);
			this->State->TabIndex = 6;
			this->State->TabStop = false;
			this->State->Text = L"State";
			// 
			// checkFactory
			// 
			this->checkFactory->AutoSize = true;
			this->checkFactory->Location = System::Drawing::Point(12, 72);
			this->checkFactory->Name = L"checkFactory";
			this->checkFactory->Size = System::Drawing::Size(32, 17);
			this->checkFactory->TabIndex = 2;
			this->checkFactory->Text = L"F";
			this->checkFactory->UseVisualStyleBackColor = true;
			this->checkFactory->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkFactory_CheckedChanged);
			// 
			// radioCount
			// 
			this->radioCount->AutoSize = true;
			this->radioCount->Location = System::Drawing::Point(12, 49);
			this->radioCount->Name = L"radioCount";
			this->radioCount->Size = System::Drawing::Size(32, 17);
			this->radioCount->TabIndex = 1;
			this->radioCount->Text = L"C";
			this->radioCount->UseVisualStyleBackColor = true;
			this->radioCount->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioCount_CheckedChanged);
			// 
			// radioWeigh
			// 
			this->radioWeigh->AutoSize = true;
			this->radioWeigh->Checked = true;
			this->radioWeigh->Location = System::Drawing::Point(12, 26);
			this->radioWeigh->Name = L"radioWeigh";
			this->radioWeigh->Size = System::Drawing::Size(36, 17);
			this->radioWeigh->TabIndex = 0;
			this->radioWeigh->TabStop = true;
			this->radioWeigh->Text = L"W";
			this->radioWeigh->UseVisualStyleBackColor = true;
			this->radioWeigh->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioWeigh_CheckedChanged);
			// 
			// warningsBox
			// 
			this->warningsBox->Controls->Add(this->overWarningCB);
			this->warningsBox->Controls->Add(this->evWarningCB);
			this->warningsBox->Location = System::Drawing::Point(5, 207);
			this->warningsBox->Name = L"warningsBox";
			this->warningsBox->Size = System::Drawing::Size(59, 100);
			this->warningsBox->TabIndex = 7;
			this->warningsBox->TabStop = false;
			this->warningsBox->Text = L"Warnings";
			// 
			// overWarningCB
			// 
			this->overWarningCB->AutoSize = true;
			this->overWarningCB->Location = System::Drawing::Point(11, 62);
			this->overWarningCB->Name = L"overWarningCB";
			this->overWarningCB->Size = System::Drawing::Size(34, 17);
			this->overWarningCB->TabIndex = 3;
			this->overWarningCB->Text = L"O";
			this->overWarningCB->UseVisualStyleBackColor = true;
			this->overWarningCB->CheckedChanged += gcnew System::EventHandler(this, &Form1::overWarningCB_CheckedChanged);
			// 
			// evWarningCB
			// 
			this->evWarningCB->AutoSize = true;
			this->evWarningCB->Location = System::Drawing::Point(12, 39);
			this->evWarningCB->Name = L"evWarningCB";
			this->evWarningCB->Size = System::Drawing::Size(33, 17);
			this->evWarningCB->TabIndex = 2;
			this->evWarningCB->Text = L"V";
			this->evWarningCB->UseVisualStyleBackColor = true;
			this->evWarningCB->CheckedChanged += gcnew System::EventHandler(this, &Form1::evWarningCB_CheckedChanged);
			// 
			// facButton
			// 
			this->facButton->Location = System::Drawing::Point(12, 12);
			this->facButton->Name = L"facButton";
			this->facButton->Size = System::Drawing::Size(75, 23);
			this->facButton->TabIndex = 8;
			this->facButton->Text = L"FACTORY";
			this->facButton->UseVisualStyleBackColor = true;
			this->facButton->Click += gcnew System::EventHandler(this, &Form1::facButton_Click);
			// 
			// Form1
			// 
			this->AccessibleName = L"WeighMode";
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(453, 319);
			this->Controls->Add(this->facButton);
			this->Controls->Add(this->warningsBox);
			this->Controls->Add(this->State);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Fennec Scales";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->State->ResumeLayout(false);
			this->State->PerformLayout();
			this->warningsBox->ResumeLayout(false);
			this->warningsBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void port_DataReceived(Object ^ sender, SerialDataReceivedEventArgs^ e)
		 {
			 static unsigned char inProgress = 0;
			 static unsigned char countInProgress = 0;
			 
			 static unsigned char statsInProgress = 0;
			 static unsigned char statsBuffer[4];
			 
			 int dataInt;
			 unsigned char data;

			 while ((dataInt = port->ReadByte()) != -1)
			 {
				 data = (unsigned char) dataInt;


				 //// Check for ongoing reception
				 if (statsInProgress)
				 {
					 statsBuffer[4 - statsInProgress] = data;
					 
					 if (!(statsInProgress--))
					 {
						 mean = ((unsigned short) statsBuffer[0] << 8) + (unsigned short) statsBuffer[1];
						 variance = ((unsigned short) statsBuffer[2] << 8) + (unsigned short) statsBuffer[3];
						 ack = COMM_ACK_STATS;
					 }
				 }

				 
				 // Check for count/item transmission in progress
				 else if (countInProgress == 6)
				 {
					 weightPer1000Items = (unsigned int) data << 24;
					 countInProgress = 5;
				 }
				 else if (countInProgress == 5)
				 {
					 weightPer1000Items |= (unsigned int) data << 16;
					 countInProgress = 4;
				 }
				 else if (countInProgress == 4)
				 {
					 weightPer1000Items |= (unsigned int) data << 8;
					 countInProgress = 3;
				 }
				 else if (countInProgress == 3)
				 {
					 weightPer1000Items |= (unsigned int) data;
					 receivedCount = RXD_WP1000I;
					 countInProgress = 0;
				 }
				 else if (countInProgress == 2)
				 {
					 count_serial = (unsigned short) data << 8;
					 countInProgress = 1;
				 }
				 else if (countInProgress == 1)
				 {
					 count_serial |= (unsigned short) data;
					 receivedCount = RXD_COUNT;

					 weightPer1000Items = (int) ( (double) weightData / (double) data ) * 1000;
					 countInProgress = 0;
				 }

				 // Check reception of state variables
				 else if (inProgress == INPGRSS_STATUS0 || inProgress == INPGRSS_STATE)
				 {
					 switch (data)
					 {
					 case ST_WEIGH: cur_state.state = WEIGH; break;
					 case ST_COUNT_I: cur_state.state = COUNT; break;
					 case ST_COUNT_F: 
						 cur_state.state = COUNT_FINAL;
						 if (inProgress = INPGRSS_STATUS0)
							countInProgress = 6;
						 else countInProgress = 2;
						 break;
					 }

					 if (inProgress == INPGRSS_STATUS0)
						 inProgress = INPGRSS_STATUS1;
					 else if (inProgress == INPGRSS_STATE)
					 {
						 sendSerialByte(COMM_ACK_STATE);
						 inProgress = 0;
						 serialChange = true;
					 }
				 }
				 else if (inProgress == INPGRSS_STATUS1 || inProgress == INPGRSS_DISP)
				 {
					 if (data & DISP_OZ)
						 cur_state.units = OUNCES;
					 else
						 cur_state.units = GRAMS;

					 if (data & DISP_LCD)
					 {
						 if (data & DISP_TTS)
							 cur_state.outputs = LCD_TTS;
						 else
							 cur_state.outputs = LCD;
					 }
					 else if (data & DISP_TTS)
						 cur_state.outputs = TTS;
					 else cur_state.outputs = NONE;
				 
					 if (inProgress == INPGRSS_STATUS1)
						init_statesRxd = 1;
					 else if (inProgress == INPGRSS_DISP)
					 {
						 sendSerialByte(COMM_ACK_UNITS);
					 }

					 inProgress = 0;
					 serialChange = true;
				 }

				 else if (inProgress == INPGRSS_WGT0)
				 {
					 weightData = (unsigned int) data << 8;
					 inProgress = INPGRSS_WGT1;
				 }
				 else if (inProgress == INPGRSS_WGT1)
				 {
					 weightData |= (unsigned int) data;
					 weightReady = true;
					 inProgress = 0;
					 sendSerialByte(COMM_NUM_RXD);
				 }
				 else if (inProgress == INPGRSS_READINGS)
				 {
					 static char numRemaining = -1;

					 if (numRemaining == -1)
					 {
						 numReadings = data;
						 numRemaining = numReadings * 2;
					 }

					 // If num remaining is even, then this is the MSB
					 if (numRemaining % 2 == 0)
					 {
						weightReadings[numReadings - numRemaining/2] = data << 8;
					 }
					 // Else this is the LSB.
					 else 
					 {
						 // Note integer truncation.
						 weightReadings[numReadings - numRemaining/2 - 1] += data;
					 }

					 if (!(--numRemaining))
					 {
						 ack = COMM_ACK_WEIGHT_READINGS;
					 }
				 }
				 else if (inProgress == INPGRSS_SAMPLES)
				 {
					 numSamples = data;
					 ack = COMM_ACK_NUM_SAMPLES;
				 }

				 // Check for reception of codes from the PIC
				 else switch (data)
				 {
				 case COMM_BEGIN_NUM:
					 weightReady = 0;
					 weightData = 0;
					 inProgress = INPGRSS_WGT0;
					 break;
				 case COMM_NUM_RXD:
					 ack = (unsigned char) COMM_NUM_RXD;
					 break;
				 case COMM_ACK_REM:
					 inProgress = INPGRSS_STATUS0;
					 break;
				 case COMM_START_FAC:
					 this->Hide();
					 factoryForm->Open();
					 break;
				 case COMM_CHANGE_STATE:
					 inProgress = INPGRSS_STATE;
					 break;
				 case COMM_CHANGE_UNITS:
				 case COMM_CHANGE_DISP:
					 inProgress = INPGRSS_DISP;
					 break;
				 case COMM_ACK_STATE:
					 ack = (unsigned char) COMM_ACK_STATE;
					 break;
				 case COMM_ACK_UNITS:
					 ack = (unsigned char) COMM_ACK_UNITS;
					 break;
				 case COMM_ACK_DISP:
					 ack = (unsigned char) COMM_ACK_DISP;
					 break;
				 case COMM_ACK_TARE:
					 ack = (unsigned char) COMM_ACK_TARE;
					 break;
				 case COMM_ACK_STATS:
					 statsInProgress = 4;
					 break;
				 case COMM_ACK_WEIGHT_READINGS:
					 inProgress = INPGRSS_READINGS;
					 break;
				 case COMM_ACK_NUM_SAMPLES:
					 inProgress = INPGRSS_SAMPLES;
					 break;
				 }
			 }
		 }

		 int sendStartUsrRem()
		 {
			 unsigned char remoteCode = COMM_START_REM;
			 array<unsigned char>^ sendArray = gcnew array<unsigned char>(1);
			 sendArray[0] = remoteCode;
			 // Send code over serial for USER_REMOTE launch
			 port->Write(sendArray, 0, 1);

			 // Wait for state sent back
			 unsigned int timeoutCounter = SERIAL_TIMEOUT_GUI;
			 while (!init_statesRxd)
			 {
				 if (!(--timeoutCounter))
				 {
					 MessageBox::Show("Serial connection timed out. Unable to connect.");
					 return -1;
				 }
				 // do nothing, wait for timeout or completion
			 }
			 return 0;
		 }

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 // Send User Remote begin and wait for state
			 int check = sendStartUsrRem();
			 if (check == -1)
				 return;
			 
			 this->Hide();

			 // Move this to a serial handler?
			 if (cur_state.isFactory)
			 {
				 factoryForm->ShowDialog();
			 }
			 else
			 {
				 usrRemoteForm->Open();
				 //usrRemoteForm->ShowDialog();
			 }

		 }
private: System::Void radioWeigh_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (radioWeigh->Checked)
			 {
				 cur_state.state = WEIGH;
			 }
		 }
private: System::Void radioCount_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (radioCount->Checked)
			 {
				 cur_state.state = COUNT;
			 }
		 }
private: System::Void checkFactory_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (checkFactory->Checked)
			 {
				 cur_state.isFactory = true;
			 }
			 else
			 {
				 cur_state.isFactory = false;
			 }
		 }
private: System::Void evWarningCB_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (evWarningCB->Checked)
			 {
				 cur_warnings |= EXCESSIVE_VARIANCE;
			 }
			 else
			 {
				 cur_warnings &= ~EXCESSIVE_VARIANCE;
			 }
		 }
private: System::Void overWarningCB_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (overWarningCB->Checked)
			 {
				 cur_warnings |= OVERLOAD;
			 }
			 else
			 {
				 cur_warnings &= ~OVERLOAD;
			 }
		 }
private: System::Void sendSerialByte(unsigned char byte)
		 {
			 /*array<unsigned char>^ sendArray = gcnew array<unsigned char>(1);
			 sendArray[0] = byte;
			 port->Write(sendArray, 0, 1);*/
			 SerialComms ^comms = gcnew SerialComms(port);
			 comms->sendSerialByte(byte);
		 }
private: System::Void facButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Hide();
			 factoryForm->Open();
		 }
};
}

