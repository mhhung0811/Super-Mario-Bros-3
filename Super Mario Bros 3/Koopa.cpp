#include "Koopa.h"
#include "EmptyObject.h"

CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	this->groundCheck = new CEmptyObject(x - KOOPA_GROUND_CHECK_X, y + KOOPA_GROUND_CHECK_Y, KOOPA_BBOX_WIDTH, 2);
	/*groundCheck->SetPosition(-(x + KOOPA_GROUND_CHECK_X), y + KOOPA_GROUND_CHECK_Y);*/
	
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	playScene->AddObject(groundCheck, 0);
	
	
	SetState(KOOPA_STATE_WALKING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_WALKING)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_SHELL_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_SHELL_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		if (vx <= 0) groundCheck->SetPosition(x - KOOPA_GROUND_CHECK_X, y + KOOPA_GROUND_CHECK_Y);
		else groundCheck->SetPosition(x + KOOPA_GROUND_CHECK_X, y + KOOPA_GROUND_CHECK_Y);
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	groundCheck->SetSpeed(vx, vy);

	// if end of the gound
	if (state == KOOPA_STATE_WALKING && EdgeCheck())
	{
		vx = -vx;
		if (vx <= 0) groundCheck->SetPosition(x - KOOPA_GROUND_CHECK_X, y + KOOPA_GROUND_CHECK_Y);
		else groundCheck->SetPosition(x + KOOPA_GROUND_CHECK_X, y + KOOPA_GROUND_CHECK_Y);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	int aniId;
	int sprId = ID_SPR_KOOPA_SHELL_IDLE;
	switch (state)
	{
	case KOOPA_STATE_WALKING:
		aniId = (vx <= 0) ? ID_ANI_KOOPA_WALK_LEFT : ID_ANI_KOOPA_WALK_RIGHT;
		break;
	case KOOPA_STATE_SHELL_HOLDED:
	case KOOPA_STATE_SHELL_IDLE:
		CSprites::GetInstance()->Get(sprId)->Draw(x, y);
		break;
	case KOOPA_STATE_SHELL_APPEAR:
		aniId = ID_ANI_KOOPA_SHELL_APPEAR;
		break;
	case KOOPA_STATE_SHELL_ROLL:
		aniId = ID_ANI_KOOPA_SHELL_ROLL;
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

bool CKoopa::EdgeCheck()
{
	float gx, gy;
	groundCheck->GetPosition(gx, gy);
	if (gy > y + KOOPA_BBOX_HEIGHT / 2)
	{
		return true;
	}
	return false;
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SHELL_IDLE:
		break;
	case KOOPA_STATE_SHELL_ROLL:
		break;
	case KOOPA_STATE_SHELL_APPEAR:
		break;
	case KOOPA_STATE_SHELL_HOLDED:
		break;
	case KOOPA_STATE_DIE:
		vx = 0;
		vy = 0;
		ay = 0;
		Delete();
		break;
	default:
		break;
	}
}