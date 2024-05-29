#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "debug.h"

#define FIREBALL_BBOX_WIDTH 8
#define FIREBALL_BBOX_HEIGHT 8

#define FIREBALL_SPEED 0.03f

#define FIREBALL_DIRECTION_LEFT_LOW_0 0
#define FIREBALL_DIRECTION_LEFT_LOW_1 1
#define FIREBALL_DIRECTION_LEFT_HIGH_0 2
#define FIREBALL_DIRECTION_LEFT_HIGH_1 3
#define FIREBALL_DIRECTION_RIGHT_LOW_0 4
#define FIREBALL_DIRECTION_RIGHT_LOW_1 5
#define FIREBALL_DIRECTION_RIGHT_HIGH_0 6
#define FIREBALL_DIRECTION_RIGHT_HIGH_1 7

#define FIREBALL_STATE_FLYING 0
#define FIREBALL_STATE_VANISH 1

#define ID_ANI_FIREBALL_FLY 130100

class CFireBall : public CGameObject
{
protected:
	int direction;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CFireBall(float x, float y, int dir);
	virtual void SetState(int state);
};