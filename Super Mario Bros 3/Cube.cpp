#include "Cube.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CCube::RenderBoundingBox()
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

	float xx = x - this->cellWidth / 2 + (float)rect.right / 2;
	float yy = y - this->cellHeight / 2 + (float)rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CCube::Render()
{
	/*DebugOut(L"Length is: %d\n", this->length);*/

	if (this->length <= 0 || this->height <= 0) return;
	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	// Top
	s->Get(this->spriteIdTopBegin)->Draw(xx, yy);
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdTopMiddle)->Draw(xx, yy);
		xx += this->cellWidth;
	}
	if (length > 1)
		s->Get(this->spriteIdTopEnd)->Draw(xx, yy);
	xx = x;
	yy += this->cellHeight;

	// Mid
	for (int i = 1; i < this->height - 1; i++)
	{
		s->Get(this->spriteIdMidBegin)->Draw(xx, yy);
		xx += this->cellWidth;
		for (int i = 1; i < this->length - 1; i++)
		{
			s->Get(this->spriteIdMidMiddle)->Draw(xx, yy);
			xx += this->cellWidth;
		}
		if (length > 1)
			s->Get(this->spriteIdMidEnd)->Draw(xx, yy);
		xx = x;
		yy += this->cellHeight;
	}

	// Bottom
	if (height > 1)
	{
		s->Get(this->spriteIdBottomBegin)->Draw(xx, yy);
		xx += this->cellWidth;
		for (int i = 1; i < this->length - 1; i++)
		{
			s->Get(this->spriteIdBottomMiddle)->Draw(xx, yy);
			xx += this->cellWidth;
		}
		if (length > 1)
			s->Get(this->spriteIdBottomEnd)->Draw(xx, yy);
	}

	/*RenderBoundingBox();*/
}

void CCube::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->cellWidth / 2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->length;
	b = t + this->cellHeight * this->height;
}