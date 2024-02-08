#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class WaterSurface : public GameObject
{
public:
    int hModel_;
    //コンストラクタ
    WaterSurface(GameObject* parent);

    //デストラクタ
    ~WaterSurface();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};