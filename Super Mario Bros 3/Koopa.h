#pragma once
#include "GameObject.h"
#include "EmptyObject.h"
#include "PlayScene.h"
#include "MysteryBox.h"
#include "BreakableBrick.h"
#include "Goomba.h"
#include "FlyGoomba.h"
#include "Mario.h"
#include "FlyKoopa.h"
#include "NormalKoopa.h"
#include "debug.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_ROLLING_SPEED 0.2f
#define KOOMBA_DIE_SPEED_X 0.1f
#define KOOMBA_DIE_SPEED_Y 0.25f

#define KOOPA_RESURRECT_TIME 1000
#define KOOPA_RESURRECT_COOLDOWN 5000
#define KOOPA_DIE_TIMEOUT 1000

#define KOOPA_BBOX_WIDTH 14
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_SHELL_BBOX_HEIGHT 14

#define KOOPA_GROUND_CHECK_X 9
#define KOOPA_GROUND_CHECK_Y 10

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL_IDLE 200
#define KOOPA_STATE_SHELL_ROLL 300
#define KOOPA_STATE_SHELL_RESURRECT 400
//#define KOOPA_STATE_SHELL_HOLDED 500
#define KOOPA_STATE_DIE 600

#define ID_ANI_KOOPA_WALK_LEFT 151002
#define ID_ANI_KOOPA_WALK_RIGHT 151102
#define ID_ANI_KOOPA_SHELL_APPEAR 152101
#define ID_ANI_KOOPA_SHELL_ROLL 152203
#define ID_ANI_KOOPA_DIE 153001

#define ID_SPR_KOOPA_SHELL_IDLE 152000

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	int point = 100;

	bool isColl = true;
	bool isBlck = false;
	bool isHolded = false;

	long die_start;

	float holdAdjX = 0;
	float holdAdjY = 0;
	long resTime = 0;
	long resCoolDown = 0;
	long toShellTimer = 0;

	CGameObject *groundCheck;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return isColl; };
	virtual int IsBlocking() { return isBlck; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	bool EdgeCheck();
public:
	CKoopa(float x, float y);
	virtual void SetState(int state);
	void ToShellIdle();
	void ToShellRoll(int dir);
	void ToShellHold(float adjX, float adjY);
	void ToResurrect();
	void ToWalking();
	bool IsHolded() { return isHolded; }
	bool IsRolled() { return (state == KOOPA_STATE_SHELL_ROLL) ? 1 : 0; }
	void Knocked(int dir = 0);
	void AltDie(int dir = 0);
	int GetPoint()
	{
		int res = 0;
		if (point > 0)
		{
			res = 100;
			point -= res;
		}
		return res;
	}
};