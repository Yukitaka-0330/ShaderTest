#pragma once
#include "GameObject.h"
#include "Direct3D.h"

//�Q�[���V�[�����
enum SCENE_ID
{
	SCENE_ID_TEST = 0,
	SCENE_ID_PLAY,
};

class SceneManager :
    public GameObject
{
private:
	SCENE_ID currentSceneID_;
	SCENE_ID nextSceneID_;
public:

	//�R���X�g���N�^
	SceneManager(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�V�[����؂�ւ�
	void ChangeScene(SCENE_ID _next);
};

