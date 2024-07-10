#include "FlyKoopa.h"

CFlyKoopa::CFlyKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = FLY_KOOPA_GRAVITY;
	this->haveWing = true;
	this->isOnPlatform = false;
	this->wing = new CWing(x + FLY_KOOPA_WING_X, y - FLY_KOOPA_WINY_Y, 1);
	wing->SetState(WING_STATE_FLAP_SLOW);

	jumpTimer = FLY_KOOPA_JUMP_COOLDOWN;

	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->AddObject(wing, 1);

	SetState(FLY_KOOPA_STATE_WALKING);
}

void CFlyKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FLY_KOOPA_STATE_WALKING)
	{
		left = x - FLY_KOOPA_BBOX_WIDTH / 2;
		top = y - FLY_KOOPA_BBOX_HEIGHT / 2;
		right = left + FLY_KOOPA_BBOX_WIDTH;
		bottom = top + FLY_KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - FLY_KOOPA_BBOX_WIDTH / 2;
		top = y - FLY_KOOPA_SHELL_BBOX_HEIGHT / 2;
		right = left + FLY_KOOPA_BBOX_WIDTH;
		bottom = top + FLY_KOOPA_SHELL_BBOX_HEIGHT;
	}
}

void CFlyKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (haveWing)
	{
		if (vx <= 0)
		{
			wing->SetDir(1);
			wing->SetPosition(x + FLY_KOOPA_WING_X, y - FLY_KOOPA_WINY_Y);
		}
		else
		{
			wing->SetDir(-1);
			wing->SetPosition(x - FLY_KOOPA_WING_X, y - FLY_KOOPA_WINY_Y);
		}
	}
}

void CFlyKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
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
	if (dynamic_cast<CMysteryBox*>(e->obj) && state == FLY_KOOPA_STATE_SHELL_ROLL)
	{
		CMysteryBox* mBox = dynamic_cast<CMysteryBox*>(e->obj);
		mBox->OpenBox();
	}
}

void CFlyKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	// Wing
	if (haveWing) 
	{
		jumpTimer += dt;
		if (vx <= 0)
		{
			wing->SetDir(1);
			wing->SetPosition(x + FLY_KOOPA_WING_X, y - FLY_KOOPA_WINY_Y);
		}
		else
		{
			wing->SetDir(-1);
			wing->SetPosition(x - FLY_KOOPA_WING_X, y - FLY_KOOPA_WINY_Y);
		}

		if (jumpTimer >= FLY_KOOPA_JUMP_COOLDOWN && isOnPlatform)
		{
			isOnPlatform = false;
			jumpTimer = 0;
			vy -= FLY_KOOPA_JUMP_SPEED;
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
	if (state == FLY_KOOPA_STATE_SHELL_IDLE)
	{
		resCoolDown += dt;
		if (resCoolDown >= FLY_KOOPA_RESURRECT_COOLDOWN)
		{
			ToResurrect();
		}
	}
	else resCoolDown = 0;
	if (state == FLY_KOOPA_STATE_SHELL_RESURRECT)
	{
		resTime += dt;
		if (resTime >= FLY_KOOPA_RESURRECT_TIME)
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

void CFlyKoopa::Render()
{
	int aniId = 0;
	int sprId = ID_SPR_FLY_KOOPA_SHELL_IDLE;
	switch (state)
	{
	case FLY_KOOPA_STATE_WALKING:
		aniId = (vx <= 0) ? ID_ANI_FLY_KOOPA_WALK_LEFT : ID_ANI_FLY_KOOPA_WALK_RIGHT;
		break;
		/*case FLY_KOOPA_STATE_SHELL_HOLDED:*/
	case FLY_KOOPA_STATE_SHELL_IDLE:
		CSprites::GetInstance()->Get(sprId)->Draw(x, y);
		break;
	case FLY_KOOPA_STATE_SHELL_RESURRECT:
		aniId = ID_ANI_FLY_KOOPA_SHELL_APPEAR;
		break;
	case FLY_KOOPA_STATE_SHELL_ROLL:
		aniId = ID_ANI_FLY_KOOPA_SHELL_ROLL;
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

void CFlyKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLY_KOOPA_STATE_WALKING:
		y -= (FLY_KOOPA_BBOX_HEIGHT - FLY_KOOPA_SHELL_BBOX_HEIGHT) / 2 + 5;
		vx = -FLY_KOOPA_WALKING_SPEED;
		break;
	case FLY_KOOPA_STATE_SHELL_IDLE:
		y += (FLY_KOOPA_BBOX_HEIGHT - FLY_KOOPA_SHELL_BBOX_HEIGHT) / 2 - 5;
		vx = 0;
		break;
	case FLY_KOOPA_STATE_SHELL_ROLL:
		ay = FLY_KOOPA_GRAVITY;
		break;
	case FLY_KOOPA_STATE_SHELL_RESURRECT:
		break;
	case FLY_KOOPA_STATE_DIE:
		vx = 0;
		vy = 0;
		ay = 0;
		Delete();
		break;
	default:
		break;
	}
}

void CFlyKoopa::ToShellIdle()
{
	isHolded = false;
	SetState(FLY_KOOPA_STATE_SHELL_IDLE);
}

void CFlyKoopa::ToShellRoll(int dir)
{
	isHolded = false;
	SetState(FLY_KOOPA_STATE_SHELL_ROLL);
	vx = dir * FLY_KOOPA_ROLLING_SPEED;
}

void CFlyKoopa::ToShellHold(float adjX, float adjY)
{
	isHolded = true;
	holdAdjX = adjX;
	holdAdjY = adjY;
	SetState(FLY_KOOPA_STATE_SHELL_IDLE);
}

void CFlyKoopa::ToResurrect()
{
	SetState(FLY_KOOPA_STATE_SHELL_RESURRECT);
}

void CFlyKoopa::ToWalking()
{
	isHolded = false;
	SetState(FLY_KOOPA_STATE_WALKING);
}

void CFlyKoopa::LoseWing()
{
	haveWing = false;
	wing->Delete();
}