#include "MyGameEngine.h"
#include "SceneFactory.h"

void MyGameEngine::Initialize()
{
	//���N���X�̏���������
	GameBase::Initialize();

#pragma region �`�揉��������
	// �V�[���t�@�N�g���������A�}�l�[�W���[�ɃZ�b�g
	sceneFactory_ = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory_);

	// �V�[���}�l�[�W���[�ɍŏ��̃V�[�����Z�b�g
	SceneManager::GetInstance()-> ChangeScene("TITLE");

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
