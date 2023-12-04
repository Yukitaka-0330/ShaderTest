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

    transform_.scale_.x = 1;
    transform_.scale_.y = 1;
    transform_.position_.z = -3;
}

//�X�V
void Arrow::Update()
{
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
