#if 0
#include "Quad.h"
#include "Camera.h"

Quad::Quad():pVertexBuffer_(nullptr), pIndexBuffer_(nullptr),pConstantBuffer_(nullptr), pTexture_(nullptr)
{
}

Quad::~Quad()
{
	Release();
}

HRESULT Quad::Initialize()
{
	HRESULT hr;
	// 頂点情報
	VERTEX vertices[] =
	{
		
		{XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)  },	// 四角形の頂点（左上）,テクスチャの座標(画鋲をイメージすればいいかも、ここに春よーみたいな感じ)
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)  },	// 四角形の頂点（右上）,テクスチャの座標
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,  -1.0f, 0.0f)  },	// 四角形の頂点（右下）,テクスチャの座標
		{XMVectorSet(-1.0f,-1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,  -1.0f, 0.0f)  },	// 四角形の頂点（左下）,テクスチャの座標
		
	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);  //ByteWidthがバッファーのサイズ
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;	 //バッファーの読み取りと書き込み方法を特定
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//バッファーをパイプラインに結びつける
	bd_vertex.CPUAccessFlags = 0;	//CPUアクセスが必要ない場合は0
	bd_vertex.MiscFlags = 0;		
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;

	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
		//return E_FAIL;
	}


	//インデックス情報
	int index[] = { 0,2,3, 0,1,2 };

	//int index[] = { 0,2,3, 0,1,2, 0,4,1};

	

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);

	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
		
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");

	return S_OK;
}

void Quad::Draw(Transform& transform)
{
	//コンスタントバッファに渡す情報
	//XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	//XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列 //カメラから見ての拡張するためのもの  //XMVectorSetはカメラの上方向
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列 //遠近感をつける //第一引数　画角、視野角をラジアンで表現している
	//第二引数 アスペクト比 第三引数　ニアクリップ面　第四引数 ファークリップ面
	//カメラ内に収めるならx軸が -1から1 y軸が-1から1 z軸が-1から1
	//視野角を狭くするとズームすることになる　遠くのものと近くのものの差が変わらなくなる　遠近感がなくなる
	/*カメラの表示距離は近い時も遠い時も決めないといけない
	遠い時に設定しないとどこまでも見えてしまうため
	近い時はある程度カメラとの距離がないと距離を圧縮して表示できなくなるから*/
	//ニアクリップ面とファークリップ面の距離はなるべく短くする　なぜか距離のずれが生じる　物体が埋まっちゃ足りしてちらつくようになる　<- zファイティング

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform *Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	//cb.matWVP = XMMatrixTranspose(view * proj);
	cb.matW = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);


	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	//UINT stride = sizeof(XMVECTOR); //前使ってたやつ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	//Direct3D::pContext_->DrawIndexed(9, 0, 0);
	Direct3D::pContext_->DrawIndexed(6, 0, 0);
}

void Quad::Release()
{
	pTexture_->Release();
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

#endif

#include "Quad.h"
#include "Camera.h"

Quad::Quad() :
	pVertexBuffer_(nullptr), pIndexBuffer_(nullptr),
	pConstantBuffer_(nullptr), pTexture_(nullptr), vertexNum_(0), indexNum_(0)
{
}

Quad::~Quad()
{
	Release();
}

HRESULT Quad::Initialize()
{


	InitVertexData();
	if (FAILED(CreateVertexBuffer()))
	{
		return E_FAIL;
	}


	InitIndexData();
	if (FAILED(CreateIndexBuffer()))
	{
		return E_FAIL;
	}

	if (FAILED(CreateConstantBuffer()))
	{
		return E_FAIL;
	}

	//テクスチャのロード
	if (FAILED(LoadTexture()))
	{
		return E_FAIL;
	}

	return S_OK;
}

void Quad::Draw(Transform& transform)
{

	Direct3D::SetShader(SHADER_3D);
	transform.Calclation();//トランスフォームを計算
	//コンスタントバッファに情報を渡す
	PassDataToCB(transform);

	//頂点バッファ、インデックスバッファ、コンスタントバッファをパイプラインにセット
	SetBufferToPipeline();

	//描画
	Direct3D::pContext_->DrawIndexed(index_.size(), 0, 0);



}

void Quad::Release()
{
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

void Quad::InitVertexData()
{
	// 頂点情報
	vertices_ =
	{
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},// 四角形の頂点（左上）
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f,  0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},// 四角形の頂点（右上）
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},// 四角形の頂点（右下）
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)}	// 四角形の頂点（左下）		
	};
	vertexNum_ = vertices_.size();
}

//頂点バッファを作成
HRESULT Quad::CreateVertexBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexNum_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices_.data();
	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

//インデックス情報を準備
void Quad::InitIndexData()
{
	index_ = { 0,2,3, 0,1,2 };

	//インデックス数
	indexNum_ = index_.size();
}

//インデックスバッファを作成
HRESULT Quad::CreateIndexBuffer()
{
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * indexNum_;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index_.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	HRESULT hr;
	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
	return S_OK;
}


//コンスタントバッファ作成
HRESULT Quad::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	HRESULT hr;
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

//テクスチャをロード
HRESULT Quad::LoadTexture()
{
	pTexture_ = new Texture;

	HRESULT hr;
	hr = pTexture_->Load("Assets\\Dice.png");
	if (FAILED(hr))
	{
		MessageBox(NULL, "テクスチャの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
	return S_OK;
}


//コンスタントバッファに各種情報を渡す
void Quad::PassDataToCB(Transform transform)
{

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();

	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();

	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

}

//各バッファをパイプラインにセット
void Quad::SetBufferToPipeline()
{
	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	//Direct3D::pContext_->DrawIndexed(indexNum_, 0, 0);
}