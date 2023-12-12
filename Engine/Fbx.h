#if 0
#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include<vector>

#pragma comment(lib, "LibFbxSDK-Md.lib")
#pragma comment(lib, "LibXml2-Md.lib")
#pragma comment(lib, "zlib-Md.lib")

//#pragma comment�̂Ƃ��� MT -> MD��Md�̂ǂ������ɒ��� �ǂ����ł��������ۂ�
//�w�b�_�[�Ńw�b�_�[���C���N���[�h����̂͂���܂��낵���Ȃ�

class Texture; //�O���錾�@cpp�Ńw�b�_�[���C���N���[�h����΂悢

using namespace std;

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;//���[���h�ϊ������̂��
		XMMATRIX	matWVP;//���[���h�r���[�v���W�F�N�V����
		XMMATRIX	matNormal;//�X�P�[���~���s�ړ��̋t�s��
		XMFLOAT4	diffuseColor;//FBX����Ƃ��Ă����ʂ̐F
		XMFLOAT4	lightPosition;//���C�g�̕���
		XMFLOAT4	eyepos;
		BOOL		isTexture;

		FLOAT shininess; //�n�C���C�g�̋���
	};
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};
	struct MATERIAL //�}�e���A��
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
		XMFLOAT4 ambient;
		XMFLOAT4 specular;
	};

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;
	//vector<int>indexCount_;
	int* indexCount_;


	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();

	//Draw����Ă΂��֐�
	void PassDataToCB(Transform transform);	//�R���X�^���g�o�b�t�@�Ɋe�����n��
	void SetBufferToPipeline();

	void InitMaterial(fbxsdk::FbxNode* pNode);

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();

	
};

#else


#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include <vector>

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")


class Texture;

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4    diffuse;
	};

	struct CBUFF_MODEL
	{
		XMMATRIX    matW;//���[���h�ϊ�
		XMMATRIX    matWVP;//���[���h�r���[�v���W�F�N�V����
		XMMATRIX    matNormal; //�t�s��
		XMFLOAT4    diffuseColor;   //�ʂ̐F
		//XMFLOAT4    lightDirection;
		//XMFLOAT4    eyePos;
		BOOL    isTextured;// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j

	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

	int vertexCount_;   //���_��
	int polygonCount_;  //�|���S����
	int materialCount_; //�}�e���A���̌�
	int* indexCount_;
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;


	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
};

#endif



