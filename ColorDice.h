#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class ColorDice : public GameObject
{
public:
    int hModel_;
    //�R���X�g���N�^
    ColorDice(GameObject* parent);

    //�f�X�g���N�^
    ~ColorDice();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};