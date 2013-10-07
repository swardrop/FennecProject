#pragma once

namespace FennecScalesGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FrmHelp
	/// </summary>
	public ref class FrmHelp : public System::Windows::Forms::Form
	{
	public:
		FrmHelp(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FrmHelp()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected: 
	private: System::Windows::Forms::Button^  okButton;
	private: System::Windows::Forms::RichTextBox^  helpRTB;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;




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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->helpRTB = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel1->Controls->Add(this->okButton);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 215);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(284, 47);
			this->panel1->TabIndex = 0;
			// 
			// okButton
			// 
			this->okButton->Location = System::Drawing::Point(197, 12);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(75, 23);
			this->okButton->TabIndex = 0;
			this->okButton->Text = L"OK";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &FrmHelp::okButton_Click);
			// 
			// helpRTB
			// 
			this->helpRTB->BackColor = System::Drawing::SystemColors::Window;
			this->helpRTB->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->helpRTB->Location = System::Drawing::Point(0, 28);
			this->helpRTB->Name = L"helpRTB";
			this->helpRTB->ReadOnly = true;
			this->helpRTB->Size = System::Drawing::Size(284, 181);
			this->helpRTB->TabIndex = 0;
			this->helpRTB->Text = L"This is where the help should be placed.\nThat\'s what I reckon.\n\n\nFor example, on " 
				L"might try to actually inform the user.\n\n\n\nThat might be crazy.\n\n\nMaybe I\'m crazy" 
				L".\n\n\nWe\'ll see.";
			// 
			// richTextBox1
			// 
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(0, 0);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(284, 26);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = L"Fennec Scales Remote Controller";
			// 
			// FrmHelp
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->helpRTB);
			this->Controls->Add(this->panel1);
			this->Name = L"FrmHelp";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Fennec Scales Help";
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void okButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
};
}
