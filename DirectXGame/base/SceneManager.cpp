#include "SceneManager.h"
#include "SafeDelete.h"
#include "SceneFactory.h"


#include <cassert>

SceneManager::~SceneManager()
{
	// 最後のシーンの終了と解放
	scene_->Finalize();
	delete scene_;

	safedelete(posteffect_);

	// デバッグテキスト解放
	debugText->Finalize();
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;

	return &instance;
}

void SceneManager::Initialze(DirectXCommon* dxCommon, WinApp* winApp)
{
	// シーンファクトリ生成し、マネージャーにセット
	sceneFactory_ = new SceneFactory();
	SetSceneFactory(sceneFactory_);

	// シーンマネージャーに最初のシーンをセット
	ChangeScene("TITLE");

	// スプライト共通部分の初期化
	spritecommon = SpriteCommon::GetInstance();
	spritecommon->Initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->windows_width, winApp->windows_height);

	//デバッグテキスト
	debugText = DebugText::GetInstance();
	// デバッグテキスト用のテクスチャ番号を指定
	const int debugTextTexNumber = 0;
	// デバッグテキスト用のテクスチャ読み込み
	spritecommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText->Initialize(spritecommon, debugTextTexNumber);

	posteffect_ = new PostEffect();
	posteffect_->SizeInitialize(100, { 500,500 }, { 0, 0 }, false, false);

	posteffect_->Initialize();
}

void SceneManager::Update()
{
	// シーン切り替えがあるなら
	if (nextScene_) {
		if (scene_) {
			// 旧シーンの終了
			scene_->Finalize();
			delete scene_;
		}

		// シーン切り替え
		scene_ = nextScene_;
		nextScene_ = nullptr;

		// 新シーンの初期化
		scene_->Initialize();
	}

	scene_->Update();
	//posteffect_->Update();
}

void SceneManager::Draw(DirectXCommon* dxCommon)
{
	// レンダーテクスチャへの描画
	//posteffect_->PreDrawScene(dxCommon->GetCmdList());
	//posteffect_->PostDrawScene(dxCommon->GetCmdList());


	//描画前処理
	dxCommon->PreDraw();

	//posteffect_->Draw(dxCommon->GetCmdList());

	spritecommon->PreDraw();
	scene_->Draw(dxCommon);
	// デバッグテキスト描画
	//debugText->DrawAll();

	//描画後処理
	dxCommon->PostDraw();
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory_);
	assert(nextScene_ == nullptr);

	// 次シーンを生成
	nextScene_ =  sceneFactory_->CreateScene(sceneName);
}
