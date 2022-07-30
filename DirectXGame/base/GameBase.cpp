#include "GameBase.h"
#include "FbxObject3d.h"

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

	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::windows_width, WinApp::windows_height);
	// FBX���[�_�[�̏�����
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDev());

	// �f�o�C�X���Z�b�g
	FbxObject3d::SetDevice(dxCommon->GetDev());
	camera_ = new Camera(1280, 720);
	// �J�������Z�b�g
	FbxObject3d::SetCamera(camera_);
	// �J���������_���Z�b�g
	camera_->SetTarget({ 0, 5, 0 });
	camera_->SetEye({ 0, 5, 10 });
	// �O���t�B�b�N�X�p�C�v���C������
	FbxObject3d::CreateGraphicsPipeline();
}

void GameBase::Finalize()
{
	// FBX���[�_�[�̉��
	FbxLoader::GetInstance()->Finalize();
	// �V�[���t�@�N�g�����
	delete sceneFactory_;
	
	//DirectX���
	delete dxCommon;

	//windowsAPI�̏I������
	winApp->Finalize();

	// WindowsAPI���
	delete winApp;

	//�I�[�f�B�I���
	audio->Finalize();
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
	camera_->Update();

	// �V�[���̍X�V
	SceneManager::GetInstance()->Update();
}

void GameBase::Draw()
{
	SceneManager::GetInstance()->Draw(dxCommon);
}
