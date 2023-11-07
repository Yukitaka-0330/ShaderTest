#include "SceneManager.h"
#include "../TestScene.h"
#include "Model.h"

SceneManager::SceneManager(GameObject* parent) :GameObject(parent, "SceneManager")
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	//�V�[���؂�ւ�
	//���݂̃V�[���Ǝ��̃V�[�����ʂ�������؂�ւ���
	if (currentSceneID_ != nextSceneID_)
	{
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();

		//���[�h�����f�[�^��S�폜
		Model::Release();
		//��Еt���I��
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		}
		currentSceneID_ = nextSceneID_;
	}
	//���݂̃V�[���̌�Еt��
	//�V�����V�[���̏���
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;
}

