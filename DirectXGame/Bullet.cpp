#include "Bullet.h"
#include "SafeDelete.h"
#include "input.h"
#include "Player.h"
#include "Enemy.h"

void Bullet::Initialze()
{
	// OBJ���烂�f���f�[�^��ǂݍ���
	model_3 = Model::LoadFromOBJ("boll");

	// 3D�I�u�W�F�N�g����
	bullet = Object3d::Create();

	// scale�̐ݒ�
	bullet->SetScale({ 2.0f, 2.0f, 2.0f });

	// position�̐ݒ�
	bullet->SetPosition({ -5, 0, -5 });
}

void Bullet::Finalize()
{
	safedelete(bullet);
}

void Bullet::Update()
{
	Input* input = Input::GetInstance();

	//// space��������
	//if (input->TriggerKey(DIK_SPACE)) {
	//	bullet->SetPosition(player->GetPosition());
	//	bulletFlag = true;
	//}

	//if (bulletFlag == true) {
	//	bullet->SetPosition(bullet->GetPosition() + Vector3(0, 0, speed));
	//	if (bullet->GetPosition().z > 120) {
	//		bulletFlag = false;
	//	}
	//}
}

void Bullet::Draw()
{
	if (bulletFlag == true) {
		bullet->Draw();
	}
}
