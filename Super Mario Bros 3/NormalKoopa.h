#pragma once
#include "GameObject.h"
#include "EmptyObject.h"
#include "PlayScene.h"
#include "MysteryBox.h"
#include "Goomba.h"
#include "FlyGoomba.h"
#include "Mario.h"
#include "debug.h"

#define NORMAL_KOOPA_GRAVITY 0.002f
#define NORMAL_KOOPA_WALKING_SPEED 0.05f
#define NORMAL_KOOPA_ROLLING_SPEED 0.2f
#define NORMAL_KOOPA_RESURRECT_TIME 1000
#define NORMAL_KOOPA_RESURRECT_COOLDOWN 5000

#define NORMAL_KOOPA_BBOX_WIDTH 14
#define NORMAL_KOOPA_BBOX_HEIGHT 24
#define NORMAL_KOOPA_SHELL_BBOX_HEIGHT 14

#define NORMAL_KOOPA_GROUND_CHECK_X 9
#define NORMAL_KOOPA_GROUND_CHECK_Y 10

#define NORMAL_KOOPA_STATE_WALKING 100
#define NORMAL_KOOPA_STATE_SHELL_IDLE 200
#define NORMAL_KOOPA_STATE_SHELL_ROLL 300
#define NORMAL_KOOPA_STATE_SHELL_RESURRECT 400
//#define KOOPA_STATE_SHELL_HOLDED 500
#define NORMAL_KOOPA_STATE_DIE 600

#define ID_ANI_NORMAL_KOOPA_WALK_LEFT 191002
#define ID_ANI_NORMAL_KOOPA_WALK_RIGHT 191102
#define ID_ANI_NORMAL_KOOPA_SHELL_APPEAR 192101
#define ID_ANI_NORMAL_KOOPA_SHELL_ROLL 192203

#define ID_SPR_NORMAL_KOOPA_SHELL_IDLE 192000

class CNormalKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	bool isHolded = false;

	float holdAdjX = 0;
	float holdAdjY = 0;
	long resTime = 0;
	long resCoolDown = 0;

	CGameObject* groundCheck;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	bool EdgeCheck();
public:
	CNormalKoopa(float x, float y);
	virtual void SetState(int state);
	void ToShellIdle();
	void ToShellRoll(int dir);
	void ToShellHold(float adjX, float adjY);
	void ToResurrect();
	void ToWalking();
	bool IsHolded() { return isHolded; }
};