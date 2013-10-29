#pragma once

#include "states.h"
//#include "commscodes.h" // TODO: change literal 32 to ADC_BUFSIZE
#include "FrmUsrRemote.h"
#include "FrmFactoryClosing.h"

namespace FennecScalesGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;

	/// <summary>
	/// Summary for FrmFactoryMode
	/// </summary>
	public ref class FrmFactoryMode : public System::Windows::Forms::Form
	{
	public:
		FrmFactoryMode(FrmUsrRemote ^remFrm, SerialComms^ sc)
		{
			InitializeComponent();
			remoteFrm = remFrm;
			comms = sc;
			remoteFrm->Hide();

			rawWeights = gcnew array<unsigned short>(5);

			buttons = gcnew array<Button ^>(5);
			buttons[0] = zeroSetButton;
			buttons[1] = two50SetButton;
			buttons[2] = five00SetButton;
			buttons[3] = seven50SetButton;
			buttons[4] = oneKiloSetButton;
			
			buttonsOn = gcnew array<bool>(5);
			for (int i = 0; i < 5; ++i)
			{
				buttonsOn[i] = false;
			}

			textBox = gcnew array<TextBox ^>(5);
			textBox[0] = zeroBox;
			textBox[1] = two50Box;
			textBox[2] = five00Box;
			textBox[3] = seven50Box;
			textBox[4] = oneKiloBox;
		}

		void Open()
		{
			resetFactoryForm();
			remoteFrm->Show();
			this->Show();
			comms->sendSerialByte(COMM_ACK_FAC);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FrmFactoryMode()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
		FrmUsrRemote ^remoteFrm;
		SerialComms ^comms;
		array<unsigned short> ^rawWeights;
		array<Button ^> ^buttons;
		array<TextBox ^> ^textBox;
		array<bool> ^buttonsOn;

	private: System::Windows::Forms::Panel^  sidePanel;
	protected: 




	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::RadioButton^  rbSamples;

	private: System::Windows::Forms::RadioButton^  rbCalibrate;





	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  rbHideUser;

	private: System::Windows::Forms::RadioButton^  rbShowUser;

	private: System::Windows::Forms::RadioButton^  rbStats;
	private: System::Windows::Forms::RadioButton^  rbWeightReadings;
	private: System::Windows::Forms::Label^  ViewLabel;
	private: System::Windows::Forms::Label^  configLabel;
	private: System::Windows::Forms::Panel^  bottomPanel;
	private: System::Windows::Forms::Button^  closeButton;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Panel^  defaultPanel;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Panel^  calibratePanel;
	private: System::Windows::Forms::Panel^  samplesPanel;
	private: System::Windows::Forms::Panel^  statsPanel;
	private: System::Windows::Forms::Panel^  readingsPanel;
	private: System::Windows::Forms::NumericUpDown^  numSamplesBox;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  updateStatsButton;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  updateReadingsButton;
	private: System::Windows::Forms::RichTextBox^  readingsBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  sendNumSamplesButton;
	private: System::Windows::Forms::TextBox^  varianceBox;
	private: System::Windows::Forms::TextBox^  meanBox;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  confirmLabel;
	private: System::Windows::Forms::ProgressBar^  progressBar;
	private: System::Windows::Forms::Button^  oneKiloSetButton;
	private: System::Windows::Forms::TextBox^  oneKiloBox;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Button^  seven50SetButton;
	private: System::Windows::Forms::TextBox^  seven50Box;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Button^  five00SetButton;
	private: System::Windows::Forms::TextBox^  five00Box;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Button^  two50SetButton;
	private: System::Windows::Forms::TextBox^  two50Box;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Button^  zeroSetButton;
	private: System::Windows::Forms::TextBox^  zeroBox;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Button^  sendCalibButton;
private: System::Windows::Forms::Button^  resetCalibButton;
private: System::Windows::Forms::Label^  calibConfLabel;





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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FrmFactoryMode::typeid));
			this->sidePanel = (gcnew System::Windows::Forms::Panel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->rbWeightReadings = (gcnew System::Windows::Forms::RadioButton());
			this->ViewLabel = (gcnew System::Windows::Forms::Label());
			this->configLabel = (gcnew System::Windows::Forms::Label());
			this->rbStats = (gcnew System::Windows::Forms::RadioButton());
			this->rbSamples = (gcnew System::Windows::Forms::RadioButton());
			this->rbCalibrate = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->rbHideUser = (gcnew System::Windows::Forms::RadioButton());
			this->rbShowUser = (gcnew System::Windows::Forms::RadioButton());
			this->bottomPanel = (gcnew System::Windows::Forms::Panel());
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->defaultPanel = (gcnew System::Windows::Forms::Panel());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->calibratePanel = (gcnew System::Windows::Forms::Panel());
			this->resetCalibButton = (gcnew System::Windows::Forms::Button());
			this->calibConfLabel = (gcnew System::Windows::Forms::Label());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->oneKiloSetButton = (gcnew System::Windows::Forms::Button());
			this->oneKiloBox = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->seven50SetButton = (gcnew System::Windows::Forms::Button());
			this->seven50Box = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->five00SetButton = (gcnew System::Windows::Forms::Button());
			this->five00Box = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->two50SetButton = (gcnew System::Windows::Forms::Button());
			this->two50Box = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->zeroSetButton = (gcnew System::Windows::Forms::Button());
			this->zeroBox = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->sendCalibButton = (gcnew System::Windows::Forms::Button());
			this->samplesPanel = (gcnew System::Windows::Forms::Panel());
			this->confirmLabel = (gcnew System::Windows::Forms::Label());
			this->sendNumSamplesButton = (gcnew System::Windows::Forms::Button());
			this->numSamplesBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->statsPanel = (gcnew System::Windows::Forms::Panel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->varianceBox = (gcnew System::Windows::Forms::TextBox());
			this->meanBox = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->updateStatsButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->readingsPanel = (gcnew System::Windows::Forms::Panel());
			this->updateReadingsButton = (gcnew System::Windows::Forms::Button());
			this->readingsBox = (gcnew System::Windows::Forms::RichTextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->sidePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->bottomPanel->SuspendLayout();
			this->defaultPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			this->calibratePanel->SuspendLayout();
			this->samplesPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numSamplesBox))->BeginInit();
			this->statsPanel->SuspendLayout();
			this->readingsPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// sidePanel
			// 
			this->sidePanel->BackColor = System::Drawing::SystemColors::ControlDark;
			this->sidePanel->Controls->Add(this->pictureBox1);
			this->sidePanel->Controls->Add(this->groupBox2);
			this->sidePanel->Controls->Add(this->groupBox1);
			this->sidePanel->Dock = System::Windows::Forms::DockStyle::Left;
			this->sidePanel->Location = System::Drawing::Point(0, 0);
			this->sidePanel->Name = L"sidePanel";
			this->sidePanel->Size = System::Drawing::Size(113, 319);
			this->sidePanel->TabIndex = 2;
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
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->rbWeightReadings);
			this->groupBox2->Controls->Add(this->ViewLabel);
			this->groupBox2->Controls->Add(this->configLabel);
			this->groupBox2->Controls->Add(this->rbStats);
			this->groupBox2->Controls->Add(this->rbSamples);
			this->groupBox2->Controls->Add(this->rbCalibrate);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox2->Location = System::Drawing::Point(11, 84);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(90, 142);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Factory";
			// 
			// rbWeightReadings
			// 
			this->rbWeightReadings->AutoSize = true;
			this->rbWeightReadings->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->rbWeightReadings->Location = System::Drawing::Point(14, 117);
			this->rbWeightReadings->Name = L"rbWeightReadings";
			this->rbWeightReadings->Size = System::Drawing::Size(70, 17);
			this->rbWeightReadings->TabIndex = 1;
			this->rbWeightReadings->TabStop = true;
			this->rbWeightReadings->Text = L"Readings";
			this->rbWeightReadings->UseVisualStyleBackColor = true;
			this->rbWeightReadings->CheckedChanged += gcnew System::EventHandler(this, &FrmFactoryMode::rbWeightReadings_CheckedChanged);
			// 
			// ViewLabel
			// 
			this->ViewLabel->AutoSize = true;
			this->ViewLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ViewLabel->Location = System::Drawing::Point(6, 78);
			this->ViewLabel->Name = L"ViewLabel";
			this->ViewLabel->Size = System::Drawing::Size(30, 13);
			this->ViewLabel->TabIndex = 3;
			this->ViewLabel->Text = L"View";
			// 
			// configLabel
			// 
			this->configLabel->AutoSize = true;
			this->configLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->configLabel->Location = System::Drawing::Point(6, 16);
			this->configLabel->Name = L"configLabel";
			this->configLabel->Size = System::Drawing::Size(69, 13);
			this->configLabel->TabIndex = 2;
			this->configLabel->Text = L"Configuration";
			// 
			// rbStats
			// 
			this->rbStats->AutoSize = true;
			this->rbStats->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->rbStats->Location = System::Drawing::Point(14, 94);
			this->rbStats->Name = L"rbStats";
			this->rbStats->Size = System::Drawing::Size(67, 17);
			this->rbStats->TabIndex = 0;
			this->rbStats->TabStop = true;
			this->rbStats->Text = L"Statistics";
			this->rbStats->UseVisualStyleBackColor = true;
			this->rbStats->CheckedChanged += gcnew System::EventHandler(this, &FrmFactoryMode::rbStats_CheckedChanged);
			// 
			// rbSamples
			// 
			this->rbSamples->AutoSize = true;
			this->rbSamples->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->rbSamples->Location = System::Drawing::Point(16, 58);
			this->rbSamples->Name = L"rbSamples";
			this->rbSamples->Size = System::Drawing::Size(65, 17);
			this->rbSamples->TabIndex = 1;
			this->rbSamples->Text = L"Samples";
			this->rbSamples->UseVisualStyleBackColor = true;
			this->rbSamples->CheckedChanged += gcnew System::EventHandler(this, &FrmFactoryMode::rbSamples_CheckedChanged);
			// 
			// rbCalibrate
			// 
			this->rbCalibrate->AutoSize = true;
			this->rbCalibrate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->rbCalibrate->Location = System::Drawing::Point(16, 34);
			this->rbCalibrate->Name = L"rbCalibrate";
			this->rbCalibrate->Size = System::Drawing::Size(66, 17);
			this->rbCalibrate->TabIndex = 0;
			this->rbCalibrate->Text = L"Calibrate";
			this->rbCalibrate->UseVisualStyleBackColor = true;
			this->rbCalibrate->CheckedChanged += gcnew System::EventHandler(this, &FrmFactoryMode::rbCalibrate_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->rbHideUser);
			this->groupBox1->Controls->Add(this->rbShowUser);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(10, 10);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(91, 68);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"User Panel";
			// 
			// rbHideUser
			// 
			this->rbHideUser->AutoSize = true;
			this->rbHideUser->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->rbHideUser->Location = System::Drawing::Point(17, 42);
			this->rbHideUser->Name = L"rbHideUser";
			this->rbHideUser->Size = System::Drawing::Size(47, 17);
			this->rbHideUser->TabIndex = 1;
			this->rbHideUser->Text = L"Hide";
			this->rbHideUser->UseVisualStyleBackColor = true;
			// 
			// rbShowUser
			// 
			this->rbShowUser->AccessibleName = L"";
			this->rbShowUser->AutoSize = true;
			this->rbShowUser->Checked = true;
			this->rbShowUser->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->rbShowUser->Location = System::Drawing::Point(17, 19);
			this->rbShowUser->Name = L"rbShowUser";
			this->rbShowUser->Size = System::Drawing::Size(52, 17);
			this->rbShowUser->TabIndex = 0;
			this->rbShowUser->TabStop = true;
			this->rbShowUser->Text = L"Show";
			this->rbShowUser->UseVisualStyleBackColor = true;
			this->rbShowUser->CheckedChanged += gcnew System::EventHandler(this, &FrmFactoryMode::rbShowUser_CheckedChanged);
			// 
			// bottomPanel
			// 
			this->bottomPanel->BackColor = System::Drawing::SystemColors::ControlLight;
			this->bottomPanel->Controls->Add(this->closeButton);
			this->bottomPanel->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->bottomPanel->Location = System::Drawing::Point(113, 279);
			this->bottomPanel->Name = L"bottomPanel";
			this->bottomPanel->Size = System::Drawing::Size(342, 40);
			this->bottomPanel->TabIndex = 5;
			// 
			// closeButton
			// 
			this->closeButton->Location = System::Drawing::Point(255, 8);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(75, 23);
			this->closeButton->TabIndex = 1;
			this->closeButton->Text = L"Close";
			this->closeButton->UseVisualStyleBackColor = true;
			this->closeButton->Click += gcnew System::EventHandler(this, &FrmFactoryMode::closeButton_Click);
			// 
			// defaultPanel
			// 
			this->defaultPanel->Controls->Add(this->pictureBox2);
			this->defaultPanel->Controls->Add(this->richTextBox1);
			this->defaultPanel->Controls->Add(this->label1);
			this->defaultPanel->Location = System::Drawing::Point(123, 6);
			this->defaultPanel->Name = L"defaultPanel";
			this->defaultPanel->Size = System::Drawing::Size(319, 262);
			this->defaultPanel->TabIndex = 6;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(3, 94);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(100, 83);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::Control;
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(113, 89);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(189, 123);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = L"This is the Factory Mode panel. If you have opened this in error, close the panel" 
				L" immediately. Do not change any configuration, as it may irreversibly alter the " 
				L"ability of your scales to weigh items.";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(18, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(284, 24);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Fennec Scales Factory Panel";
			// 
			// calibratePanel
			// 
			this->calibratePanel->Controls->Add(this->resetCalibButton);
			this->calibratePanel->Controls->Add(this->calibConfLabel);
			this->calibratePanel->Controls->Add(this->progressBar);
			this->calibratePanel->Controls->Add(this->oneKiloSetButton);
			this->calibratePanel->Controls->Add(this->oneKiloBox);
			this->calibratePanel->Controls->Add(this->label15);
			this->calibratePanel->Controls->Add(this->seven50SetButton);
			this->calibratePanel->Controls->Add(this->seven50Box);
			this->calibratePanel->Controls->Add(this->label14);
			this->calibratePanel->Controls->Add(this->five00SetButton);
			this->calibratePanel->Controls->Add(this->five00Box);
			this->calibratePanel->Controls->Add(this->label13);
			this->calibratePanel->Controls->Add(this->two50SetButton);
			this->calibratePanel->Controls->Add(this->two50Box);
			this->calibratePanel->Controls->Add(this->label12);
			this->calibratePanel->Controls->Add(this->zeroSetButton);
			this->calibratePanel->Controls->Add(this->zeroBox);
			this->calibratePanel->Controls->Add(this->label11);
			this->calibratePanel->Controls->Add(this->label10);
			this->calibratePanel->Controls->Add(this->sendCalibButton);
			this->calibratePanel->Location = System::Drawing::Point(114, 0);
			this->calibratePanel->Name = L"calibratePanel";
			this->calibratePanel->Size = System::Drawing::Size(339, 273);
			this->calibratePanel->TabIndex = 7;
			// 
			// resetCalibButton
			// 
			this->resetCalibButton->Location = System::Drawing::Point(221, 213);
			this->resetCalibButton->Name = L"resetCalibButton";
			this->resetCalibButton->Size = System::Drawing::Size(75, 23);
			this->resetCalibButton->TabIndex = 29;
			this->resetCalibButton->Text = L"Reset";
			this->resetCalibButton->UseVisualStyleBackColor = true;
			this->resetCalibButton->Visible = false;
			this->resetCalibButton->Click += gcnew System::EventHandler(this, &FrmFactoryMode::resetCalibButton_Click);
			// 
			// calibConfLabel
			// 
			this->calibConfLabel->AutoSize = true;
			this->calibConfLabel->Location = System::Drawing::Point(63, 242);
			this->calibConfLabel->Name = L"calibConfLabel";
			this->calibConfLabel->Size = System::Drawing::Size(106, 13);
			this->calibConfLabel->TabIndex = 28;
			this->calibConfLabel->Text = L"Calibration data sent.";
			this->calibConfLabel->Visible = false;
			// 
			// progressBar
			// 
			this->progressBar->Location = System::Drawing::Point(46, 212);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(250, 23);
			this->progressBar->Step = 1;
			this->progressBar->TabIndex = 26;
			// 
			// oneKiloSetButton
			// 
			this->oneKiloSetButton->Location = System::Drawing::Point(221, 173);
			this->oneKiloSetButton->Name = L"oneKiloSetButton";
			this->oneKiloSetButton->Size = System::Drawing::Size(75, 23);
			this->oneKiloSetButton->TabIndex = 25;
			this->oneKiloSetButton->Text = L"Set";
			this->oneKiloSetButton->UseVisualStyleBackColor = true;
			this->oneKiloSetButton->Click += gcnew System::EventHandler(this, &FrmFactoryMode::oneKiloSetButton_Click);
			// 
			// oneKiloBox
			// 
			this->oneKiloBox->BackColor = System::Drawing::SystemColors::Control;
			this->oneKiloBox->Location = System::Drawing::Point(113, 175);
			this->oneKiloBox->Name = L"oneKiloBox";
			this->oneKiloBox->Size = System::Drawing::Size(99, 20);
			this->oneKiloBox->TabIndex = 24;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(63, 178);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(43, 13);
			this->label15->TabIndex = 23;
			this->label15->Text = L"1000 g:";
			// 
			// seven50SetButton
			// 
			this->seven50SetButton->Location = System::Drawing::Point(221, 147);
			this->seven50SetButton->Name = L"seven50SetButton";
			this->seven50SetButton->Size = System::Drawing::Size(75, 23);
			this->seven50SetButton->TabIndex = 22;
			this->seven50SetButton->Text = L"Set";
			this->seven50SetButton->UseVisualStyleBackColor = true;
			this->seven50SetButton->Click += gcnew System::EventHandler(this, &FrmFactoryMode::seven50SetButton_Click);
			// 
			// seven50Box
			// 
			this->seven50Box->BackColor = System::Drawing::SystemColors::Control;
			this->seven50Box->Location = System::Drawing::Point(113, 149);
			this->seven50Box->Name = L"seven50Box";
			this->seven50Box->Size = System::Drawing::Size(99, 20);
			this->seven50Box->TabIndex = 21;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(69, 152);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(37, 13);
			this->label14->TabIndex = 20;
			this->label14->Text = L"750 g:";
			// 
			// five00SetButton
			// 
			this->five00SetButton->Location = System::Drawing::Point(221, 121);
			this->five00SetButton->Name = L"five00SetButton";
			this->five00SetButton->Size = System::Drawing::Size(75, 23);
			this->five00SetButton->TabIndex = 19;
			this->five00SetButton->Text = L"Set";
			this->five00SetButton->UseVisualStyleBackColor = true;
			this->five00SetButton->Click += gcnew System::EventHandler(this, &FrmFactoryMode::five00SetButton_Click);
			// 
			// five00Box
			// 
			this->five00Box->BackColor = System::Drawing::SystemColors::Control;
			this->five00Box->Location = System::Drawing::Point(113, 123);
			this->five00Box->Name = L"five00Box";
			this->five00Box->Size = System::Drawing::Size(99, 20);
			this->five00Box->TabIndex = 18;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(69, 126);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(37, 13);
			this->label13->TabIndex = 17;
			this->label13->Text = L"500 g:";
			// 
			// two50SetButton
			// 
			this->two50SetButton->Location = System::Drawing::Point(221, 95);
			this->two50SetButton->Name = L"two50SetButton";
			this->two50SetButton->Size = System::Drawing::Size(75, 23);
			this->two50SetButton->TabIndex = 16;
			this->two50SetButton->Text = L"Set";
			this->two50SetButton->UseVisualStyleBackColor = true;
			this->two50SetButton->Click += gcnew System::EventHandler(this, &FrmFactoryMode::two50SetButton_Click);
			// 
			// two50Box
			// 
			this->two50Box->BackColor = System::Drawing::SystemColors::Control;
			this->two50Box->Location = System::Drawing::Point(113, 97);
			this->two50Box->Name = L"two50Box";
			this->two50Box->Size = System::Drawing::Size(99, 20);
			this->two50Box->TabIndex = 15;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(69, 100);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(37, 13);
			this->label12->TabIndex = 14;
			this->label12->Text = L"250 g:";
			// 
			// zeroSetButton
			// 
			this->zeroSetButton->Location = System::Drawing::Point(221, 69);
			this->zeroSetButton->Name = L"zeroSetButton";
			this->zeroSetButton->Size = System::Drawing::Size(75, 23);
			this->zeroSetButton->TabIndex = 13;
			this->zeroSetButton->Text = L"Set";
			this->zeroSetButton->UseVisualStyleBackColor = true;
			this->zeroSetButton->Click += gcnew System::EventHandler(this, &FrmFactoryMode::zeroSetButton_Click);
			// 
			// zeroBox
			// 
			this->zeroBox->BackColor = System::Drawing::SystemColors::Control;
			this->zeroBox->Location = System::Drawing::Point(113, 71);
			this->zeroBox->Name = L"zeroBox";
			this->zeroBox->Size = System::Drawing::Size(99, 20);
			this->zeroBox->TabIndex = 12;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(43, 74);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(63, 13);
			this->label11->TabIndex = 11;
			this->label11->Text = L"Empty (0 g):";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(85, 23);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(160, 24);
			this->label10->TabIndex = 10;
			this->label10->Text = L"Calibrate Scales";
			// 
			// sendCalibButton
			// 
			this->sendCalibButton->Location = System::Drawing::Point(46, 211);
			this->sendCalibButton->Name = L"sendCalibButton";
			this->sendCalibButton->Size = System::Drawing::Size(250, 23);
			this->sendCalibButton->TabIndex = 27;
			this->sendCalibButton->Text = L"Finalise Scale Calibration";
			this->sendCalibButton->UseVisualStyleBackColor = true;
			this->sendCalibButton->Visible = false;
			this->sendCalibButton->Click += gcnew System::EventHandler(this, &FrmFactoryMode::sendCalibButton_Click);
			// 
			// samplesPanel
			// 
			this->samplesPanel->Controls->Add(this->confirmLabel);
			this->samplesPanel->Controls->Add(this->sendNumSamplesButton);
			this->samplesPanel->Controls->Add(this->numSamplesBox);
			this->samplesPanel->Controls->Add(this->label5);
			this->samplesPanel->Controls->Add(this->label4);
			this->samplesPanel->Location = System::Drawing::Point(114, 0);
			this->samplesPanel->Name = L"samplesPanel";
			this->samplesPanel->Size = System::Drawing::Size(339, 273);
			this->samplesPanel->TabIndex = 8;
			// 
			// confirmLabel
			// 
			this->confirmLabel->AutoSize = true;
			this->confirmLabel->Location = System::Drawing::Point(104, 200);
			this->confirmLabel->Name = L"confirmLabel";
			this->confirmLabel->Size = System::Drawing::Size(142, 13);
			this->confirmLabel->TabIndex = 15;
			this->confirmLabel->Text = L"Number of Samples set to (x)";
			this->confirmLabel->Visible = false;
			// 
			// sendNumSamplesButton
			// 
			this->sendNumSamplesButton->Location = System::Drawing::Point(134, 152);
			this->sendNumSamplesButton->Name = L"sendNumSamplesButton";
			this->sendNumSamplesButton->Size = System::Drawing::Size(75, 23);
			this->sendNumSamplesButton->TabIndex = 14;
			this->sendNumSamplesButton->Text = L"Send to PIC";
			this->sendNumSamplesButton->UseVisualStyleBackColor = true;
			this->sendNumSamplesButton->Click += gcnew System::EventHandler(this, &FrmFactoryMode::sendNumSamplesButton_Click);
			// 
			// numSamplesBox
			// 
			this->numSamplesBox->Location = System::Drawing::Point(112, 124);
			this->numSamplesBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {32, 0, 0, 0});
			this->numSamplesBox->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numSamplesBox->Name = L"numSamplesBox";
			this->numSamplesBox->Size = System::Drawing::Size(120, 20);
			this->numSamplesBox->TabIndex = 13;
			this->numSamplesBox->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(16, 83);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(315, 13);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Enter the number of weight samples to retain in the circular buffer:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(59, 23);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(230, 24);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Set Number of Samples";
			// 
			// statsPanel
			// 
			this->statsPanel->Controls->Add(this->label9);
			this->statsPanel->Controls->Add(this->label8);
			this->statsPanel->Controls->Add(this->varianceBox);
			this->statsPanel->Controls->Add(this->meanBox);
			this->statsPanel->Controls->Add(this->label7);
			this->statsPanel->Controls->Add(this->label6);
			this->statsPanel->Controls->Add(this->updateStatsButton);
			this->statsPanel->Controls->Add(this->label3);
			this->statsPanel->Location = System::Drawing::Point(114, 0);
			this->statsPanel->Name = L"statsPanel";
			this->statsPanel->Size = System::Drawing::Size(339, 273);
			this->statsPanel->TabIndex = 9;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(242, 159);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(47, 16);
			this->label9->TabIndex = 9;
			this->label9->Text = L"counts";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(242, 111);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(47, 16);
			this->label8->TabIndex = 8;
			this->label8->Text = L"counts";
			// 
			// varianceBox
			// 
			this->varianceBox->BackColor = System::Drawing::SystemColors::Control;
			this->varianceBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->varianceBox->Location = System::Drawing::Point(113, 156);
			this->varianceBox->Name = L"varianceBox";
			this->varianceBox->ReadOnly = true;
			this->varianceBox->Size = System::Drawing::Size(110, 22);
			this->varianceBox->TabIndex = 7;
			// 
			// meanBox
			// 
			this->meanBox->BackColor = System::Drawing::SystemColors::Control;
			this->meanBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->meanBox->Location = System::Drawing::Point(113, 111);
			this->meanBox->Name = L"meanBox";
			this->meanBox->ReadOnly = true;
			this->meanBox->Size = System::Drawing::Size(110, 22);
			this->meanBox->TabIndex = 6;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(41, 159);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(62, 16);
			this->label7->TabIndex = 5;
			this->label7->Text = L"Variance";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(61, 111);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(42, 16);
			this->label6->TabIndex = 4;
			this->label6->Text = L"Mean";
			// 
			// updateStatsButton
			// 
			this->updateStatsButton->Location = System::Drawing::Point(130, 237);
			this->updateStatsButton->Name = L"updateStatsButton";
			this->updateStatsButton->Size = System::Drawing::Size(75, 23);
			this->updateStatsButton->TabIndex = 3;
			this->updateStatsButton->Text = L"Update";
			this->updateStatsButton->UseVisualStyleBackColor = true;
			this->updateStatsButton->Click += gcnew System::EventHandler(this, &FrmFactoryMode::updateStatsButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(86, 23);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(161, 24);
			this->label3->TabIndex = 1;
			this->label3->Text = L"Weight Statistics";
			// 
			// readingsPanel
			// 
			this->readingsPanel->Controls->Add(this->updateReadingsButton);
			this->readingsPanel->Controls->Add(this->readingsBox);
			this->readingsPanel->Controls->Add(this->label2);
			this->readingsPanel->Location = System::Drawing::Point(114, 0);
			this->readingsPanel->Name = L"readingsPanel";
			this->readingsPanel->Size = System::Drawing::Size(339, 273);
			this->readingsPanel->TabIndex = 10;
			// 
			// updateReadingsButton
			// 
			this->updateReadingsButton->Location = System::Drawing::Point(134, 245);
			this->updateReadingsButton->Name = L"updateReadingsButton";
			this->updateReadingsButton->Size = System::Drawing::Size(75, 23);
			this->updateReadingsButton->TabIndex = 2;
			this->updateReadingsButton->Text = L"Update";
			this->updateReadingsButton->UseVisualStyleBackColor = true;
			this->updateReadingsButton->Click += gcnew System::EventHandler(this, &FrmFactoryMode::updateReadingsButton_Click);
			// 
			// readingsBox
			// 
			this->readingsBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->readingsBox->Location = System::Drawing::Point(87, 51);
			this->readingsBox->Name = L"readingsBox";
			this->readingsBox->ReadOnly = true;
			this->readingsBox->Size = System::Drawing::Size(165, 188);
			this->readingsBox->TabIndex = 1;
			this->readingsBox->Text = L"";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(83, 22);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(169, 24);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Weight Readings";
			// 
			// FrmFactoryMode
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(455, 319);
			this->Controls->Add(this->readingsPanel);
			this->Controls->Add(this->statsPanel);
			this->Controls->Add(this->samplesPanel);
			this->Controls->Add(this->calibratePanel);
			this->Controls->Add(this->defaultPanel);
			this->Controls->Add(this->bottomPanel);
			this->Controls->Add(this->sidePanel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Location = System::Drawing::Point(250, 340);
			this->MaximizeBox = false;
			this->Name = L"FrmFactoryMode";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Factory Panel";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FrmFactoryMode::FrmFactoryMode_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FrmFactoryMode::FrmFactoryMode_FormClosed);
			this->sidePanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->bottomPanel->ResumeLayout(false);
			this->defaultPanel->ResumeLayout(false);
			this->defaultPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			this->calibratePanel->ResumeLayout(false);
			this->calibratePanel->PerformLayout();
			this->samplesPanel->ResumeLayout(false);
			this->samplesPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numSamplesBox))->EndInit();
			this->statsPanel->ResumeLayout(false);
			this->statsPanel->PerformLayout();
			this->readingsPanel->ResumeLayout(false);
			this->readingsPanel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		private:

			void resetFactoryForm()
			{
				calibratePanel->Hide();
				samplesPanel->Hide();
				statsPanel->Hide();
				readingsPanel->Hide();
				defaultPanel->Show();
			}

			void showPanel(Panel^ panel)
			{
				resetFactoryForm();
				defaultPanel->Hide();
				panel->Show();
			}

			unsigned short getRawWeight()
			{
				comms->sendChange(COMM_CAL_RAWVAL, COMM_CAL_ACK_RAWVAL);
				return rawWeight;
			}

			void setButtonPress(int id)
			{
				if (buttonsOn[id])
				{
					if (progressBar->Value == progressBar->Maximum)
					{
						progressBar->Show();
						sendCalibButton->Hide();
					}
					buttons[id]->Text = "Set";
					textBox[id]->Text = "";
					progressBar->Increment(-20);
					buttonsOn[id] = false;
				}
				else
				{
					rawWeights[id] = getRawWeight();

					buttons[id]->Text = "Reset";
					textBox[id]->Text = String::Format("{0}", rawWeights[id]);

					progressBar->Increment(20);
					if (progressBar->Value == progressBar->Maximum)
					{
						progressBar->Hide();
						sendCalibButton->Show();
					}
					buttonsOn[id] = true;
				}
			}

			void calcCalibrate(array<short> ^gradients, array<short> ^intercepts)
			{
				for (int i = 0; i < 4; ++i)
				{
					gradients[i] = (short) ( (double) 250*CAL_GRADIENT_FACTOR / double (rawWeights[i + 1] - rawWeights[i]));
					intercepts[i] =  250*i - rawWeights[i] * (int) gradients[i] / CAL_GRADIENT_FACTOR;
				}
			}

			void resetCalibrateFrame()
			{
				for (int i = 0; i < 5; ++i)
				{
					buttons[i]->Text = "Set";
					textBox[i]->Text = "";
					progressBar->Increment(-20);
					buttonsOn[i] = false;
				}

				progressBar->Show();
				resetCalibButton->Hide();
				calibConfLabel->Hide();
			}

			void getStats()
			{
				comms->sendChange(COMM_GET_STATS, COMM_ACK_STATS);
				meanBox->Text = String::Format("{0}", mean);
				double _variance = (double) variance / 10;
				varianceBox->Text = String::Format("{0:f1}", _variance);
			}

			void getReadings()
			{
				comms->sendChange(COMM_WEIGHT_READINGS, COMM_ACK_WEIGHT_READINGS);

				readingsBox->Text = "";

				for (int i = 0; i < numReadings; ++i)
				{
					readingsBox->AppendText(String::Format("{0}:\t", i));
					readingsBox->AppendText(String::Format("{0}\n", weightReadings[i]));
				}
			}

			void getNumSamples()
			{
				comms->sendChange(COMM_GET_NUM_SAMPLES, COMM_ACK_NUM_SAMPLES);
				if (numSamples > 1)
					numSamplesBox->Value = numSamples;
			}

			void sendNumSamples(unsigned char num)
			{
				comms->sendChange(COMM_SET_NUM_SAMPLES, num, COMM_NUM_RXD);
			}

			
	private: System::Void FrmFactoryMode_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 Application::Exit();
			 }
