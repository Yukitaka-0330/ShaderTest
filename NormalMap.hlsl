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
	float		scrollX;
	float		scrollY;

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


	float3  binormal = cross(normal, tangent);
	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal); //従法線ベクトルをローカル座標に変換したやつ

	outData.normal = normalize(mul(normal, matNormal));
	normal.w = 0;

	tangent = mul(tangent, matNormal);
	tangent = normalize(tangent); //接線ベクトルをローカル座標に変換したやつ
	tangent.w = 0;

	float4 eye = normalize(mul(pos, matW) - eyepos);
	outData.eyev = eye;


	outData.Neyev.x = dot(eye, tangent); //接空間の視線ベクトル
	outData.Neyev.y = dot(eye, normal); //接空間の視線ベクトル
	outData.Neyev.z = dot(eye, outData.normal); //接空間の視線ベクトル
	outData.Neyev.w = 0; //接空間の視線ベクトル


	float4 light = normalize(lightPosition);
	light.w = 0;
	light = normalize(light);

	outData.color = mul(light, outData.normal);
	outData.color.w = 0.0;

	outData.light.x = dot(light, tangent);//接空間の光源ベクトル
	outData.light.y = dot(light, normal);
	outData.light.z = dot(light, outData.normal);
	outData.light.w = 0;
	return outData;
	

	/*自分
	* //float4 posw = mul(pos, matW);
	//outData.eyev = normalize(posw - eyepos); //ワールド座標の視線ベクトル

	//outData.Neyev.x = dot(outData.eyev, tangent); //接空間の視線ベクトル
	//outData.Neyev.y = dot(outData.eyev, binormal); //接空間の視線ベクトル
	//outData.Neyev.z = dot(outData.eyev, outData.normal); //接空間の視線ベクトル
	//outData.Neyev.w = 0; //接空間の視線ベクトル


	//float4 light = normalize(lightPosition);
	//light.w = 0;
	//light = normalize(light);

	//outData.color = mul(light, normal);
	//outData.color.w = 0.0;

	//outData.light.x = dot(light, tangent);//接空間の光源ベクトル
	//outData.light.y = dot(light, binormal);
	//outData.light.z = dot(light, outData.normal);
	outData.light.w = 0;

	//まとめて出力
	return outData;
	*/
	
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);
	float4 diffuse;
	float4 ambient;
	float4 Specular;

	float2 tmpNormalUV = inData.uv;
	tmpNormalUV.x = tmpNormalUV.x + scrollX;
	tmpNormalUV.y = tmpNormalUV.y + scrollY;

	if (hasNormalMap)
	{
		float4 tmpNormal = normalTex.Sample(g_sampler, inData.uv) * 2.0f - 1.0f;
		float4 tmpNormal2 = normalTex.Sample(g_sampler, inData.uv + (float2)(scrollX * 0.4 + (-scrollY) * 0.4)) * 2.0f - 1.0f;
		tmpNormal.w = 0;
		tmpNormal2.w = 0;
		tmpNormal = normalize(tmpNormal + tmpNormal2);

		float4 NL = clamp(dot(normalize(inData.light), tmpNormal), 0, 1);
		float4 light = normalize(lightPosition);
		light = normalize(light);
		float4 reflection = reflect(inData.light, tmpNormal);
		float4 specular = pow(saturate(dot(reflection, inData.Neyev)), shiness) * specularColor;
	

		if (hasTexture != 0)
		{
			diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * NL;
			ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else
		{
			diffuse = lightSource * diffuseColor * NL;
			ambient = lightSource * diffuseColor * ambientColor;
		}
		return  diffuse + ambient + Specular;
		//return g_texture.Sample(g_sampler, tmpNormalUV);

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
			result.a = inData.uv.x;
		return result;
	}
}