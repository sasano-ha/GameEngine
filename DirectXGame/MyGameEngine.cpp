#include "MyGameEngine.h"
#include "SceneFactory.h"

void MyGameEngine::Initialize()
{
	//基底クラスの初期化処理
	GameBase::Initialize();

#pragma region 描画初期化処理
	// シーンファクトリ生成し、マネージャーにセット
	sceneFactory_ = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory_);

	// シーンマネージャーに最初のシーンをセット
	SceneManager::GetInstance()-> ChangeScene("TITLE");

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
