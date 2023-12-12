#include "ColorBall.h"
#include "Engine/Model.h"

//�R���X�g���N�^
ColorBall::ColorBall(GameObject* parent)
    :GameObject(parent, "ColorBall"), hModel_(-1)
{
}

//�f�X�g���N�^
ColorBall::~ColorBall()
{
}

//������
void ColorBall::Initialize()
{
    hModel_ = Model::Load("Assets/Donut.fbx");
    assert(hModel_ >= 0);

    transform_.position_.x = 3;
    transform_.position_.y = 2;
    //transform_.rotate_.x = -90;
    transform_.scale_ = { 0.5,0.5,0.5 };
}

//�X�V
void ColorBall::Update()
{
    //transform_.rotate_.y += 1;
}

//�`��
void ColorBall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void ColorBall::Release()
{
}
