#include "Player.h"
#include "SafeDelete.h"
#include "input.h"
#include "Vector3.h"
#include "PlayerBullet.h"


void Player::Initialze()
{
	// OBJ���烂�f���f�[�^��ǂݍ���
	model_1 = Model::LoadFromOBJ("boll");

	// 3D�I�u�W�F�N�g����
	player = Object3d::Create();

	// 3D�I�u�W�F�N�g��3D���f�����Ђ��Â�
	player->SetModel(model_1);

	// scale�̐ݒ�
	player->SetScale({ 3.0f, 3.0f, 3.0f });

	// position�̐ݒ�
	player->SetPosition({ -5, 0, -5 });
}

void Player::Finalize()
{
	// 3D�I�u�W�F�N�g���
	safedelete(model_1);

	// 3D�I�u�W�F�N�g���
	safedelete(player);
	//safedelete(bullet_);
}

void Player::Update()
{
	Input* input = Input::GetInstance();

	// ���@�̑���
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

	//3D�I�u�W�F�N�g�X�V
	player->Update();

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}


}

void Player::Draw()
{
	//3D�I�u�W�F�N�g�̕`��
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

	//�e��o�^����
	bullets_.push_back(std::move(newBullet));
}
