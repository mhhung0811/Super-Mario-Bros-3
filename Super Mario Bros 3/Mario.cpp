#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "MysteryBox.h"
#include "Mushroom.h"
#include "MushroomGreen.h"
#include "PiranhaPlant.h"
#include "FireBall.h"
#include "Koopa.h"
#include "RacoonLeaf.h"
#include "FlyGoomba.h"
#include "Spawner.h"
#include "FlyKoopa.h"
#include "NormalKoopa.h"
#include "PiranhaPlantBite.h"
#include "BreakableBrick.h"
#include "Button.h"
#include "Teleporter.h"
#include "EndGate.h"
#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (y > 210) SetState(MARIO_STATE_DIE);

	// Revive
	if (state == MARIO_STATE_DIE && (GetTickCount64() - die_time > MARIO_DIE_TIME))
	{
		vy = 0;
		Restart();
	}

	// Tele stuff
	if (state == MARIO_STATE_TELE)
	{
		float tx, ty;
		nearestTele->GetPosition(tx, ty);
		CTeleporter* p = dynamic_cast<CTeleporter*>(nearestTele);
		LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
		if (waitTele > 0)
		{
			waitTele -= dt;
			if (waitTele <= 0)
				playScene->ResetCam();
		}
		if (isTeleUp)
		{
			if (y < ty - MARIO_TELE_DIS)
			{
				p->Teleport();
				waitTele = 100;
				vy = -MARIO_TELE_SPEED;
				isFinishTele = true;
				isCamStaticY = false;
			}
			if (isFinishTele && y < p->GetDesY() - MARIO_TELE_DIS)
			{
				isBlck = true;
				isColl = true;
				canSetState = true;
				SetState(MARIO_STATE_WALKING_RIGHT);
			}
		}
		if (!isTeleUp)
		{
			if (y > ty + MARIO_TELE_DIS)
			{
				p->Teleport();
				waitTele = 100;
				vy = MARIO_TELE_SPEED;
				isFinishTele = true;
				isCamStaticY = true;
			}
			if (isFinishTele && y > p->GetDesY() + MARIO_TELE_DIS)
			{
				isBlck = true;
				isColl = true;
				canSetState = true;
				SetState(MARIO_STATE_WALKING_RIGHT);
			}
		}
		CCollision::GetInstance()->Process(this, dt, coObjects);
		return;
	}

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
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->UpdateUIRuncharge(GetRunCharges());
	

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

	// Attack timer
	if (isAttacking)
	{
		Attack(coObjects);
		attackTimer -= dt;
		if (attackTimer <= 0)
		{
			isAttacking = false;
			//canSetState = true;
			SetState(MARIO_STATE_IDLE);
			attackTimer = 0;
		}
	}

	// Kick timer
	if (state == MARIO_STATE_KICK)
	{
		kickTimer -= dt;
		if (kickTimer <= 0)
		{
			canSetState = true;
			SetState(MARIO_STATE_IDLE);
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
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->UpdateUILives();
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
	else if (dynamic_cast<CFlyKoopa*>(e->obj))
		OnCollisionWithFlyKoopa(e);
	else if (dynamic_cast<CNormalKoopa*>(e->obj))
		OnCollisionWithNormalKoopa(e);
	else if (dynamic_cast<CPiranhaPlantBite*>(e->obj))
		OnCollisionWithPiranhaPlantBite(e);
	else if (dynamic_cast<CBreakableBrick*>(e->obj))
		OnCollisionWithBreakableBrick(e);
	else if (dynamic_cast<CButton*>(e->obj))
		OnCollisionWithButton(e);
	else if (dynamic_cast<CTeleporter*>(e->obj))
		OnCollisionWithTeleporter(e);
	else if (dynamic_cast<CEndGate*>(e->obj))
		OnCollisionWithEndGate(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			float px, py;
			goomba->GetPosition(px, py);

			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(px, py, goomba->GetPoint());
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
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->UpdateUICoin(1);
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
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	if (dynamic_cast<CMushroomGreen*>(p))
	{
		lives++;
		playScene->UpdateUILives();
	}
	else
	{
		if (level != MARIO_LEVEL_RACOON)
			SetLevel(MARIO_LEVEL_BIG);
	}
	p->IsAbsorbed();
	float px, py;
	p->GetPosition(px, py);
	playScene->FlowScore(px, py, p->GetPoint());
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
			float px, py;
			koopa->GetPosition(px, py);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(px, py, koopa->GetPoint());
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
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(kx, ky, koopa->GetPoint());
		}
		break;
	}
	case KOOPA_STATE_SHELL_ROLL:
	{
		// jump on top >> stop Koopa shell and deflect a bit 
		if (e->ny < 0)
		{
			float kx, ky;
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			koopa->ToShellIdle();
			koopa->GetPosition(kx, ky);
			koopa->SetPosition(kx, ky + (KOOPA_BBOX_HEIGHT - KOOPA_SHELL_BBOX_HEIGHT) / 2 - 10);
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
	float px, py;
	p->GetPosition(px, py);
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->FlowScore(px, py, p->GetPoint());
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
			float px, py;
			flyGoomba->GetPosition(px, py);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(px, py, flyGoomba->GetPoint());
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

void CMario::OnCollisionWithFlyKoopa(LPCOLLISIONEVENT e)
{
	CFlyKoopa* flyKoopa = dynamic_cast<CFlyKoopa*>(e->obj);

	switch (flyKoopa->GetState())
	{
	case FLY_KOOPA_STATE_WALKING:
	{
		// jump on top >> turn Koopa to shell and deflect a bit 
		if (e->ny < 0)
		{
			if (flyKoopa->HaveWing()) flyKoopa->LoseWing();
			else flyKoopa->ToShellIdle();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			float px, py;
			flyKoopa->GetPosition(px, py);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(px, py, flyKoopa->GetPoint());
		}
		else // hit by koopa
		{
			IsDamaged();
		}
		break;
	}
	case FLY_KOOPA_STATE_SHELL_IDLE:
	{
		float kx, ky;
		flyKoopa->GetPosition(kx, ky);
		if (isHolding)
		{
			holdedObj = flyKoopa;
			if (level == MARIO_LEVEL_SMALL) flyKoopa->ToShellHold(MARIO_HOLD_X, MARIO_HOLD_Y);
			else flyKoopa->ToShellHold(MARIO_HOLD_X, MARIO_BIG_HOLD_Y);
		}
		else
		{
			// deflect if jump on top
			if (e->ny < 0)
			{
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			float kx, ky;
			flyKoopa->GetPosition(kx, ky);
			flyKoopa->SetPosition(kx, ky + (FLY_KOOPA_BBOX_HEIGHT - FLY_KOOPA_SHELL_BBOX_HEIGHT) / 2 - 10);
			flyKoopa->ToShellRoll((kx - x > 0) ? 1 : -1);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(kx, ky, flyKoopa->GetPoint());
		}
		break;
	}
	case FLY_KOOPA_STATE_SHELL_ROLL:
	{
		// jump on top >> stop Koopa shell and deflect a bit 
		if (e->ny < 0)
		{
			float kx, ky;
			flyKoopa->GetPosition(kx, ky);
			flyKoopa->SetPosition(kx, ky + (FLY_KOOPA_BBOX_HEIGHT - FLY_KOOPA_SHELL_BBOX_HEIGHT) / 2 - 10);
			flyKoopa->ToShellIdle();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else // hit by flyKoopa
		{
			IsDamaged();
		}
		break;
	}
	default:
		break;
	}
}

void CMario::OnCollisionWithNormalKoopa(LPCOLLISIONEVENT e)
{
	CNormalKoopa* normalKoopa = dynamic_cast<CNormalKoopa*>(e->obj);

	switch (normalKoopa->GetState())
	{
	case NORMAL_KOOPA_STATE_WALKING:
	{
		// jump on top >> turn Koopa to shell and deflect a bit 
		if (e->ny < 0)
		{
			normalKoopa->ToShellIdle();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			float px, py;
			normalKoopa->GetPosition(px, py);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(px, py, normalKoopa->GetPoint());
		}
		else // hit by koopa
		{
			IsDamaged();
		}
		break;
	}
	case NORMAL_KOOPA_STATE_SHELL_IDLE:
	{
		float kx, ky;
		normalKoopa->GetPosition(kx, ky);
		if (isHolding)
		{
			holdedObj = normalKoopa;
			if (level == MARIO_LEVEL_SMALL) normalKoopa->ToShellHold(MARIO_HOLD_X, MARIO_HOLD_Y);
			else normalKoopa->ToShellHold(MARIO_HOLD_X, MARIO_BIG_HOLD_Y);
		}
		else
		{
			// deflect if jump on top
			if (e->ny < 0)
			{
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			float kx, ky;
			normalKoopa->GetPosition(kx, ky);
			normalKoopa->SetPosition(kx, ky + (NORMAL_KOOPA_BBOX_HEIGHT - NORMAL_KOOPA_SHELL_BBOX_HEIGHT) / 2 - 10);
			normalKoopa->ToShellRoll((kx - x > 0) ? 1 : -1);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(kx, ky, normalKoopa->GetPoint());
		}
		break;
	}
	case NORMAL_KOOPA_STATE_SHELL_ROLL:
	{
		// jump on top >> stop Koopa shell and deflect a bit 
		if (e->ny < 0)
		{
			float kx, ky;
			normalKoopa->GetPosition(kx, ky);
			normalKoopa->SetPosition(kx, ky + (NORMAL_KOOPA_BBOX_HEIGHT - NORMAL_KOOPA_SHELL_BBOX_HEIGHT) / 2 - 10);
			normalKoopa->ToShellIdle();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else // hit by Koopa
		{
			IsDamaged();
		}
		break;
	}
	default:
		break;
	}
}

void CMario::OnCollisionWithPiranhaPlantBite(LPCOLLISIONEVENT e)
{
	CPiranhaPlantBite* p = dynamic_cast<CPiranhaPlantBite*>(e->obj);
	IsDamaged();
}

void CMario::OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e)
{
	if (e->ny > 0)
	{
		onAir = MARIO_ON_AIR_TIME;
		CBreakableBrick* p = (CBreakableBrick*)e->obj;
		if (level == MARIO_LEVEL_SMALL) p->TryOpenBox();
		else p->OpenBox();
	}
}

void CMario::OnCollisionWithButton(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		CButton* p = (CButton*)e->obj;
		if (p->GetState() == BUTTON_STATE_ACTIVE)
			p->PressButton();
	}
}

void CMario::OnCollisionWithTeleporter(LPCOLLISIONEVENT e)
{
	nearestTele = dynamic_cast<CTeleporter*>(e->obj);
}
void CMario::OnCollisionWithEndGate(LPCOLLISIONEVENT e)
{
	CEndGate* gate = dynamic_cast<CEndGate*>(e->obj);
	gate->End();
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (state == MARIO_STATE_TELE)
	{
		aniId = ID_ANI_MARIO_SMALL_TELE;
	}
	else if (state == MARIO_STATE_KICK)
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
	else if (isSitting)
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
	if (state == MARIO_STATE_TELE)
	{
		aniId = ID_ANI_MARIO_TELE;
	}
	else if (state == MARIO_STATE_KICK)
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
	if (state == MARIO_STATE_TELE)
	{
		aniId = ID_ANI_MARIO_RACOON_TELE;
	}
	else if (state == MARIO_STATE_ATTACK || isAttacking)
	{
		aniId = (nx >= 0) ? ID_ANI_MARIO_RACOON_ATTACK_RIGHT : ID_ANI_MARIO_RACOON_ATTACK_LEFT;
	} else if (state == MARIO_STATE_KICK)
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

void CMario::RenderHitBox()
{
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;
	GetHitBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(l - cx + MARIO_RACOON_HIT_BBOX_WIDTH / 2, t - cy + MARIO_RACOON_HIT_BBOX_HEIGHT / 2, bbox, &rect, BBOX_ALPHA);
}

void CMario::Render()
{
	if (untouchable != 0)
	{
		if (GetTickCount64() % 2 == 0)
			return;
	}

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

	//if (level == MARIO_LEVEL_RACOON) RenderHitBox();
	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d, Run: %d, RunTimer: %d", coin, runCharge, runChargeTimer);
}

void CMario::SetState(int state)
{
	//if (this->state == MARIO_STATE_DIE) return;
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
			if (y < (SCREEN_HEIGHT - SCREEN_UI) / 2)
			{
				isCamFollowY = true;
			}
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
		die_time = GetTickCount64();
		canSetState = false;
		break;
	case MARIO_STATE_KICK:
		float kx, ky;
		if (dynamic_cast<CKoopa*>(holdedObj))
		{
			CKoopa* koopa = dynamic_cast<CKoopa*>(holdedObj);
			koopa->GetPosition(kx, ky);
			koopa->ToShellRoll((kx - x > 0) ? 1 : -1);
			holdedObj = NULL;
			kickTimer = MARIO_KICK_TIME;
			canSetState = false;
		}
		if (dynamic_cast<CFlyKoopa*>(holdedObj))
		{
			CFlyKoopa* flyKoopa = dynamic_cast<CFlyKoopa*>(holdedObj);
			flyKoopa->GetPosition(kx, ky);
			flyKoopa->ToShellRoll((kx - x > 0) ? 1 : -1);
			holdedObj = NULL;
			kickTimer = MARIO_KICK_TIME;
			canSetState = false;
		}
		if (dynamic_cast<CNormalKoopa*>(holdedObj))
		{
			CNormalKoopa* normalKoopa = dynamic_cast<CNormalKoopa*>(holdedObj);
			normalKoopa->GetPosition(kx, ky);
			normalKoopa->ToShellRoll((kx - x > 0) ? 1 : -1);
			holdedObj = NULL;
			kickTimer = MARIO_KICK_TIME;
			canSetState = false;
		}
		break;
	case MARIO_STATE_ATTACK:
		attackTimer = MARIO_ATTACK_TIME;
		//canSetState = false;
		isAttacking = true;
		break;
	case MARIO_STATE_TELE:
		canSetState = false;
		isBlck = false;
		isColl = false;
		vx = 0;
		vy = (isTeleUp ? -1 : 1) * MARIO_TELE_SPEED;
		break;
	}
	

	CGameObject::SetState(state);
}

void CMario::GetHitBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MARIO_RACOON_HIT_BBOX_WIDTH / 2 + MARIO_RACOON_HIT_BBOX_X;
	top = y - MARIO_RACOON_HIT_BBOX_HEIGHT / 2 + MARIO_RACOON_HIT_BBOX_Y;
	right = left + MARIO_RACOON_HIT_BBOX_WIDTH;
	bottom = top + MARIO_RACOON_HIT_BBOX_HEIGHT;
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
	if (isHolding)
	{
		if (dynamic_cast<CKoopa*>(holdedObj))
		{
			CKoopa* koopa = dynamic_cast<CKoopa*>(holdedObj);
			if (koopa->IsHolded()) return true;
		}
		if (dynamic_cast<CFlyKoopa*>(holdedObj))
		{
			CFlyKoopa* flyKoopa = dynamic_cast<CFlyKoopa*>(holdedObj);
			if (flyKoopa->IsHolded()) return true;
		}
		if (dynamic_cast<CNormalKoopa*>(holdedObj))
		{
			CNormalKoopa* normalKoopa = dynamic_cast<CNormalKoopa*>(holdedObj);
			if (normalKoopa->IsHolded()) return true;
		}
	}
	return false;
}

bool CMario::IsDamaged()
{
	if (untouchable == 0)
	{
		holdedObj = NULL;
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

void CMario::Attack(vector<LPGAMEOBJECT>* coObjects)
{
	holdedObj = nullptr;
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (InHitBox(coObjects->at(i)))
		{
			if (dynamic_cast<CGoomba*>(coObjects->at(i)))
			{
				CGoomba* p = dynamic_cast<CGoomba*>(coObjects->at(i));
				float px, py;
				p->GetPosition(px, py);
				p->AltDie((x < px) ? 1 : -1);

				LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
				playScene->FlowScore(px, py, p->GetPoint());
			}
			else if (dynamic_cast<CFlyGoomba*>(coObjects->at(i)))
			{
				CFlyGoomba* p = dynamic_cast<CFlyGoomba*>(coObjects->at(i));
				float px, py;
				p->GetPosition(px, py);
				p->AltDie((x < px) ? 1 : -1);

				LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
				playScene->FlowScore(px, py, p->GetPoint());
			}
			else if (dynamic_cast<CKoopa*>(coObjects->at(i)))
			{
				CKoopa* p = dynamic_cast<CKoopa*>(coObjects->at(i));
				float px, py;
				p->GetPosition(px, py);
				p->Knocked((x < px) ? 1 : -1);
			}
			else if (dynamic_cast<CFlyKoopa*>(coObjects->at(i)))
			{
				CFlyKoopa* p = dynamic_cast<CFlyKoopa*>(coObjects->at(i));
				float px, py;
				p->GetPosition(px, py);
				p->Knocked((x < px) ? 1 : -1);
			}
			else if (dynamic_cast<CNormalKoopa*>(coObjects->at(i)))
			{
				CNormalKoopa* p = dynamic_cast<CNormalKoopa*>(coObjects->at(i));
				float px, py;
				p->GetPosition(px, py);
				p->Knocked((x < px) ? 1 : -1);
			}
			else if (dynamic_cast<CPiranhaPlant*>(coObjects->at(i)))
			{
				CPiranhaPlant* p = dynamic_cast<CPiranhaPlant*>(coObjects->at(i));
				float px, py;
				p->GetPosition(px, py);
				p->SetState(PIRANHAPLANT_STATE_DIE);

				LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
				playScene->FlowScore(px, py, p->GetPoint());
			}
			else if (dynamic_cast<CPiranhaPlantBite*>(coObjects->at(i)))
			{
				CPiranhaPlantBite* p = dynamic_cast<CPiranhaPlantBite*>(coObjects->at(i));
				float px, py;
				p->GetPosition(px, py);
				p->SetState(PIRANHAPLANT_BITE_STATE_DIE);

				LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
				playScene->FlowScore(px, py, p->GetPoint());
			}
			else if (dynamic_cast<CMysteryBox*>(coObjects->at(i)))
			{
				CMysteryBox* p = dynamic_cast<CMysteryBox*>(coObjects->at(i));
				p->OpenBox();
			}
			else if (dynamic_cast<CBreakableBrick*>(coObjects->at(i)))
			{
				CBreakableBrick* p = dynamic_cast<CBreakableBrick*>(coObjects->at(i));
				p->OpenBox();
			}
		}
	}
}

bool CMario::InHitBox(LPGAMEOBJECT obj)
{
	if (obj == NULL) return -1;
	float l1, t1, r1, b1, l2, t2, r2, b2;
	obj->GetBoundingBox(l2, t2, r2, b2);

	// Is in Safe Box
	GetHitBox(l1, t1, r1, b1);
	if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
	{
		return true;
	}
	//DebugOut(L"no box found\n");
	return false;
}

void CMario::Teleport(bool isUp)
{
	if (state == MARIO_STATE_TELE) return;
	if (nearestTele != nullptr)
	{
		float l1, t1, r1, b1, l2, t2, r2, b2;
		GetBoundingBox(l1, t1, r1, b1);
		nearestTele->GetBoundingBox(l2, t2, r2, b2);
		if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
		{
			isTeleUp = isUp;
			isFinishTele = false;
			SetState(MARIO_STATE_TELE);
		}
	}
}

void CMario::Restart()
{
	if (lives > 0)
	{
		lives--;
		LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
		playScene->UpdateUILives();
		playScene->Restart();

		SetPosition(20, 150);

		canSetState = true;
		level = MARIO_LEVEL_SMALL;
		SetState(MARIO_STATE_IDLE);
		vy = 0;
		ay = MARIO_GRAVITY;
		playScene->ResetCam();
	}
	else
		CGame::GetInstance()->InitiateSwitchScene(20);
}

int CMario::GetRunCharges()
{
	float r = MARIO_RUN_CHARGE_MAX / 6;
	if (runCharge < r) return 0;
	else if (runCharge < 2 * r) return 1;
	else if (runCharge < 3 * r) return 2;
	else if (runCharge < 4 * r) return 3;
	else if (runCharge < 5 * r) return 4;
	else if (runCharge < 6 * r) return 5;
	else return 6;
}