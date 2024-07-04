#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "MysteryBox.h"
#include "Mushroom.h"
#include "PiranhaPlant.h"
#include "FireBall.h"
#include "Koopa.h"
#include "RacoonLeaf.h"
#include "FlyGoomba.h"
#include "Spawner.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y > (SCREEN_HEIGHT - SCREEN_UI) / 2)
	{
		isCamFollowY = false;
	}

	// Run Charge
	if (abs(vx) >= MARIO_RUNNING_SLOW_SPEED && 
		abs(ax) >= MARIO_ACCEL_RUN_SLOW_X && 
		vx * ax > 0 &&
		runCharge <= MARIO_RUN_CHARGE_MAX * 1.2)
	{
		if (isOnPlatform)
			runCharge += dt;
		runChargeTimer = 0;
	}
	else
	{
		if (runChargeTimer >= MARIO_RUN_CHARGE_DROP_TIME && runCharge > 0)
		{
			runCharge -= MARIO_RUN_CHARGE_MAX / 6;
			if (runCharge < 0) runCharge = 0;
			runChargeTimer = 0;
		}
		else
		{
			if (runCharge > 0)
				runChargeTimer += dt;
		}
	}

	// Flow timer
	if (flowTimer > 0)
	{
		flowTimer -= dt;
		if (flowTimer <= 0 || isOnPlatform)
		{
			ay = MARIO_GRAVITY;
		}
	}

	// Flap timer
	if (isOnPlatform) onAir = 0;
	else onAir += 1;
	if (flapTimer > 0)
	{
		flapTimer -= dt;
	}
	if (flapTimer <= 0 && state == MARIO_STATE_FLAP_FLOW)
	{
		SetState(MARIO_STATE_FLAP_FLOW_RELEASE);
	}

	// Kick timer
	if (state == MARIO_STATE_KICK)
	{
		kickTimer -= dt;
		if (kickTimer <= 0)
		{
			canSetState = true;
			kickTimer = 0;
		}
	}

	// Max Drop Speed
	if (state == MARIO_STATE_FLAP_FLOW && vy > MARIO_FLAP_FLOW_SPEED_Y) vy = MARIO_FLAP_FLOW_SPEED_Y;
	else if (vy > MARIO_DROP_SPEED_Y) vy = MARIO_DROP_SPEED_Y;

	// Max Fly Speed
	if ((state == MARIO_STATE_FLAP_FLOW || state == MARIO_STATE_FLAP_FLOW_RELEASE) && vy < -MARIO_FLY_SPEED_Y) vy = -MARIO_FLY_SPEED_Y;

	// Drag force
	if (state == MARIO_STATE_IDLE && ax == 0)
	{
		vx /= 1.1f;
		if (abs(vx) <= 0.00001f) vx = 0;
	}

	// Max Velocity
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) 
		{
			isOnPlatform = true;
		}
		else
		{
			runChargeTimer = MARIO_RUN_CHARGE_DROP_TIME;
		}
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}	

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMysteryBox*>(e->obj))
		OnCollisionWithMysteryBox(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranhaPlant(e);
	else if (dynamic_cast<CFireBall*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CRacoonLeaf*>(e->obj))
		OnCollisionWithRacoonLeaf(e);
	else if (dynamic_cast<CFlyGoomba*>(e->obj))
		OnCollisionWithFlyGoomba(e);
	else if (dynamic_cast<CSpawner*>(e->obj))
		OnCollisionWithSpawner(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		IsDamaged();
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithMysteryBox(LPCOLLISIONEVENT e)
{
	if (e->ny > 0)
	{
		onAir = MARIO_ON_AIR_TIME;
		CMysteryBox* p = (CMysteryBox*)e->obj;
		p->OpenBox();
	}
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* p = (CMushroom*)e->obj;
	SetLevel(MARIO_LEVEL_BIG);
	p->IsAbsorbed();
}

void CMario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	CPiranhaPlant* piranhaPlant = dynamic_cast<CPiranhaPlant*>(e->obj);
	IsDamaged();
}

void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	CFireBall* fireBall = dynamic_cast<CFireBall*>(e->obj);
	bool damageSuccess = IsDamaged();
	if (damageSuccess == true) fireBall->Delete();
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	switch (koopa->GetState())
	{
	case KOOPA_STATE_WALKING:
	{
		// jump on top >> turn Koopa to shell and deflect a bit 
		if (e->ny < 0)
		{
			koopa->ToShellIdle();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else // hit by koopa
		{
			IsDamaged();
		}
		break;
	}
	case KOOPA_STATE_SHELL_IDLE:
	{
		float kx, ky;
		koopa->GetPosition(kx, ky);
		if (isHolding)
		{
			holdedObj = koopa;
			if (level == MARIO_LEVEL_SMALL) koopa->ToShellHold(MARIO_HOLD_X, MARIO_HOLD_Y);
			else koopa->ToShellHold(MARIO_HOLD_X, MARIO_BIG_HOLD_Y);
		}
		else
		{
			// deflect if jump on top
			if (e->ny < 0)
			{
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			float kx, ky;
			koopa->GetPosition(kx, ky);
			koopa->SetPosition(kx, ky + (KOOPA_BBOX_HEIGHT - KOOPA_SHELL_BBOX_HEIGHT) / 2 - 10);
			koopa->ToShellRoll((kx - x > 0) ? 1 : -1);
		}
		break;
	}
	case KOOPA_STATE_SHELL_ROLL:
	{
		// jump on top >> stop Koopa shell and deflect a bit 
		if (e->ny < 0)
		{
			float kx, ky;
			koopa->GetPosition(kx, ky);
			koopa->SetPosition(kx, ky + (KOOPA_BBOX_HEIGHT - KOOPA_SHELL_BBOX_HEIGHT) / 2 - 10);
			koopa->ToShellIdle();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else // hit by koopa
		{
			IsDamaged();
		}
		break;
	}
	default:
		break;
	}
}

void CMario::OnCollisionWithRacoonLeaf(LPCOLLISIONEVENT e)
{
	CRacoonLeaf* p = (CRacoonLeaf*)e->obj;
	SetLevel(MARIO_LEVEL_RACOON);
	p->IsAbsorbed();
}

void CMario::OnCollisionWithFlyGoomba(LPCOLLISIONEVENT e)
{
	CFlyGoomba* flyGoomba = dynamic_cast<CFlyGoomba*>(e->obj);

	// jump on top >> kill damage Fly Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (flyGoomba->GetState() != FLY_GOOMBA_STATE_DIE)
		{
			float kx, ky;
			flyGoomba->GetPosition(kx, ky);
			flyGoomba->SetPosition(kx, ky + (FLY_GOOMBA_BBOX_HEIGHT) / 2 - 10);
			flyGoomba->Damaged();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		IsDamaged();
	}
}

void CMario::OnCollisionWithSpawner(LPCOLLISIONEVENT e)
{
	onAir = MARIO_ON_AIR_TIME;
	CSpawner* spawner = dynamic_cast<CSpawner*>(e->obj);
	spawner->Spawn();
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (state == MARIO_STATE_KICK)
	{
		aniId = (nx >= 0) ? ID_ANI_MARIO_SMALL_HOLDSHELL_KICK_RIGHT : ID_ANI_MARIO_SMALL_HOLDSHELL_KICK_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (holdedObj)
		{
			aniId = (nx >= 0) ? ID_ANI_MARIO_SMALL_HOLDSHELL_JUMP_RIGHT : ID_ANI_MARIO_SMALL_HOLDSHELL_JUMP_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			aniId = (nx >= 0) ? ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT : ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			aniId = (nx >= 0) ? ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT : ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
	if (isSitting)
	{
		aniId = (nx >= 0) ? ID_ANI_MARIO_SIT_RIGHT : ID_ANI_MARIO_SIT_LEFT;
	}
	else if (vx == 0)
	{
		if (nx > 0)
		{
			if (holdedObj) aniId = ID_ANI_MARIO_SMALL_HOLDSHELL_IDLE_RIGHT;
			else aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
		}
		else
		{
			if (holdedObj) aniId = ID_ANI_MARIO_SMALL_HOLDSHELL_IDLE_LEFT;
			else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
		}
	}
	else if (vx > 0)
	{
		if (holdedObj && ax == 0)
			aniId = ID_ANI_MARIO_SMALL_HOLDSHELL_IDLE_RIGHT;
		else if (holdedObj)
			aniId = ID_ANI_MARIO_SMALL_HOLDSHELL_WALK_RIGHT;
		else if (ax < 0)
			aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
		else if (ax == MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
		else if (ax == MARIO_ACCEL_RUN_SLOW_X)
			aniId = ID_ANI_MARIO_SMALL_RUNNING_SLOW_RIGHT;
		else if (ax == MARIO_ACCEL_WALK_X)		
			aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
		else if (ax == 0)
			aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
	}
	else // vx < 0
	{
		if (holdedObj && ax == 0)
			aniId = ID_ANI_MARIO_SMALL_HOLDSHELL_IDLE_LEFT;
		else if (holdedObj)
			aniId = ID_ANI_MARIO_SMALL_HOLDSHELL_WALK_LEFT;
		else if (ax > 0)
			aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
		else if (ax == -MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
		else if (ax == MARIO_ACCEL_RUN_SLOW_X)
			aniId = ID_ANI_MARIO_SMALL_RUNNING_SLOW_LEFT;
		else if (ax == -MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
		else if (ax == 0)
			aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (state == MARIO_STATE_KICK)
	{
		aniId = (nx >= 0) ? ID_ANI_MARIO_HOLDSHELL_KICK_RIGHT : ID_ANI_MARIO_HOLDSHELL_KICK_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (holdedObj)
		{
			aniId = (nx >= 0) ? ID_ANI_MARIO_HOLDSHELL_JUMP_RIGHT : ID_ANI_MARIO_HOLDSHELL_JUMP_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			aniId = (nx >= 0) ? ID_ANI_MARIO_JUMP_RUN_RIGHT : ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (vy >= 0)
			{
				aniId = (nx >= 0) ? ID_ANI_MARIO_JUMP_RELEASE_RIGHT : ID_ANI_MARIO_JUMP_RELEASE_LEFT;
			}
			else
			{
				aniId = (nx >= 0) ? ID_ANI_MARIO_JUMP_WALK_RIGHT : ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
	}
	else if (isSitting)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_SIT_RIGHT;
		else
			aniId = ID_ANI_MARIO_SIT_LEFT;
	}
	else if (vx == 0)
	{
		if (nx > 0)
		{
			if (holdedObj) aniId = ID_ANI_MARIO_HOLDSHELL_IDLE_RIGHT;
			else aniId = ID_ANI_MARIO_IDLE_RIGHT;
		}
		else
		{
			if (holdedObj) aniId = ID_ANI_MARIO_HOLDSHELL_IDLE_LEFT;
			else aniId = ID_ANI_MARIO_IDLE_LEFT;
		}
	}
	else if (vx > 0)
	{
		if (holdedObj && ax == 0)
			aniId = ID_ANI_MARIO_HOLDSHELL_IDLE_RIGHT;
		else if (holdedObj)
			aniId = ID_ANI_MARIO_HOLDSHELL_WALK_RIGHT;
		else if (ax < 0)
			aniId = ID_ANI_MARIO_BRACE_RIGHT;
		else if (ax == MARIO_ACCEL_RUN_SLOW_X)
			aniId = ID_ANI_MARIO_RUNNING_SLOW_RIGHT;
		else if (ax == MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_RUNNING_RIGHT;
		else if (ax == MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_WALKING_RIGHT;
		else if (ax == 0)
			aniId = ID_ANI_MARIO_IDLE_RIGHT;
	}
	else // vx < 0
	{
		if (holdedObj && ax == 0)
			aniId = ID_ANI_MARIO_HOLDSHELL_IDLE_LEFT;
		else if (holdedObj)
			aniId = ID_ANI_MARIO_HOLDSHELL_WALK_LEFT;
		else if (ax > 0)
			aniId = ID_ANI_MARIO_BRACE_LEFT;
		else if (ax == -MARIO_ACCEL_RUN_SLOW_X)
			aniId = ID_ANI_MARIO_RUNNING_SLOW_LEFT;
		else if (ax == -MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_RUNNING_LEFT;
		else if (ax == -MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_WALKING_LEFT;
		else if (ax == 0)
			aniId = ID_ANI_MARIO_IDLE_LEFT;
	}
	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for Racoon Mario
//
int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (state == MARIO_STATE_KICK)
	{
		aniId = (nx >= 0) ? ID_ANI_MARIO_RACOON_HOLDSHELL_KICK_RIGHT : ID_ANI_MARIO_RACOON_HOLDSHELL_KICK_LEFT;
	}
	else if (!isOnPlatform)
	{
		if (holdedObj)
		{
			aniId = (nx >= 0) ? ID_ANI_MARIO_RACOON_HOLDSHELL_JUMP_RIGHT : ID_ANI_MARIO_RACOON_HOLDSHELL_JUMP_LEFT;
		}
		else if (state == MARIO_STATE_FLAP_FLOW)
		{
			if (runCharge >= MARIO_RUN_CHARGE_MAX)
				aniId = (nx >= 0) ? ID_ANI_MARIO_RACOON_FLAP_FLY_RIGHT : ID_ANI_MARIO_RACOON_FLAP_FLY_LEFT;
			else 
				aniId = (nx >= 0) ? ID_ANI_MARIO_RACOON_FLAP_FLOW_RIGHT : ID_ANI_MARIO_RACOON_FLAP_FLOW_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			aniId = (nx >= 0) ? ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT : ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (vy >= 0)
				aniId = (nx >= 0) ? ID_ANI_MARIO_RACOON_JUMP_RELEASE_RIGHT : ID_ANI_MARIO_RACOON_JUMP_RELEASE_LEFT;
			else
				aniId = (nx >= 0) ? ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT : ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT;
		}
	}
	else if (isSitting)
	{
		aniId = (nx >= 0) ? ID_ANI_MARIO_RACOON_SIT_RIGHT : ID_ANI_MARIO_RACOON_SIT_LEFT;
	}
	else if (vx == 0)
	{
		if (nx >= 0)
		{
			if (holdedObj)
				aniId = ID_ANI_MARIO_RACOON_HOLDSHELL_IDLE_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
		}
		else
		{
			if (holdedObj)
				aniId = ID_ANI_MARIO_RACOON_HOLDSHELL_IDLE_LEFT;
			else
				aniId = ID_ANI_MARIO_RACOON_IDLE_LEFT;
		}
	}
	else if (vx > 0)
	{
		if (holdedObj && ax == 0)
			aniId = ID_ANI_MARIO_RACOON_HOLDSHELL_IDLE_RIGHT;
		else if (holdedObj)
			aniId = ID_ANI_MARIO_RACOON_HOLDSHELL_WALK_RIGHT;
		else if (ax < 0)
			aniId = ID_ANI_MARIO_RACOON_BRACE_RIGHT;
		else if (ax == MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_RACOON_RUNNING_RIGHT;
		else if (ax == MARIO_ACCEL_RUN_SLOW_X)
			aniId = ID_ANI_MARIO_RACOON_RUNNING_SLOW_RIGHT;
		else if (ax == MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
		else if (ax == 0)
			aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
	}
	else // vx < 0
	{
		if (holdedObj && ax == 0)
			aniId = ID_ANI_MARIO_RACOON_HOLDSHELL_IDLE_LEFT;
		else if (holdedObj)
			aniId = ID_ANI_MARIO_RACOON_HOLDSHELL_WALK_LEFT;
		else if (ax > 0)
			aniId = ID_ANI_MARIO_RACOON_BRACE_LEFT;
		else if (ax == -MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_RACOON_RUNNING_LEFT;
		else if (ax == -MARIO_ACCEL_RUN_SLOW_X)
			aniId = ID_ANI_MARIO_RACOON_RUNNING_SLOW_LEFT;
		else if (ax == -MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_RACOON_WALKING_LEFT;
		else if (ax == 0)
			aniId = ID_ANI_MARIO_RACOON_IDLE_LEFT;
	}
	if (aniId == -1) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d, Run: %d, RunTimer: %d", coin, runCharge, runChargeTimer);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 
	if (!this->canSetState) return;
	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		isHolding = true;
		maxVx = (runCharge < MARIO_RUN_CHARGE_MAX) ? MARIO_RUNNING_SLOW_SPEED : MARIO_RUNNING_SPEED;
		ax = (runCharge < MARIO_RUN_CHARGE_MAX) ? MARIO_ACCEL_RUN_SLOW_X : MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		isHolding = true;
		maxVx = -((runCharge < MARIO_RUN_CHARGE_MAX) ? MARIO_RUNNING_SLOW_SPEED : MARIO_RUNNING_SPEED);
		ax = -((runCharge < MARIO_RUN_CHARGE_MAX) ? MARIO_ACCEL_RUN_SLOW_X : MARIO_ACCEL_RUN_X);
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		isHolding = false;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		isHolding = false;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		// First jump
		if (isOnPlatform && canJump)
		{
			ay = 0;
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		canJump = false;
		break;

	case MARIO_STATE_HOLD_JUMP:
		if (isSitting) break;
		// Drop after jump time
		if (onAir >= MARIO_ON_AIR_TIME)
		{
			ay = MARIO_GRAVITY;
			if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		}
		// Holding jump
		else
		{
			vy -= MARIO_JUMP_HOLDING_SPEED_Y;
		}
		break;
	case MARIO_STATE_RELEASE_JUMP:
		canJump = true;
		/*ay = MARIO_GRAVITY;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;*/
		/*if (onAir >= MARIO_FIRST_JUMP_TIME)
		{
			vy += MARIO_JUMP_SPEED_Y / 2;
			ay = MARIO_GRAVITY;
		}*/
		vy += MARIO_JUMP_SPEED_Y / 2;
		ay = MARIO_GRAVITY;

		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_FLAP_FLOW:
		flowTimer = 0;
		// Running
		if (runCharge >= MARIO_RUN_CHARGE_MAX)
		{
			isCamFollowY = true;
			vy = -MARIO_FLAP_FLY_SPEED_Y;
			ay = -MARIO_FLAP_FLY_ACC_Y;
		}
		// Walking
		else
		{
			vy = MARIO_FLAP_FLOW_SPEED_Y;
			ay = MARIO_FLAP_FLOW_ACC_Y;
		}
		break;
	case MARIO_STATE_FLAP_FLOW_RELEASE:
		flowTimer = MARIO_FLOW_TIME;
		//ay = MARIO_GRAVITY;
		break;
	case MARIO_STATE_IDLE:
		ax = 0.0f;
		//vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_KICK:
		float kx, ky;
		CKoopa* koopa = dynamic_cast<CKoopa*>(holdedObj);
		koopa->GetPosition(kx, ky);
		koopa->ToShellRoll((kx - x > 0) ? 1 : -1);
		holdedObj = NULL;
		kickTimer = MARIO_KICK_TIME;
		canSetState = false;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG  || level == MARIO_LEVEL_RACOON)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

int CMario::GetLevel()
{
	return this->level;
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

bool CMario::IsHoldingShell()
{
	if (isHolding && dynamic_cast<CKoopa*>(holdedObj))
	{
		CKoopa* koopa = dynamic_cast<CKoopa*>(holdedObj);
		if (koopa->IsHolded()) return true;
	}
	return false;
}

bool CMario::IsDamaged()
{
	if (untouchable == 0)
	{
		holdedObj = nullptr;
		switch (level)
		{
		case MARIO_LEVEL_SMALL:
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
			break;
		case MARIO_LEVEL_BIG:
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
			break;
		case MARIO_LEVEL_RACOON:
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
			break;
		default:
			break;
		}
		return true;
	}
	return false;
}

bool CMario::IsGrounded()
{
	return isOnPlatform;
}

void CMario::Flap()
{
	/*if (flapTimer >= MARIO_FLAP_COOLDOWN)
	{
		SetState(MARIO_STATE_FLAP_FLOW);
		flapTimer = MARIO_FLAP_COOLDOWN;
	}*/
	SetState(MARIO_STATE_FLAP_FLOW);
	flapTimer = MARIO_FLAP_COOLDOWN;
}