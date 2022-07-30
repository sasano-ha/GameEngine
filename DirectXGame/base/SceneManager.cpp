#include "SceneManager.h"
#include "SafeDelete.h"
#include "SceneFactory.h"


#include <cassert>

SceneManager::~SceneManager()
{
	// �Ō�̃V�[���̏I���Ɖ��
	scene_->Finalize();
	delete scene_;

	safedelete(posteffect_);

	// �f�o�b�O�e�L�X�g���
	debugText->Finalize();
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;

	return &instance;
}

void SceneManager::Initialze(DirectXCommon* dxCommon, WinApp* winApp)
{
	// �V�[���t�@�N�g���������A�}�l�[�W���[�ɃZ�b�g
	sceneFactory_ = new SceneFactory();
	SetSceneFactory(sceneFactory_);

	// �V�[���}�l�[�W���[�ɍŏ��̃V�[�����Z�b�g
	ChangeScene("TITLE");

	// �X�v���C�g���ʕ����̏�����
	spritecommon = SpriteCommon::GetInstance();
	spritecommon->Initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->windows_width, winApp->windows_height);

	//�f�o�b�O�e�L�X�g
	debugText = DebugText::GetInstance();
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	const int debugTextTexNumber = 0;
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
	spritecommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// �f�o�b�O�e�L�X�g������
	debugText->Initialize(spritecommon, debugTextTexNumber);

	posteffect_ = new PostEffect();
	posteffect_->SizeInitialize(100, { 500,500 }, { 0, 0 }, false, false);

	posteffect_->Initialize();
}

void SceneManager::Update()
{
	// �V�[���؂�ւ�������Ȃ�
	if (nextScene_) {
		if (scene_) {
			// ���V�[���̏I��
			scene_->Finalize();
			delete scene_;
		}

		// �V�[���؂�ւ�
		scene_ = nextScene_;
		nextScene_ = nullptr;

		// �V�V�[���̏�����
		scene_->Initialize();
	}

	scene_->Update();
	//posteffect_->Update();
}

void SceneManager::Draw(DirectXCommon* dxCommon)
{
	// �����_�[�e�N�X�`���ւ̕`��
	//posteffect_->PreDrawScene(dxCommon->GetCmdList());
	//posteffect_->PostDrawScene(dxCommon->GetCmdList());


	//�`��O����
	dxCommon->PreDraw();

	//posteffect_->Draw(dxCommon->GetCmdList());

	spritecommon->PreDraw();
	scene_->Draw(dxCommon);
	// �f�o�b�O�e�L�X�g�`��
	//debugText->DrawAll();

	//�`��㏈��
	dxCommon->PostDraw();
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory_);
	assert(nextScene_ == nullptr);

	// ���V�[���𐶐�
	nextScene_ =  sceneFactory_->CreateScene(sceneName);
}
