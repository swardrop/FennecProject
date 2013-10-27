#pragma once

extern bool closeAll;
extern bool closeFactory;

namespace FennecScalesGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FrmFactoryClosing
	/// </summary>
	public ref class FrmFactoryClosing : public System::Windows::Forms::Form
	{
	public:
		FrmFactoryClosing(Form ^p)
		{
			InitializeComponent();
			parent = p;
			closeFactory = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FrmFactoryClosing()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label2;
	protected: 
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  buttonGoBack;

	private: System::Windows::Forms::Button^  quitButton;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::RadioButton^  rbCloseAll;
	private: System::Windows::Forms::RadioButton^  rbCloseFactory;
	private: System::Windows::Forms::Label^  label3;

			 Form ^parent;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FrmFactoryClosing::typeid));
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->buttonGoBack = (gcnew System::Windows::Forms::Button());
			this->quitButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->rbCloseAll = (gcnew System::Windows::Forms::RadioButton());
			this->rbCloseFactory = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(34, 59);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(187, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"The scales will revert to LOCAL mode.";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel1->Controls->Add(this->buttonGoBack);
			this->panel1->Controls->Add(this->quitButton);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 129);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(284, 45);
			this->panel1->TabIndex = 6;
			// 
			// buttonGoBack
			// 
			this->buttonGoBack->Location = System::Drawing::Point(12, 10);
			this->buttonGoBack->Name = L"buttonGoBack";
			this->buttonGoBack->Size = System::Drawing::Size(75, 23);
			this->buttonGoBack->TabIndex = 2;
			this->buttonGoBack->Text = L"Go Back";
			this->buttonGoBack->UseVisualStyleBackColor = true;
			this->buttonGoBack->Click += gcnew System::EventHandler(this, &FrmFactoryClosing::buttonGoBack_Click);
			// 
			// quitButton
			// 
			this->quitButton->Location = System::Drawing::Point(197, 10);
			this->quitButton->Name = L"quitButton";
			this->quitButton->Size = System::Drawing::Size(75, 23);
			this->quitButton->TabIndex = 0;
			this->quitButton->Text = L"Close";
			this->quitButton->UseVisualStyleBackColor = true;
			this->quitButton->Click += gcnew System::EventHandler(this, &FrmFactoryClosing::quitButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(160, 16);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Closing Factory Panel";
			// 
			// rbCloseAll
			// 
			this->rbCloseAll->AutoSize = true;
			this->rbCloseAll->Checked = true;
			this->rbCloseAll->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->rbCloseAll->Location = System::Drawing::Point(11, 39);
			this->rbCloseAll->Name = L"rbCloseAll";
			this->rbCloseAll->Size = System::Drawing::Size(74, 17);
			this->rbCloseAll->TabIndex = 8;
			this->rbCloseAll->TabStop = true;
			this->rbCloseAll->Text = L"Close All";
			this->rbCloseAll->UseVisualStyleBackColor = true;
			// 
			// rbCloseFactory
			// 
			this->rbCloseFactory->AutoSize = true;
			this->rbCloseFactory->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->rbCloseFactory->Location = System::Drawing::Point(11, 87);
			this->rbCloseFactory->Name = L"rbCloseFactory";
			this->rbCloseFactory->Size = System::Drawing::Size(165, 17);
			this->rbCloseFactory->TabIndex = 10;
			this->rbCloseFactory->Text = L"Close only Factory Panel";
			this->rbCloseFactory->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(34, 107);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(235, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"The scales will remain in USER REMOTE mode.";
			// 
			// FrmFactoryClosing
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 174);
			this->Controls->Add(this->rbCloseFactory);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->rbCloseAll);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FrmFactoryClosing";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Close Factory Panel";
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void quitButton_Click(System::Object^  sender, System::EventArgs^  e) {

				 closeFactory = true;

				 if (rbCloseAll->Checked)
				 {
					 closeAll = true;
					 Application::Exit();
				 }

				 parent->Close();
				 this->Close();
			 }
private: System::Void buttonGoBack_Click(System::Object^  sender, System::EventArgs^  e) {
			 closeFactory = false;
			 this->Close();
		 }
};
}
