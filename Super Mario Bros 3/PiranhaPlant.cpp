#include "PiranhaPlant.h"

CPiranhaPlant::CPiranhaPlant(float x, float y) :CGameObject(x, y)
{
	this->fixedX = x;
	this->fixedY = y;
	this->isIdle = 0;
	this->facingDir = 0;
	this->canShoot = true;
	SetState(PIRANHAPLANT_STATE_IDLE);
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHAPLANT_BBOX_WIDTH / 2;
	top = y - PIRANHAPLANT_BBOX_HEIGHT / 2;
	right = left + PIRANHAPLANT_BBOX_WIDTH;
	bottom = top + PIRANHAPLANT_BBOX_HEIGHT;
}

/*
	Get shoot box in world coord
*/
void CPiranhaPlant::GetShootBox(int id, float& left, float& top, float& right, float& bottom)
{
	/*float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);*/
	float bx, by, rx, ry;
	switch (id)
	{
	case ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_0:
		rx = PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_0_X;
		ry = PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_0_Y;
		break;
	case ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_1:
		rx = PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_1_X;
		ry = PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_1_Y;
		break;
	case ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_0:
		rx = PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_0_X;
		ry = PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_0_Y;
		break;
	case ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_1:
		rx = PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_1_X;
		ry = PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_1_Y;
		break;
	case ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_0:
		rx = PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_0_X;
		ry = PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_0_Y;
		break;
	case ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_1:
		rx = PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_1_X;
		ry = PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_1_Y;
		break;
	case ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_0:
		rx = PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_0_X;
		ry = PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_0_Y;
		break;
	case ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_1:
		rx = PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_1_X;
		ry = PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_1_Y;
		break;
	case ID_PIRANHAPLANT_SAFE_BOX:
		rx = PIRANHAPLANT_SAFE_BOX_X;
		ry = PIRANHAPLANT_SAFE_BOX_Y;
		break;
	default:
		rx = 0;
		ry = 0;
		break;
	}
	bx = x + rx;
	by = y + ry;

	left = bx;
	top = by;
	right = left + PIRANHAPLANT_SHOOT_BOX_WIDTH;
	bottom = top + PIRANHAPLANT_SHOOT_BOX_HEIGHT;
}

void CPiranhaPlant::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - PIRANHAPLANT_BBOX_WIDTH / 2 + (float)rect.right / 2;
	float yy = y - PIRANHAPLANT_BBOX_HEIGHT / 2 + (float)rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}
void CPiranhaPlant::RenderShootBox(int id)
{
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
	
	float l, t, r, b;
	GetShootBox(id, l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);	

	CGame::GetInstance()->Draw(l - cx, t - cy, bbox, &rect, BBOX_ALPHA);
}

