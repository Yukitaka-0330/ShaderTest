#pragma once
#include "Engine/GameObject.h"


//���������Ǘ�����N���X
class Stage : public GameObject
{

public:
    int hModel_;
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};