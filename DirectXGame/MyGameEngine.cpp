#include "MyGameEngine.h"
#include "GameScene.h"
#include "TitleScene.h"

void MyGameEngine::Initialize()
{
	//���N���X�̏���������
	GameBase::Initialize();

#pragma region �`�揉��������
	//scene_ = new GameScene();
	BaseScene* scene = new TitleScene();
	// �V�[���}�l�[�W���[�ɍŏ��̃V�[�����Z�b�g
	sceneManager_-> SetNextScene(scene);

#pragma endregion �`�揉��������
}

void MyGameEngine::Finalize()
{
	//���N���X�̏���������
	GameBase::Finalize();
}

void MyGameEngine::Update()
{
	GameBase::Update();
}

void MyGameEngine::Draw()
{
	GameBase::Draw();
}
