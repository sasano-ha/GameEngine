#include "MyGameEngine.h"


void MyGameEngine::Initialize()
{
	//���N���X�̏���������
	GameBase::Initialize();

#pragma region �`�揉��������

	SceneManager::GetInstance()->Initialze(dxCommon, winApp);

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
