#include "input.h"
#include "Object3d.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


Input* Input::GetInstance()
{
    static Input instance;

    return &instance;
}

void Input::Initialize(WinApp* winApp)
{
    HRESULT result;

    //借りてきたWinAppのインスタンスを記録
    this->winApp = winApp;

    // DirectInputオブジェクトの生成
    result = DirectInput8Create(
        winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);

    //キーボードデバイス生成
    result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);

    // マウスデバイスの生成	
    result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);

    // 入力データ形式セット
    result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式

    // 排他的制御レベルのセット
    result = devkeyboard->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

    // 入力データ形式のセット
    result = devMouse->SetDataFormat(&c_dfDIMouse2); // 標準形式

    // 排他制御レベルのセット
    result = devMouse->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update()
{
    HRESULT result;

    // 前回のキー入力を保存
    memcpy(keyPre, key, sizeof(key));

    // キーボード情報の取得開始
    result = devkeyboard->Acquire();

    // 全キーの入力情報を取得する
    result = devkeyboard->GetDeviceState(sizeof(key), key);

    // マウス情報の取得開始
    result = devMouse->Acquire();

    // 前回の入力を保存
    mouseStatePre = mouseState;

    // マウスの入力
    result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);

    MousePos();
}

POINT Input::MousePos()
{
    GetCursorPos(&mousePos_);
    // 取得したスクリーン座標をウィンドウ座標に変換する
    ScreenToClient(winApp->GetHwnd(), &mousePos_);

    return mousePos_;
}

bool Input::PushKey(BYTE keyNumber)
{
    // 指定キーを押していればtrueを返す
    if (key[keyNumber]) {
        return true;
    }
    // そうでなければfalseを返す
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    if (!keyPre[keyNumber] && key[keyNumber]) {
        return true;
    }
    return false;
}

bool Input::PushMouseLeft()
{
    // 左クリックを押している
    if (mouseState.rgbButtons[0]) {
        return true;
    }
    // 押していない
    return false;
}

bool Input::PushMouseRight()
{
    // 右クリックを押している
    if (mouseState.rgbButtons[1]) {
        return true;
    }
    // 押していない
    return false;
}

bool Input::PushMouseMiddle()
{
    // 中心クリックを押している
    if (mouseState.rgbButtons[2]) {
        return true;
    }
    // 押していない
    return false;
}

bool Input::TriggerMouseLeft()
{
    // 前回が0で、今回が0でなければトリガー
    if (!mouseStatePre.rgbButtons[0] && mouseState.rgbButtons[0]) {
        return true;
    }

    // トリガーでない
    return false;
}

bool Input::TriggerMouseRight()
{
    // 前回が0で、今回が0でなければトリガー
    if (!mouseStatePre.rgbButtons[1] && mouseState.rgbButtons[1]) {
        return true;
    }

    // トリガーでない
    return false;
}

bool Input::TriggerMouseMiddle()
{
    // 前回が0で、今回が0でなければトリガー
    if (!mouseStatePre.rgbButtons[2] && mouseState.rgbButtons[2]) {
        return true;
    }

    // トリガーでない
    return false;
}
