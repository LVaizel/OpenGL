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
	private: System::Windows::Forms::RadioButton^ Transform;
	private: System::Windows::Forms::RadioButton^ WaterScene;


	private: System::Windows::Forms::Button^ ResetLightPosition;
	private: System::Windows::Forms::Button^ ResetTransform;

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
		static bool s_TransformEnabled = false;
		static bool s_WaterSceneEnabled = false;
		static bool s_SpaceSceneEnabled = false;

		static bool s_TranslateEnabled = false;
		static bool s_RotateEnabled = false;
		static bool s_ScaleEnabled = false;

		static int s_SpecularStrength = 4;
		static float s_SpecularR = 100;
		static float s_SpecularG = 100;
		static float s_SpecularB = 100;
		static bool s_ResetLight = false;

		static float s_Frequency = 4.0f;
		static float s_Amplitude = 1.0f;

		static bool s_Tint = false;
		static bool s_WireFrameRender = false;

	private: System::Windows::Forms::RadioButton^ SpaceScene;
	private: System::Windows::Forms::CheckBox^ TranslateCheckBox;
	private: System::Windows::Forms::CheckBox^ RotateCheckBox;
	private: System::Windows::Forms::CheckBox^ ScaleCheckBox;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ FrequencyLabel;

	private: System::Windows::Forms::TrackBar^ FrequencyScrollbar;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ AmplitudeLabel;

	private: System::Windows::Forms::TrackBar^ AplitudeScrollbar;
	private: System::Windows::Forms::CheckBox^ TintCheckbox;
	private: System::Windows::Forms::CheckBox^ WireFrameRenderCheckbox;

	public:

	public:
		static bool s_ResetTransform = false;


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
			this->Transform = (gcnew System::Windows::Forms::RadioButton());
			this->WaterScene = (gcnew System::Windows::Forms::RadioButton());
			this->ResetLightPosition = (gcnew System::Windows::Forms::Button());
			this->ResetTransform = (gcnew System::Windows::Forms::Button());
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
			this->SpaceScene = (gcnew System::Windows::Forms::RadioButton());
			this->TranslateCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->RotateCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->ScaleCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->FrequencyLabel = (gcnew System::Windows::Forms::Label());
			this->FrequencyScrollbar = (gcnew System::Windows::Forms::TrackBar());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->AmplitudeLabel = (gcnew System::Windows::Forms::Label());
			this->AplitudeScrollbar = (gcnew System::Windows::Forms::TrackBar());
			this->TintCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->WireFrameRenderCheckbox = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecG))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FrequencyScrollbar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AplitudeScrollbar))->BeginInit();
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
			// Transform
			// 
			this->Transform->AutoSize = true;
			this->Transform->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Transform->Location = System::Drawing::Point(15, 268);
			this->Transform->Name = L"Transform";
			this->Transform->Size = System::Drawing::Size(81, 17);
			this->Transform->TabIndex = 1;
			this->Transform->TabStop = true;
			this->Transform->Text = L"Transform";
			this->Transform->UseVisualStyleBackColor = true;
			this->Transform->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::Transform_CheckedChanged);
			// 
			// WaterScene
			// 
			this->WaterScene->AutoSize = true;
			this->WaterScene->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->WaterScene->Location = System::Drawing::Point(15, 393);
			this->WaterScene->Name = L"WaterScene";
			this->WaterScene->Size = System::Drawing::Size(99, 17);
			this->WaterScene->TabIndex = 2;
			this->WaterScene->TabStop = true;
			this->WaterScene->Text = L"Water Scene";
			this->WaterScene->UseVisualStyleBackColor = true;
			this->WaterScene->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::WaterScene_CheckedChanged);
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
			// ResetTransform
			// 
			this->ResetTransform->Cursor = System::Windows::Forms::Cursors::Hand;
			this->ResetTransform->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->ResetTransform->Location = System::Drawing::Point(28, 292);
			this->ResetTransform->Name = L"ResetTransform";
			this->ResetTransform->Size = System::Drawing::Size(123, 23);
			this->ResetTransform->TabIndex = 4;
			this->ResetTransform->Text = L"Reset Transform";
			this->ResetTransform->UseVisualStyleBackColor = true;
			this->ResetTransform->Click += gcnew System::EventHandler(this, &ToolWindow::ResetTransform_Click);
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
			// SpaceScene
			// 
			this->SpaceScene->AutoSize = true;
			this->SpaceScene->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SpaceScene->Location = System::Drawing::Point(15, 565);
			this->SpaceScene->Name = L"SpaceScene";
			this->SpaceScene->Size = System::Drawing::Size(101, 17);
			this->SpaceScene->TabIndex = 18;
			this->SpaceScene->TabStop = true;
			this->SpaceScene->Text = L"Space Scene";
			this->SpaceScene->UseVisualStyleBackColor = true;
			this->SpaceScene->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::SpaceScene_CheckedChanged);
			// 
			// TranslateCheckBox
			// 
			this->TranslateCheckBox->AutoSize = true;
			this->TranslateCheckBox->Location = System::Drawing::Point(28, 322);
			this->TranslateCheckBox->Name = L"TranslateCheckBox";
			this->TranslateCheckBox->Size = System::Drawing::Size(70, 17);
			this->TranslateCheckBox->TabIndex = 19;
			this->TranslateCheckBox->Text = L"Translate";
			this->TranslateCheckBox->UseVisualStyleBackColor = true;
			this->TranslateCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::TranslateCheckBox_CheckedChanged);
			// 
			// RotateCheckBox
			// 
			this->RotateCheckBox->AutoSize = true;
			this->RotateCheckBox->Location = System::Drawing::Point(28, 346);
			this->RotateCheckBox->Name = L"RotateCheckBox";
			this->RotateCheckBox->Size = System::Drawing::Size(58, 17);
			this->RotateCheckBox->TabIndex = 20;
			this->RotateCheckBox->Text = L"Rotate";
			this->RotateCheckBox->UseVisualStyleBackColor = true;
			this->RotateCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::RotateCheckBox_CheckedChanged);
			// 
			// ScaleCheckBox
			// 
			this->ScaleCheckBox->AutoSize = true;
			this->ScaleCheckBox->Location = System::Drawing::Point(28, 370);
			this->ScaleCheckBox->Name = L"ScaleCheckBox";
			this->ScaleCheckBox->Size = System::Drawing::Size(53, 17);
			this->ScaleCheckBox->TabIndex = 21;
			this->ScaleCheckBox->Text = L"Scale";
			this->ScaleCheckBox->UseVisualStyleBackColor = true;
			this->ScaleCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::ScaleCheckBox_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 424);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(57, 13);
			this->label1->TabIndex = 24;
			this->label1->Text = L"Frequency";
			// 
			// FrequencyLabel
			// 
			this->FrequencyLabel->AutoSize = true;
			this->FrequencyLabel->Location = System::Drawing::Point(488, 424);
			this->FrequencyLabel->Name = L"FrequencyLabel";
			this->FrequencyLabel->Size = System::Drawing::Size(13, 13);
			this->FrequencyLabel->TabIndex = 23;
			this->FrequencyLabel->Text = L"4";
			// 
			// FrequencyScrollbar
			// 
			this->FrequencyScrollbar->BackColor = System::Drawing::SystemColors::Control;
			this->FrequencyScrollbar->Location = System::Drawing::Point(141, 411);
			this->FrequencyScrollbar->Maximum = 400;
			this->FrequencyScrollbar->Name = L"FrequencyScrollbar";
			this->FrequencyScrollbar->Size = System::Drawing::Size(337, 45);
			this->FrequencyScrollbar->TabIndex = 22;
			this->FrequencyScrollbar->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->FrequencyScrollbar->Value = 400;
			this->FrequencyScrollbar->Scroll += gcnew System::EventHandler(this, &ToolWindow::Frequency_Scroll);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(12, 475);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(53, 13);
			this->label6->TabIndex = 27;
			this->label6->Text = L"Amplitude";
			// 
			// AmplitudeLabel
			// 
			this->AmplitudeLabel->AutoSize = true;
			this->AmplitudeLabel->Location = System::Drawing::Point(488, 475);
			this->AmplitudeLabel->Name = L"AmplitudeLabel";
			this->AmplitudeLabel->Size = System::Drawing::Size(13, 13);
			this->AmplitudeLabel->TabIndex = 26;
			this->AmplitudeLabel->Text = L"1";
			// 
			// AplitudeScrollbar
			// 
			this->AplitudeScrollbar->BackColor = System::Drawing::SystemColors::Control;
			this->AplitudeScrollbar->Location = System::Drawing::Point(141, 462);
			this->AplitudeScrollbar->Maximum = 100;
			this->AplitudeScrollbar->Name = L"AplitudeScrollbar";
			this->AplitudeScrollbar->Size = System::Drawing::Size(337, 45);
			this->AplitudeScrollbar->TabIndex = 25;
			this->AplitudeScrollbar->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->AplitudeScrollbar->Value = 1;
			this->AplitudeScrollbar->Scroll += gcnew System::EventHandler(this, &ToolWindow::Amplitude_Scroll);
			// 
			// TintCheckbox
			// 
			this->TintCheckbox->AutoSize = true;
			this->TintCheckbox->Location = System::Drawing::Point(15, 542);
			this->TintCheckbox->Name = L"TintCheckbox";
			this->TintCheckbox->Size = System::Drawing::Size(68, 17);
			this->TintCheckbox->TabIndex = 29;
			this->TintCheckbox->Text = L"Tint Blue";
			this->TintCheckbox->UseVisualStyleBackColor = true;
			this->TintCheckbox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::TintCheckbox_CheckedChanged);
			// 
			// WireFrameRenderCheckbox
			// 
			this->WireFrameRenderCheckbox->AutoSize = true;
			this->WireFrameRenderCheckbox->Location = System::Drawing::Point(15, 518);
			this->WireFrameRenderCheckbox->Name = L"WireFrameRenderCheckbox";
			this->WireFrameRenderCheckbox->Size = System::Drawing::Size(115, 17);
			this->WireFrameRenderCheckbox->TabIndex = 28;
			this->WireFrameRenderCheckbox->Text = L"WireFrame Render";
			this->WireFrameRenderCheckbox->UseVisualStyleBackColor = true;
			this->WireFrameRenderCheckbox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::WireFrameRenderCheckbox_CheckedChanged);
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(548, 625);
			this->ControlBox = false;
			this->Controls->Add(this->TintCheckbox);
			this->Controls->Add(this->WireFrameRenderCheckbox);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->AmplitudeLabel);
			this->Controls->Add(this->AplitudeScrollbar);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->FrequencyLabel);
			this->Controls->Add(this->FrequencyScrollbar);
			this->Controls->Add(this->ScaleCheckBox);
			this->Controls->Add(this->RotateCheckBox);
			this->Controls->Add(this->TranslateCheckBox);
			this->Controls->Add(this->SpaceScene);
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
			this->Controls->Add(this->ResetTransform);
			this->Controls->Add(this->ResetLightPosition);
			this->Controls->Add(this->WaterScene);
			this->Controls->Add(this->Transform);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FrequencyScrollbar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AplitudeScrollbar))->EndInit();
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
		s_TransformEnabled = Transform->Checked;
		s_WaterSceneEnabled = WaterScene->Checked;
		s_SpaceSceneEnabled = SpaceScene->Checked;

		s_Frequency = (float)FrequencyScrollbar->Value / 100;
		s_Amplitude = (float)AplitudeScrollbar->Value / 100;

		FrequencyLabel->Text = s_Frequency.ToString("F2");
		AmplitudeLabel->Text = s_Amplitude.ToString("F2");
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
	private: System::Void ResetTransform_Click(System::Object^ sender, System::EventArgs^ e) {
		s_ResetTransform = true;
	}
	private: System::Void MoveLight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_MoveLightEnabled = MoveLight->Checked;
	}
	private: System::Void Transform_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_TransformEnabled = Transform->Checked;
	}
	private: System::Void WaterScene_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_WaterSceneEnabled = WaterScene->Checked;
	}
	private: System::Void SpaceScene_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_SpaceSceneEnabled = SpaceScene->Checked;
	}
	private: System::Void TranslateCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_TranslateEnabled = TranslateCheckBox->Checked;
	}
	private: System::Void RotateCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_RotateEnabled = RotateCheckBox->Checked;
	}
	private: System::Void ScaleCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_ScaleEnabled = ScaleCheckBox->Checked;
	}
	private: System::Void Frequency_Scroll(System::Object^ sender, System::EventArgs^ e) {
		float frequency = (float)FrequencyScrollbar->Value / 100;
		FrequencyLabel->Text = frequency.ToString("F2");
		s_Frequency = frequency;
	}
	private: System::Void Amplitude_Scroll(System::Object^ sender, System::EventArgs^ e) {
		float amplitude = (float)AplitudeScrollbar->Value / 100;
		AmplitudeLabel->Text = amplitude.ToString("F2");
		s_Amplitude = amplitude;
	}
	private: System::Void TintCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_Tint = TintCheckbox->Checked;
	}
	private: System::Void WireFrameRenderCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		s_WireFrameRender = WireFrameRenderCheckbox->Checked;
	}
};
}