#pragma once
#include "GameObject.h"

#define WING_BBOX_WIDTH 8
#define WING_BBOX_HEIGHT 8

#define WING_STATE_CLOSE 100
#define WING_STATE_FLAP_SLOW 200
#define WING_STATE_FLAP_FAST 300

#define ID_ANI_WING_CLOSE_LEFT 185000
#define ID_ANI_WING_CLOSE_RIGHT 185001
#define ID_ANI_WING_FLAP_SLOW_LEFT 186000
#define ID_ANI_WING_FLAP_SLOW_RIGHT 186001
#define ID_ANI_WING_FLAP_FAST_LEFT 187000
#define ID_ANI_WING_FLAP_FAST_RIGHT 187001

class CWing : public CGameObject
{
protected:
	int dir;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CWing(float x, float y, int dir = -1);
	virtual void SetState(int state);
};