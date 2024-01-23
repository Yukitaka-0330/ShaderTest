//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー
Texture2D		normalTex : register(t1);

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global:register (b0)
{
	float4x4	matW;			//ワールド行列
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matNormal;		//法線
	float4		diffuseColor;	// ディフューズカラー（マテリアルの色）
	float4		ambientColor;
	float4		specularColor;
	float		shiness;
	int			hasTexture;		// テクスチャ貼ってあるかどうか
	int			hasNormalMap;	//ノーマルマップが張られているかどうか
};

cbuffer global:register (b1)
{
	float4		lightPosition;	//ライトの方向
	float4		eyepos;			//視点
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos		: SV_POSITION;	//位置
	float2 uv		: TEXCOORD;	//UV座標
	float4 eyev		: POSITION; //ワールド座標に変換された視線ベクトル
	float4 Neyev	: POSITION1;//ノーマルマップ用の接空間に変換された視線ベクトル
	float4 normal   : POSITION2;//法線ベクトル
	float4 light	: POSITION3;//ライトを接空間に変換したベクトル
	float4 color	: POSITION4;//色
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL, float4 tangent : TANGENT)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData = (VS_OUT)0;
	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	outData.uv = (float2)uv;

	float3 binormal = cross(normal, tangent);

	normal.w = 0;
	normal = mul(normal, matNormal);
	normal = normalize(normal);//法線ベクトルをローカル座標に変換したやつ
	normal.w = 0;
	outData.normal = normal;

	tangent.w = 0;
	tangent = mul(tangent, matNormal);
	tangent = normalize(tangent); //接線ベクトルをローカル座標に変換したやつ

	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal); //従法線ベクトルをローカル座標に変換したやつ


	float4 posw = mul(pos, matW);
	outData.eyev = normalize(posw - eyepos); //ワールド座標の視線ベクトル

	outData.Neyev.x = dot(outData.eyev, tangent); //接空間の視線ベクトル
	outData.Neyev.y = dot(outData.eyev, binormal); //接空間の視線ベクトル
	outData.Neyev.z = dot(outData.eyev, normal); //接空間の視線ベクトル
	outData.Neyev.w = 0; //接空間の視線ベクトル


	float4 light = normalize(lightPosition);
	light.w = 0;
	light = normalize(light);

	outData.color = mul(light, normal);
	outData.color.w = 0.0;

	outData.light.x = dot(light, tangent);//接空間の光源ベクトル
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, normal);
	outData.light.w = 0;

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	//float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);
	//float4 ambentSource = ambientColor;
	//float4 diffuse;
	//float4 ambient;
	//float4 NL = dot(inData.normal, normalize(lightPosition));
	////float4 NL = saturate(dot(inData.normal, normalize(lightPosition)));

	//float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition));
	//float4 specular = pow(saturate(dot(reflect, normalize(inData.eyev))), shiness) * specularColor;

	//if (hasTexture == false)
	//{
	//	diffuse = lightSource * diffuseColor * inData.color;
	//	ambient = lightSource * diffuseColor * ambentSource;
	//}
	//else
	//{
	//	diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
	//	ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambentSource;
	//}

	//return diffuse + ambient + specular;
	////return shiness /100.0f;


	float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);
	float4 diffuse;
	float4 ambient;

	if (hasNormalMap)
	{
		//inData.light = normalize(inData.light);
		float4 tmpNormal = normalTex.Sample(g_sampler, inData.uv) * 2.0f - 1.0f;
		tmpNormal.w = 0;
		tmpNormal = normalize(tmpNormal);

		float4 NL = clamp(dot(tmpNormal, inData.light), 0, 1);

		float4 reflection = reflect(-inData.light, tmpNormal);
		float4 specular = pow(saturate(dot(reflection, inData.Neyev)), shiness) * specularColor;

		if (hasTexture != 0)
		{
			diffuse = g_texture.Sample(g_sampler, inData.uv) * NL;
			ambient = g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else
		{
			diffuse = diffuseColor * NL;
			ambient = diffuseColor * ambientColor;
		}
		return   diffuse;
	}
	else
	{
		float4 reflection = reflect(normalize(lightPosition), inData.normal);

		float4 specular = pow(saturate(dot(normalize(reflection), inData.eyev)), shiness) * specularColor;
		if (hasTexture == 0)
		{
			diffuse = lightSource * diffuseColor * inData.color;
			ambient = lightSource * diffuseColor * ambientColor;
		}
		else
		{
			diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
			ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		float4 result = diffuse + ambient + specular;
		if (hasTexture)
		{
			result.a = inData.uv.x;
		}
		return result;

	}
}