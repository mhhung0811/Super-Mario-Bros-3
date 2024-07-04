#pragma once

#include "Cube.h"

// 
// Invicible Wall!
// 
class CWorldWall : public CCube
{
protected:
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
	CWorldWall(
		float x, float y,
		float cellWidth, float cellHeight,
		int length, int height,
		int sprite_id_top_begin, int sprite_id_top_middle, int sprite_id_top_end,
		int sprite_id_mid_begin, int sprite_id_mid_middle, int sprite_id_mid_end,
		int sprite_id_bottom_begin, int sprite_id_bottom_middle, int sprite_id_bottom_end)
		: CCube(
			x, y,
			cellWidth, cellHeight,
			length, height,
			sprite_id_top_begin, sprite_id_top_middle, sprite_id_top_end,
			sprite_id_mid_begin, sprite_id_mid_middle, sprite_id_mid_end,
			sprite_id_bottom_begin, sprite_id_bottom_middle, sprite_id_bottom_end
		)
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

	void Render() {}
};

typedef CWorldWall* LPWORLDWALL;