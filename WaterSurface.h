#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class WaterSurface : public GameObject
{
public:
    int hModel_;
    //�R���X�g���N�^
    WaterSurface(GameObject* parent);

    //�f�X�g���N�^
    ~WaterSurface();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};