#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Arrow : public GameObject
{
public:
    int hModel_;
    //�R���X�g���N�^
    Arrow(GameObject* parent);

    //�f�X�g���N�^
    ~Arrow();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};