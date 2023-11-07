#include "Input.h"


namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr; //�L�[�{�[�h�̂𓮂������߂̕ϐ��B
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256];    //�O�t���[���ł̊e�L�[�̏��
	XMVECTOR mousePosition; //�}�E�X�̃|�W�V����

	

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr); 
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr); //�f�o�C�X�I�u�W�F�N�g���쐬
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard); //�f�o�C�X�̎�ނ�ݒ�
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);//�������x���̐ݒ�����Ă���
	}

	void Update()
	{
		memcpy(prevKeyState, keyState, sizeof(keyState));

		pKeyDevice->Acquire();//����͕K�������Ȃ��ƃ_���I
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState); //�L�[�̏�Ԃ��킩��
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80) //0x��16�i�̂���
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode)&& !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//�O��͉����ĂāA���͉����ĂȂ�
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

