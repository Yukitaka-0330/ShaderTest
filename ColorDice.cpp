#include "ColorDice.h"
#include "Engine/Model.h"

//�R���X�g���N�^
ColorDice::ColorDice(GameObject* parent)
    :GameObject(parent, "ColorDice"), hModel_(-1)
{
}

//�f�X�g���N�^
ColorDice::~ColorDice()
{
}

//������
void ColorDice::Initialize()
{
    //hModel_ = Model::Load("Assets/Donut.fbx");
    hModel_ = Model::Load("Assets/ColorDice.fbx");
   // hModel_ = Model::Load("Assets/WaterSurface.fbx");
    assert(hModel_ >= 0);

    //transform_.position_.x = 3;
    transform_.position_.y = 3;
    //transform_.position_.z = -7;
    //transform_.rotate_.x = -90;
    //transform_.scale_ = { 0.5,0.5,0.5 };

    transform_.scale_ = { 1.5f,1.5f,1.5f };
}

//�X�V
void ColorDice::Update()
{
    transform_.rotate_.y += 1;
}

//�`��
void ColorDice::Draw()
{
   /* Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);*/
}

//�J��
void ColorDice::Release()
{
}
