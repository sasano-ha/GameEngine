#include "PlayerBullet.h"
#include "SafeDelete.h"
#include "input.h"
#include "Enemy.h"

void PlayerBullet::Initialze(const Vector3& position, const Vector3& velocity)
{
	// OBJからモデルデータを読み込む
	model_3 = Model::LoadFromOBJ("boll");

	// 3Dオブジェクト生成
	bullet = Object3d::Create();

	//3Dオブジェクトに3Dモデルをひもづけ
	bullet->SetModel(model_3);

	// scaleの設定
	bullet->SetScale({ 2.0f, 2.0f, 2.0f });

	// positionの設定
	bullet->SetPosition(position);

	velocity_ = velocity;
}

void PlayerBullet::Finalize()
{
	safedelete(model_3);
	safedelete(bullet);
}

void PlayerBullet::Update()
{
	bullet->SetPosition(bullet->GetPosition() + velocity_);

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	bullet->Update();
}

void PlayerBullet::Draw()
{
	bullet->Draw();
}
