#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include <d3d11.h>

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

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
    lightSourcePosition_ = { 1,1,1,0 };
    pCBStageScene = nullptr;
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    hModel_ = Model::Load("Assets/Ground.fbx");
    assert(hModel_ >= 0);
   
    transform_.position_.y = -1;
    transform_.scale_.x = 10;
    transform_.scale_.y = 10;
    transform_.scale_.z = 10;

    InitConstantBuffer();
}

//�X�V
void Stage::Update()
{
    //��������̈ʒu��WASD�Ő���
    t.position_ = ConvertFloat4ToFloat3(LightPosController::GetLightPosition());

    if (Input::IsKey(DIK_W))
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
    }

    float wValue = 1.0f;
    LightPosController::SetLightPosition(ConvertFloat3ToFloat4(t.position_ , wValue));

    CBUFF_STAGESCENE cb;
    cb.lightDirection = lightSourcePosition_;
    XMStoreFloat4(&cb.eyePos, Camera::GetEyePosition());

    InitConstantBuffer();
    //Direct3D::pContext_->UpdateSubresource(pCBStageScene, 0, NULL, &cb, 0, 0);

    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene); //���_�V�F�[�_
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene); //�s�N�Z���V�F�[�_

}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Stage::Release()
{
}
