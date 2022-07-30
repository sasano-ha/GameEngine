#include "TitleScene.h"
#include "SceneManager.h"
#include "Sound.h"
#include "input.h"
#include "DebugText.h"

void TitleScene::Initialize()
{
	SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/title.png");

	// スプライトの生成
	sprite = Sprite::Create(1, { 0,0 }, false, false);
}

void TitleScene::Finalize()
{
	// スプライト解放
	delete sprite;
}

void TitleScene::Update()
{

	Input* input = Input::GetInstance();

	// 座標操作
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{

	}

	if (input->TriggerKey(DIK_1))
	{
		// シーン切り替え
		SceneManager::GetInstance()->ChangeScene("GAME");
	}

	//スプライト更新
	sprite->Update();
}

void TitleScene::Draw(DirectXCommon* dxCommon)
{
	// スプライト共通コマンド
	SpriteCommon::GetInstance()->PreDraw();

	// スプライト描画
	sprite->Draw();

	// スプライト共通コマンド
	SpriteCommon::GetInstance()->PreDraw();
}