#pragma once

#include <windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION 0x0800  //DirectInputのバージョン指定
#include <dinput.h>
#include "WinApp.h"



// 入力
class Input final
{
public:
	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	struct MouseMove {
		LONG lX;	// マウスのX軸の傾きの情報
		LONG lY;	// マウスのY軸の傾きの情報
		LONG lZ;	// マウスのZ軸の傾きの情報
	};

public:// メンバ関数

	static Input* GetInstance();

	// 初期化
	void Initialize(WinApp* winApp);

	// 更新
	void Update();

	/// <summary>
	///	キー押したかをチェック
	/// </summary>
	/// <paragm name = "keyNumber">キー番号（DIK_0 等）</paragm>
	/// <returns>押されているか</return>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	///	キーのトリガーをチェック
	/// </summary>
	/// <paragm name = "keyNumber">キー番号（DIK_0 等）</paragm>
	/// <returns>トリガーか</return>
	bool TriggerKey(BYTE keyNumber);

	/// <summary>
	/// キーの左ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool PushMouseLeft();

	/// <summary>
	/// キーの左ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool PushMouseRight();

	/// <summary>
	/// キーの中ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool PushMouseMiddle();

	/// <summary>
	/// キーの左ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool TriggerMouseLeft();

	/// <summary>
	/// キーの左ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool TriggerMouseRight();

	/// <summary>
	/// キーの中ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガーか</returns>
	bool TriggerMouseMiddle();

	/// <summary>
	/// マウスの座標
	/// </summary>
	/// <returns></returns>
	POINT MousePos();

private:
	// コンストラクタをprivateにする
	Input() = default;
	// デストラクタをprivateとにする
	~Input() = default;
public:
	// コピーコンストラクタを無効にする
	Input(const Input& obj) = delete;
	// 代入演算子を無効にする
	Input& operator=(const Input& obj) = delete;


private:// メンバ関数
	// DirectInputのインスタンス生成
	ComPtr<IDirectInput8> dinput = nullptr;
	// キーボードのデバイス
	ComPtr<IDirectInputDevice8> devkeyboard;
	// マウスのデバイス
	ComPtr<IDirectInputDevice8> devMouse;
	// 全キーの状態
	BYTE key[256] = {};
	// 前回の全キーの状態
	BYTE keyPre[256] = {};
	// WindowsAPI
	WinApp* winApp = nullptr;
	// 全マウスの状態
	DIMOUSESTATE2 mouseState = {};
	// 前回マウスの状態（）
	DIMOUSESTATE2 mouseStatePre = {};
	POINT mousePos_;
};
