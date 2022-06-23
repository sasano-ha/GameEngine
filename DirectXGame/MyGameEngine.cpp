#include "MyGameEngine.h"
#include "GameScene.h"

void MyGameEngine::Initialize()
{
	//基底クラスの初期化処理
	GameBase::Initialize();

#pragma region 描画初期化処理
	scene_ = new GameScene();
	scene_->Initialize();

#pragma endregion 描画初期化処理
}

void MyGameEngine::Finalize()
{
	//基底クラスの初期化処理
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
	//描画前処理
	dxCommon->PreDraw();

	scene_->Draw();

	// デバッグテキスト描画
	debugText->DrawAll();

	// ４．描画コマンドここまで

	//描画後処理
	dxCommon->PostDraw();
}
