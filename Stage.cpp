#include "Stage.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
   /* hModel_ = Model::Load("Assets/Ground.fbx");
    assert(hModel_ >= 0);*/

    transform_.position_.y = -1;
    transform_.scale_.x = 10;
    transform_.scale_.y = 10;
    transform_.scale_.z = 10;

}

//�X�V
void Stage::Update()
{
    

}

//�`��
void Stage::Draw()
{
    /*Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);*/
}

//�J��
void Stage::Release()
{
}
