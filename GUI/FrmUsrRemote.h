#pragma once

#include "states.h"
#include "FrmExitConf.h"
#include "FrmHelp.h"
#include "commscodes.h"

namespace FennecScalesGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;

	/// <summary>
	/// Summary for FrmUsrRemote
	/// </summary>
	public ref class FrmUsrRemote : public System::Windows::Forms::Form
	{
	public:
		FrmUsrRemote(SerialPort^ sp)
		{
			InitializeComponent();

			setButtons(cur_state);
			showPanel(cur_state.state);
			showWarnings(); // Need to find some way to show as soon as a warning appears (event-driven)
			setUnitsLabel();
			port = sp;
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

	private: System::Windows::Forms::Panel^  bottomPanel;
	private: System::Windows::Forms::Button^  helpButton;
	private: System::Windows::Forms::Button^  closeButton;
	private: System::Windows::Forms::Button^  tareButton;
	private: System::Windows::Forms::TextBox^  weightBox;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  unitsLabel;
	private: System::Windows::Forms::GroupBox^  weightGroupBox;






	private: System::Windows::Forms::Panel^  initialCountPanel;
	private: System::Windows::Forms::Button^  numEnterButton;
	private: System::Windows::Forms::NumericUpDown^  knownCountBox;


	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Panel^  finalCountPanel;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  countBox;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  resetCountButton;
	private: System::Windows::Forms::Panel^  warningPanel;

	private: System::Windows::Forms::Label^  overloadLabel;

	private: System::Windows::Forms::Label^  excessiveVarianceLabel;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Label^  label1;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FrmUsrRemote::typeid));
			this->weighPanel = (gcnew System::Windows::Forms::Panel());
			this->unitsLabel = (gcnew System::Windows::Forms::Label());
			this->weightBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tareButton = (gcnew System::Windows::Forms::Button());
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
			this->finalCountPanel = (gcnew System::Windows::Forms::Panel());
			this->resetCountButton = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->countBox = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->initialCountPanel = (gcnew System::Windows::Forms::Panel());
			this->numEnterButton = (gcnew System::Windows::Forms::Button());
			this->knownCountBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->weightGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->bottomPanel = (gcnew System::Windows::Forms::Panel());
			this->helpButton = (gcnew System::Windows::Forms::Button());
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->warningPanel = (gcnew System::Windows::Forms::Panel());
			this->overloadLabel = (gcnew System::Windows::Forms::Label());
			this->excessiveVarianceLabel = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->weighPanel->SuspendLayout();
			this->sidePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->countPanel->SuspendLayout();
			this->finalCountPanel->SuspendLayout();
			this->initialCountPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->knownCountBox))->BeginInit();
			this->bottomPanel->SuspendLayout();
			this->warningPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// weighPanel
			// 
			this->weighPanel->Controls->Add(this->unitsLabel);
			this->weighPanel->Controls->Add(this->weightBox);
			this->weighPanel->Controls->Add(this->label3);
			this->weighPanel->Controls->Add(this->tareButton);
			this->weighPanel->Location = System::Drawing::Point(160, 98);
			this->weighPanel->Name = L"weighPanel";
			this->weighPanel->Size = System::Drawing::Size(271, 65);
			this->weighPanel->TabIndex = 2;
			this->weighPanel->Visible = false;
			// 
			// unitsLabel
			// 
			this->unitsLabel->AutoSize = true;
			this->unitsLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->unitsLabel->Location = System::Drawing::Point(197, 9);
			this->unitsLabel->Name = L"unitsLabel";
			this->unitsLabel->Size = System::Drawing::Size(53, 20);
			this->unitsLabel->TabIndex = 3;
			this->unitsLabel->Text = L"grams";
			// 
			// weightBox
			// 
			this->weightBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->weightBox->Location = System::Drawing::Point(81, 6);
			this->weightBox->Name = L"weightBox";
			this->weightBox->ReadOnly = true;
			this->weightBox->Size = System::Drawing::Size(100, 26);
			this->weightBox->TabIndex = 2;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(5, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(70, 20);
			this->label3->TabIndex = 1;
			this->label3->Text = L"Weight:";
			// 
			// tareButton
			// 
			this->tareButton->Location = System::Drawing::Point(93, 38);
			this->tareButton->Name = L"tareButton";
			this->tareButton->Size = System::Drawing::Size(75, 23);
			this->tareButton->TabIndex = 0;
			this->tareButton->Text = L"Tare";
			this->tareButton->UseVisualStyleBackColor = true;
			this->tareButton->Click += gcnew System::EventHandler(this, &FrmUsrRemote::tareButton_Click);
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
			this->countPanel->Controls->Add(this->finalCountPanel);
			this->countPanel->Controls->Add(this->initialCountPanel);
			this->countPanel->Controls->Add(this->weightGroupBox);
			this->countPanel->Location = System::Drawing::Point(114, 0);
			this->countPanel->Name = L"countPanel";
			this->countPanel->Size = System::Drawing::Size(339, 273);
			this->countPanel->TabIndex = 3;
			this->countPanel->Visible = false;
			// 
			// finalCountPanel
			// 
			this->finalCountPanel->Controls->Add(this->resetCountButton);
			this->finalCountPanel->Controls->Add(this->label6);
			this->finalCountPanel->Controls->Add(this->countBox);
			this->finalCountPanel->Controls->Add(this->label5);
			this->finalCountPanel->Location = System::Drawing::Point(6, 68);
			this->finalCountPanel->Name = L"finalCountPanel";
			this->finalCountPanel->Size = System::Drawing::Size(329, 89);
			this->finalCountPanel->TabIndex = 10;
			// 
			// resetCountButton
			// 
			this->resetCountButton->Location = System::Drawing::Point(131, 61);
			this->resetCountButton->Name = L"resetCountButton";
			this->resetCountButton->Size = System::Drawing::Size(75, 23);
			this->resetCountButton->TabIndex = 9;
			this->resetCountButton->Text = L"Reset";
			this->resetCountButton->UseVisualStyleBackColor = true;
			this->resetCountButton->Click += gcnew System::EventHandler(this, &FrmUsrRemote::resetCountButton_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(238, 33);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(47, 20);
			this->label6->TabIndex = 8;
			this->label6->Text = L"items";
			// 
			// countBox
			// 
			this->countBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->countBox->Location = System::Drawing::Point(120, 30);
			this->countBox->Name = L"countBox";
			this->countBox->ReadOnly = true;
			this->countBox->Size = System::Drawing::Size(100, 26);
			this->countBox->TabIndex = 7;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(37, 33);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(77, 20);
			this->label5->TabIndex = 0;
			this->label5->Text = L"There are";
			// 
			// initialCountPanel
			// 
			this->initialCountPanel->Controls->Add(this->numEnterButton);
			this->initialCountPanel->Controls->Add(this->knownCountBox);
			this->initialCountPanel->Controls->Add(this->label4);
			this->initialCountPanel->Controls->Add(this->textBox3);
			this->initialCountPanel->Location = System::Drawing::Point(6, 3);
			this->initialCountPanel->Name = L"initialCountPanel";
			this->initialCountPanel->Size = System::Drawing::Size(329, 120);
			this->initialCountPanel->TabIndex = 9;
			// 
			// numEnterButton
			// 
			this->numEnterButton->Location = System::Drawing::Point(236, 78);
			this->numEnterButton->Name = L"numEnterButton";
			this->numEnterButton->Size = System::Drawing::Size(75, 23);
			this->numEnterButton->TabIndex = 3;
			this->numEnterButton->Text = L"OK";
			this->numEnterButton->UseVisualStyleBackColor = true;
			this->numEnterButton->Click += gcnew System::EventHandler(this, &FrmUsrRemote::numEnterButton_Click);
			// 
			// knownCountBox
			// 
			this->knownCountBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->knownCountBox->Location = System::Drawing::Point(161, 79);
			this->knownCountBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->knownCountBox->Name = L"knownCountBox";
			this->knownCountBox->Size = System::Drawing::Size(59, 22);
			this->knownCountBox->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(8, 81);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(147, 16);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Known number of items:";
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::SystemColors::Control;
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox3->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(11, 23);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(306, 36);
			this->textBox3->TabIndex = 0;
			this->textBox3->Text = L"Please place a known number of items on the scale, then input that number:";
			// 
			// weightGroupBox
			// 
			this->weightGroupBox->Location = System::Drawing::Point(3, 184);
			this->weightGroupBox->Name = L"weightGroupBox";
			this->weightGroupBox->Size = System::Drawing::Size(333, 88);
			this->weightGroupBox->TabIndex = 8;
			this->weightGroupBox->TabStop = false;
			this->weightGroupBox->Text = L"Weight";
			// 
			// bottomPanel
			// 
			this->bottomPanel->BackColor = System::Drawing::SystemColors::ControlLight;
			this->bottomPanel->Controls->Add(this->helpButton);
			this->bottomPanel->Controls->Add(this->closeButton);
			this->bottomPanel->Location = System::Drawing::Point(113, 279);
			this->bottomPanel->Name = L"bottomPanel";
			this->bottomPanel->Size = System::Drawing::Size(341, 40);
			this->bottomPanel->TabIndex = 4;
			// 
			// helpButton
			// 
			this->helpButton->Location = System::Drawing::Point(6, 9);
			this->helpButton->Name = L"helpButton";
			this->helpButton->Size = System::Drawing::Size(75, 23);
			this->helpButton->TabIndex = 2;
			this->helpButton->Text = L"Help";
			this->helpButton->UseVisualStyleBackColor = true;
			this->helpButton->Click += gcnew System::EventHandler(this, &FrmUsrRemote::helpButton_Click);
			// 
			// closeButton
			// 
			this->closeButton->Location = System::Drawing::Point(256, 9);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(75, 23);
			this->closeButton->TabIndex = 1;
			this->closeButton->Text = L"Close";
			this->closeButton->UseVisualStyleBackColor = true;
			this->closeButton->Click += gcnew System::EventHandler(this, &FrmUsrRemote::closeButton_Click);
			// 
			// warningPanel
			// 
			this->warningPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->warningPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->warningPanel->Controls->Add(this->overloadLabel);
			this->warningPanel->Controls->Add(this->excessiveVarianceLabel);
			this->warningPanel->Controls->Add(this->pictureBox2);
			this->warningPanel->Controls->Add(this->label1);
			this->warningPanel->Dock = System::Windows::Forms::DockStyle::Right;
			this->warningPanel->Location = System::Drawing::Point(455, 0);
			this->warningPanel->Name = L"warningPanel";
			this->warningPanel->Size = System::Drawing::Size(112, 319);
			this->warningPanel->TabIndex = 0;
			this->warningPanel->Visible = false;
			// 
			// overloadLabel
			// 
			this->overloadLabel->AutoSize = true;
			this->overloadLabel->Location = System::Drawing::Point(6, 192);
			this->overloadLabel->Name = L"overloadLabel";
			this->overloadLabel->Size = System::Drawing::Size(92, 13);
			this->overloadLabel->TabIndex = 3;
			this->overloadLabel->Text = L"Beam Overloaded";
			this->overloadLabel->Visible = false;
			// 
			// excessiveVarianceLabel
			// 
			this->excessiveVarianceLabel->AutoSize = true;
			this->excessiveVarianceLabel->Location = System::Drawing::Point(6, 167);
			this->excessiveVarianceLabel->Name = L"excessiveVarianceLabel";
			this->excessiveVarianceLabel->Size = System::Drawing::Size(100, 13);
			this->excessiveVarianceLabel->TabIndex = 2;
			this->excessiveVarianceLabel->Text = L"Excessive Variance";
			this->excessiveVarianceLabel->Visible = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(6, 82);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(100, 74);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(21, 59);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(74, 18);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Warning!";
			// 
			// FrmUsrRemote
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(567, 319);
			this->Controls->Add(this->warningPanel);
			this->Controls->Add(this->weighPanel);
			this->Controls->Add(this->bottomPanel);
			this->Controls->Add(this->countPanel);
			this->Controls->Add(this->sidePanel);
			this->Name = L"FrmUsrRemote";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Fennec Scales Remote Controller";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FrmUsrRemote::FrmUsrRemote_FormClosing);
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
			this->finalCountPanel->ResumeLayout(false);
			this->finalCountPanel->PerformLayout();
			this->initialCountPanel->ResumeLayout(false);
			this->initialCountPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->knownCountBox))->EndInit();
			this->bottomPanel->ResumeLayout(false);
			this->warningPanel->ResumeLayout(false);
			this->warningPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void rbWeigh_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (rbWeigh->Checked)
			 {
				 if (cur_state.state != WEIGH)
				 {
					 cur_state.state = WEIGH;
					 // Send serial code for weigh
					 resetWeighPanel();
					 showPanel(WEIGH);
				 }
			 }
			 else // if rbCount->Checked
			 {
				 if (cur_state.state != COUNT)
				 {
					 cur_state.state = COUNT;
					 // Send serial code for count
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
			else if (state == COUNT || COUNT_FINAL)
			{
				//this->weighPanel->Hide();
				this->weighPanel->Location = System::Drawing::Point(160, 203);
				resetCountPanel();
				this->countPanel->Show();
				//this->countPanel->BringToFront();
				//this->weighPanel->BringToFront();
			}
		}

	private: System::Void resetCountPanel()
			 {
				 if (cur_state.state == COUNT)
				 {
					 this->initialCountPanel->Show();
					 this->finalCountPanel->Hide();
				 }
				 else
				 {
					 this->initialCountPanel->Hide();
					 this->finalCountPanel->Show();
				 }
			 }

			 System::Void resetWeighPanel()
			 {
				 this->weighPanel->Location = System::Drawing::Point(160, 98);
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

		System::Void showWarnings()
		{
			if (cur_warnings)
			{
				this->ClientSize = System::Drawing::Size(567, 319);
				this->warningPanel->Show();
			}
			else
			{
				this->ClientSize = System::Drawing::Size(454, 319);
				this->warningPanel->Hide();
			}

			if (cur_warnings & EXCESSIVE_VARIANCE)
			{
				this->excessiveVarianceLabel->Show();
			}
			else
			{
				this->excessiveVarianceLabel->Hide();
			}

			if (cur_warnings & OVERLOAD)
			{
				this->overloadLabel->Show();
			}
			else
			{
				this->overloadLabel->Hide();
			}
		}

		System::Void setUnitsLabel()
		{
			if (cur_state.units == GRAMS)
			{
				unitsLabel->Text = "grams";
			}
			else
			{
				unitsLabel->Text = "ounces";
			}
		}

private: System::Void rbGrams_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (rbGrams->Checked)
			 {
				 cur_state.units = GRAMS;
			 }
			 else
			 {
				 cur_state.units = OUNCES;
			 }
			 setUnitsLabel();
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
private: System::Void tareButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 // Send TARE code over serial
			 // Wait for ack.
		 }
private: System::Void closeButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void FrmUsrRemote_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 
			 if (!closing)
			 {
				closing = true;
				FrmExitConf^ exitForm = gcnew FrmExitConf();
				exitForm->Show();
			 }

			 if (!closeAll)
			 {
				 e->Cancel = true;
			 }
		 }
private: System::Void helpButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 FrmHelp^ helpForm = gcnew FrmHelp();
			 helpForm->Show();
		 }
private: System::Void numEnterButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 unsigned short knownCount = (unsigned short) knownCountBox->Value; //safe cast

			 if (knownCount < 1)
			 {
				 // Count must be positive.
				 return;
			 }

			 // Send knownCount over serial.
			 // Wait for ack

			 this->initialCountPanel->Hide();
			 this->finalCountPanel->Show();

			 cur_state.state = COUNT_FINAL;

		 }
private: System::Void resetCountButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 cur_state.state = COUNT;
			 // Send reset to count mode over serial
			 // Wait for ack.
			 resetCountPanel();
		 }
};
}
