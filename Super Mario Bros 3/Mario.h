#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "PlayScene.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SLOW_SPEED 0.125f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_TELE_SPEED		0.05f

#define MARIO_ACCEL_WALK_X	0.0005f
#define	MARIO_ACCEL_RUN_SLOW_X	0.0007f
#define MARIO_ACCEL_RUN_X	0.0009f

#define MARIO_JUMP_SPEED_Y		0.25f
#define MARIO_JUMP_RUN_SPEED_Y	0.35f
#define MARIO_JUMP_HOLDING_SPEED_Y 0.002f

#define MARIO_FLAP_FLOW_SPEED_Y 0.05f
#define MARIO_FLAP_FLOW_ACC_Y	0.0001f
#define MARIO_FLAP_FLY_SPEED_Y	0.01f
#define MARIO_FLAP_FLY_ACC_Y	0.0001f
#define MARIO_DROP_SPEED_Y		0.25f
#define MARIO_FLY_SPEED_Y		0.15f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_HOLD_JUMP		302

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_KICK			700

#define MARIO_STATE_FLAP_FLOW		800
#define MARIO_STATE_FLAP_FLOW_RELEASE 801

#define MARIO_STATE_ATTACK			900

#define MARIO_STATE_TELE			1000

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_RUNNING_SLOW_LEFT	602
#define ID_ANI_MARIO_RUNNING_SLOW_RIGHT	603

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_JUMP_RELEASE_LEFT 802
#define ID_ANI_MARIO_JUMP_RELEASE_RIGHT 803

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_HOLDSHELL_IDLE_LEFT 2500
#define ID_ANI_MARIO_HOLDSHELL_IDLE_RIGHT 2501
#define ID_ANI_MARIO_HOLDSHELL_WALK_LEFT 2502
#define ID_ANI_MARIO_HOLDSHELL_WALK_RIGHT 2503
#define ID_ANI_MARIO_HOLDSHELL_JUMP_LEFT 2504
#define ID_ANI_MARIO_HOLDSHELL_JUMP_RIGHT 2505
#define ID_ANI_MARIO_HOLDSHELL_KICK_LEFT 2506
#define ID_ANI_MARIO_HOLDSHELL_KICK_RIGHT 2507

#define ID_ANI_MARIO_TELE 2900

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_RUNNING_SLOW_LEFT 1302
#define ID_ANI_MARIO_SMALL_RUNNING_SLOW_RIGHT 1303

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_HOLDSHELL_IDLE_LEFT 2600
#define ID_ANI_MARIO_SMALL_HOLDSHELL_IDLE_RIGHT 2601
#define ID_ANI_MARIO_SMALL_HOLDSHELL_WALK_LEFT 2602
#define ID_ANI_MARIO_SMALL_HOLDSHELL_WALK_RIGHT 2603
#define ID_ANI_MARIO_SMALL_HOLDSHELL_JUMP_LEFT 2604
#define ID_ANI_MARIO_SMALL_HOLDSHELL_JUMP_RIGHT 2605
#define ID_ANI_MARIO_SMALL_HOLDSHELL_KICK_LEFT 2606
#define ID_ANI_MARIO_SMALL_HOLDSHELL_KICK_RIGHT 2607

#define ID_ANI_MARIO_SMALL_TELE 3000

// RACOON MARIO
#define ID_ANI_MARIO_RACOON_IDLE_LEFT 1700
#define ID_ANI_MARIO_RACOON_IDLE_RIGHT 1701

#define ID_ANI_MARIO_RACOON_WALKING_LEFT 1800
#define ID_ANI_MARIO_RACOON_WALKING_RIGHT 1801

#define ID_ANI_MARIO_RACOON_RUNNING_LEFT 1900
#define ID_ANI_MARIO_RACOON_RUNNING_RIGHT 1901

#define ID_ANI_MARIO_RACOON_RUNNING_SLOW_LEFT 1902
#define ID_ANI_MARIO_RACOON_RUNNING_SLOW_RIGHT 1903

#define ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT 2000
#define ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT 2001

#define ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT 2100
#define ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT 2101

#define ID_ANI_MARIO_RACOON_JUMP_RELEASE_LEFT 2102
#define ID_ANI_MARIO_RACOON_JUMP_RELEASE_RIGHT 2103

#define ID_ANI_MARIO_RACOON_SIT_LEFT 2200
#define ID_ANI_MARIO_RACOON_SIT_RIGHT 2201

#define ID_ANI_MARIO_RACOON_BRACE_LEFT 2300
#define ID_ANI_MARIO_RACOON_BRACE_RIGHT 2301

