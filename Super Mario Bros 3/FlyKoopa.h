#pragma once
#include "GameObject.h"
#include "EmptyObject.h"
#include "PlayScene.h"
#include "MysteryBox.h"
#include "Goomba.h"
#include "FlyGoomba.h"
#include "NormalKoopa.h"
#include "Mario.h"
#include "Wing.h"
#include "debug.h"

#define FLY_KOOPA_GRAVITY 0.002f
#define FLY_KOOPA_WALKING_SPEED 0.05f
#define FLY_KOOPA_ROLLING_SPEED 0.2f
#define FLY_KOOPA_JUMP_SPEED 0.45f
#define FLY_KOOMBA_DIE_SPEED_X 0.1f
#define FLY_KOOMBA_DIE_SPEED_Y 0.25f

#define FLY_KOOPA_RESURRECT_TIME 1000
#define FLY_KOOPA_RESURRECT_COOLDOWN 5000
#define FLY_KOOPA_JUMP_COOLDOWN 1000
#define FLY_KOOPA_DIE_TIMEOUT 1000

#define FLY_KOOPA_BBOX_WIDTH 14
#define FLY_KOOPA_BBOX_HEIGHT 24
#define FLY_KOOPA_SHELL_BBOX_HEIGHT 14

#define FLY_KOOPA_WING_X 3
#define FLY_KOOPA_WINY_Y 4

#define FLY_KOOPA_GROUND_CHECK_X 9
#define FLY_KOOPA_GROUND_CHECK_Y 10

#define FLY_KOOPA_STATE_WALKING 100
#define FLY_KOOPA_STATE_SHELL_IDLE 200
#define FLY_KOOPA_STATE_SHELL_ROLL 300
#define FLY_KOOPA_STATE_SHELL_RESURRECT 400
//#define KOOPA_STATE_SHELL_HOLDED 500
#define FLY_KOOPA_STATE_DIE 600

#define ID_ANI_FLY_KOOPA_WALK_LEFT 191002
#define ID_ANI_FLY_KOOPA_WALK_RIGHT 191102
#define ID_ANI_FLY_KOOPA_SHELL_APPEAR 192101
#define ID_ANI_FLY_KOOPA_SHELL_ROLL 192203
#define ID_ANI_FLY_KOOPA_DIE 193001

#define ID_SPR_FLY_KOOPA_SHELL_IDLE 192000

class CFlyKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	bool haveWing;
	int jumpTimer;
	bool isOnPlatform;

	long die_start;
	CWing* wing;

	bool isColl = true;
	bool isBlck = false;
	bool isHolded = false;

	float holdAdjX = 0;
	float holdAdjY = 0;
	long resTime = 0;
	long resCoolDown = 0;
	long toShellTimer = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return isColl; };
	virtual int IsBlocking() { return isBlck; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CFlyKoopa(float x, float y);
	virtual void SetState(int state);
	bool HaveWing() { return haveWing; }
	void LoseWing();
	void ToShellIdle();
	void ToShellRoll(int dir);
	void ToShellHold(float adjX, float adjY);
	void ToResurrect();
	void ToWalking();
	bool IsHolded() { return isHolded; }
	bool IsRolled() { return (state == FLY_KOOPA_STATE_SHELL_ROLL) ? 1 : 0; }
};