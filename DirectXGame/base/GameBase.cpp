#include "GameBase.h"
#include "FbxObject3d.h"

void GameBase::Initialize()
{
	//windowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();


	MSG msg{};  // メッセージ
#pragma endregion WindowsAPI初期化

#pragma region DirectX初期化処理

	//DirectXの初期化
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	// DirectX初期化処理　ここから

	//入力の初期化
	input = Input::GetInstance();
	input->Initialize(winApp);

	//オーディオの初期化
	audio = Sound::GetInstance();
	audio->Initialize();

	// 音声読み込み
	audio->LoadWave("Alarm01.wav");
	// 音声再生
	//audio->PlayWave("Alarm01.wav");

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::windows_width, WinApp::windows_height);
	// FBXローダーの初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDev());

	// デバイスをセット
	FbxObject3d::SetDevice(dxCommon->GetDev());
	camera_ = new Camera(1280, 720);
	// カメラをセット
	FbxObject3d::SetCamera(camera_);
	// カメラ注視点をセット
	camera_->SetTarget({ 0, 5, 0 });
	camera_->SetEye({ 0, 5, 10 });
	// グラフィックスパイプライン生成
	FbxObject3d::CreateGraphicsPipeline();
}

void GameBase::Finalize()
{
	// FBXローダーの解放
	FbxLoader::GetInstance()->Finalize();
	// シーンファクトリ解放
	delete sceneFactory_;
	
	//DirectX解放
	delete dxCommon;

	//windowsAPIの終了処理
	winApp->Finalize();

	// WindowsAPI解放
	delete winApp;

	//オーディオ解放
	audio->Finalize();
}

void GameBase::Update()
{
	//windowsのメッセージ処理
	if (winApp->ProcessMessage()) {
		//ゲームループを抜ける
		endRequst_ = true;
		return;
	}

	input->Update();
	camera_->Update();

	// シーンの更新
	SceneManager::GetInstance()->Update();
}

void GameBase::Draw()
{
	SceneManager::GetInstance()->Draw(dxCommon);
}
