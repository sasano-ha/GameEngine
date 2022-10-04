#include "GameScene.h"
#include "Sound.h"
#include "input.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "SafeDelete.h"
#include "Player.h"


void GameScene::Initialize()
{
	SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/gameplay.png");
	SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/cursor.png");
	//SpriteCommon::GetInstance()->LoadTexture(100, L"Resources/white1x1.png");

	// �X�v���C�g���ʃe�N�X�`���ǂݍ���
	//spriteCommon->LoadTexture(1, L"Resources/gameplay.png");
	//spriteCommon->LoadTexture(2, L"Resources/house.png");

	// �X�v���C�g�̐���
	sprite_1 = Sprite::Create(1, { 0, 0 }, false, false);
	sprite_2 = Sprite::Create(2, { 0, 0 }, false, false);
	sprite_2->SetPosition({ 0, 0, 0});

	player_ = new Player();
	player_->Initialze();

	enemy_[2] = new Enemy();
	enemy_[2]->Initialze();

	/*bullet_ = new Bullet();
	bullet_->Initialze();*/

	// OBJ���烂�f���f�[�^��ǂݍ���
	//bullet = Object3d::Create();


	// 3D�I�u�W�F�N�g��3D���f�����Ђ��Â�
	//bullet->SetModel(model_1);

	// scale�̐ݒ�
	//bullet->SetScale({ 2.0f, 2.0f, 2.0f });

	// position�̐ݒ�
	//bullet->SetPosition({ -5, 0, -5 });

	// �����ǂݍ���
	Sound::GetInstance()->LoadWave("Alarm01.wav");
	// �����Đ�
	//audio->PlayWave("Alarm01.wav");

	// ���f�������w�肵�ăt�@�C���ǂݍ���
	//FbxLoader::GetInstance()->LoadModelFromFile("cube");
	fbxmodel_1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	fbxobject_1 = new FbxObject3d;
	fbxobject_1->Initialize();
	fbxobject_1->SetModel(fbxmodel_1);
}

void GameScene::Finalize()
{
	// �X�v���C�g���
	safedelete(sprite_1);
	safedelete(sprite_2);

	// 3D�I�u�W�F�N�g���

	player_->Finalize();
	enemy_[2]->Finalize();
	/*bullet_->Finalize();*/
	
	//safedelete(bullet);

	safedelete(fbxobject_1);
	safedelete(fbxmodel_1);
}

void GameScene::Update()
{

	Input* input = Input::GetInstance();

	//if (input->TriggerKey(DIK_SPACE))
	//{
	//	// �V�[���؂�ւ�
	//	SceneManager::GetInstance()->ChangeScene("TITLE");
	//}

	if (input->TriggerKey(DIK_0))
	{
		fbxobject_1->PlayAnimation();
	}

	// ���W����
	//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	//{

	//}

	// space��������
	/*if (input->TriggerKey(DIK_SPACE)) {
		bullet->SetPosition(player->GetPosition());
		bulletFlag = true;
	}

	if (bulletFlag == true) {
		bullet->SetPosition(bullet->GetPosition() + Vector3(0, 0, speed));
		if (bullet->GetPosition().z > 120) {
			bulletFlag = false;
		}
	}

	for (int i = 0; i < 3; i++) {
		float distance = (enemy[i]->GetPosition().x - bullet->GetPosition().x) * (enemy[i]->GetPosition().x - bullet->GetPosition().x) +
			(enemy[i]->GetPosition().y - bullet->GetPosition().y) + (enemy[i]->GetPosition().z - bullet->GetPosition().z);
		if (distance <= bulletRadius + enemuyRadius[i]) {
			enemyFlag[i] = false;
			bulletFlag = false;
		}
	}*/
	
	

	sprite_2->SetPosition(XMFLOAT3{float(input->GetInstance()->MousePos().x) - 100, float(input->GetInstance()->MousePos().y) - 100, 0 });

	//DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
	DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);

	if (input->PushMouseLeft()) {
		DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
	}


	//3D�I�u�W�F�N�g�X�V
	player_->Update();
	enemy_[2]->Update();
	//bullet_->Update();

	//fbxobject_1->Updata();

	//�X�v���C�g�X�V
	sprite_1->Update();
	sprite_2->Update();
}

void GameScene::Draw(DirectXCommon* dxCommon)
{
	// �X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->PreDraw();

	// �X�v���C�g�`��
	sprite_1->Draw();
	sprite_2->Draw();

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw();

	//3D�I�u�W�F�N�g�̕`��
	player_->Draw();
	enemy_[2]->Draw();
	//bullet_->Draw();
	/*if (bulletFlag == true) {
		bullet->Draw();
	}*/
	

	//fbxobject_1->Draw(dxCommon->GetCmdList());

	//3D�I�u�W�F�N�g�̕`��㏈��
	Object3d::PostDraw();
}
