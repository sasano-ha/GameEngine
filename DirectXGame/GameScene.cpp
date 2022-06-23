#include "GameScene.h"
#include "Sound.h"
#include "input.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "SceneManager.h"

void GameScene::Initialize()
{
	SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/gameplay.png");

	// �X�v���C�g���ʃe�N�X�`���ǂݍ���
	//spriteCommon->LoadTexture(1, L"Resources/gameplay.png");
	//spriteCommon->LoadTexture(2, L"Resources/house.png");

	// �X�v���C�g�̐���
	sprite = Sprite::Create(1, { 0,0 }, false, false);

	//OBJ���烂�f���f�[�^��ǂݍ���
	model_1 = Model::LoadFromOBJ("ground");
	model_2 = Model::LoadFromOBJ("triangle_mat");
	//3D�I�u�W�F�N�g����
	object3d_1 = Object3d::Create();
	object3d_2 = Object3d::Create();
	object3d_3 = Object3d::Create();
	//3D�I�u�W�F�N�g��3D���f�����Ђ��Â�
	object3d_1->SetModel(model_1);
	object3d_2->SetModel(model_2);
	object3d_3->SetModel(model_2);

	object3d_2->SetScale({ 20.0f, 20.0f, 20.0f });
	object3d_3->SetScale({ 30.0f, 30.0f, 30.0f });

	object3d_2->SetPosition({ -5, 0, -5 });
	object3d_3->SetPosition({ +5, 0, +5 });

	// �����ǂݍ���
	Sound::GetInstance()->LoadWave("Alarm01.wav");
	// �����Đ�
	//audio->PlayWave("Alarm01.wav");
}

void GameScene::Finalize()
{
	// �X�v���C�g���
	delete sprite;

	// 3D�I�u�W�F�N�g���
	delete model_1;
	delete model_2;

	// 3D�I�u�W�F�N�g���
	delete object3d_1;
	delete object3d_2;
	delete object3d_3;
}

void GameScene::Update()
{

	Input* input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE))
	{
		// �V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	// ���W����
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{

	}

	if (input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{

	}

	DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
	DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);

	//3D�I�u�W�F�N�g�X�V
	object3d_1->Update();
	object3d_2->Update();
	object3d_3->Update();

	//�X�v���C�g�X�V
	sprite->Update();
}

void GameScene::Draw()
{
	// �X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->PreDraw();

	// �X�v���C�g�`��
	sprite->Draw();

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw();

	//3D�I�u�W�F�N�g�̕`��
	object3d_1->Draw();
	object3d_2->Draw();
	object3d_3->Draw();

	//3D�I�u�W�F�N�g�̕`��㏈��
	Object3d::PostDraw();

	// �X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->PreDraw();
}
