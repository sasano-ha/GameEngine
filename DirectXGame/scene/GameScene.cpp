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

	// スプライト共通テクスチャ読み込み
	//spriteCommon->LoadTexture(1, L"Resources/gameplay.png");
	//spriteCommon->LoadTexture(2, L"Resources/house.png");

	// スプライトの生成
	sprite_1 = Sprite::Create(1, { 0, 0 }, false, false);
	sprite_2 = Sprite::Create(2, { 0, 0 }, false, false);
	sprite_2->SetPosition({ 0, 0, 0});

	//sprite->SetRotation(mousePos_);

	// OBJからモデルデータを読み込む
	model_1 = Model::LoadFromOBJ("boll");
	model_2 = Model::LoadFromOBJ("triangle_mat");
	// 3Dオブジェクト生成
	player = Object3d::Create();
	for (int i = 0; i < 3; i++) {
		enemy[i] = Object3d::Create();
	}
	bullet = Object3d::Create();


	// 3Dオブジェクトに3Dモデルをひもづけ
	player->SetModel(model_1);
	for (int i = 0; i < 3; i++) {
		enemy[i]->SetModel(model_2);
	}
	bullet->SetModel(model_1);

	// scaleの設定
	player->SetScale({ 3.0f, 3.0f, 3.0f });
	for (int i = 0; i < 3; i++) {
		enemy[i]->SetScale({ 20.0f, 20.0f, 20.0f });
	}
	bullet->SetScale({ 2.0f, 2.0f, 2.0f });

	// positionの設定
	player->SetPosition({ -5, 0, -5 });
	enemy[0]->SetPosition({ -70, 0, 100 });
	enemy[1]->SetPosition({   0, 0, 100 });
	enemy[2]->SetPosition({  70, 0, 100});
	bullet->SetPosition({ -5, 0, -5 });

	// 音声読み込み
	Sound::GetInstance()->LoadWave("Alarm01.wav");
	// 音声再生
	//audio->PlayWave("Alarm01.wav");

	// モデル名を指定してファイル読み込み
	//FbxLoader::GetInstance()->LoadModelFromFile("cube");
	fbxmodel_1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	fbxobject_1 = new FbxObject3d;
	fbxobject_1->Initialize();
	fbxobject_1->SetModel(fbxmodel_1);
}

void GameScene::Finalize()
{
	// スプライト解放
	safedelete(sprite_1);
	safedelete(sprite_2);

	// 3Dオブジェクト解放
	safedelete(model_1);
	safedelete(model_2);

	// 3Dオブジェクト解放
	safedelete(player);

	for (int i = 0; i < 3; i++) {
		safedelete(enemy[i]);
	}
	
	safedelete(bullet);

	safedelete(fbxobject_1);
	safedelete(fbxmodel_1);
}

void GameScene::Update()
{

	Input* input = Input::GetInstance();

	//if (input->TriggerKey(DIK_SPACE))
	//{
	//	// シーン切り替え
	//	SceneManager::GetInstance()->ChangeScene("TITLE");
	//}

	if (input->TriggerKey(DIK_0))
	{
		fbxobject_1->PlayAnimation();
	}

	// 座標操作
	//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	//{

	//}


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

	// space押した時
	if (input->TriggerKey(DIK_SPACE)) {
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
	}
	

	sprite_2->SetPosition(XMFLOAT3{float(input->GetInstance()->MousePos().x) - 100, float(input->GetInstance()->MousePos().y) - 100, 0 });

	//DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
	DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);

	if (input->PushMouseLeft()) {
		DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
	}


	//3Dオブジェクト更新
	player->Update();

	for (int i = 0; i < 3; i++) {
		enemy[i]->Update();
	}
	
	bullet->Update();

	//fbxobject_1->Updata();

	//スプライト更新
	sprite_1->Update();
	sprite_2->Update();
}

void GameScene::Draw(DirectXCommon* dxCommon)
{
	// スプライト共通コマンド
	SpriteCommon::GetInstance()->PreDraw();

	// スプライト描画
	sprite_1->Draw();
	sprite_2->Draw();

	//3Dオブジェクト描画前処理
	Object3d::PreDraw();

	//3Dオブジェクトの描画
	player->Draw();

	for (int i = 0; i < 3; i++) {
		if (enemyFlag[i] == true) {
			enemy[i]->Draw();
		}
	}
	
	if (bulletFlag == true) {
		bullet->Draw();
	}
	

	//fbxobject_1->Draw(dxCommon->GetCmdList());

	//3Dオブジェクトの描画後処理
	Object3d::PostDraw();
}
