#pragma once

#include "GameObject.h"

class CCube : public CGameObject
{
protected:
	int length;
	int height;
	float cellWidth;
	float cellHeight;
	int spriteIdTopBegin,
		spriteIdTopMiddle,
		spriteIdTopEnd,
		spriteIdMidBegin,
		spriteIdMidMiddle,
		spriteIdMidEnd,
		spriteIdBottomBegin,
		spriteIdBottomMiddle,
		spriteIdBottomEnd;
public:
	CCube(
		float x, float y,
		float cellWidth, float cellHeight,
		int length, int height,
		int sprite_id_top_begin, int sprite_id_top_middle, int sprite_id_top_end,
		int sprite_id_mid_begin, int sprite_id_mid_middle, int sprite_id_mid_end,
		int sprite_id_bottom_begin, int sprite_id_bottom_middle, int sprite_id_bottom_end) : CGameObject(x, y)
	{
		this->length = length;
		this->height = height;
		this->cellWidth = cellWidth;
		this->cellHeight = cellHeight;

		this->spriteIdTopBegin = sprite_id_top_begin;
		this->spriteIdTopMiddle = sprite_id_top_middle;
		this->spriteIdTopEnd = sprite_id_top_end;

		this->spriteIdMidBegin = sprite_id_mid_begin;
		this->spriteIdMidMiddle = sprite_id_mid_middle;
		this->spriteIdMidEnd = sprite_id_mid_end;

		this->spriteIdBottomBegin = sprite_id_bottom_begin;
		this->spriteIdBottomMiddle = sprite_id_bottom_middle;
		this->spriteIdBottomEnd = sprite_id_bottom_end;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	virtual int IsDirectionColliable(float nx, float ny) { return 1; };
	virtual int IsBlocking() { return 1; }
};

typedef CCube* LPCube;