void CPiranhaPlant::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CKoopa*>(e->obj))
	{
		CKoopa* p = dynamic_cast<CKoopa*>(e->obj);
		if (p->IsRolled())
		{
			SetState(PIRANHAPLANT_STATE_DIE);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(x, y, 0);
		}
	}
	if (dynamic_cast<CFlyKoopa*>(e->obj))
	{
		CFlyKoopa* p = dynamic_cast<CFlyKoopa*>(e->obj);
		if (p->IsRolled())
		{
			SetState(PIRANHAPLANT_STATE_DIE);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(x, y, 0);
		}
	}

	if (dynamic_cast<CNormalKoopa*>(e->obj))
	{
		CNormalKoopa* p = dynamic_cast<CNormalKoopa*>(e->obj);
		if (p->IsRolled())
		{
			SetState(PIRANHAPLANT_STATE_DIE);
			LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			playScene->FlowScore(x, y, 0);
		}
	}
}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cx, cy;
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	CGame::GetInstance()->GetCamPos(cx, cy);
	// Appear & Disappear
	if (state == PIRANHAPLANT_STATE_APPEAR && y <= (fixedY)-PIRANHAPLANT_BBOX_HEIGHT)
	{
		isColl = 1;
		SetState(PIRANHAPLANT_STATE_IDLE);
	}
	if (state == PIRANHAPLANT_STATE_DISAPPEAR && y >= (fixedY) + 10)
	{
		SetState(PIRANHAPLANT_STATE_IDLE);
	}
	if (state == PIRANHAPLANT_STATE_IDLE)
	{
		// Detect Player
		LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
		LPGAMEOBJECT player = playScene->GetPlayer();
		int boxId = -1;
		if (player == NULL) DebugOut(L"Player is null\n");
		else boxId = InWhichBox(player);
		// Action in when player in zone
		switch (boxId)
		{
		case ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_0:
			facingDir = 0;
			// only shoot 1 per idle UP
			if (canShoot && y < fixedY)
			{
				canShoot = false;
				playScene->CreateFireBall(x, y - 8, FIREBALL_DIRECTION_LEFT_LOW_0);
			}
			break;
		case ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_1:
			facingDir = 0;
			if (canShoot && y < fixedY)
			{
				canShoot = false;
				playScene->CreateFireBall(x, y - 8, FIREBALL_DIRECTION_LEFT_LOW_1);
			}
			break;
		case ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_0:
			facingDir = 1;
			if (canShoot && y < fixedY)
			{
				canShoot = false;
				playScene->CreateFireBall(x, y - 8, FIREBALL_DIRECTION_LEFT_HIGH_0);
			}
			break;
		case ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_1:
			facingDir = 1;
			if (canShoot && y < fixedY)
			{
				canShoot = false;
				playScene->CreateFireBall(x, y - 8, FIREBALL_DIRECTION_LEFT_HIGH_1);
			}
			break;
		case ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_0:
			facingDir = 2;
			if (canShoot && y < fixedY)
			{
				canShoot = false;
				playScene->CreateFireBall(x, y - 8, FIREBALL_DIRECTION_RIGHT_LOW_1);
			}
			break;
		case ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_1:
			facingDir = 2;
			if (canShoot && y < fixedY)
			{
				canShoot = false;
				playScene->CreateFireBall(x, y - 8, FIREBALL_DIRECTION_RIGHT_LOW_1);
			}
			break;
		case ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_0:
			facingDir = 3;
			if (canShoot && y < fixedY)
			{
				canShoot = false;
				playScene->CreateFireBall(x, y - 8, FIREBALL_DIRECTION_RIGHT_HIGH_0);
			}
			break;
		case ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_1:
			facingDir = 3;
			if (canShoot && y < fixedY)
			{
				canShoot = false;
				playScene->CreateFireBall(x, y - 8, FIREBALL_DIRECTION_RIGHT_HIGH_1);
			}
			break;
		case ID_PIRANHAPLANT_SAFE_BOX:
			isIdle = 0;
			break;
		default:
			facingDir = 1;
			break;
		}

		// to Other state
		if (isIdle > ((x < 1500) ? PIRANHAPLANT_IDLE_TIME : PIRANHAPLANT_GREEN_IDLE_TIME))
		{
			isIdle = 0;
			if (y < (fixedY))
			{
				isColl = 0;
				SetState(PIRANHAPLANT_STATE_DISAPPEAR);
			}
			else
			{
				SetState(PIRANHAPLANT_STATE_APPEAR);
			}
		}
		else
		{
			isIdle += dt;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::Render()
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CSprites* s = CSprites::GetInstance();
	int aniId, sprId;
	switch (facingDir)
	{
	case 0:
		aniId = (x < 1500) ? ID_ANI_PIRANHAPLANT_APPEAR_LEFT : ID_ANI_PIRANHAPLANT_GREEN_APPEAR_LEFT;
		sprId = (x < 1500) ? ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED_LEFT_DOWN : ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN_LEFT_DOWN;
		break;
	case 1:
		aniId = (x < 1500) ? ID_ANI_PIRANHAPLANT_APPEAR_LEFT : ID_ANI_PIRANHAPLANT_GREEN_APPEAR_LEFT;
		sprId = (x < 1500) ? ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED_LEFT_UP : ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN_LEFT_UP;
		break;
	case 2:
		aniId = (x < 1500) ? ID_ANI_PIRANHAPLANT_APPEAR_RIGHT : ID_ANI_PIRANHAPLANT_GREEN_APPEAR_RIGHT;
		sprId = (x < 1500) ? ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED_RIGHT_DOWN : ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN_RIGHT_DOWN;
		break;
	case 3:
		aniId = (x < 1500) ? ID_ANI_PIRANHAPLANT_APPEAR_RIGHT : ID_ANI_PIRANHAPLANT_GREEN_APPEAR_RIGHT;
		sprId = (x < 1500) ? ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED_RIGHT_UP : ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN_RIGHT_UP;
		break;
	default:
		aniId = (x < 1500) ? ID_ANI_PIRANHAPLANT_APPEAR_LEFT : ID_ANI_PIRANHAPLANT_GREEN_APPEAR_LEFT;
		sprId = (x < 1500) ? ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED_LEFT_UP : ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN_LEFT_UP;
	}
	if (state == PIRANHAPLANT_STATE_IDLE)
	{
		s->Get(sprId + 1)->Draw(x, y);
	}
	else
	{
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}

	/*RenderShootBox(ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_0);
	RenderShootBox(ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_1);
	RenderShootBox(ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_0);
	RenderShootBox(ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_1);
	RenderShootBox(ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_0);
	RenderShootBox(ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_1);
	RenderShootBox(ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_0);
	RenderShootBox(ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_1);
	RenderShootBox(ID_PIRANHAPLANT_SAFE_BOX);
	RenderBoundingBox();*/
}

void CPiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHAPLANT_STATE_APPEAR:
		vy = -((x < 1500) ? PIRANHAPLANT_APPEAR_SPEED : PIRANHAPLANT_GREEN_APPEAR_SPEED);
		break;
	case PIRANHAPLANT_STATE_DISAPPEAR:
		vy = (x < 1500) ? PIRANHAPLANT_APPEAR_SPEED : PIRANHAPLANT_GREEN_APPEAR_SPEED;
		break;
	case PIRANHAPLANT_STATE_IDLE:
		canShoot = true;
		vy = 0;
		break;
	case PIRANHAPLANT_STATE_DIE:
		isDeleted = true;
		break;
	default:
		break;
	}
}

