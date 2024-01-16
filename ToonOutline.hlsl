//������������������������������������������������������������������������������
// �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D	g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

Texture2D	g_toon_texture : register(t1);//�g�D�[���V�F�[�f�B���O�p�̃e�N�X�`��
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
	float		shiness;
	bool		isTexture;		// �e�N�X�`���\���Ă��邩�ǂ���
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
	float4 color	: COLOR;	//�F�i���邳�j
	float4 eyev		: POSITION1;
	float4 normal   : POSITION2;
	float4 light	: POSITION3;
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData = (VS_OUT)0;
	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��

	pos = pos + normal * 0.15;

	outData.pos = mul(pos, matWVP);
	outData.uv = uv;
	normal.w = 0;
	normal = mul(normal, matNormal);
	normal = normalize(normal);
	outData.normal = normal;



	float4 light = normalize(lightPosition);
	light = normalize(light);

	outData.color = saturate(dot(normal, light));
	float4 posw = mul(pos, matW);
	outData.eyev = eyepos - posw;
	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);
	float4 ambentSource = ambientColor;
	float4 diffuse;
	float4 ambient;
	float4 NL = dot(inData.normal, normalize(lightPosition));

	float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition));
	float4 specular = pow(saturate(dot(reflect, normalize(inData.eyev))), shiness) * specularColor;

	float2 uv;
	uv.x = abs(dot(inData.normal, normalize(inData.eyev)));
	uv.y = abs(dot(inData.normal, normalize(inData.eyev)));
	float4 tI = g_toon_texture.Sample(g_sampler, uv);

	if (isTexture == false)
	{
		diffuse = lightSource * diffuseColor * tI;
		ambient = lightSource * diffuseColor * ambentSource;
	}
	else
	{
		diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * tI;
		ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambentSource;
	}

	if (abs(dot(normalize(inData.eyev), inData.normal)) < 0.2f)
	{
		return float4(0, 0, 0, 1);
	}
	else
		return diffuse + ambient;
}