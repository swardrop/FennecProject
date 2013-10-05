#pragma once

#include "states.h"

namespace FennecScalesGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FrmUsrRemote
	/// </summary>
	public ref class FrmUsrRemote : public System::Windows::Forms::Form
	{
	public:
		FrmUsrRemote()
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			setButtons(cur_state);
			showPanel(cur_state.state);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FrmUsrRemote()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  weighPanel;
	private: System::Windows::Forms::Panel^  sidePanel;
	protected: 


	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::CheckBox^  cbTTS;

	private: System::Windows::Forms::CheckBox^  cbLCD;

	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::RadioButton^  rbOz;

	private: System::Windows::Forms::RadioButton^  rbGrams;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  rbCount;

	private: System::Windows::Forms::RadioButton^  rbWeigh;


	private: System::Windows::Forms::Panel^  countPanel;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Panel^  bottomPanel;
	private: System::Windows::Forms::Button^  helpButton;
	private: System::Windows::Forms::Button^  closeButton;
	private: System::Windows::Forms::Button^  tareButton;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  unitsLabel;










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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FrmUsrRemote::typeid));
			this->weighPanel = (gcnew System::Windows::Forms::Panel());
			this->sidePanel = (gcnew System::Windows::Forms::Panel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->cbTTS = (gcnew System::Windows::Forms::CheckBox());
			this->cbLCD = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->rbOz = (gcnew System::Windows::Forms::RadioButton());
			this->rbGrams = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->rbCount = (gcnew System::Windows::Forms::RadioButton());
			this->rbWeigh = (gcnew System::Windows::Forms::RadioButton());
			this->countPanel = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->bottomPanel = (gcnew System::Windows::Forms::Panel());
			this->tareButton = (gcnew System::Windows::Forms::Button());
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->helpButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->unitsLabel = (gcnew System::Windows::Forms::Label());
			this->weighPanel->SuspendLayout();
			this->sidePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->countPanel->SuspendLayout();
			this->bottomPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// weighPanel
			// 
			this->weighPanel->Controls->Add(this->unitsLabel);
			this->weighPanel->Controls->Add(this->textBox1);
			this->weighPanel->Controls->Add(this->label3);
			this->weighPanel->Controls->Add(this->tareButton);
			this->weighPanel->Location = System::Drawing::Point(114, 0);
			this->weighPanel->Name = L"weighPanel";
			this->weighPanel->Size = System::Drawing::Size(339, 273);
			this->weighPanel->TabIndex = 2;
			this->weighPanel->Visible = false;
			// 
			// sidePanel
			// 
			this->sidePanel->BackColor = System::Drawing::SystemColors::ControlDark;
			this->sidePanel->Controls->Add(this->pictureBox1);
			this->sidePanel->Controls->Add(this->groupBox3);
			this->sidePanel->Controls->Add(this->groupBox2);
			this->sidePanel->Controls->Add(this->groupBox1);
			this->sidePanel->Dock = System::Windows::Forms::DockStyle::Left;
			this->sidePanel->Location = System::Drawing::Point(0, 0);
			this->sidePanel->Name = L"sidePanel";
			this->sidePanel->Size = System::Drawing::Size(113, 319);
			this->sidePanel->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->ImageLocation = L"";
			this->pictureBox1->Location = System::Drawing::Point(3, 232);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(105, 79);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->cbTTS);
			this->groupBox3->Controls->Add(this->cbLCD);
			this->groupBox3->Location = System::Drawing::Point(11, 158);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(90, 68);
			this->groupBox3->TabIndex = 3;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Outputs";
			// 
			// cbTTS
			// 
			this->cbTTS->AutoSize = true;
			this->cbTTS->Location = System::Drawing::Point(19, 45);
			this->cbTTS->Name = L"cbTTS";
			this->cbTTS->Size = System::Drawing::Size(47, 17);
			this->cbTTS->TabIndex = 3;
			this->cbTTS->Text = L"TTS";
			this->cbTTS->UseVisualStyleBackColor = true;
			this->cbTTS->CheckedChanged += gcnew System::EventHandler(this, &FrmUsrRemote::cbTTS_CheckedChanged);
			// 
			// cbLCD
			// 
			this->cbLCD->AutoSize = true;
			this->cbLCD->Location = System::Drawing::Point(19, 19);
			this->cbLCD->Name = L"cbLCD";
			this->cbLCD->Size = System::Drawing::Size(47, 17);
			this->cbLCD->TabIndex = 2;
			this->cbLCD->Text = L"LCD";
			this->cbLCD->UseVisualStyleBackColor = true;
			this->cbLCD->CheckedChanged += gcnew System::EventHandler(this, &FrmUsrRemote::cbLCD_CheckedChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->rbOz);
			this->groupBox2->Controls->Add(this->rbGrams);
			this->groupBox2->Location = System::Drawing::Point(11, 84);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(90, 68);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Units";
			// 
			// rbOz
			// 
			this->rbOz->AutoSize = true;
			this->rbOz->Location = System::Drawing::Point(19, 44);
			this->rbOz->Name = L"rbOz";
			this->rbOz->Size = System::Drawing::Size(60, 17);
			this->rbOz->TabIndex = 1;
			this->rbOz->Text = L"ounces";
			this->rbOz->UseVisualStyleBackColor = true;
			// 
			// rbGrams
			// 
			this->rbGrams->AutoSize = true;
			this->rbGrams->Location = System::Drawing::Point(19, 20);
			this->rbGrams->Name = L"rbGrams";
			this->rbGrams->Size = System::Drawing::Size(53, 17);
			this->rbGrams->TabIndex = 0;
			this->rbGrams->Text = L"grams";
			this->rbGrams->UseVisualStyleBackColor = true;
			this->rbGrams->CheckedChanged += gcnew System::EventHandler(this, &FrmUsrRemote::rbGrams_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->rbCount);
			this->groupBox1->Controls->Add(this->rbWeigh);
			this->groupBox1->Location = System::Drawing::Point(10, 10);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(91, 68);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Mode";
			// 
			// rbCount
			// 
			this->rbCount->AutoSize = true;
			this->rbCount->Location = System::Drawing::Point(20, 42);
			this->rbCount->Name = L"rbCount";
			this->rbCount->Size = System::Drawing::Size(53, 17);
			this->rbCount->TabIndex = 1;
			this->rbCount->TabStop = true;
			this->rbCount->Text = L"Count";
			this->rbCount->UseVisualStyleBackColor = true;
			// 
			// rbWeigh
			// 
			this->rbWeigh->AccessibleName = L"rbWeigh";
			this->rbWeigh->AutoSize = true;
			this->rbWeigh->Location = System::Drawing::Point(20, 19);
			this->rbWeigh->Name = L"rbWeigh";
			this->rbWeigh->Size = System::Drawing::Size(56, 17);
			this->rbWeigh->TabIndex = 0;
			this->rbWeigh->TabStop = true;
			this->rbWeigh->Text = L"Weigh";
			this->rbWeigh->UseVisualStyleBackColor = true;
			this->rbWeigh->CheckedChanged += gcnew System::EventHandler(this, &FrmUsrRemote::rbWeigh_CheckedChanged);
			// 
			// countPanel
			// 
			this->countPanel->Controls->Add(this->label2);
			this->countPanel->Location = System::Drawing::Point(453, 0);
			this->countPanel->Name = L"countPanel";
			this->countPanel->Size = System::Drawing::Size(339, 273);
			this->countPanel->TabIndex = 3;
			this->countPanel->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(145, 29);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(65, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Count Mode";
			// 
			// bottomPanel
			// 
			this->bottomPanel->BackColor = System::Drawing::SystemColors::ControlLight;
			this->bottomPanel->Controls->Add(this->helpButton);
			this->bottomPanel->Controls->Add(this->closeButton);
			this->bottomPanel->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->bottomPanel->Location = System::Drawing::Point(113, 279);
			this->bottomPanel->Name = L"bottomPanel";
			this->bottomPanel->Size = System::Drawing::Size(679, 40);
			this->bottomPanel->TabIndex = 4;
			// 
			// tareButton
			// 
			this->tareButton->Location = System::Drawing::Point(131, 147);
			this->tareButton->Name = L"tareButton";
			this->tareButton->Size = System::Drawing::Size(75, 23);
			this->tareButton->TabIndex = 0;
			this->tareButton->Text = L"Tare";
			this->tareButton->UseVisualStyleBackColor = true;
			// 
			// closeButton
			// 
			this->closeButton->Location = System::Drawing::Point(256, 9);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(75, 23);
			this->closeButton->TabIndex = 1;
			this->closeButton->Text = L"Close";
			this->closeButton->UseVisualStyleBackColor = true;
			// 
			// helpButton
			// 
			this->helpButton->Location = System::Drawing::Point(6, 9);
			this->helpButton->Name = L"helpButton";
			this->helpButton->Size = System::Drawing::Size(75, 23);
			this->helpButton->TabIndex = 2;
			this->helpButton->Text = L"Help";
			this->helpButton->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(44, 101);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(70, 20);
			this->label3->TabIndex = 1;
			this->label3->Text = L"Weight:";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(120, 98);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(100, 26);
			this->textBox1->TabIndex = 2;
			// 
			// unitsLabel
			// 
			this->unitsLabel->AutoSize = true;
			this->unitsLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->unitsLabel->Location = System::Drawing::Point(236, 101);
			this->unitsLabel->Name = L"unitsLabel";
			this->unitsLabel->Size = System::Drawing::Size(53, 20);
			this->unitsLabel->TabIndex = 3;
			this->unitsLabel->Text = L"grams";
			// 
			// FrmUsrRemote
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(792, 319);
			this->Controls->Add(this->bottomPanel);
			this->Controls->Add(this->countPanel);
			this->Controls->Add(this->weighPanel);
			this->Controls->Add(this->sidePanel);
			this->Name = L"FrmUsrRemote";
			this->Text = L"FrmUsrRemote";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FrmUsrRemote::FrmUsrRemote_FormClosed);
			this->weighPanel->ResumeLayout(false);
			this->weighPanel->PerformLayout();
			this->sidePanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->countPanel->ResumeLayout(false);
			this->countPanel->PerformLayout();
			this->bottomPanel->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void FrmUsrRemote_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 Application::Exit();
			 }
