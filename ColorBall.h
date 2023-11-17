#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class ColorBall : public GameObject
{
public:
    int hModel_;
    //コンストラクタ
    ColorBall(GameObject* parent);

    //デストラクタ
    ~ColorBall();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};