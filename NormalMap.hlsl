//������������������������������������������������������������������������������
// �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[
Texture2D		normalTex : register(t1);

//������������������������������������������������������������������������������
 // �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global:register (b0)
{
	float4x4	matW;			//���[���h�s��
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matNormal;		//�@��
	float4		diffuseColor;	// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	float4		ambientColor;
	float4		specularColor;
	float		shininess;
	int			hasTexture;		// �e�N�X�`���\���Ă��邩�ǂ���
	int			hasNormalMap;	//�m�[�}���}�b�v�������Ă��邩�ǂ���
	float		scrollX;
	float		scrollY;

};

cbuffer global:register (b1)
{
	float4		lightPosition;	//���C�g�̕���
	float4		eyepos;			//���_
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos		: SV_POSITION;	//�ʒu
	float2 uv		: TEXCOORD;	//UV���W
	float4 eyev		: POSITION; //���[���h���W�ɕϊ����ꂽ�����x�N�g��
	float4 Neyev	: POSITION1;//�m�[�}���}�b�v�p�̐ڋ�Ԃɕϊ����ꂽ�����x�N�g��
	float4 normal   : POSITION2;//�@���x�N�g��
	float4 light	: POSITION3;//���C�g��ڋ�Ԃɕϊ������x�N�g��
	float4 color	: POSITION4;//�F
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL, float4 tangent : TANGENT)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData = (VS_OUT)0;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, matWVP);
	outData.uv = (float2)uv;


	float3  binormal = cross(normal, tangent);
	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal); //�]�@���x�N�g�������[�J�����W�ɕϊ��������

	outData.normal = normalize(mul(normal, matNormal));
	normal.w = 0;

	tangent = mul(tangent, matNormal);
	tangent = normalize(tangent); //�ڐ��x�N�g�������[�J�����W�ɕϊ��������
	tangent.w = 0;

	float4 eye = normalize(mul(pos, matW) - eyepos);
	outData.eyev = eye;


	outData.Neyev.x = dot(eye, tangent); //�ڋ�Ԃ̎����x�N�g��
	outData.Neyev.y = dot(eye, normal); //�ڋ�Ԃ̎����x�N�g��
	outData.Neyev.z = dot(eye, outData.normal); //�ڋ�Ԃ̎����x�N�g��
	outData.Neyev.w = 0; //�ڋ�Ԃ̎����x�N�g��


	float4 light = normalize(lightPosition);
	light.w = 0;
	light = normalize(light);

	outData.color = mul(light, outData.normal);
	outData.color.w = 0.0f;

	outData.light.x = dot(light, tangent);//�ڋ�Ԃ̌����x�N�g��
	outData.light.y = dot(light, normal);
	outData.light.z = dot(light, outData.normal);
	outData.light.w = 0;
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
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
		float4 tmpNormal = normalTex.Sample(g_sampler, tmpNormalUV) * 2.0f - 1.0f;
		float4 tmpNormal2 = normalTex.Sample(g_sampler, inData.uv +(scrollX * 0.4 + (-scrollY) * 0.4)) * 2.0f - 1.0f;
		tmpNormal.w = 0;
		tmpNormal2.w = 0;
		tmpNormal = normalize(tmpNormal + tmpNormal2);

		float4 NL = clamp(dot(tmpNormal, normalize(inData.light)), 0, 1);
		/*float4 light = normalize(lightPosition);
		light = normalize(light);*/
		float4 reflection = reflect(inData.light, tmpNormal);
		float4 specular = pow(saturate(dot(reflection, inData.Neyev)), 1) * lightSource;
		//return reflection;

		if (hasTexture != 0)
		{
			diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * NL;
			ambient = g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else
		{
			diffuse = diffuseColor * NL;
			ambient = diffuseColor * ambientColor;
		}
		//return specular;
		return  diffuse + ambient + specular;

	}
	else
	{
		float4 reflection = reflect(normalize(lightPosition), inData.normal);

		float4 specular = pow(saturate(dot(normalize(reflection), inData.eyev)), shininess) * specularColor;
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
		/*float4 result = diffuse + ambient + specular;
		if (hasTexture)
			result.a = inData.uv.x;
		return result;*/
		//return specular;

		return diffuse + specular + ambient;
	}
}