#pragma once
#include "GameObject.h"
#include "PlayScene.h"

class CEndGate : public CGameObject
{
protected:
	float bboxWidth;
	float bboxHeight;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CEndGate(float x, float y, float bboxWidth, float bboxHeight);
	void End();
};