////───────────────────────────────────────
//// テクスチャ＆サンプラーデータのグローバル変数定義
////───────────────────────────────────────
//Texture2D	g_texture : register(t0);	//テクスチャー
//SamplerState	g_sampler : register(s0);	//サンプラー
//
////───────────────────────────────────────
// // コンスタントバッファ
//// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
////───────────────────────────────────────
//cbuffer global
//{
//	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
//	float4x4	matW;			//ワールド行列
//	float4x4	matNormal;		//法線
//	float4		diffuseColor;	// ディフューズカラー（マテリアルの色）
//	bool		isTexture;		// テクスチャ貼ってあるかどうか
//
//	float4		lightDirection;	//ライトの方向
//	float4		eyepos;			//視点
//};
//
////───────────────────────────────────────
//// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
////───────────────────────────────────────
//struct VS_OUT
//{
//	float4 pos    : SV_POSITION;	//位置
//	float2 uv	: TEXCOORD;	//UV座標
//	float4 color	: COLOR;	//色（明るさ）
//};
//
////───────────────────────────────────────
//// 頂点シェーダ
////───────────────────────────────────────
//VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
//{
//	//ピクセルシェーダーへ渡す情報
//	VS_OUT outData;
//
//	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
//	//スクリーン座標に変換し、ピクセルシェーダーへ
//	outData.pos = mul(pos, matWVP);
//	outData.uv = uv;
//
//	normal = mul(normal, matW);
//
//	float4 light = float4(-1, 1, 0, 0);
//	light = normalize(light);
//	outData.color = clamp(dot(normal, light), 0, 1);
//
//	//まとめて出力
//	return outData;
//}
//
////───────────────────────────────────────
//// ピクセルシェーダ
////───────────────────────────────────────
//float4 PS(VS_OUT inData) : SV_Target
//{
//	float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);
//	float4 ambentSource = float4(0.5, 0.5, 0.5, 1.0); //物体がどれだけ環境光を反射または放射するかを制御する
//	float4 diffuse;
//	float4 ambient;
//
//	float4 l;
//
//
//	if (isTexture == false)
//	{
//		diffuse = lightSource * diffuseColor * inData.color;
//		ambient = lightSource * diffuseColor * ambentSource;
//
//
//	}
//	else
//	{
//		diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
//		ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambentSource;
//	}
//	return diffuse + ambient;
//}

//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D       g_texture : register(t0);   //テクスチャー
SamplerState    g_sampler : register(s0);   //サンプラー

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
    float4x4    matW;
    float4x4    matWVP;         // ワールド・ビュー・プロジェクションの合成行列
    float4x4    matNormal;           // 法線
    float4      diffuseColor;       //マテリアルの色＝拡散反射係数
    bool        isTextured;         //テクスチャーが貼られているかどうか

    float4      vecLight;
    float4      CameraPosition;
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
    float4 pos  : SV_POSITION;  //位置
    float2 uv   : TEXCOORD;     //UV座標
    float4 color    : COLOR;    //色（明るさ）
    float4 viewDir  :TEXCOORD1; //視線ベクトル
    float4 reflection   :TexCOORD2;
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
    //ピクセルシェーダーへ渡す情報
    VS_OUT outData;

    //ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
    //スクリーン座標に変換し、ピクセルシェーダーへ
    outData.pos = mul(pos, matWVP);
    outData.uv = uv;


    /* l */float4 light = normalize(vecLight);
    /* n */normal = mul(normal, matNormal);
    /* r */outData.reflection = 2.0f * normal * dot(normal, light) - light;
    /* v */outData.viewDir = normalize(mul(CameraPosition, matW) - mul(pos, matW));


    float4 l = vecLight;
    light = normalize(light);
    outData.color = clamp(dot(normal, light), 0, 1);

    //まとめて出力
    return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
    float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);
    float4 ambientSource = float4(0.2, 0.2, 0.2, 1.0);

    float4 diffuse;
    float4 ambient;
    float glossiness = 5.0f;
    float4 specular;

    if (isTextured == false)
    {
        diffuse = lightSource * diffuseColor * inData.color;
        ambient = lightSource * diffuseColor * ambientSource;
        specular = (pow(dot(inData.reflection, inData.viewDir), glossiness)) * diffuseColor * lightSource;

    }
    else
    {
        diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
        ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientSource;
        specular = (pow(dot(inData.reflection, inData.viewDir), glossiness)) * g_texture.Sample(g_sampler, inData.uv) * lightSource;
    }

    return ambient + diffuse + specular;
}
