#pragma once
#include "Engine/GameObject.h"


//◆◆◆を管理するクラス
class Stage : public GameObject
{

public:
    int hModel_;
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};