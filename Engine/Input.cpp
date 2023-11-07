#include "Input.h"


namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr; //キーボードのを動かすための変数。
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256];    //前フレームでの各キーの状態
	XMVECTOR mousePosition; //マウスのポジション

	

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr); 
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr); //デバイスオブジェクトを作成
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard); //デバイスの種類を設定
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);//強調レベルの設定をしている
	}

	void Update()
	{
		memcpy(prevKeyState, keyState, sizeof(keyState));

		pKeyDevice->Acquire();//これは必ず書かないとダメ！
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState); //キーの状態がわかる
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80) //0xは16進のこと
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if (IsKey(keyCode)&& !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//前回は押してて、今は押してない
		if  (!(prevKeyState[keyCode] & 0x80) && IsKey(keyCode))
		{
			return true;
		}
		return false;
	}

	XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
		SAFE_RELEASE(pKeyDevice);
	}
}

