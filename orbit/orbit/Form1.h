#pragma once

namespace orbit {

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





	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::ComboBox^  comboBox1;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ComboBox^  comboBox8;
	private: System::Windows::Forms::ComboBox^  comboBox7;
	private: System::Windows::Forms::ComboBox^  comboBox6;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::ComboBox^  comboBox5;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::ComboBox^  comboBox4;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::TextBox^  textBox1;










	private: System::ComponentModel::IContainer^  components;











	protected: 


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox8 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox7 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox6 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox5 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::Transparent;
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 135);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox1->Location = System::Drawing::Point(2, 9);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(196, 124);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::Color::Transparent;
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Location = System::Drawing::Point(12, 153);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(200, 42);
			this->groupBox2->TabIndex = 10;
			this->groupBox2->TabStop = false;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->label1->Font = (gcnew System::Drawing::Font(L"Miramonte", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(6, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(188, 27);
			this->label1->TabIndex = 0;
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->Cursor = System::Windows::Forms::Cursors::Help;
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(0, 0);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(224, 210);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox2->TabIndex = 11;
			this->pictureBox2->TabStop = false;
			this->toolTip1->SetToolTip(this->pictureBox2, L"login");
			// 
			// comboBox1
			// 
			this->comboBox1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"warrior", L"magician", L"thief", L"archer"});
			this->comboBox1->Location = System::Drawing::Point(6, 12);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(188, 22);
			this->comboBox1->TabIndex = 0;
			this->comboBox1->Text = L"select a job";
			this->toolTip1->SetToolTip(this->comboBox1, L"select a job");
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox1_SelectedIndexChanged);
			// 
			// comboBox8
			// 
			this->comboBox8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox8->FormattingEnabled = true;
			this->comboBox8->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox8->Location = System::Drawing::Point(103, 180);
			this->comboBox8->Name = L"comboBox8";
			this->comboBox8->Size = System::Drawing::Size(91, 22);
			this->comboBox8->TabIndex = 12;
			this->comboBox8->Text = L"skill 3 key";
			this->toolTip1->SetToolTip(this->comboBox8, L"select a skill 3 key");
			this->comboBox8->Visible = false;
			this->comboBox8->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox8_SelectedIndexChanged);
			// 
			// comboBox7
			// 
			this->comboBox7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox7->FormattingEnabled = true;
			this->comboBox7->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox7->Location = System::Drawing::Point(103, 152);
			this->comboBox7->Name = L"comboBox7";
			this->comboBox7->Size = System::Drawing::Size(91, 22);
			this->comboBox7->TabIndex = 11;
			this->comboBox7->Text = L"skill 2 key";
			this->toolTip1->SetToolTip(this->comboBox7, L"select a skill 2 key");
			this->comboBox7->Visible = false;
			this->comboBox7->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox7_SelectedIndexChanged);
			// 
			// comboBox6
			// 
			this->comboBox6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox6->FormattingEnabled = true;
			this->comboBox6->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox6->Location = System::Drawing::Point(103, 124);
			this->comboBox6->Name = L"comboBox6";
			this->comboBox6->Size = System::Drawing::Size(91, 22);
			this->comboBox6->TabIndex = 10;
			this->comboBox6->Text = L"skill 1 key";
			this->toolTip1->SetToolTip(this->comboBox6, L"select a skill 1 key");
			this->comboBox6->Visible = false;
			this->comboBox6->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox6_SelectedIndexChanged);
			// 
			// comboBox5
			// 
			this->comboBox5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox5->FormattingEnabled = true;
			this->comboBox5->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox5->Location = System::Drawing::Point(103, 40);
			this->comboBox5->Name = L"comboBox5";
			this->comboBox5->Size = System::Drawing::Size(91, 22);
			this->comboBox5->TabIndex = 6;
			this->comboBox5->Text = L"loot key";
			this->toolTip1->SetToolTip(this->comboBox5, L"select a loot key");
			this->comboBox5->Visible = false;
			this->comboBox5->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox5_SelectedIndexChanged);
			this->comboBox5->Click += gcnew System::EventHandler(this, &Form1::comboBox5_Click);
			// 
			// comboBox4
			// 
			this->comboBox4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox4->Location = System::Drawing::Point(103, 96);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(91, 22);
			this->comboBox4->TabIndex = 4;
			this->comboBox4->Text = L"mana key";
			this->toolTip1->SetToolTip(this->comboBox4, L"select a mana key");
			this->comboBox4->Visible = false;
			this->comboBox4->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox4_SelectedIndexChanged);
			// 
			// comboBox3
			// 
			this->comboBox3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox3->Location = System::Drawing::Point(103, 68);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(91, 22);
			this->comboBox3->TabIndex = 3;
			this->comboBox3->Text = L"health key";
			this->toolTip1->SetToolTip(this->comboBox3, L"select a health key");
			this->comboBox3->Visible = false;
			this->comboBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox3_SelectedIndexChanged);
			// 
			// comboBox2
			// 
			this->comboBox2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(45) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", 
				L"T", L"U", L"V", L"W", L"X", L"Y", L"Z", L"SHIFT", L"CTRL", L"ALT", L"PAGE UP", L"PAGE DOWN", L"END", L"HOME", L"INS", L"DEL"});
			this->comboBox2->Location = System::Drawing::Point(6, 40);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(91, 22);
			this->comboBox2->TabIndex = 2;
			this->comboBox2->Text = L"attack key";
			this->toolTip1->SetToolTip(this->comboBox2, L"select a attack key");
			this->comboBox2->Visible = false;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox2_SelectedIndexChanged);
			this->comboBox2->Click += gcnew System::EventHandler(this, &Form1::comboBox2_Click);
			// 
			// button1
			// 
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Location = System::Drawing::Point(6, 208);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(188, 23);
			this->button1->TabIndex = 13;
			this->button1->Text = L"reset";
			this->toolTip1->SetToolTip(this->button1, L"reset");
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Visible = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(6, 181);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(91, 21);
			this->textBox5->TabIndex = 9;
			this->textBox5->Text = L"skill 3 cooldown";
			this->toolTip1->SetToolTip(this->textBox5, L"input the skill 3 cooldown");
			this->textBox5->Visible = false;
			this->textBox5->Click += gcnew System::EventHandler(this, &Form1::textBox5_Click);
			this->textBox5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBox5_KeyPress);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(6, 153);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(91, 21);
			this->textBox4->TabIndex = 8;
			this->textBox4->Text = L"skill 2 cooldown";
			this->toolTip1->SetToolTip(this->textBox4, L"input the skill 2 cooldown");
			this->textBox4->Visible = false;
			this->textBox4->Click += gcnew System::EventHandler(this, &Form1::textBox4_Click);
			this->textBox4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBox4_KeyPress);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(6, 125);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(91, 21);
			this->textBox3->TabIndex = 7;
			this->textBox3->Text = L"skill 1 cooldown";
			this->toolTip1->SetToolTip(this->textBox3, L"input the skill 1 cooldown");
			this->textBox3->Visible = false;
			this->textBox3->Click += gcnew System::EventHandler(this, &Form1::textBox3_Click);
			this->textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBox3_KeyPress);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(6, 97);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(91, 21);
			this->textBox2->TabIndex = 5;
			this->textBox2->Text = L"mana value";
			this->toolTip1->SetToolTip(this->textBox2, L"input the mana value");
			this->textBox2->Visible = false;
			this->textBox2->Click += gcnew System::EventHandler(this, &Form1::textBox2_Click);
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBox2_KeyPress);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(6, 69);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(91, 21);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"health value";
			this->toolTip1->SetToolTip(this->textBox1, L"input the health value");
			this->textBox1->Visible = false;
			this->textBox1->Click += gcnew System::EventHandler(this, &Form1::textBox1_Click);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBox1_KeyPress);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::Color::Transparent;
			this->groupBox3->Controls->Add(this->button1);
			this->groupBox3->Controls->Add(this->comboBox8);
			this->groupBox3->Controls->Add(this->comboBox7);
			this->groupBox3->Controls->Add(this->comboBox6);
			this->groupBox3->Controls->Add(this->textBox5);
			this->groupBox3->Controls->Add(this->textBox4);
			this->groupBox3->Controls->Add(this->textBox3);
			this->groupBox3->Controls->Add(this->comboBox5);
			this->groupBox3->Controls->Add(this->textBox2);
			this->groupBox3->Controls->Add(this->comboBox4);
			this->groupBox3->Controls->Add(this->comboBox3);
			this->groupBox3->Controls->Add(this->comboBox2);
			this->groupBox3->Controls->Add(this->textBox1);
			this->groupBox3->Controls->Add(this->comboBox1);
			this->groupBox3->Location = System::Drawing::Point(12, 201);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(200, 40);
			this->groupBox3->TabIndex = 12;
			this->groupBox3->TabStop = false;
			this->groupBox3->Visible = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 14);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(224, 210);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Font = (gcnew System::Drawing::Font(L"Miramonte", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->Opacity = 0.8;
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"orbit";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e);
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox3_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox4_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox5_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox6_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox7_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox8_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox2_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox5_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void textBox2_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void textBox3_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox3_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void textBox4_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox4_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void textBox5_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox5_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e);
private: System::Void Settings();
};
}
