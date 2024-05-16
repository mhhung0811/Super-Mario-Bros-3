#include "PlatformOneWay.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

int CPlatformOneWay::IsDirectionColliable(float nx, float ny) {
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}