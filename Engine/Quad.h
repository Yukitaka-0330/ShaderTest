#if 0
#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"

using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matW;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;
public:
	/// <summary>
	/// 四角形を表すクラスのコンストラクタ
	/// </summary>
	Quad();

	~Quad();
	HRESULT Initialize();
	void Draw(Transform& transform);
	void Release();
};
#endif

#if 0

#pragma once

#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"
#include <vector>
#include "Transform.h"

using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matNormal; //matWからNormal用に改名
};

struct VERTEX
{
	XMVECTOR postion;
	XMVECTOR uv;
	XMVECTOR normal;

};

class Quad
{
protected:
	int vertexNum_;
	std::vector<VERTEX> vertices_;
	int indexNum_;//インデックス数
	std::vector<int> index_;//インデックス情報

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;
public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw(Transform& transform);
	void Release();

private:
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();
	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();

	//---------Draw関数から呼ばれる関数---------
	void PassDataToCB(XMMATRIX worldMatrix);	//コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();
};

#endif

#pragma once

#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"
#include <vector>
#include "Transform.h"

using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matNormal; //matWからNormal用に改名
};

struct VERTEX
{
	XMVECTOR postion;
	XMVECTOR uv;
	XMVECTOR normal;

};

class Quad
{
protected:
	int vertexNum_;
	std::vector<VERTEX> vertices_;
	int indexNum_;//インデックス数
	std::vector<int> index_;//インデックス情報

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;
public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw(Transform& transform);
	void Release();

private:
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();
	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();

	//---------Draw関数から呼ばれる関数---------
	void PassDataToCB(Transform transform);	//コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();
};
