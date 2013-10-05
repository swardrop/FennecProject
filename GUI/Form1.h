#pragma once

#include "FrmUsrRemote.h"
#include "FrmFactoryMode.h"
#include "states.h"

namespace FennecScalesGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			cur_state.state = WEIGH; // TODO: replace with proper init.
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
		FrmUsrRemote^ usrRemoteForm;
		FrmFactoryMode^ factoryForm;

	private: System::Windows::Forms::PictureBox^  pictureBox1;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  State;

	private: System::Windows::Forms::RadioButton^  radioCount;
	private: System::Windows::Forms::RadioButton^  radioWeigh;
	private: System::Windows::Forms::CheckBox^  checkFactory;



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
			this->radioCount = (gcnew System::Windows::Forms::RadioButton());
			this->radioWeigh = (gcnew System::Windows::Forms::RadioButton());
			this->checkFactory = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->State->SuspendLayout();
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
			// Form1
			// 
			this->AccessibleName = L"WeighMode";
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(453, 319);
			this->Controls->Add(this->State);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Name = L"Form1";
			this->Text = L"Fennec Scales";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->State->ResumeLayout(false);
			this->State->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Hide();

			 usrRemoteForm = gcnew FrmUsrRemote();

			 if (cur_state.isFactory)
			 {
				 factoryForm = gcnew FrmFactoryMode();
				 factoryForm->ShowDialog();
			 }
			 else
			 {
				 usrRemoteForm->ShowDialog();
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
};
}

