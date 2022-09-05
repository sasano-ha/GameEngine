#include "Enemy.h"
#include "SafeDelete.h"


void Enemy::Initialze()
{
	// OBJ���烂�f���f�[�^��ǂݍ���
	model_2 = Model::LoadFromOBJ("triangle_mat");

	// 3D�I�u�W�F�N�g����
	for (int i = 0; i < 3; i++) {
		enemy[i] = Object3d::Create();
	}

	// 3D�I�u�W�F�N�g��3D���f�����Ђ��Â�
	for (int i = 0; i < 3; i++) {
		enemy[i]->SetModel(model_2);
	}

	// scale�̐ݒ�
	for (int i = 0; i < 3; i++) {
		enemy[i]->SetScale({ 20.0f, 20.0f, 20.0f });
	}

	// position�̐ݒ�
	enemy[0]->SetPosition({ -70, 0, 100 });
	enemy[1]->SetPosition({ 0, 0, 100 });
	enemy[2]->SetPosition({ 70, 0, 100 });
}

void Enemy::Finalize()
{
	// 3D�I�u�W�F�N�g���
	safedelete(model_2);

	for (int i = 0; i < 3; i++) {
		safedelete(enemy[i]);
	}
}

void Enemy::Update()
{
	for (int i = 0; i < 3; i++) {
		enemy[i]->Update();
	}
}

void Enemy::Draw()
{
	for (int i = 0; i < 3; i++) {
		if (enemyFlag[i] == true) {
			enemy[i]->Draw();
		}
	}
}