private: System::Void closeButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void FrmFactoryMode_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 
			 if (!closeFactory && !closeAll)
			 {
				 FrmFactoryClosing ^closeForm = gcnew FrmFactoryClosing(this);
				 closeForm->ShowDialog();
				 e->Cancel = true;
			 }			 

			 if (!closeAll)
			 {
				 e->Cancel = true;
				 if (closeFactory)
				 {
					 this->Hide();
					 remoteFrm->Show();
					 closeFactory = false;
				 }
			 }
			 
		 }
private: System::Void rbShowUser_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

			 if (rbShowUser->Checked)
			 {
				 remoteFrm->Show();
			 }
			 else
			 {
				 remoteFrm->Hide();
			 }
		 }
private: System::Void rbCalibrate_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

			 if (rbCalibrate->Checked)
			 {
				 resetCalibrateFrame();
				 showPanel(calibratePanel);
			 }
		 }
private: System::Void rbSamples_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			
			 if (rbSamples->Checked)
			 {
				 getNumSamples();
				 confirmLabel->Visible = false;
				 showPanel(samplesPanel);
			 }
		 }
private: System::Void rbStats_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 
			 if (rbStats->Checked)
			 {
				 getStats();
				 showPanel(statsPanel);
			 }
		 }
private: System::Void rbWeightReadings_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 
			 if (rbWeightReadings->Checked)
			 {
				 getReadings();
				 showPanel(readingsPanel);
			 }
		 }
