#include "Player.h"
#include "SafeDelete.h"
#include "input.h"


void Player::Initialze()
{
	// OBJからモデルデータを読み込む
	model_1 = Model::LoadFromOBJ("boll");

	// 3Dオブジェクト生成
	player = Object3d::Create();

	// 3Dオブジェクトに3Dモデルをひもづけ
	player->SetModel(model_1);

	// scaleの設定
	player->SetScale({ 3.0f, 3.0f, 3.0f });

	// positionの設定
	player->SetPosition({ -5, 0, -5 });
}

void Player::Finalize()
{
	// 3Dオブジェクト解放
	safedelete(model_1);

	// 3Dオブジェクト解放
	safedelete(player);
}

void Player::Update()
{
	Input* input = Input::GetInstance();

	// 自機の操作
	if (input->PushKey(DIK_W)) {
		player->SetPosition(player->GetPosition() + Vector3(0, speed, 0));
	}
	else if (input->PushKey(DIK_S)) {
		player->SetPosition(player->GetPosition() + Vector3(0, -speed, 0));
	}
	else if (input->PushKey(DIK_A)) {
		player->SetPosition(player->GetPosition() + Vector3(-speed, 0, 0));
	}
	else if (input->PushKey(DIK_D)) {
		player->SetPosition(player->GetPosition() + Vector3(speed, 0, 0));
	}

	//3Dオブジェクト更新
	player->Update();
}

void Player::Draw()
{
	//3Dオブジェクトの描画
	player->Draw();
}
