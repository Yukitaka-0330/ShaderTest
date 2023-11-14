//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D	g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	matW;	//ワールド行列
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
	float2 uv	: TEXCOORD;	//UV座標
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//ワールド座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matW);
	outData.uv = uv;


	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	/*
	// テクスチャサンプリング
	float4 color = g_texture.Sample(g_sampler, inData.uv);

	// 正確なグレースケール変換式
	float grayscale = 0.298912 * color.x + 0.586611 * color.y + 0.114478 * color.z;

	// グレースケールにするための近似値を求める式
	grayscale = (2 * color.x + 4 * color.y + color.z) / 7;

	return grayscale;
	*/

	//値は階調数
	/*float4 color = floor(g_texture.Sample(g_sampler, inData.uv) * 5.0) / 5;
	return color;*/

	return g_texture.Sample(g_sampler, inData.uv);
	
}