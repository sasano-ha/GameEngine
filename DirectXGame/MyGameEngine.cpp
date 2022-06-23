#include "MyGameEngine.h"
#include "GameScene.h"
#include "TitleScene.h"

void MyGameEngine::Initialize()
{
	//基底クラスの初期化処理
	GameBase::Initialize();

#pragma region 描画初期化処理
	//scene_ = new GameScene();
	BaseScene* scene = new TitleScene();
	// シーンマネージャーに最初のシーンをセット
	sceneManager_-> SetNextScene(scene);

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
