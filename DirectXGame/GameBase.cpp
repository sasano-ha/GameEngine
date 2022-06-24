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
	spriteCommon = SpriteCommon::GetInstance();
	spriteCommon->Initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->windows_width, winApp->windows_height);

	//�f�o�b�O�e�L�X�g
	debugText = DebugText::GetInstance();
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	const int debugTextTexNumber = 0;
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// �f�o�b�O�e�L�X�g������
	debugText->Initialize(spriteCommon, debugTextTexNumber);


	//���͂̏�����
	input = Input::GetInstance();
	input->Initialize(winApp);

	//�I�[�f�B�I�̏�����
	audio = Sound::GetInstance();
	audio->Initialize();

	// �����ǂݍ���
	audio->LoadWave("Alarm01.wav");
	// �����Đ�
	//audio->PlayWave("Alarm01.wav");

	//3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::windows_width, WinApp::windows_height);
	// FBX���[�_�[�̏�����
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDev());
}

void GameBase::Finalize()
{
	// FBX���[�_�[�̉��
	FbxLoader::GetInstance()->Finalize();
	// �V�[���t�@�N�g�����
	delete sceneFactory_;
	// �f�o�b�O�e�L�X�g���
	debugText->Finalize();

	//�I�[�f�B�I���
	audio->Finalize();

	//DirectX���
	delete dxCommon;

	//windowsAPI�̏I������
	winApp->Finalize();
	// WindowsAPI���
	delete winApp;
}

void GameBase::Update()
{
	//windows�̃��b�Z�[�W����
	if (winApp->ProcessMessage()) {
		//�Q�[�����[�v�𔲂���
		endRequst_ = true;
		return;
	}

	input->Update();

	// �V�[���̍X�V
	SceneManager::GetInstance()->Update();
}

void GameBase::Draw()
{
	//�`��O����
	dxCommon->PreDraw();

	SceneManager::GetInstance()->Draw();

	// �f�o�b�O�e�L�X�g�`��
	debugText->DrawAll();

	//�`��㏈��
	dxCommon->PostDraw();
}