private: System::Void rbWeigh_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (rbWeigh->Checked)
			 {
				 if (cur_state.state != WEIGH)
				 {
					 cur_state.state = WEIGH;
					 // Send serial code for weigh
					 showPanel(WEIGH);
				 }
			 }
			 else // if rbCount->Checked
			 {
				 if (cur_state.state != COUNT)
				 {
					 cur_state.state = COUNT;
					 resetCountPanel();
					 showPanel(COUNT);
				 }
			 }
		 }

	private: System::Void showPanel(systemStates state)
		{
			if (state == WEIGH)
			{
				this->countPanel->Hide();
				this->weighPanel->Show();
				this->weighPanel->BringToFront();
			}
			else if (state == COUNT)
			{
				this->weighPanel->Hide();
				this->countPanel->Show();
				this->countPanel->BringToFront();
			}
		}

	private: System::Void resetCountPanel()
			 {
				 //TODO: stuff that puts the counts panel back in order.
			 }

	private: System::Void setButtons(State state)
			{
				if (cur_state.state == WEIGH)
				{
					rbWeigh->Checked = true;
					rbCount->Checked = false;
				}
				else
				{
					rbCount->Checked = true;
					rbWeigh->Checked = false;
				}

				if (cur_state.units == GRAMS)
				{
					rbGrams->Checked = true;
					rbOz->Checked = false;
				}
				else
				{
					rbOz->Checked = true;
					rbGrams->Checked = false;
				}

				if (cur_state.outputs == LCD || cur_state.outputs == LCD_TTS)
				{
					cbLCD->Checked = true;
				}
				else 
				{
					cbLCD->Checked = false;
				}

				if (cur_state.outputs == TTS || cur_state.outputs == LCD_TTS)
				{
					cbTTS->Checked = true;
				}
				else
				{
					cbTTS->Checked = false;
				}
			}
