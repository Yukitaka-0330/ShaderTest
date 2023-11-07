#pragma once
#include <list>
#include <string>
#include "Transform.h"

using std::string;
using std::list;

class SphereCollider;
;
class GameObject
{
protected:
	list <GameObject*> childList_;
	Transform	transform_;
	GameObject* pParent_;
	string	objectName_;
	bool isDead;
	SphereCollider* pCollider_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

	void KillMe();
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	/*template<class GameObject> void SetTransform(GameObject SetPosition())
	{

	}*/
	void SetPosition(XMFLOAT3 _position);
	void SetRotate(XMFLOAT3 _rotate);
	void SetScale(XMFLOAT3 _scale);
	GameObject* FindChildObject(string _objName);
	GameObject* GetRootJob();
	GameObject* FindObject(string _objName);
	void AddCollider(SphereCollider* pCollider);
	void Collision(GameObject* pTarget);
	virtual void OnCollision(GameObject* pTarget);
	void RoundRobin(GameObject* pTarget);
	
public:

	//テンプレートの定義
	template <class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* pObject;
		pObject = new T(parent);
		pObject->Initialize();
		parent->childList_.push_back(pObject);
		return pObject;
	}

};
