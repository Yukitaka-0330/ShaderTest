#pragma once
#include "Engine/GameObject.h"
#include "ColorBall.h"
#include "LightPosController.h"

struct CBUFF_STAGESCENE
{
    XMFLOAT4    lightPosition;
    XMFLOAT4    eyePos;
};

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_;
    int hLightBall_;
    Transform trLight;
    ID3D11Buffer* pCBStageScene;


    void InitConstantBuffer();
    XMFLOAT4 lightSourcePosition_;

public:
    
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    // FLOAT4�^����FLOAT3�^�ւ̕ϊ��֐�
    DirectX::XMFLOAT3 ConvertFloat4ToFloat3(const DirectX::XMFLOAT4& float4Value)
    {
        return DirectX::XMFLOAT3(float4Value.x, float4Value.y, float4Value.z);
    }

    // FLOAT3�^����FLOAT4�^�ւ̕ϊ��֐�
    DirectX::XMFLOAT4 ConvertFloat3ToFloat4(const DirectX::XMFLOAT3& float3Value, float wValue)
    {
        return DirectX::XMFLOAT4(float3Value.x, float3Value.y, float3Value.z, wValue);
    }

    void SetLightPos(XMFLOAT4& _pos)
    {
        lightSourcePosition_ = _pos;
    }

    XMFLOAT4 GetLightPos()
    {
        return(lightSourcePosition_);
    }

};