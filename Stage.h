#pragma once
#include "Engine/GameObject.h"
#include "ColorBall.h"
#include "LightPosController.h"

struct CBUFF_STAGESCENE
{
    XMFLOAT4    lightPosition;
    XMFLOAT4    eyePos;
};

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_;
    int hLightBall_;
    Transform trLight;
    ID3D11Buffer* pCBStageScene;


    void InitConstantBuffer();
    XMFLOAT4 lightSourcePosition_;

public:
    
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    // FLOAT4型からFLOAT3型への変換関数
    DirectX::XMFLOAT3 ConvertFloat4ToFloat3(const DirectX::XMFLOAT4& float4Value)
    {
        return DirectX::XMFLOAT3(float4Value.x, float4Value.y, float4Value.z);
    }

    // FLOAT3型からFLOAT4型への変換関数
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