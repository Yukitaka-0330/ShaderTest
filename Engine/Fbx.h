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
		XMMATRIX	matW;
		XMMATRIX	matWVP;//wvp
		XMMATRIX	matNormal;//���[���h�ϊ������̂��
		XMFLOAT4	diffuseColor;//�ʂ̐F
		XMFLOAT4	lightDirection;//���C�g�̕���
		XMFLOAT4	eyepos;
		int			isTexture;
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
		XMFLOAT4	diffuse;
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



