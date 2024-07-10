#include "NormalKoopa.h"

CNormalKoopa::CNormalKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = NORMAL_KOOPA_GRAVITY;
	//this->groundCheck = new CEmptyObject(x - NORMAL_KOOPA_GROUND_CHECK_X, y + NORMAL_KOOPA_GROUND_CHECK_Y, NORMAL_KOOPA_BBOX_WIDTH, 2);
	/*groundCheck->SetPosition(-(x + NORMAL_KOOPA_GROUND_CHECK_X), y + NORMAL_KOOPA_GROUND_CHECK_Y);*/

	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	//playScene->AddObject(groundCheck, 0);


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
		//if (vx <= 0) groundCheck->SetPosition(x - NORMAL_KOOPA_GROUND_CHECK_X, y + NORMAL_KOOPA_GROUND_CHECK_Y);
		//else groundCheck->SetPosition(x + NORMAL_KOOPA_GROUND_CHECK_X, y + NORMAL_KOOPA_GROUND_CHECK_Y);
	}
	if (dynamic_cast<CMysteryBox*>(e->obj) && state == NORMAL_KOOPA_STATE_SHELL_ROLL)
	{
		CMysteryBox* mBox = dynamic_cast<CMysteryBox*>(e->obj);
		mBox->OpenBox();
	}
}

void CNormalKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*DebugOut(L"state: %d\n", state);*/

	vy += ay * dt;
	vx += ax * dt;

	//groundCheck->SetSpeed(vx, vy);

	// Patrol
	if (state == NORMAL_KOOPA_STATE_WALKING && EdgeCheck())
	{
		vx = -vx;
		//if (vx <= 0) groundCheck->SetPosition(x - NORMAL_KOOPA_GROUND_CHECK_X, y + NORMAL_KOOPA_GROUND_CHECK_Y);
		//else groundCheck->SetPosition(x + NORMAL_KOOPA_GROUND_CHECK_X, y + NORMAL_KOOPA_GROUND_CHECK_Y);
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

bool CNormalKoopa::EdgeCheck()
{
	float gx, gy;
	//groundCheck->GetPosition(gx, gy);
	/*if (gy > y + NORMAL_KOOPA_BBOX_HEIGHT / 2)
	{
		return true;
	}*/
	return false;
}

void CNormalKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case NORMAL_KOOPA_STATE_WALKING:
		y -= (NORMAL_KOOPA_BBOX_HEIGHT - NORMAL_KOOPA_SHELL_BBOX_HEIGHT) / 2 + 5;
		vx = -NORMAL_KOOPA_WALKING_SPEED;
		/*if (vx <= 0) groundCheck->SetPosition(x - NORMAL_KOOPA_GROUND_CHECK_X, y + NORMAL_KOOPA_GROUND_CHECK_Y);
		else groundCheck->SetPosition(x + NORMAL_KOOPA_GROUND_CHECK_X, y + NORMAL_KOOPA_GROUND_CHECK_Y);*/
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
		/*case NORMAL_KOOPA_STATE_SHELL_HOLDED:
			vx = 0;
			vy = 0;
			ax = 0;
			ay = 0;
			break;*/
	case NORMAL_KOOPA_STATE_DIE:
		vx = 0;
		vy = 0;
		ay = 0;
		Delete();
		break;
	default:
		break;
	}
}

void CNormalKoopa::ToShellIdle()
{
	isHolded = false;
	SetState(NORMAL_KOOPA_STATE_SHELL_IDLE);
}

void CNormalKoopa::ToShellRoll(int dir)
{
	isHolded = false;
	SetState(NORMAL_KOOPA_STATE_SHELL_ROLL);
	vx = dir * NORMAL_KOOPA_ROLLING_SPEED;
}

void CNormalKoopa::ToShellHold(float adjX, float adjY)
{
	isHolded = true;
	holdAdjX = adjX;
	holdAdjY = adjY;
	SetState(NORMAL_KOOPA_STATE_SHELL_IDLE);
}

void CNormalKoopa::ToResurrect()
{
	SetState(NORMAL_KOOPA_STATE_SHELL_RESURRECT);
}

void CNormalKoopa::ToWalking()
{
	isHolded = false;
	SetState(NORMAL_KOOPA_STATE_WALKING);
}