private: System::Void updateReadingsButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 getReadings();
		 }
private: System::Void updateStatsButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 getStats();
		 }
private: System::Void sendNumSamplesButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 sendNumSamples((unsigned char) numSamplesBox->Value);

			 confirmLabel->Text = String::Format("Number of samples set to {0}.", numSamplesBox->Value);
			 confirmLabel->Visible = true;
		 }
private: System::Void zeroSetButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 setButtonPress(0);
		 }
private: System::Void two50SetButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 setButtonPress(1);
		 }
private: System::Void five00SetButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 setButtonPress(2);
		 }
private: System::Void seven50SetButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 setButtonPress(3);
		 }
private: System::Void oneKiloSetButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 setButtonPress(4);
		 }
private: System::Void sendCalibButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 array<short> ^gradients = gcnew array<short>(4);
			 array<short> ^intercepts = gcnew array<short>(4);
			 array<short> ^combined = gcnew array<short>(12);
			 bool fail = false;

			// Disable serial handling of anything else
			serialBlock = true;

			// First, produce the calibration matrix
			calcCalibrate(gradients, intercepts);

			// Send code to initiate data exchange
			//comms->sendSerialByte(COMM_CAL_DATA);
			int j = 0;
			combined[j++] = COMM_CAL_DATA;

			// Then send the three middle corner points
			for (int i = 1; i < 4; ++i)
			{
				//comms->sendSerialShort(rawWeights[i]);
				combined[j++] = rawWeights[i];
			}

			// Then send the four gradients
			for (int i = 0; i < 4; ++i)
			{
				//comms->sendSerialShort(gradients[i]);
				combined[j++] = gradients[i];
			}

			// Then send the four y-intercepts
			for (int i = 0; i < 4; ++i)
			{
				//comms->sendSerialShort(intercepts[i]);
				combined[j++] = intercepts[i];
			}

			comms->sendSerialShortArray(combined);

			// Re-enable serial handling
			serialBlock = false;

			calibConfLabel->Text = "Calibration data sent.\nWaiting for acknowledge...";
			calibConfLabel->Show();
			this->Update();

			int time = SERIAL_TIMEOUT_GUI;

			while (ack != COMM_CAL_ACK_DATA)
			{
				if (!(--time))
				{
					fail = true;
				}
			}
			ack = 0;

			if (fail)
			{
				calibConfLabel->Text = "Acknowledge from scales not received.\nCalibration may not be successful.";
			}
			else
			{
				calibConfLabel->Text = "Calibration data sent.\nAcknowledge from scales received.";
			}
			sendCalibButton->Hide();
			 resetCalibButton->Show();

		 }
private: System::Void resetCalibButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 resetCalibrateFrame();
		 }
};
}
