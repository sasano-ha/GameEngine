#include "MyGameEngine.h"

void MyGameEngine::Initialize()
{
	//基底クラスの初期化処理
	GameBase::Initialize();

#pragma region 描画初期化処理

	//OBJからモデルデータを読み込む
	model_1 = Model::LoadFromOBJ("ground");
	model_2 = Model::LoadFromOBJ("triangle_mat");
	//3Dオブジェクト生成
	object3d_1 = Object3d::Create();
	object3d_2 = Object3d::Create();
	object3d_3 = Object3d::Create();
	//3Dオブジェクトに3Dモデルをひもづけ
	object3d_1->SetModel(model_1);
	object3d_2->SetModel(model_2);
	object3d_3->SetModel(model_2);

	object3d_2->SetScale({ 20.0f, 20.0f, 20.0f });
	object3d_3->SetScale({ 30.0f, 30.0f, 30.0f });


	object3d_2->SetPosition({ -5, 0, -5 });
	object3d_3->SetPosition({ +5, 0, +5 });

	//// 音声読み込み
	//audio->LoadWave("Alarm01.wav");
	//// 音声再生
	//audio->PlayWave("Alarm01.wav");

	// スプライト共通テクスチャ読み込み
	spriteCommon->LoadTexture(1, L"Resources/texture.png");
	spriteCommon->LoadTexture(2, L"Resources/house.png");

	

	// スプライトの生成
	for (int i = 0; i < 20; i++)
	{
		int texNumber = 1;
		Sprite* sprite = Sprite::Create(spriteCommon, texNumber, { 0,0 }, false, false);

		// スプライトの座標変更
		sprite->SetPosition({ (float)(rand() % 1280), (float)(rand() % 720), 0 });
		sprite->SetRotation((float)(rand() % 360));
		sprite->SetSize({ (float)(rand() % 400), (float)(rand() % 400) });
		//sprites[i].isInvisible = true;
		//sprites[i].size.x = 400.0f;
		//sprites[i].size.y = 100.0f;
		// 頂点バッファに反映
		sprite->TransferVertexBuffer();

		sprites.push_back(sprite);
	}
#pragma endregion 描画初期化処理
}

void MyGameEngine::Finalize()
{
	

	// スプライト解放
	for (auto& sprite : sprites) {
		delete sprite;
	}
	sprites.clear();


	// 3Dオブジェクト解放
	delete model_1;
	delete model_2;

	// 3Dオブジェクト解放
	delete object3d_1;
	delete object3d_2;
	delete object3d_3;

	//基底クラスの初期化処理
	GameBase::Finalize();
}

void MyGameEngine::Update()
{
	

#pragma region DirectX毎フレーム処理
	// DirectX毎フレーム処理　ここから

	

	float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

	if (input->PushKey(DIK_SPACE))     // スペースキーが押されていたら
	{
		// 画面クリアカラーの数値を書き換える
		clearColor[1] = 1.0f;
	}

	// 座標操作
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{

	}

	if (input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{

	}

	debugText->Print("Hello,DirectX!!", 200, 100);
	debugText->Print("Nihon Kogakuin", 200, 200, 2.0f);

	//3Dオブジェクト更新
	object3d_1->Update();
	object3d_2->Update();
	object3d_3->Update();

	//スプライト更新
	for (auto& sprite : sprites) {
		sprite->Update();
	}

	// DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理
}

void MyGameEngine::Draw()
{
	//描画前処理
	dxCommon->PreDraw();

	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCmdList());

	//3Dオブジェクトの描画
	object3d_1->Draw();
	object3d_2->Draw();
	object3d_3->Draw();

	//3Dオブジェクトの描画後処理
	Object3d::PostDraw();

	// スプライト共通コマンド
	spriteCommon->PreDraw();

	for (auto& sprite : sprites) {
		sprite->Draw();
	}

	// デバッグテキスト描画
	debugText->DrawAll();

	// ４．描画コマンドここまで

	//描画後処理
	dxCommon->PostDraw();
}
