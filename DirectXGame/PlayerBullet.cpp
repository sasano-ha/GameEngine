#include "PlayerBullet.h"
#include "SafeDelete.h"
#include "input.h"
#include "Enemy.h"

void PlayerBullet::Initialze(const Vector3& position, const Vector3& velocity)
{
	// OBJ���烂�f���f�[�^��ǂݍ���
	model_3 = Model::LoadFromOBJ("boll");

	// 3D�I�u�W�F�N�g����
	bullet = Object3d::Create();

	//3D�I�u�W�F�N�g��3D���f�����Ђ��Â�
	bullet->SetModel(model_3);

	// scale�̐ݒ�
	bullet->SetScale({ 2.0f, 2.0f, 2.0f });

	// position�̐ݒ�
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