#define ID_ANI_MARIO_RACOON_FLAP_FLOW_LEFT 2400
#define ID_ANI_MARIO_RACOON_FLAP_FLOW_RIGHT 2401
#define ID_ANI_MARIO_RACOON_FLAP_FLY_LEFT 2402
#define ID_ANI_MARIO_RACOON_FLAP_FLY_RIGHT 2403

#define	ID_ANI_MARIO_RACOON_HOLDSHELL_IDLE_LEFT 2700
#define	ID_ANI_MARIO_RACOON_HOLDSHELL_IDLE_RIGHT 2701
#define	ID_ANI_MARIO_RACOON_HOLDSHELL_WALK_LEFT 2702
#define	ID_ANI_MARIO_RACOON_HOLDSHELL_WALK_RIGHT 2703
#define	ID_ANI_MARIO_RACOON_HOLDSHELL_JUMP_LEFT 2704
#define	ID_ANI_MARIO_RACOON_HOLDSHELL_JUMP_RIGHT 2705
#define	ID_ANI_MARIO_RACOON_HOLDSHELL_KICK_LEFT 2706
#define	ID_ANI_MARIO_RACOON_HOLDSHELL_KICK_RIGHT 2707

#define ID_ANI_MARIO_RACOON_ATTACK_LEFT 2800
#define ID_ANI_MARIO_RACOON_ATTACK_RIGHT 2801

#define ID_ANI_MARIO_RACOON_TELE 3100

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACOON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  16
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16
#define MARIO_RACOON_HIT_BBOX_WIDTH 48
#define MARIO_RACOON_HIT_BBOX_HEIGHT 8

#define MARIO_RACOON_HIT_BBOX_X 0
#define MARIO_RACOON_HIT_BBOX_Y 8

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_HOLD_X 12
#define MARIO_HOLD_Y -1
#define MARIO_BIG_HOLD_Y 2

#define MARIO_TELE_DIS 32

#define MARIO_UNTOUCHABLE_TIME 1500

#define MARIO_ON_AIR_TIME		15
#define MARIO_FIRST_JUMP_TIME	5

#define MARIO_FLOW_TIME			200
#define MARIO_FLAP_COOLDOWN		150
#define MARIO_KICK_TIME			150
#define MARIO_ATTACK_TIME		350
#define MARIO_DIE_TIME			2000

#define MARIO_RUN_CHARGE_MAX	1500
#define MARIO_RUN_CHARGE_DROP_TIME	400

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isHolding;
	BOOLEAN canSetState;
	BOOLEAN isAttacking;
	BOOLEAN isCamFollowY;
	BOOLEAN isCamStaticY;
	BOOLEAN isTeleUp;
	BOOLEAN isFinishTele;
	BOOLEAN isBlck;
	BOOLEAN isColl;

	CGameObject* holdedObj = NULL;
	CGameObject* nearestTele = NULL;

	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	long onAir;
	bool canJump;
	long flowTimer;
	long flapTimer;
	long kickTimer;
	long runCharge;
	long runChargeTimer;
	long attackTimer;
	long waitTele;
	int die_time;

	int level; 
	int lives;
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithMysteryBox(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithRacoonLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithFlyGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithSpawner(LPCOLLISIONEVENT e);
	void OnCollisionWithFlyKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithNormalKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlantBite(LPCOLLISIONEVENT e);
	void OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithButton(LPCOLLISIONEVENT e);
	void OnCollisionWithTeleporter (LPCOLLISIONEVENT e);
	void OnCollisionWithEndGate(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		isHolding = false;
		canSetState = true;
		isAttacking = false;
		isCamFollowY = false;
		isCamStaticY = false;
		isTeleUp = false;
		isFinishTele = false;
		isBlck = true;
		isColl = true;

		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		onAir = 0;
		canJump = true;
		flowTimer = 0;
		flapTimer = 0;
		kickTimer = 0;
		runCharge = 0;
		runChargeTimer = 0;
		attackTimer = 0;
		waitTele = 0;
		die_time = 0;

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		lives = 4;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void RenderHitBox();
	void SetState(int state);

	int IsCollidable() { return (state != MARIO_STATE_DIE && isColl); }

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0 && isBlck); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel();
	int GetLives() { return lives; }
	int GetRunCharges();
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetHitBox(float& left, float& top, float& right, float& bottom);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	bool IsHoldingShell();
	bool IsDamaged();
	bool IsGrounded();
	bool IsCamFollowY() { return isCamFollowY; }
	bool IsCamStaticY() { return isCamStaticY; }
	bool InHitBox(LPGAMEOBJECT obj);
	int FaceDirection() { return nx; }
	int IsUp() { return (vy > 0) ? 1 : -1; }

	void Flap();
	void Attack(vector<LPGAMEOBJECT>* coObjects);
	void Teleport(bool isUp);
	void Restart();
};