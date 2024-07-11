#include "FlyGoomba.h"
#include "debug.h"

CFlyGoomba::CFlyGoomba(float x, float y) :CGameObject(x, y)
{
	this->haveWings = true;
	this->ax = 0;
	this->ay = FLY_GOOMBA_GRAVITY;
	this->isOnPlatform = false;
	this->leftWing = new CWing(x - FLY_GOOMBA_WING_X -	1, y - FLY_GOOMBA_WING_Y, -1);
	this->rightWing = new CWing(x + FLY_GOOMBA_WING_X, y - FLY_GOOMBA_WING_Y, 1);
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->AddObject(leftWing, 1);
	playScene->AddObject(rightWing, 1);

	stepTimer = 0;
	jumpCount = 0;
	jumpTimer = FLY_GOOMBA_JUMP_COOLDOWN;

	die_start = -1;
	SetState(FLY_GOOMBA_STATE_WALKING);
}

void CFlyGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FLY_GOOMBA_STATE_DIE)
	{
		left = x - FLY_GOOMBA_BBOX_WIDTH / 2;
		top = y - FLY_GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + FLY_GOOMBA_BBOX_WIDTH;
		bottom = top + FLY_GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - FLY_GOOMBA_BBOX_WIDTH / 2;
		top = y - FLY_GOOMBA_BBOX_HEIGHT / 2;
		right = left + FLY_GOOMBA_BBOX_WIDTH;
		bottom = top + FLY_GOOMBA_BBOX_HEIGHT;
	}
}

void CFlyGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	leftWing->SetPosition(x - FLY_GOOMBA_WING_X - 1, y - FLY_GOOMBA_WING_Y);
	rightWing->SetPosition(x + FLY_GOOMBA_WING_X, y - FLY_GOOMBA_WING_Y);
};

void CFlyGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFlyGoomba*>(e->obj)) return;
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		if (e->ny < 0) isOnPlatform = true;
	}
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
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

void CFlyGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	leftWing->SetPosition(x - FLY_GOOMBA_WING_X - 1, y - FLY_GOOMBA_WING_Y);
	rightWing->SetPosition(x + FLY_GOOMBA_WING_X, y - FLY_GOOMBA_WING_Y);

	stepTimer += dt;
	jumpTimer += dt;

	if ( ((state == FLY_GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > FLY_GOOMBA_DIE_TIMEOUT)) ||
		((state == FLY_GOOMBA_STATE_ALT_DIE) && (GetTickCount64() - die_start > FLY_GOOMBA_ALT_DIE_TIMEOUT)) )
	{
		isDeleted = true;
		return;
	}

	if (haveWings)
	{
		if (jumpTimer >= FLY_GOOMBA_JUMP_COOLDOWN)
		{
			if (jumpCount < 3)
			{
				leftWing->SetState(WING_STATE_FLAP_SLOW);
				rightWing->SetState(WING_STATE_FLAP_SLOW);
				if (stepTimer >= FLY_GOOMBA_JUMP_STEP)
				{
					stepTimer = 0;
					jumpCount++;
					vy -= FLY_GOOMBA_SMALL_JUMP_SPEED;
				}
			}
			else
			{
				if (stepTimer >= FLY_GOOMBA_JUMP_STEP)
				{
					stepTimer = 0;
					jumpCount = 0;
					jumpTimer = 0;
					vy -= FLY_GOOMBA_BIG_JUMP_SPEED;
					leftWing->SetState(WING_STATE_FLAP_FAST);
					rightWing->SetState(WING_STATE_FLAP_FAST);
				}
			}
		}
		else if (isOnPlatform)
		{
			leftWing->SetState(WING_STATE_CLOSE);
			rightWing->SetState(WING_STATE_CLOSE);
		}
	}

	isOnPlatform = true;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFlyGoomba::Render()
{
	int aniId = ID_ANI_FLY_GOOMBA_WALKING;
	if (state == FLY_GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_FLY_GOOMBA_DIE;
	}
	if (state == FLY_GOOMBA_STATE_ALT_DIE)
	{
		aniId = ID_ANI_FLY_GOOMBA_ALT_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CFlyGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLY_GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (FLY_GOOMBA_BBOX_HEIGHT - FLY_GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case FLY_GOOMBA_STATE_ALT_DIE:
		die_start = GetTickCount64();
		haveWings = false;
		leftWing->Delete();
		rightWing->Delete();
		break;
	case FLY_GOOMBA_STATE_WALKING:
		vx = -FLY_GOOMBA_WALKING_SPEED;
		break;
	}
}

void CFlyGoomba::Damaged()
{
	if (haveWings)
	{
		haveWings = false;
		leftWing->Delete();
		rightWing->Delete();
	}
	else
	{
		SetState(FLY_GOOMBA_STATE_DIE);
	}
}

void CFlyGoomba::AltDie(int dir)
{
	SetState(FLY_GOOMBA_STATE_ALT_DIE);
	isColl = 0;
	vx = dir * FLY_GOOMBA_ALT_DIE_SPEED_X;
	vy = -FLY_GOOMBA_ALT_DIE_SPEED_X;

	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->FlowScore(x, y, 0);
}