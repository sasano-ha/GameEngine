#include "GameBase.h"

void GameBase::Initialize()
{
	//windowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();


	MSG msg{};  // ���b�Z�[�W
#pragma endregion WindowsAPI������

#pragma region DirectX����������
	//DirectX�̏�����
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	// DirectX�����������@��������

	// �X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->windows_width, winApp->windows_height);

	//�f�o�b�O�e�L�X�g
	debugText = new DebugText();
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	const int debugTextTexNumber = 0;
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// �f�o�b�O�e�L�X�g������
	debugText->Initialize(spriteCommon, debugTextTexNumber);


	//���͂̏�����
	input = new Input();
	input->Initialize(winApp);

	//�I�[�f�B�I�̏�����
	audio = new Sound();
	audio->Initialize();

	// �����ǂݍ���
	audio->LoadWave("Alarm01.wav");
	// �����Đ�
	audio->PlayWave("Alarm01.wav");

	//3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::windows_width, WinApp::windows_height);
}

void GameBase::Finalize()
{
	// �f�o�b�O�e�L�X�g���
	debugText->Finalize();
	delete debugText;

	// �X�v���C�g���ʕ����
	delete spriteCommon;

	//�I�[�f�B�I���
	audio->Finalize();
	delete audio;

	//DirectX���
	delete dxCommon;

	// ���͉��
	delete input;

	//windowsAPI�̏I������
	winApp->Finalize();
	// WindowsAPI���
	delete winApp;
}

void GameBase::Update()
{
	GameBase::Update();

	//windows�̃��b�Z�[�W����
	if (winApp->ProcessMessage()) {
		//�Q�[�����[�v�𔲂���
		endRequst_ = true;
		return;
	}

	input->Update();
}
