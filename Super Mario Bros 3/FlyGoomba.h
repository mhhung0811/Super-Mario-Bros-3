#pragma once
#include "GameObject.h"
#include "Wing.h"
#include "Koopa.h"
#include "PlayScene.h"

#define FLY_GOOMBA_GRAVITY 0.002f
#define FLY_GOOMBA_WALKING_SPEED 0.05f
#define FLY_GOOMBA_SMALL_JUMP_SPEED 0.15f
#define FLY_GOOMBA_BIG_JUMP_SPEED 0.45f
#define FLY_GOOMBA_ALT_DIE_SPEED_X 0.1f
#define FLY_GOOMBA_ALT_DIE_SPEED_Y 0.25f

#define FLY_GOOMBA_JUMP_STEP 250
#define FLY_GOOMBA_JUMP_COOLDOWN 800

#define FLY_GOOMBA_BBOX_WIDTH 16
#define FLY_GOOMBA_BBOX_HEIGHT 13
#define FLY_GOOMBA_BBOX_HEIGHT_DIE 7

#define FLY_GOOMBA_WING_X 7
#define FLY_GOOMBA_WING_Y 7

#define FLY_GOOMBA_DIE_TIMEOUT 500
#define FLY_GOOMBA_ALT_DIE_TIMEOUT 1000

#define FLY_GOOMBA_STATE_WALKING 100
#define FLY_GOOMBA_STATE_DIE 200
#define FLY_GOOMBA_STATE_ALT_DIE 300

#define ID_ANI_FLY_GOOMBA_WALKING 173000
#define ID_ANI_FLY_GOOMBA_DIE 174000
#define ID_ANI_FLY_GOOMBA_ALT_DIE 174001

class CFlyGoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	bool isColl = 1;
	bool haveWings;
	int stepTimer;
	int jumpCount;
	int jumpTimer;
	bool isOnPlatform;

	CWing* leftWing;
	CWing* rightWing;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return isColl; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFlyGoomba(float x, float y);
	virtual void SetState(int state);
	void Damaged();
	void AltDie(int dir = 0);
};