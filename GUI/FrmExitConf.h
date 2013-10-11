#pragma once

#include "commscodes.h"

extern bool closing;
extern bool closeAll;

namespace FennecScalesGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;

	/// <summary>
	/// Summary for FrmExitConf
	/// </summary>
	public ref class FrmExitConf : public System::Windows::Forms::Form
	{
	public:
		FrmExitConf(SerialPort^ sp)
		{
			InitializeComponent();
			port = sp;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FrmExitConf()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Button^  quitButton;

	private: System::Windows::Forms::Button^  cbGoBack;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  label2;
	protected: 
		SerialPort^ port;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->quitButton = (gcnew System::Windows::Forms::Button());
			this->cbGoBack = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(213, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Are you sure you want to quit\?";
			// 
			// quitButton
			// 
			this->quitButton->Location = System::Drawing::Point(150, 10);
			this->quitButton->Name = L"quitButton";
			this->quitButton->Size = System::Drawing::Size(75, 23);
			this->quitButton->TabIndex = 0;
			this->quitButton->Text = L"Quit";
			this->quitButton->UseVisualStyleBackColor = true;
			this->quitButton->Click += gcnew System::EventHandler(this, &FrmExitConf::button1_Click);
			// 
			// cbGoBack
			// 
			this->cbGoBack->Location = System::Drawing::Point(12, 10);
			this->cbGoBack->Name = L"cbGoBack";
			this->cbGoBack->Size = System::Drawing::Size(75, 23);
			this->cbGoBack->TabIndex = 2;
			this->cbGoBack->Text = L"Go Back";
			this->cbGoBack->UseVisualStyleBackColor = true;
			this->cbGoBack->Click += gcnew System::EventHandler(this, &FrmExitConf::cbGoBack_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel1->Controls->Add(this->cbGoBack);
			this->panel1->Controls->Add(this->quitButton);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 83);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(237, 45);
			this->panel1->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 47);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(187, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"The scales will revert to LOCAL mode.";
			// 
			// FrmExitConf
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(237, 128);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label1);
			this->Name = L"FrmExitConf";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Fennec Scales";
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 // Send signal over serial to revert to LOCAL
				 array<unsigned char>^ sendArray = gcnew array<unsigned char>(1);
				 sendArray[0] = COMM_STOP_REM;
				 port->Write(sendArray, 0, 1);

				 // Close application
				 closeAll = true;
				 Application::Exit();
			 }
private: System::Void cbGoBack_Click(System::Object^  sender, System::EventArgs^  e) {
			 closing = false;
			 this->Close();
		 }
};
}
