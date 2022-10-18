#include "Player.h"
#include "SafeDelete.h"
#include "input.h"
#include "Vector3.h"
#include "PlayerBullet.h"


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
	//safedelete(bullet_);
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

	if (input->TriggerKey(DIK_SPACE)) {
		Player::Attack();
	}

	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		}
	);

	//3Dオブジェクト更新
	player->Update();

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}


}

void Player::Draw()
{
	//3Dオブジェクトの描画
	player->Draw();
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw();
	}
}

void Player::Attack()
{
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
	newBullet->Initialze(player->GetPosition(), velocity);

	//弾を登録する
	bullets_.push_back(std::move(newBullet));
}
