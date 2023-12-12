#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include <d3d11.h>

namespace 
{
    const XMFLOAT4 DEF_LIGHT_POSITION{ 1, 2, 1, 0 };
}

void Stage::InitConstantBuffer()
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CBUFF_STAGESCENE);
    cb.Usage = D3D11_USAGE_DEFAULT;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = 0;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;
    
    Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pCBStageScene);

}

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
    lightSourcePosition_ = DEF_LIGHT_POSITION;
    pCBStageScene = nullptr;
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    hModel_ = Model::Load("Assets/Ground.fbx");
    hLightBall_ = Model::Load("assets/Ball2.fbx");
    assert(hModel_ >= 0);
    assert(hLightBall_ >= 0);

    Camera::SetPosition(XMVECTOR{ 0, 5, -10, 0 });
    Camera::SetTarget(XMVECTOR{ 0, 2, 0, 0 });
   
    transform_.position_.y = -1;
    transform_.scale_.x = 10;
    transform_.scale_.y = 10;
    transform_.scale_.z = 10;

    trLight.position_ = { 0,0,0 };
    trLight.rotate_ = { 0,0,0 };
    trLight.scale_ = { 0.4f,0.4f,0.4f };

    InitConstantBuffer();
}

//更新
void Stage::Update()
{
    //光源からの位置をWASDで制御
   // t.position_ = ConvertFloat4ToFloat3(LightPosController::GetLightPosition());

    /*if (Input::IsKey(DIK_W))
    {
        t.position_.z += 0.5f;
    }

    if (Input::IsKey(DIK_A))
    {
        t.position_.x -= 0.5f;
    }

    if (Input::IsKey(DIK_S))
    {
        t.position_.z -= 0.5f;
    }

    if (Input::IsKey(DIK_D))
    {
        t.position_.x += 0.5f;
    }*/

   /* float wValue = 1.0f;
    LightPosController::SetLightPosition(ConvertFloat3ToFloat4(t.position_ , wValue));*/

    if (Input::IsKey(DIK_W))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.0f, p.z + 0.1f, p.w + 0.0f };
        SetLightPos(margin);
    }

    if (Input::IsKey(DIK_S))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.0f, p.z - 0.1f, p.w - 0.0f };
        SetLightPos(margin);
    }

    if (Input::IsKey(DIK_A))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.1f, p.y - 0.0f, p.z - 0.0f, p.w - 0.0f };
        SetLightPos(margin);
    }

    if (Input::IsKey(DIK_D))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x + 0.1f, p.y + 0.0f, p.z + 0.0f, p.w + 0.0f };
        SetLightPos(margin);
    }

    if (Input::IsKey(DIK_UP))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y + 0.1f, p.z - 0.0f, p.w - 0.0f };
        SetLightPos(margin);
    }

    if (Input::IsKey(DIK_DOWN))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.1f, p.z - 0.0f, p.w - 0.0f };
        SetLightPos(margin);
    }

    XMFLOAT4 tmp{ GetLightPos() };
    trLight.position_ = { tmp.x , tmp.y , tmp.z };

    CBUFF_STAGESCENE cb;
    cb.lightPosition = lightSourcePosition_;
    XMStoreFloat4(&cb.eyePos, Camera::GetEyePosition());

    Direct3D::pContext_->UpdateSubresource(pCBStageScene, 0, NULL, &cb, 0, 0);

    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene); //頂点シェーダ
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene); //ピクセルシェーダ

}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    Model::SetTransform(hLightBall_, trLight);
    Model::Draw(hLightBall_);
}

//開放
void Stage::Release()
{
}
