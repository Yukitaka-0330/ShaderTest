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
	// ���_���
	VERTEX vertices[] =
	{
		
		{XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)  },	// �l�p�`�̒��_�i����j,�e�N�X�`���̍��W(��e���C���[�W����΂��������A�����ɏt��[�݂����Ȋ���)
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)  },	// �l�p�`�̒��_�i�E��j,�e�N�X�`���̍��W
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,  -1.0f, 0.0f)  },	// �l�p�`�̒��_�i�E���j,�e�N�X�`���̍��W
		{XMVectorSet(-1.0f,-1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,  -1.0f, 0.0f)  },	// �l�p�`�̒��_�i�����j,�e�N�X�`���̍��W
		
	};

	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);  //ByteWidth���o�b�t�@�[�̃T�C�Y
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;	 //�o�b�t�@�[�̓ǂݎ��Ə������ݕ��@�����
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//�o�b�t�@�[���p�C�v���C���Ɍ��т���
	bd_vertex.CPUAccessFlags = 0;	//CPU�A�N�Z�X���K�v�Ȃ��ꍇ��0
	bd_vertex.MiscFlags = 0;		
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;

	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
		//return E_FAIL;
	}


	//�C���f�b�N�X���
	int index[] = { 0,2,3, 0,1,2 };

	//int index[] = { 0,2,3, 0,1,2, 0,4,1};

	

	// �C���f�b�N�X�o�b�t�@�𐶐�����
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
		//�G���[����
		MessageBox(nullptr, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
		
	}

	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}

	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");

	return S_OK;
}

void Quad::Draw(Transform& transform)
{
	//�R���X�^���g�o�b�t�@�ɓn�����
	//XMVECTOR position = { 0, 3, -10, 0 };	//�J�����̈ʒu
	//XMVECTOR target = { 0, 0, 0, 0 };	//�J�����̏œ_
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//�r���[�s�� //�J�������猩�Ă̊g�����邽�߂̂���  //XMVectorSet�̓J�����̏����
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//�ˉe�s�� //���ߊ������� //�������@��p�A����p�����W�A���ŕ\�����Ă���
	//������ �A�X�y�N�g�� ��O�����@�j�A�N���b�v�ʁ@��l���� �t�@�[�N���b�v��
	//�J�������Ɏ��߂�Ȃ�x���� -1����1 y����-1����1 z����-1����1
	//����p����������ƃY�[�����邱�ƂɂȂ�@�����̂��̂Ƌ߂��̂��̂̍����ς��Ȃ��Ȃ�@���ߊ����Ȃ��Ȃ�
	/*�J�����̕\�������͋߂����������������߂Ȃ��Ƃ����Ȃ�
	�������ɐݒ肵�Ȃ��Ƃǂ��܂ł������Ă��܂�����
	�߂����͂�����x�J�����Ƃ̋������Ȃ��Ƌ��������k���ĕ\���ł��Ȃ��Ȃ邩��*/
	//�j�A�N���b�v�ʂƃt�@�[�N���b�v�ʂ̋����͂Ȃ�ׂ��Z������@�Ȃ��������̂��ꂪ������@���̂����܂����ᑫ�肵�Ă�����悤�ɂȂ�@<- z�t�@�C�e�B���O

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform *Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	//cb.matWVP = XMMatrixTranspose(view * proj);
	cb.matW = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);


	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ

	//���_�o�b�t�@
	//UINT stride = sizeof(XMVECTOR); //�O�g���Ă����
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

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

	//�e�N�X�`���̃��[�h
	if (FAILED(LoadTexture()))
	{
		return E_FAIL;
	}

	return S_OK;
}

void Quad::Draw(Transform& transform)
{

	Direct3D::SetShader(SHADER_3D);
	transform.Calclation();//�g�����X�t�H�[�����v�Z
	//�R���X�^���g�o�b�t�@�ɏ���n��
	PassDataToCB(transform);

	//���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�R���X�^���g�o�b�t�@���p�C�v���C���ɃZ�b�g
	SetBufferToPipeline();

	//�`��
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
	// ���_���
	vertices_ =
	{
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},// �l�p�`�̒��_�i����j
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f,  0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},// �l�p�`�̒��_�i�E��j
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)},// �l�p�`�̒��_�i�E���j
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)}	// �l�p�`�̒��_�i�����j		
	};
	vertexNum_ = vertices_.size();
}

//���_�o�b�t�@���쐬
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
		MessageBox(NULL, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

//�C���f�b�N�X��������
void Quad::InitIndexData()
{
	index_ = { 0,2,3, 0,1,2 };

	//�C���f�b�N�X��
	indexNum_ = index_.size();
}

//�C���f�b�N�X�o�b�t�@���쐬
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
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}


//�R���X�^���g�o�b�t�@�쐬
HRESULT Quad::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	HRESULT hr;
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

//�e�N�X�`�������[�h
HRESULT Quad::LoadTexture()
{
	pTexture_ = new Texture;

	HRESULT hr;
	hr = pTexture_->Load("Assets\\Dice.png");
	if (FAILED(hr))
	{
		MessageBox(NULL, "�e�N�X�`���̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}


//�R���X�^���g�o�b�t�@�Ɋe�����n��
void Quad::PassDataToCB(Transform transform)
{

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();

	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();

	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ

}

//�e�o�b�t�@���p�C�v���C���ɃZ�b�g
void Quad::SetBufferToPipeline()
{
	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

	//Direct3D::pContext_->DrawIndexed(indexNum_, 0, 0);
}