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
    pSprite = new Sprite();
    pSprite->Initialize();
    //モデルデータのロード
   // hModel_ = Model::Load("Assets/BoxDefault.fbx");
   /* hModel_ = Model::Load("Assets/ShaderSample.png");
    assert(hModel_ >= 0);*/
}

//更新
void Stage::Update()
{
    //transform_.rotate_.y += 1;
}

//描画
void Stage::Draw()
{
   /* Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);*/
    pSprite->Draw(transform_);
}

//開放
void Stage::Release()
{
}
