#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include<vector>

#pragma comment(lib, "LibFbxSDK-Md.lib")
#pragma comment(lib, "LibXml2-Md.lib")
#pragma comment(lib, "zlib-Md.lib")

//#pragma commentのところ MT -> MDかMdのどっちかに直す どっちでもいいっぽい
//ヘッダーでヘッダーをインクルードするのはあんまりよろしくない

class Texture; //前方宣言　cppでヘッダーをインクルードすればよい

using namespace std;

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
		XMMATRIX	matWVP;//wvp
		XMMATRIX	matNormal;//ワールド変換だけのやつ
		XMFLOAT4	diffuseColor;//面の色
		XMFLOAT4	lightDirection;//ライトの方向
		XMFLOAT4	eyepos;
		int			isTexture;
	};
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};
	struct MATERIAL //マテリアル
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


	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();

	//Drawから呼ばれる関数
	void PassDataToCB(Transform transform);	//コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();

	void InitMaterial(fbxsdk::FbxNode* pNode);

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();

	
};



