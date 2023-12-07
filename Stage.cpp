#include "Stage.h"
#include "Engine/Input.h"
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
    hModel_ = Model::Load("Assets/Ground.fbx");
    assert(hModel_ >= 0);
   
    transform_.position_.y = -1;
    transform_.scale_.x = 10;
    transform_.scale_.y = 10;
    transform_.scale_.z = 10;
}

//更新
void Stage::Update()
{
    //光源からの位置をWASDで制御
    t.position_ = ConvertFloat4ToFloat3(LightPosController::GetLightPosition());

    if (Input::IsKey(DIK_W))
    {
        t.position_.z += 0.5f;
    }

    if (Input::IsKey(DIK_A))
    {
        t.position_.x -= 0.5f;
    }

    if (Input::IsKey(DIK_S))
    {
        t.position_.z -= 0.5f;
    }

    if (Input::IsKey(DIK_D))
    {
        t.position_.x += 0.5f;
    }

    float wValue = 1.0f;
    LightPosController::SetLightPosition(ConvertFloat3ToFloat4(t.position_ , wValue));

}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Stage::Release()
{
}
