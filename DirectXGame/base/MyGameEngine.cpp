#include "MyGameEngine.h"


void MyGameEngine::Initialize()
{
	//基底クラスの初期化処理
	GameBase::Initialize();

#pragma region 描画初期化処理

	SceneManager::GetInstance()->Initialze(dxCommon, winApp);

#pragma endregion 描画初期化処理
}

void MyGameEngine::Finalize()
{
	//基底クラスの初期化処理
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
