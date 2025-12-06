#pragma once

namespace PrimitiveDrawTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		static bool RenderRedChannel;
		static bool RenderGreenChannel;
	private: System::Windows::Forms::RadioButton^ MoveLight;
	private: System::Windows::Forms::RadioButton^ ColorByPosition;
	private: System::Windows::Forms::RadioButton^ MoveCubesToSphere;
	private: System::Windows::Forms::Button^ ResetLightPosition;
	private: System::Windows::Forms::Button^ ResetTeapotPosition;
	private: System::Windows::Forms::TrackBar^ SpecStrength;
	private: System::Windows::Forms::TrackBar^ SpecR;
	private: System::Windows::Forms::TrackBar^ SpecG;
	private: System::Windows::Forms::TrackBar^ SpecB;




	private: System::Windows::Forms::Label^ SpecStrengthVal;

	private: System::Windows::Forms::Label^ SpecularStrength;
	private: System::Windows::Forms::Label^ SpecularColor;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ SpecRVal;
	private: System::Windows::Forms::Label^ SpecGVal;
	private: System::Windows::Forms::Label^ SpecBVal;

	public:
		static bool s_MoveLightEnabled = true;
		static bool s_ColorByPositionEnabled = false;
		static bool s_MoveCubesToSphereEnabled = false;

		static int s_SpecularStrength = 4;
		static float s_SpecularR = 100;
		static float s_SpecularG = 100;
		static float s_SpecularB = 100;
		static bool s_ResetLight = false;
		static bool s_ResetTeapot = false;


		ToolWindow(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->MoveLight = (gcnew System::Windows::Forms::RadioButton());
			this->ColorByPosition = (gcnew System::Windows::Forms::RadioButton());
			this->MoveCubesToSphere = (gcnew System::Windows::Forms::RadioButton());
			this->ResetLightPosition = (gcnew System::Windows::Forms::Button());
			this->ResetTeapotPosition = (gcnew System::Windows::Forms::Button());
			this->SpecStrength = (gcnew System::Windows::Forms::TrackBar());
			this->SpecR = (gcnew System::Windows::Forms::TrackBar());
			this->SpecG = (gcnew System::Windows::Forms::TrackBar());
			this->SpecB = (gcnew System::Windows::Forms::TrackBar());
			this->SpecStrengthVal = (gcnew System::Windows::Forms::Label());
			this->SpecularStrength = (gcnew System::Windows::Forms::Label());
			this->SpecularColor = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SpecRVal = (gcnew System::Windows::Forms::Label());
			this->SpecGVal = (gcnew System::Windows::Forms::Label());
			this->SpecBVal = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecG))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecB))->BeginInit();
			this->SuspendLayout();
			// 
			// MoveLight
			// 
			this->MoveLight->AutoSize = true;
			this->MoveLight->Checked = true;
			this->MoveLight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MoveLight->Location = System::Drawing::Point(15, 12);
			this->MoveLight->Name = L"MoveLight";
			this->MoveLight->Size = System::Drawing::Size(88, 17);
			this->MoveLight->TabIndex = 0;
			this->MoveLight->TabStop = true;
			this->MoveLight->Text = L"Move Light";
			this->MoveLight->UseVisualStyleBackColor = true;
			this->MoveLight->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::MoveLight_CheckedChanged);
			// 
			// ColorByPosition
			// 
			this->ColorByPosition->AutoSize = true;
			this->ColorByPosition->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ColorByPosition->Location = System::Drawing::Point(15, 268);
			this->ColorByPosition->Name = L"ColorByPosition";
			this->ColorByPosition->Size = System::Drawing::Size(121, 17);
			this->ColorByPosition->TabIndex = 1;
			this->ColorByPosition->TabStop = true;
			this->ColorByPosition->Text = L"Color By Position";
			this->ColorByPosition->UseVisualStyleBackColor = true;
			this->ColorByPosition->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::ColorByPosition_CheckedChanged);
			// 
			// MoveCubesToSphere
			// 
			this->MoveCubesToSphere->AutoSize = true;
			this->MoveCubesToSphere->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MoveCubesToSphere->Location = System::Drawing::Point(15, 324);
			this->MoveCubesToSphere->Name = L"MoveCubesToSphere";
			this->MoveCubesToSphere->Size = System::Drawing::Size(158, 17);
			this->MoveCubesToSphere->TabIndex = 2;
			this->MoveCubesToSphere->TabStop = true;
			this->MoveCubesToSphere->Text = L"Move Cubes To Sphere";
			this->MoveCubesToSphere->UseVisualStyleBackColor = true;
			this->MoveCubesToSphere->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::MoveCubesToSphere_CheckedChanged);
			// 
			// ResetLightPosition
			// 
			this->ResetLightPosition->Cursor = System::Windows::Forms::Cursors::Hand;
			this->ResetLightPosition->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->ResetLightPosition->Location = System::Drawing::Point(28, 35);
			this->ResetLightPosition->Name = L"ResetLightPosition";
			this->ResetLightPosition->Size = System::Drawing::Size(123, 23);
			this->ResetLightPosition->TabIndex = 3;
			this->ResetLightPosition->Text = L"Reset Light Position\r\n";
			this->ResetLightPosition->UseVisualStyleBackColor = true;
			this->ResetLightPosition->Click += gcnew System::EventHandler(this, &ToolWindow::ResetLightPosition_Click);
			// 
			// ResetTeapotPosition
			// 
			this->ResetTeapotPosition->Cursor = System::Windows::Forms::Cursors::Hand;
			this->ResetTeapotPosition->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->ResetTeapotPosition->Location = System::Drawing::Point(28, 292);
			this->ResetTeapotPosition->Name = L"ResetTeapotPosition";
			this->ResetTeapotPosition->Size = System::Drawing::Size(123, 23);
			this->ResetTeapotPosition->TabIndex = 4;
			this->ResetTeapotPosition->Text = L"Reset Teapot Position";
			this->ResetTeapotPosition->UseVisualStyleBackColor = true;
			this->ResetTeapotPosition->Click += gcnew System::EventHandler(this, &ToolWindow::ResetTeapotPosition_Click);
			// 
			// SpecStrength
			// 
			this->SpecStrength->BackColor = System::Drawing::SystemColors::Control;
			this->SpecStrength->Location = System::Drawing::Point(141, 64);
			this->SpecStrength->Maximum = 128;
			this->SpecStrength->Minimum = 1;
			this->SpecStrength->Name = L"SpecStrength";
			this->SpecStrength->Size = System::Drawing::Size(337, 45);
			this->SpecStrength->TabIndex = 5;
			this->SpecStrength->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->SpecStrength->Value = 4;
			this->SpecStrength->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecStrength_Scroll);
			// 
			// SpecR
			// 
			this->SpecR->Location = System::Drawing::Point(141, 115);
			this->SpecR->Maximum = 300;
			this->SpecR->Name = L"SpecR";
			this->SpecR->Size = System::Drawing::Size(337, 45);
			this->SpecR->TabIndex = 6;
			this->SpecR->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->SpecR->Value = 100;
			this->SpecR->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecR_Scroll);
			// 
			// SpecG
			// 
			this->SpecG->Location = System::Drawing::Point(141, 166);
			this->SpecG->Maximum = 300;
			this->SpecG->Name = L"SpecG";
			this->SpecG->Size = System::Drawing::Size(337, 45);
			this->SpecG->TabIndex = 7;
			this->SpecG->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->SpecG->Value = 100;
			this->SpecG->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecG_Scroll);
			// 
			// SpecB
			// 
			this->SpecB->Location = System::Drawing::Point(141, 217);
			this->SpecB->Maximum = 300;
			this->SpecB->Name = L"SpecB";
			this->SpecB->Size = System::Drawing::Size(337, 45);
			this->SpecB->TabIndex = 8;
			this->SpecB->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->SpecB->Value = 100;
			this->SpecB->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecB_Scroll);
			// 
			// SpecStrengthVal
			// 
			this->SpecStrengthVal->AutoSize = true;
			this->SpecStrengthVal->Location = System::Drawing::Point(488, 77);
			this->SpecStrengthVal->Name = L"SpecStrengthVal";
			this->SpecStrengthVal->Size = System::Drawing::Size(13, 13);
			this->SpecStrengthVal->TabIndex = 9;
			this->SpecStrengthVal->Text = L"4";
			// 
			// SpecularStrength
			// 
			this->SpecularStrength->AutoSize = true;
			this->SpecularStrength->Location = System::Drawing::Point(12, 77);
			this->SpecularStrength->Name = L"SpecularStrength";
			this->SpecularStrength->Size = System::Drawing::Size(92, 13);
			this->SpecularStrength->TabIndex = 10;
			this->SpecularStrength->Text = L"Specular Strength";
			// 
			// SpecularColor
			// 
			this->SpecularColor->AutoSize = true;
			this->SpecularColor->Location = System::Drawing::Point(12, 129);
			this->SpecularColor->Name = L"SpecularColor";
			this->SpecularColor->Size = System::Drawing::Size(76, 13);
			this->SpecularColor->TabIndex = 11;
			this->SpecularColor->Text = L"Specular Color";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(120, 129);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(15, 13);
			this->label2->TabIndex = 12;
			this->label2->Text = L"R";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(120, 181);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(15, 13);
			this->label3->TabIndex = 13;
			this->label3->Text = L"G";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(120, 230);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(14, 13);
			this->label4->TabIndex = 14;
			this->label4->Text = L"B";
			// 
			// SpecRVal
			// 
			this->SpecRVal->AutoSize = true;
			this->SpecRVal->Location = System::Drawing::Point(488, 128);
			this->SpecRVal->Name = L"SpecRVal";
			this->SpecRVal->Size = System::Drawing::Size(25, 13);
			this->SpecRVal->TabIndex = 15;
			this->SpecRVal->Text = L"100";
			// 
			// SpecGVal
			// 
			this->SpecGVal->AutoSize = true;
			this->SpecGVal->Location = System::Drawing::Point(488, 181);
			this->SpecGVal->Name = L"SpecGVal";
			this->SpecGVal->Size = System::Drawing::Size(25, 13);
			this->SpecGVal->TabIndex = 16;
			this->SpecGVal->Text = L"100";
			// 
			// SpecBVal
			// 
			this->SpecBVal->AutoSize = true;
			this->SpecBVal->Location = System::Drawing::Point(488, 230);
			this->SpecBVal->Name = L"SpecBVal";
			this->SpecBVal->Size = System::Drawing::Size(25, 13);
			this->SpecBVal->TabIndex = 17;
			this->SpecBVal->Text = L"100";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(548, 352);
			this->ControlBox = false;
			this->Controls->Add(this->SpecBVal);
			this->Controls->Add(this->SpecGVal);
			this->Controls->Add(this->SpecRVal);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->SpecularColor);
			this->Controls->Add(this->SpecularStrength);
			this->Controls->Add(this->SpecStrengthVal);
			this->Controls->Add(this->SpecB);
			this->Controls->Add(this->SpecG);
			this->Controls->Add(this->SpecR);
			this->Controls->Add(this->SpecStrength);
			this->Controls->Add(this->ResetTeapotPosition);
			this->Controls->Add(this->ResetLightPosition);
			this->Controls->Add(this->MoveCubesToSphere);
			this->Controls->Add(this->ColorByPosition);
			this->Controls->Add(this->MoveLight);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecStrength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecG))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecB))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
		SpecStrength->Value = 4;
		s_SpecularStrength = SpecStrength->Value;

		SpecR->Value = 100;
		SpecG->Value = 100;
		SpecB->Value = 100;
		s_SpecularR = (float)SpecR->Value / 100;
		s_SpecularG = (float)SpecG->Value / 100;
		s_SpecularB = (float)SpecB->Value / 100;

		SpecStrengthVal->Text = s_SpecularStrength.ToString();
		SpecRVal->Text = s_SpecularR.ToString();
		SpecGVal->Text = s_SpecularG.ToString();
		SpecBVal->Text = s_SpecularB.ToString();

		s_MoveLightEnabled = MoveLight->Checked;
		s_ColorByPositionEnabled = ColorByPosition->Checked;
		s_MoveCubesToSphereEnabled = MoveCubesToSphere->Checked;
	}
	private: System::Void SpecStrength_Scroll(System::Object^ sender, System::EventArgs^ e) {
		SpecStrengthVal->Text = SpecStrength->Value.ToString();
		s_SpecularStrength = SpecStrength->Value;
	}
	private: System::Void SpecR_Scroll(System::Object^ sender, System::EventArgs^ e) {
		s_SpecularR = (float)SpecR->Value / 100;
		SpecRVal->Text = s_SpecularR.ToString();
	}
	private: System::Void SpecG_Scroll(System::Object^ sender, System::EventArgs^ e) {
		s_SpecularG = (float)SpecG->Value / 100;
		SpecGVal->Text = s_SpecularG.ToString();
	}

	private: System::Void SpecB_Scroll(System::Object^ sender, System::EventArgs^ e) {
		s_SpecularB = (float)SpecB->Value / 100;
		SpecBVal->Text = s_SpecularB.ToString();
	}
	private: System::Void ResetLightPosition_Click(System::Object^ sender, System::EventArgs^ e) {
		s_ResetLight = true;
	}
	private: System::Void ResetTeapotPosition_Click(System::Object^ sender, System::EventArgs^ e) {
		s_ResetTeapot = true;
	}
	private: System::Void MoveLight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_MoveLightEnabled = MoveLight->Checked;
	}
	private: System::Void ColorByPosition_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_ColorByPositionEnabled = ColorByPosition->Checked;
	}
	private: System::Void MoveCubesToSphere_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_MoveCubesToSphereEnabled = MoveCubesToSphere->Checked;
	}
	};
}