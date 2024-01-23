#include "ColorBall.h"
#include "Engine/Model.h"

//コンストラクタ
ColorBall::ColorBall(GameObject* parent)
    :GameObject(parent, "ColorBall"), hModel_(-1)
{
}

//デストラクタ
ColorBall::~ColorBall()
{
}

//初期化
void ColorBall::Initialize()
{
    //hModel_ = Model::Load("Assets/Donut.fbx");
    hModel_ = Model::Load("Assets/ColorDice.fbx");
    assert(hModel_ >= 0);

    //transform_.position_.x = 3;
    transform_.position_.y = 3;
    //transform_.position_.z = -7;
    //transform_.rotate_.x = -90;
    //transform_.scale_ = { 0.5,0.5,0.5 };

    transform_.scale_ = { 1.5f,1.5f,1.5f };
}

//更新
void ColorBall::Update()
{
    transform_.rotate_.y += 1;
}

//描画
void ColorBall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void ColorBall::Release()
{
}