int CPiranhaPlant::InWhichBox(LPGAMEOBJECT obj)
{
	float cx, cy;
	float bug1, bug2;
	bug1 = -24;	// it has to be -24 for the collider to work well
	bug2 = -24;	// still a mystery!
	CGame::GetInstance()->GetCamPos(cx, cy);

	if (obj == NULL) return -1;
	float l1, t1, r1, b1, l2, t2, r2, b2;
	obj->GetBoundingBox(l2, t2, r2, b2);
	l2 -= cx;
	t2 -= cy;
	r2 -= cx;
	b2 -= cy;
	// Is in Left Low 0
	GetShootBox(ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_0, l1, t1, r1, b1);
	l1 = l1 - cx + bug1;
	t1 = t1 - cy + bug2;
	r1 = r1 - cx + bug1;
	b1 = b1 - cy + bug2;
	if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
	{
		//DebugOut(L"is: %d\n", ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_0);
		return ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_0;
	}
	// Is in Left Low 1
	GetShootBox(ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_1, l1, t1, r1, b1);
	l1 = l1 - cx + bug1;
	t1 = t1 - cy + bug2;
	r1 = r1 - cx + bug1;
	b1 = b1 - cy + bug2;
	if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
	{
		//DebugOut(L"is: %d\n", ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_1);
		return ID_PIRANHAPLANT_SHOOT_BOX_LEFT_LOW_1;
	}
	// Is in Left High 0
	GetShootBox(ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_0, l1, t1, r1, b1);
	l1 = l1 - cx + bug1;
	t1 = t1 - cy + bug2;
	r1 = r1 - cx + bug1;
	b1 = b1 - cy + bug2;
	if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
	{
		//DebugOut(L"is: %d\n", ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_0);
		return ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_0;
	}
	// Is in Left High 1
	GetShootBox(ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_1, l1, t1, r1, b1);
	l1 = l1 - cx + bug1;
	t1 = t1 - cy + bug2;
	r1 = r1 - cx + bug1;
	b1 = b1 - cy + bug2;
	if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
	{
		//DebugOut(L"is: %d\n", ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_1);
		return ID_PIRANHAPLANT_SHOOT_BOX_LEFT_HIGH_1;
	}

	// Is in Righ Low 0
	GetShootBox(ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_0, l1, t1, r1, b1);
	l1 = l1 - cx + bug1;
	t1 = t1 - cy + bug2;
	r1 = r1 - cx + bug1;
	b1 = b1 - cy + bug2;
	if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
	{
		//DebugOut(L"is: %d\n", ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_0);
		return ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_0;
	}
	// Is in Right Low 1
	GetShootBox(ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_1, l1, t1, r1, b1);
	l1 = l1 - cx + bug1;
	t1 = t1 - cy + bug2;
	r1 = r1 - cx + bug1;
	b1 = b1 - cy + bug2;
	if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
	{
		//DebugOut(L"is: %d\n", ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_1);
		return ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_LOW_1;
	}
	// Is in Right High 0
	GetShootBox(ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_0, l1, t1, r1, b1);
	l1 = l1 - cx + bug1;
	t1 = t1 - cy + bug2;
	r1 = r1 - cx + bug1;
	b1 = b1 - cy + bug2;
	if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
	{
		//DebugOut(L"is: %d\n", ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_0);
		return ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_0;
	}
	// Is in Right High 1
	GetShootBox(ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_1, l1, t1, r1, b1);
	l1 = l1 - cx + bug1;
	t1 = t1 - cy + bug2;
	r1 = r1 - cx + bug1;
	b1 = b1 - cy + bug2;
	if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
	{
		//DebugOut(L"is: %d\n", ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_1);
		return ID_PIRANHAPLANT_SHOOT_BOX_RIGHT_HIGH_1;
	}
	// Is in Safe Box
	GetShootBox(ID_PIRANHAPLANT_SAFE_BOX, l1, t1, r1, b1);
	l1 = l1 - cx + bug1;
	t1 = t1 - cy + bug2;
	r1 = r1 - cx + bug1;
	b1 = b1 - cy + bug2;
	if (OverlapBox(l1, t1, r1, b1, l2, t2, r2, b2))
	{
		//DebugOut(L"is: %d\n", ID_PIRANHAPLANT_SAFE_BOX);
		return ID_PIRANHAPLANT_SAFE_BOX;
	}
	//DebugOut(L"no box found\n");
	return -1;
}