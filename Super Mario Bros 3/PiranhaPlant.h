#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#include "debug.h"

#define PIRANHAPLANT_BBOX_WIDTH 16
#define PIRANHAPLANT_BBOX_HEIGHT 31
#define PIRANHAPLANT_APPEAR_SPEED 0.025f

#define PIRANHAPLANT_IDLE_TIME 1000

#define PIRANHAPLANT_STATE_IDLE 100
#define PIRANHAPLANT_STATE_APPEAR 200
#define PIRANHAPLANT_STATE_DISAPPEAR 300

#define ID_ANI_PIRANHAPLANT_APPEAR_LEFT 121100
#define ID_ANI_PIRANHAPLANT_APPEAR_RIGHT 121300

class CPiranhaPlant : public CGameObject
{
protected:
	float fixedX;
	float fixedY;
	unsigned long isIdle;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void RenderBoundingBox();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CPiranhaPlant(float x, float y);
	virtual void SetState(int state);
};