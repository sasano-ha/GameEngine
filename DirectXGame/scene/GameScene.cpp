#include "GameScene.h"
#include "Sound.h"
#include "input.h"
#include "DebugText.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "SafeDelete.h"


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

	//sprite->SetRotation(mousePos_);

	// OBJ���烂�f���f�[�^��ǂݍ���
	model_1 = Model::LoadFromOBJ("boll");
	model_2 = Model::LoadFromOBJ("triangle_mat");
	// 3D�I�u�W�F�N�g����
	object3d_1 = Object3d::Create();
	object3d_2 = Object3d::Create();
	object3d_3 = Object3d::Create();
	// 3D�I�u�W�F�N�g��3D���f�����Ђ��Â�
	object3d_1->SetModel(model_1);
	object3d_2->SetModel(model_2);
	object3d_3->SetModel(model_2);

	object3d_1->SetScale({ 5.0f, 5.0f, 5.0f });
	object3d_2->SetScale({ 20.0f, 20.0f, 20.0f });
	object3d_3->SetScale({ 30.0f, 30.0f, 30.0f });

	object3d_1->SetPosition({ -5, 0, -5 });
	object3d_2->SetPosition({ -5, 0, -5 });
	object3d_3->SetPosition({ +5, 0, +5 });

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
	safedelete(model_1);
	safedelete(model_2);

	// 3D�I�u�W�F�N�g���
	safedelete(object3d_1);
	safedelete(object3d_2);
	safedelete(object3d_3);

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

	if (input->PushKey(DIK_W)) {
		object3d_1->SetPosition(object3d_1->GetPosition()+ speed_);
	}

	sprite_2->SetPosition(XMFLOAT3{float(input->GetInstance()->MousePos().x) - 100, float(input->GetInstance()->MousePos().y) - 100, 0 });

	if (input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{

	}

	DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
	DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);



	//3D�I�u�W�F�N�g�X�V
	object3d_1->Update();
	/*object3d_2->Update();
	object3d_3->Update();*/

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
	object3d_1->Draw();
	//object3d_2->Draw();
	//object3d_3->Draw();

	//fbxobject_1->Draw(dxCommon->GetCmdList());

	//3D�I�u�W�F�N�g�̕`��㏈��
	Object3d::PostDraw();
}
