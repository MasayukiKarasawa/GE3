#include "input.h"

#include<cassert>


using namespace Microsoft::WRL;

void input::Initalize(HINSTANCE hInstance, HWND hwnd)
{
    HRESULT result;

    // DirectInputの初期化
    ComPtr<IDirectInput8> directInput;
    result = DirectInput8Create(
        hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

    // キーボードデバイスの生成
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    // 入力データ形式のセット
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
    assert(SUCCEEDED(result));
    // 排他制御レベルのセット
    result = keyboard->SetCooperativeLevel(
        hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

void input::Updete()
{
    //keyPreの中にkeyの情報をコピーする
    memcpy(keyPre, key, sizeof(key));

    // キーボード情報の取得開始
    keyboard->Acquire();
    // 全キーの入力状態を取得する
    keyboard->GetDeviceState(sizeof(key), key);

}

bool input::PushKey(BYTE keyNumber)
{
    //指定キーを押していればをtrue返す
    if (key[keyNumber]) {
        return true;
    }
    //そうでなければfalseを返す
    return false;
}

bool input::TriggerKey(BYTE keyNumber)
{
    if (key[keyNumber]&& keyPre[keyNumber] == 0) {
        return true;
    }
    return false;
}
