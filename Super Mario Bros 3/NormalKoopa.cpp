#include "NormalKoopa.h"

CNormalKoopa::CNormalKoopa(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	this->ax = 0;
	this->ay = NORMAL_KOOPA_GRAVITY;

	SetState(NORMAL_KOOPA_STATE_WALKING);
}

void CNormalKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == NORMAL_KOOPA_STATE_WALKING)
	{
		left = x - NORMAL_KOOPA_BBOX_WIDTH / 2;
		top = y - NORMAL_KOOPA_BBOX_HEIGHT / 2;
		right = left + NORMAL_KOOPA_BBOX_WIDTH;
		bottom = top + NORMAL_KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - NORMAL_KOOPA_BBOX_WIDTH / 2;
		top = y - NORMAL_KOOPA_SHELL_BBOX_HEIGHT / 2;
		right = left + NORMAL_KOOPA_BBOX_WIDTH;
		bottom = top + NORMAL_KOOPA_SHELL_BBOX_HEIGHT;
	}
}

void CNormalKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CNormalKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	if (dynamic_cast<CMysteryBox*>(e->obj) && state == NORMAL_KOOPA_STATE_SHELL_ROLL)
	{
		CMysteryBox* mBox = dynamic_cast<CMysteryBox*>(e->obj);
		mBox->OpenBox();
	}

	if (dynamic_cast<CKoopa*>(e->obj))
	{
		CKoopa* p = dynamic_cast<CKoopa*>(e->obj);
		if (p->IsRolled())
		{
			int dir = 0;
			if (e->nx > 0) dir = 1;
			if (e->nx < 0) dir = -1;
			AltDie(dir);
		}
	}

	if (dynamic_cast<CFlyKoopa*>(e->obj))
	{
		CFlyKoopa* p = dynamic_cast<CFlyKoopa*>(e->obj);
		if (p->IsRolled())
		{
			int dir = 0;
			if (e->nx > 0) dir = 1;
			if (e->nx < 0) dir = -1;
			AltDie(dir);
		}
	}

	if (dynamic_cast<CNormalKoopa*>(e->obj))
	{
		CNormalKoopa* p = dynamic_cast<CNormalKoopa*>(e->obj);
		if (p->IsRolled())
		{
			int dir = 0;
			if (e->nx > 0) dir = 1;
			if (e->nx < 0) dir = -1;
			AltDie(dir);
		}
	}
}

void CNormalKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	// Die time
	if ((state == FLY_KOOPA_STATE_DIE) && GetTickCount64() - die_start > FLY_KOOPA_DIE_TIMEOUT)
	{
		isDeleted = true;
		return;
	}

	// Fix shell can't stop bug
	if (toShellTimer > 0)
	{
		toShellTimer -= dt;
		if (toShellTimer <= 0)
		{
			vx = 0;
			isBlck = false;
			toShellTimer = 0;
		}
	}

	// Holded
	if (isHolded)
	{
		// Detect Player
		LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
		LPGAMEOBJECT player = playScene->GetPlayer();

		float pvx, pvy;
		float px, py;
		player->GetPosition(px, py);
		player->GetSpeed(pvx, pvy);

		if (vx < 0) x = px - holdAdjX;
		if (vx > 0) x = px + holdAdjX;
		y = py + holdAdjY;

		vx = pvx;
		vy = pvy;
	}

	// Resurrect
	if (state == NORMAL_KOOPA_STATE_SHELL_IDLE)
	{
		resCoolDown += dt;
		if (resCoolDown >= NORMAL_KOOPA_RESURRECT_COOLDOWN)
		{
			ToResurrect();
		}
	}
	else resCoolDown = 0;
	if (state == NORMAL_KOOPA_STATE_SHELL_RESURRECT)
	{
		resTime += dt;
		if (resTime >= NORMAL_KOOPA_RESURRECT_TIME)
		{
			// deal damage to player
			if (isHolded)
			{
				LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
				CMario* mario = dynamic_cast<CMario*>(playScene->GetPlayer());
				mario->IsDamaged();
			}
			ToWalking();
			resTime = 0;
		}
	}
	else resTime = 0;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CNormalKoopa::Render()
{
	int aniId = 0;
	int sprId = ID_SPR_NORMAL_KOOPA_SHELL_IDLE;
	switch (state)
	{
	case NORMAL_KOOPA_STATE_WALKING:
		aniId = (vx <= 0) ? ID_ANI_NORMAL_KOOPA_WALK_LEFT : ID_ANI_NORMAL_KOOPA_WALK_RIGHT;
		break;
		/*case NORMAL_KOOPA_STATE_SHELL_HOLDED:*/
	case NORMAL_KOOPA_STATE_SHELL_IDLE:
		CSprites::GetInstance()->Get(sprId)->Draw(x, y);
		break;
	case NORMAL_KOOPA_STATE_SHELL_RESURRECT:
		aniId = ID_ANI_NORMAL_KOOPA_SHELL_APPEAR;
		break;
	case NORMAL_KOOPA_STATE_SHELL_ROLL:
		aniId = ID_ANI_NORMAL_KOOPA_SHELL_ROLL;
		break;
	case NORMAL_KOOPA_STATE_DIE:
		aniId = ID_ANI_NORMAL_KOOPA_DIE;
		break;
	default:
		aniId = 0;
		break;
	}
	if (aniId != 0)
	{
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CNormalKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case NORMAL_KOOPA_STATE_WALKING:
		y -= (NORMAL_KOOPA_BBOX_HEIGHT - NORMAL_KOOPA_SHELL_BBOX_HEIGHT) / 2 + 5;
		vx = -NORMAL_KOOPA_WALKING_SPEED;
		break;
	case NORMAL_KOOPA_STATE_SHELL_IDLE:
		y += (NORMAL_KOOPA_BBOX_HEIGHT - NORMAL_KOOPA_SHELL_BBOX_HEIGHT) / 2 - 5;
		vx = 0;
		break;
	case NORMAL_KOOPA_STATE_SHELL_ROLL:
		ay = NORMAL_KOOPA_GRAVITY;
		break;
	case NORMAL_KOOPA_STATE_SHELL_RESURRECT:
		break;
	case NORMAL_KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		break;
	default:
		break;
	}
}

void CNormalKoopa::ToShellIdle()
{
	toShellTimer = 100;
	isHolded = false;
	SetState(NORMAL_KOOPA_STATE_SHELL_IDLE);
}

void CNormalKoopa::ToShellRoll(int dir)
{
	isBlck = true;
	isHolded = false;
	SetState(NORMAL_KOOPA_STATE_SHELL_ROLL);
	vx = dir * NORMAL_KOOPA_ROLLING_SPEED;
}

void CNormalKoopa::ToShellHold(float adjX, float adjY)
{
	isBlck = false;
	isHolded = true;
	holdAdjX = adjX;
	holdAdjY = adjY;
	SetState(NORMAL_KOOPA_STATE_SHELL_IDLE);
}

void CNormalKoopa::ToResurrect()
{
	isBlck = false;
	SetState(NORMAL_KOOPA_STATE_SHELL_RESURRECT);
}

void CNormalKoopa::ToWalking()
{
	isBlck = false;
	isHolded = false;
	SetState(NORMAL_KOOPA_STATE_WALKING);
}

void CNormalKoopa::Knocked(int dir)
{
	ToShellIdle();
	vx = dir * KOOMBA_DIE_SPEED_X;
	vy = -KOOMBA_DIE_SPEED_Y;
}

void CNormalKoopa::AltDie(int dir)
{
	SetState(NORMAL_KOOPA_STATE_DIE);
	isColl = 0;
	vx = dir * NORMAL_KOOMBA_DIE_SPEED_X;
	vy = -NORMAL_KOOMBA_DIE_SPEED_Y;

	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->FlowScore(x, y, 0);
}
