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

//#pragma commentのところ MT -> MDかMdのどっちかに直す どっちでもいいっぽい
//ヘッダーでヘッダーをインクルードするのはあんまりよろしくない

class Texture; //前方宣言　cppでヘッダーをインクルードすればよい

using namespace std;

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;//ワールド変換だけのやつ
		XMMATRIX	matWVP;//ワールドビュープロジェクション
		XMMATRIX	matNormal;//スケール×平行移動の逆行列
		XMFLOAT4	diffuseColor;//FBXからとってきた面の色
		XMFLOAT4	lightPosition;//ライトの方向
		XMFLOAT4	eyepos;
		BOOL		isTexture;

		FLOAT shininess; //ハイライトの強さ
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
	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4    diffuse;
	};

	struct CBUFF_MODEL
	{
		XMMATRIX    matW;//ワールド変換
		XMMATRIX    matWVP;//ワールドビュープロジェクション
		XMMATRIX    matNormal; //逆行列
		XMFLOAT4    diffuseColor;   //面の色
		//XMFLOAT4    lightDirection;
		//XMFLOAT4    eyePos;
		BOOL    isTextured;// ディフューズカラー（マテリアルの色）

	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

	int vertexCount_;   //頂点数
	int polygonCount_;  //ポリゴン数
	int materialCount_; //マテリアルの個数
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



