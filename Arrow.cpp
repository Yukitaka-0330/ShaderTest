#include "Arrow.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Arrow::Arrow(GameObject* parent)
    :GameObject(parent, "Arrow"), hModel_(-1)
{
}

//�f�X�g���N�^
Arrow::~Arrow()
{
}

//������
void Arrow::Initialize()
{
    hModel_ = Model::Load("Assets/Arrow.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Arrow::Update()
{
    transform_.rotate_.y = 90;
    transform_.scale_.x = 1;
    transform_.scale_.y = 1;
    transform_.position_.z = -3;

    //transform_.position_.y = 2;
}

//�`��
void Arrow::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Arrow::Release()
{
}
