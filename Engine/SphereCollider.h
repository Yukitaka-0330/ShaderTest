#pragma once
class SphereCollider
{
private:
	float radius_;

public:
	SphereCollider(float _r);
	float GetRadius() { return(radius_); }

};

