#include "Arrow.h"
#include "Engine/Model.h"

//コンストラクタ
Arrow::Arrow(GameObject* parent)
    :GameObject(parent, "Arrow"), hModel_(-1)
{
}

//デストラクタ
Arrow::~Arrow()
{
}

//初期化
void Arrow::Initialize()
{
    hModel_ = Model::Load("Assets/Arrow.fbx");
    assert(hModel_ >= 0);

    transform_.scale_.x = 1;
    transform_.scale_.y = 1;
    transform_.position_.z = -3;
}

//更新
void Arrow::Update()
{
}

//描画
void Arrow::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Arrow::Release()
{
}
