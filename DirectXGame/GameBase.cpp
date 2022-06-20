#include "GameBase.h"

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

	// スプライト共通部分の初期化
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->windows_width, winApp->windows_height);

	//デバッグテキスト
	debugText = new DebugText();
	// デバッグテキスト用のテクスチャ番号を指定
	const int debugTextTexNumber = 0;
	// デバッグテキスト用のテクスチャ読み込み
	spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText->Initialize(spriteCommon, debugTextTexNumber);


	//入力の初期化
	input = new Input();
	input->Initialize(winApp);

	//オーディオの初期化
	audio = new Sound();
	audio->Initialize();

	// 音声読み込み
	audio->LoadWave("Alarm01.wav");
	// 音声再生
	audio->PlayWave("Alarm01.wav");

	//3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::windows_width, WinApp::windows_height);
}

void GameBase::Finalize()
{
	// デバッグテキスト解放
	debugText->Finalize();
	delete debugText;

	// スプライト共通部解放
	delete spriteCommon;

	//オーディオ解放
	audio->Finalize();
	delete audio;

	//DirectX解放
	delete dxCommon;

	// 入力解放
	delete input;

	//windowsAPIの終了処理
	winApp->Finalize();
	// WindowsAPI解放
	delete winApp;
}

void GameBase::Update()
{
	GameBase::Update();

	//windowsのメッセージ処理
	if (winApp->ProcessMessage()) {
		//ゲームループを抜ける
		endRequst_ = true;
		return;
	}

	input->Update();
}
