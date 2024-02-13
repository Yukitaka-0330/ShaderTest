#include "WaterSurface.h"
#include "Engine/Model.h"

//�R���X�g���N�^
WaterSurface::WaterSurface(GameObject* parent)
    :GameObject(parent, "WaterSurface"), hModel_(-1)
{
}

//�f�X�g���N�^
WaterSurface::~WaterSurface()
{
}

//������
void WaterSurface::Initialize()
{
    //hModel_ = Model::Load("Assets/WaterSurface.fbx");
    hModel_ = Model::Load("Assets/Water.fbx");
    assert(hModel_ >= 0);

    //transform_.position_.x = 3;
    transform_.position_.y = 1;
    //transform_.position_.z = -7;
    //transform_.rotate_.x = -90;
    //transform_.scale_ = { 0.5,0.5,0.5 };

    transform_.scale_ = { 1.5f,1.5f,1.5f };
}

//�X�V
void WaterSurface::Update()
{
    //transform_.rotate_.y += 1;
}

//�`��
void WaterSurface::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void WaterSurface::Release()
{
}
