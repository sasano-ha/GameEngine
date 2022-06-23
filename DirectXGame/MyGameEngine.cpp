#include "MyGameEngine.h"
#include "GameScene.h"

void MyGameEngine::Initialize()
{
	//���N���X�̏���������
	GameBase::Initialize();

#pragma region �`�揉��������
	scene_ = new GameScene();
	scene_->Initialize();

#pragma endregion �`�揉��������
}

void MyGameEngine::Finalize()
{
	//���N���X�̏���������
	GameBase::Finalize();

	scene_->Finalize();
}

void MyGameEngine::Update()
{
	GameBase::Update();

	scene_->Update();
}

void MyGameEngine::Draw()
{
	//�`��O����
	dxCommon->PreDraw();

	scene_->Draw();

	// �f�o�b�O�e�L�X�g�`��
	debugText->DrawAll();

	// �S�D�`��R�}���h�����܂�

	//�`��㏈��
	dxCommon->PostDraw();
}
