#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class ColorBall : public GameObject
{
public:
    int hModel_;
    //�R���X�g���N�^
    ColorBall(GameObject* parent);

    //�f�X�g���N�^
    ~ColorBall();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};