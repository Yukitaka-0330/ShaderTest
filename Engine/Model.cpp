#include"Model.h"
#include"Direct3D.h"
namespace Model
{
	//���f���̃|�C���^���Ԃ�����ł����x�N�^
	vector<ModelData*>_datas;

	int Load(std::string fileName)
	{
		//�t�@�C�����̃��f����ǂݍ���ŁA�������f�����̂��̂��������炻�̃��f���ԍ�(�z��̃C���f�b�N�X-1)��Ԃ��֐�
		//�������O�̃��f�����Ȃ�������A���f����ǂݍ���ŁA�x�N�^�ɒǉ�

		ModelData* pData = new ModelData;
		pData->mFileName_ = fileName;
		pData->pfbx_ = nullptr;

		//�t�@�C���l�[����������������ǂ܂Ȃ�
		for (auto& e : _datas)
		{
			if (e->mFileName_ == fileName)
			{
				pData->pfbx_ = e->pfbx_;
				break;
			}
		}

		if (pData->pfbx_ == nullptr)
		{
			pData->pfbx_ = new Fbx;
			pData->pfbx_->Load(fileName);	
		}

		_datas.push_back(pData);
		return(_datas.size() - 1);
	}
	void SetTransform(int hModel, Transform& transform)
	{
		//���f���ԍ���_datas�̃C���f�b�N�X
		_datas[hModel]->Transform_ = transform;
	}
	void Draw(int hModel)
	{
		//���f���ԍ��́A_datas�̃C���f�b�N�X
		_datas[hModel]->pfbx_->Draw(_datas[hModel]->Transform_);
	}
	void Release()
	{
		bool isRefferd = false; //�Q�Ƃ���Ă��邩
		for (int i= 0; i<_datas.size();i++)
		{
			for (int j = i + 1; j < _datas.size(); j++)
			{
				if (_datas[i]->pfbx_ == _datas[i]->pfbx_)
				{
					isRefferd = true;
					break;
				}
			}
			if (isRefferd == false)
			{
				SAFE_DELETE(_datas[i]->pfbx_);
			}
			SAFE_DELETE(_datas[i]);
		}
		_datas.clear();
		
	}
}