private: System::Void rbGrams_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (rbGrams->Checked)
			 {
				 cur_state.units = GRAMS;
				 unitsLabel->Text = "grams";
			 }
			 else
			 {
				 cur_state.units = OUNCES;
				 unitsLabel->Text = "ounces";
			 }
			 // TODO: Add handler for changing numerical value based on units
		 }

private: System::Void cbLCD_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (cbLCD->Checked)
			 {
				 // TODO: Send LCD enable code
				 if (cur_state.outputs == NONE)
				 {
					cur_state.outputs = LCD;
				 }
				 else
				 {
					 cur_state.outputs = LCD_TTS;
				 }
			 }
			 else
			 {
				 //TODO: Send LCD disable code
				 if (cur_state.outputs == LCD_TTS)
				 {
					 cur_state.outputs = TTS;
				 }
				 else
				 {
					 cur_state.outputs = NONE;
				 }
			 }
		 }
private: System::Void cbTTS_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (cbTTS->Checked)
			 {
				 if (cur_state.outputs == NONE)
				 {
					 cur_state.outputs = TTS;
				 }
				 else
				 {
					 cur_state.outputs = LCD_TTS;
				 }
			 }
			 else
			 {
				 if (cur_state.outputs == LCD_TTS)
				 {
					 cur_state.outputs = LCD;
				 }
				 else
				 {
					 cur_state.outputs = NONE;
				 }
			 }
		 }
};
}
