#pragma once
#include<string>
#include<vector>
#include"Fbx.h"
#include"Transform.h"

using std::string;
using std::vector;

namespace Model
{
	struct ModelData
	{
		//FBX
		Fbx* pfbx_;
		//�g�����X�t�H�[��
		Transform Transform_;
		//�t�@�C����
		string mFileName_;
	};

	//���f�������[�h
	//�����FfileName�@�t�@�C����
	//�ߒl�F���̃��f���f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName);

	//���[���h�s���ݒ�
	//�����FhModel	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetTransform(int hModel, Transform& transform);

	//�`��
	//�����FhModel	�`�悵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void Draw(int hModel);

	void Release();
}