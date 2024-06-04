#pragma once
#include "GameObject.h"
#include "debug.h"

/*
	An empry object with no sprite
*/

class CEmptyObject : public CGameObject
{
protected:
	float bboxWidth;
	float bboxHeight;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CEmptyObject(float x, float y, float bboxWidth, float bboxHeight);
};