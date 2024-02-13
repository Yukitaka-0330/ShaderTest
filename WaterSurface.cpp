#include "WaterSurface.h"
#include "Engine/Model.h"

//コンストラクタ
WaterSurface::WaterSurface(GameObject* parent)
    :GameObject(parent, "WaterSurface"), hModel_(-1)
{
}

//デストラクタ
WaterSurface::~WaterSurface()
{
}

//初期化
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

//更新
void WaterSurface::Update()
{
    //transform_.rotate_.y += 1;
}

//描画
void WaterSurface::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void WaterSurface::Release()
{
}
