#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include <vector>
#include"Texture.h"
#include "Transform.h"

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;} //開放処理


using namespace DirectX;
using std::vector;
class Sprite
{
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX	world;	//頂点座標変換行列
		XMMATRIX	uvTrans; //テクスチャ座標変換行列
		XMFLOAT4	color;	//テクスチャとの合成
		float scroll;
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};

	HRESULT hr;

protected:
	UINT  vertexNum_; //頂点数
	vector<VERTEX> vertices_; //頂点情報
	ID3D11Buffer* pVertexBuffer_; //頂点バッファ

	UINT indexNum_; //インデックス数
	vector<int> index_; //インデックス情報

	Texture* pTexture_; //テクスチャ

	//もとはないやつ
	ID3D11Buffer* pIndexBuffer_; //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

public:
	Sprite();
	~Sprite();

	//初期化(ポリゴンを表示するため各種情報を準備)
	//戻り値 成功/失敗
	HRESULT Initialize();

	//描画
	//引数：transform	トランスフォームクラスオブジェクト
	void Draw(Transform& transform);
	void Draw(Transform& transform, RECT rect, float alpha);

	//解放
	void Release();

	/// <summary>
	/// 画像サイズの取得
	/// </summary>
	/// <returns>画像サイズ</returns>
	XMFLOAT2 GetTextureSize() { return pTexture_->GetTextureSize(); }

	/// <summary>
	/// ロード
	/// </summary>
	/// <param name="fileName">画像ファイル名</param>
	/// <returns>成功/失敗</returns>
	HRESULT Load(std::string fileName);
	float scrollVall;

private:

	//Initializeから呼ばれる関数
	virtual void InitVertexData(); //頂点情報を準備
	HRESULT  CreateVertexBuffer(); //頂点バッファを作成

	virtual void InitIndexData(); //インデックス情報を準備
	HRESULT CreateIndexBuffer(); //インデックスバッファを作成

	HRESULT CreateConstantBuffer(); //コンスタントバッファを作成
	
	HRESULT LoadTexture(); //テクスチャをロード

	//Drawから呼ばれる関数
	void PassDataToCB(XMMATRIX worldMatrix); //コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline(); //各バッファをパイプラインにセット

};

