#include "GameObject.h"
#include "Direct3D.h"
#include "SphereCollider.h"
GameObject::GameObject() : pParent_(nullptr), objectName_("")
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :pParent_(parent), objectName_(name),isDead(false),pCollider_(nullptr)
{
	if (parent != nullptr)
	{
		this->transform_.pParent_ = &(parent->transform_);
	}
	
}

GameObject::~GameObject()
{
	SAFE_RELEASE(pParent_);
}

// �������폜����
void GameObject::KillMe()
{
	isDead = true;
}


void GameObject::UpdateSub()
{
	Update();
	RoundRobin(GetRootJob());

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->isDead)
		{
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else 
			itr++;
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::ReleaseSub()
{
	
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->ReleaseSub();

	Release();
}

//void GameObject::SetTrans(Transform _transform)
//{
//	this->transform_ = _transform;
//}

void GameObject::SetPosition(XMFLOAT3 _position)
{
	this->transform_.position_ = _position;
}

void GameObject::SetRotate(XMFLOAT3 _rotate)
{
	this->transform_.rotate_ = _rotate;
}

void GameObject::SetScale(XMFLOAT3 _scale)
{
	this->transform_.scale_ = _scale;
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_)
	{
		return(this); //������_objName�̃I�u�W�F�N�g������!!
	}
	else
	{
		for (auto itr : childList_)
		{

			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}

		//��L�Ɠ����@�C�e���[�^�[�̏��������قȂ邾��
		/*for (auto itr = childList_.begin();itr != childList_.end(); itr++)
		{

			GameObject* obj = (*itr)->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}*/
	}
	return nullptr;
}


/// <summary>
/// �ċN�Ăяo����RootJob��T���Ă��̃A�h���X��Ԃ��֐�
/// </summary>
/// <returns>RootJob�̃A�h���X(GameObject * �^)</returns>
GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	//�������猩�āA���[�g�W���u��T���āA���̃��[�g�W���u����S���̎q�������ǂ���objName��T���B
	return GetRootJob()->FindChildObject(_objName);
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	if (pTarget == this || pTarget->pCollider_ == nullptr)
	{
		return; //�������g�A�܂��̓^�[�Q�b�g�ɃR���C�_�[���A�^�b�`����Ă��Ȃ�
	}

	

	/*XMVECTOR v
	{
		this->transform_.position_.x - pTarget->transform_.position_.x,
		this->transform_.position_.y - pTarget->transform_.position_.y,
		this->transform_.position_.z - pTarget->transform_.position_.z,
	};	
	XMVECTOR dist = XMVector3Dot(v, v);*/
	float dist = (transform_.position_.x - pTarget->transform_.position_.x) * (transform_.position_.x - pTarget->transform_.position_.x)
		+ (transform_.position_.y - pTarget->transform_.position_.y) * (transform_.position_.y - pTarget->transform_.position_.y)
		+ (transform_.position_.z - pTarget->transform_.position_.z) * (transform_.position_.x - pTarget->transform_.position_.z);
	float rDist = (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius() * (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius()));

	if (dist <= rDist)
	{
		OnCollision(pTarget);
 		//double p = 0;
		//KillMe();
	}

		
}

 void GameObject::OnCollision(GameObject* pTarget)
{
	 /*if (pTarget == this || pTarget->pCollider_ == nullptr)
	 {
		 KillMe();
	 }*/
}


void GameObject::RoundRobin(GameObject* pTarget)
{
	if(pCollider_ == nullptr)
		return;

	if (pTarget->pCollider_ != nullptr) //�����ƃ^�[�Q�b�g
		Collision(pTarget);

	//if (pTarget->pCollider_ != nullptr) //�����ƃ^�[�Q�b�g
	//	OnCollision(pTarget);


	//�����̎q���S���ƃ^�[�Q�b�g
	for (auto itr = pTarget->childList_.begin();itr != pTarget->childList_.end(); itr++)
		RoundRobin(*itr);
}

