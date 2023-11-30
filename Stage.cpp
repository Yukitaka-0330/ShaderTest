#include "Stage.h"
#include "Engine/Model.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
   /* hModel_ = Model::Load("Assets/Ground.fbx");
    assert(hModel_ >= 0);*/

    transform_.position_.y = -1;
    transform_.scale_.x = 10;
    transform_.scale_.y = 10;
    transform_.scale_.z = 10;

}

//更新
void Stage::Update()
{
    

}

//描画
void Stage::Draw()
{
    /*Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);*/
}

//開放
void Stage::Release()
{
}
