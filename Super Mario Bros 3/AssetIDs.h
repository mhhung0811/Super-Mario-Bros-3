#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_TILES 30


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPA	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_PLATFORM_ONE_WAY 6
#define OBJECT_TYPE_DECOR 7
#define OBJECT_TYPE_CUBE_ONE_WAY 8
#define OBJECT_TYPE_MYSTERY_BOX 9
#define OBJECT_TYPE_MUSHROOM 10
#define OBJECT_TYPE_CUBE 11
#define OBJECT_TYPE_PIRANHAPLANT 12
#define OBJECT_TYPE_FIREBALL 13
#define OBJECT_TYPE_RACOONLEAF 14
#define OBJECT_TYPE_FLY_GOOMBA 15
#define OBJECT_TYPE_WING 16
#define OBJECT_TYPE_SPAWNER 17
#define OBJECT_TYPE_WORLDWALL 18
#define OBJECT_TYPE_FLY_KOOPA 19
#define OBJECT_TYPE_NORMAL_KOOPA 20
#define OBJECT_TYPE_PIRANHAPLANT_BITE 21

#define OBJECT_TYPE_PORTAL	50


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)

#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RELEASE (ID_SPRITE_MARIO_BIG_JUMP + 30)
#define ID_SPRITE_MARIO_BIG_JUMP_RELEASE_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RELEASE + 1)
#define ID_SPRITE_MARIO_BIG_JUMP_RELEASE_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RELEASE + 2)

#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)

#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_BIG_HOLDSHELL (ID_SPRITE_MARIO_BIG + 700)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_IDLE (ID_SPRITE_MARIO_BIG_HOLDSHELL + 10)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_IDLE_LEFT (ID_SPRITE_MARIO_BIG_HOLDSHELL_IDLE + 1)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_HOLDSHELL_IDLE + 2)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_WALK (ID_SPRITE_MARIO_BIG_HOLDSHELL + 20)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_WALK_LEFT (ID_SPRITE_MARIO_BIG_HOLDSHELL_WALK + 1)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_WALK_RIGHT (ID_SPRITE_MARIO_BIG_HOLDSHELL_WALK + 2)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_RUNNING (ID_SPRITE_MARIO_BIG_HOLDSHELL + 30)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_HOLDSHELL_RUNNING + 1)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_HOLDSHELL_RUNNING + 2)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_KICK (ID_SPRITE_MARIO_BIG_HOLDSHELL + 40)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_KICK_LEFT (ID_SPRITE_MARIO_BIG_HOLDSHELL_KICK + 1)
#define ID_SPRITE_MARIO_BIG_HOLDSHELL_KICK_RIGHT (ID_SPRITE_MARIO_BIG_HOLDSHELL_KICK + 2)


#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

//#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
//#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
//#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#define ID_SPRITE_MARIO_SMALL_HOLDSHELL (ID_SPRITE_MARIO_SMALL + 600)
#define ID_SPRITE_MARIO_SMALL_HOLDSHELL_IDLE (ID_SPRITE_MARIO_SMALL_HOLDSHELL + 10)
#define ID_SPRITE_MARIO_SMALL_HOLDSHELL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_HOLDSHELL_IDLE + 1)
#define ID_SPRITE_MARIO_SMALL_HOLDSHELL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_HOLDSHELL_IDLE + 2)
#define ID_SPRITE_MARIO_SMALL_HOLDSHELL_WALK (ID_SPRITE_MARIO_SMALL_HOLDSHELL + 20)
#define ID_SPRITE_MARIO_SMALL_HOLDSHELL_WALK_LEFT (ID_SPRITE_MARIO_SMALL_HOLDSHELL_WALK + 1)
#define ID_SPRITE_MARIO_SMALL_HOLDSHELL_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_HOLDSHELL_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_HOLDSHELL_KICK (ID_SPRITE_MARIO_SMALL_HOLDSHELL + 30)
#define ID_SPRITE_MARIO_SMALL_HOLDSHELL_KICK_LEFT (ID_SPRITE_MARIO_SMALL_HOLDSHELL_KICK + 1)
#define ID_SPRITE_MARIO_SMALL_HOLDSHELL_KICK_RIGHT (ID_SPRITE_MARIO_SMALL_HOLDSHELL_KICK + 2)


#define ID_SPRITE_MARIO_RACOON (ID_SPRITE_MARIO + 4000)
#define ID_SPRITE_MARIO_RACOON_IDLE (ID_SPRITE_MARIO_RACOON + 100)
#define ID_SPRITE_MARIO_RACOON_IDLE_LEFT (ID_SPRITE_MARIO_RACOON_IDLE + 10)
#define ID_SPRITE_MARIO_RACOON_IDLE_RIGHT (ID_SPRITE_MARIO_RACOON_IDLE + 20)

#define ID_SPRITE_MARIO_RACOON_WALKING (ID_SPRITE_MARIO_RACOON + 200)
#define ID_SPRITE_MARIO_RACOON_WALKING_LEFT (ID_SPRITE_MARIO_RACOON_WALKING + 10)
#define ID_SPRITE_MARIO_RACOON_WALKING_RIGHT (ID_SPRITE_MARIO_RACOON_WALKING + 20)
#define ID_SPRITE_MARIO_RACOON_RUNNING (ID_SPRITE_MARIO_RACOON + 300)
#define ID_SPRITE_MARIO_RACOON_RUNNING_LEFT (ID_SPRITE_MARIO_RACOON_RUNNING + 10)
#define ID_SPRITE_MARIO_RACOON_RUNNING_RIGHT (ID_SPRITE_MARIO_RACOON_RUNNING + 20)
#define ID_SPRITE_MARIO_RACOON_JUMP (ID_SPRITE_MARIO_RACOON + 400)
#define ID_SPRITE_MARIO_RACOON_JUMP_WALK (ID_SPRITE_MARIO_RACOON_JUMP + 10)
#define ID_SPRITE_MARIO_RACOON_JUMP_WALK_LEFT (ID_SPRITE_MARIO_RACOON_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_RACOON_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_RACOON_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_RACOON_JUMP_RUN (ID_SPRITE_MARIO_RACOON_JUMP + 20)
#define ID_SPRITE_MARIO_RACOON_JUMP_RUN_LEFT (ID_SPRITE_MARIO_RACOON_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_RACOON_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_RACOON_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_RACOON_JUMP_RELEASE (ID_SPRITE_MARIO_RACOON_JUMP + 30)
#define ID_SPRITE_MARIO_RACOON_JUMP_RELEASE_LEFT (ID_SPRITE_MARIO_RACOON_JUMP_RELEASE + 1)
#define ID_SPRITE_MARIO_RACOON_JUMP_RELEASE_RIGHT (ID_SPRITE_MARIO_RACOON_JUMP_RELEASE + 2)

#define ID_SPRITE_MARIO_RACOON_SIT (ID_SPRITE_MARIO_RACOON + 500)
#define ID_SPRITE_MARIO_RACOON_SIT_LEFT (ID_SPRITE_MARIO_RACOON_SIT + 10)
#define ID_SPRITE_MARIO_RACOON_SIT_RIGHT (ID_SPRITE_MARIO_RACOON_SIT + 20)

#define ID_SPRITE_MARIO_RACOON_BRACE (ID_SPRITE_MARIO_RACOON + 600)
#define ID_SPRITE_MARIO_RACOON_BRACE_LEFT (ID_SPRITE_MARIO_RACOON_BRACE + 10)
#define ID_SPRITE_MARIO_RACOON_BRACE_RIGHT (ID_SPRITE_MARIO_RACOON_BRACE + 20)

#define ID_SPRITE_MARIO_RACOON_FLAP (ID_SPIRTE_MARIO_RACOON + 700)
#define ID_SPRITE_MARIO_RACOON_FLAP_FLOW_UP (ID_SPRITE_MARIO_RACOON_FLAP + 10)
#define ID_SPRITE_MARIO_RACOON_FLAP_FLOW_DOWN (ID_SPRITE_MARIO_RACOON_FLAP + 20)
#define ID_SPRITE_MARIO_RACOON_FLAP_FLY_UP (ID_SPRITE_MARIO_RACOON_FLAP + 30)
#define ID_SPRITE_MARIO_RACOON_FLAP_FLY_DOWN (ID_SPRITE_MARIO_RACOON_FLAP + 40)

#define ID_SPRITE_MARIO_RACOON_HOLDSHELL (ID_SPRITE_MARIO_RACOON + 800)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_IDLE (ID_SPRITE_MARIO_RACOON_HOLDSHELL + 10)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_IDLE_LEFT (ID_SPRITE_MARIO_RACOON_HOLDSHELL_IDLE + 1)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_IDLE_RIGHT (ID_SPRITE_MARIO_RACOON_HOLDSHELL_IDLE + 2)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_WALK (ID_SPRITE_MARIO_RACOON_HOLDSHELL + 20)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_WALK_LEFT (ID_SPRITE_MARIO_RACOON_HOLDSHELL_WALK + 1)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_WALK_RIGHT (ID_SPRITE_MARIO_RACOON_HOLDSHELL_WALK + 2)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_RUNNING (ID_SPRITE_MARIO_RACOON_HOLDSHELL + 30)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_RUNNING_LEFT (ID_SPRITE_MARIO_RACOON_HOLDSHELL_RUNNING + 1)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_RUNNING_RIGHT (ID_SPRITE_MARIO_RACOON_HOLDSHELL_RUNNING + 2)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_KICK (ID_SPRITE_MARIO_RACOON_HOLDSHELL + 40)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_KICK_LEFT (ID_SPRITE_MARIO_RACOON_HOLDSHELL_KICK + 1)
#define ID_SPRITE_MARIO_RACOON_HOLDSHELL_KICK_RIGHT (ID_SPRITE_MARIO_RACOON_HOLDSHELL_KICK + 2)

#define ID_SPRITE_MARIO_RACOON_ATTACK (ID_SPRITE_MARIO_RACOON + 900)
#define ID_SPRITE_MARIO_RACOON_ATTACK_LEFT (ID_SPRITE_MARIO_RACOON_ATTACK + 10)
#define ID_SPRITE_MARIO_RACOON_ATTACK_RIGHT (ID_SPRITE_MARIO_RACOON_ATTACK + 20)

#pragma endregion 

#define ID_SPRITE_BRICK 20000

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_GROUND 60000
#define ID_SPRITE_GROUND_TOP_BEGIN (ID_SPRITE_GROUND + 1000)
#define ID_SPRITE_GROUND_TOP_MIDDLE (ID_SPRITE_GROUND + 2000)
#define ID_SPRITE_GROUND_TOP_END (ID_SPRITE_GROUND + 3000)
#define ID_SPRITE_GROUND_MID_BEGIN (ID_SPRITE_GROUND + 4000)
#define ID_SPRITE_GROUND_MID_MIDDLE (ID_SPRITE_GROUND + 5000)
#define ID_SPRITE_GROUND_MID_END (ID_SPRITE_GROUND + 6000)

#pragma region CUBES
#define ID_SPRITE_CUBE 70000

#define ID_SPRITE_CUBE_PINK_TOP_BEGIN (ID_SPRITE_CUBE + 100)
#define ID_SPRITE_CUBE_PINK_TOP_MIDDLE (ID_SPRITE_CUBE + 200)
#define ID_SPRITE_CUBE_PINK_TOP_END (ID_SPRITE_CUBE + 300)
#define ID_SPRITE_CUBE_PINK_MID_BEGIN (ID_SPRITE_CUBE + 400)
#define ID_SPRITE_CUBE_PINK_MID_MIDDLE (ID_SPRITE_CUBE + 500)
#define ID_SPRITE_CUBE_PINK_MID_END (ID_SPRITE_CUBE + 600)
#define ID_SPRITE_CUBE_PINK_BOTTOM_BEGIN (ID_SPRITE_CUBE + 700)
#define ID_SPRITE_CUBE_PINK_BOTTOM_MIDDLE (ID_SPRITE_CUBE + 800)
#define ID_SPRITE_CUBE_PINK_BOTTOM_END (ID_SPRITE_CUBE + 900)

#define ID_SPRITE_CUBE_BLUE_TOP_BEGIN (ID_SPRITE_CUBE + 1100)
#define ID_SPRITE_CUBE_BLUE_TOP_MIDDLE (ID_SPRITE_CUBE + 1200)
#define ID_SPRITE_CUBE_BLUE_TOP_END (ID_SPRITE_CUBE + 1300)
#define ID_SPRITE_CUBE_BLUE_MID_BEGIN (ID_SPRITE_CUBE + 1400)
#define ID_SPRITE_CUBE_BLUE_MID_MIDDLE (ID_SPRITE_CUBE + 1500)
#define ID_SPRITE_CUBE_BLUE_MID_END (ID_SPRITE_CUBE + 1600)
#define ID_SPRITE_CUBE_BLUE_BOTTOM_BEGIN (ID_SPRITE_CUBE + 1700)
#define ID_SPRITE_CUBE_BLUE_BOTTOM_MIDDLE (ID_SPRITE_CUBE + 1800)
#define ID_SPRITE_CUBE_BLUE_BOTTOM_END (ID_SPRITE_CUBE + 1900)

#define ID_SPRITE_CUBE_GREEN_TOP_BEGIN (ID_SPRITE_CUBE + 2100)
#define ID_SPRITE_CUBE_GREEN_TOP_MIDDLE (ID_SPRITE_CUBE + 2200)
#define ID_SPRITE_CUBE_GREEN_TOP_END (ID_SPRITE_CUBE + 2300)
#define ID_SPRITE_CUBE_GREEN_MID_BEGIN (ID_SPRITE_CUBE + 2400)
#define ID_SPRITE_CUBE_GREEN_MID_MIDDLE (ID_SPRITE_CUBE + 2500)
#define ID_SPRITE_CUBE_GREEN_MID_END (ID_SPRITE_CUBE + 2600)
#define ID_SPRITE_CUBE_GREEN_BOTTOM_BEGIN (ID_SPRITE_CUBE + 2700)
#define ID_SPRITE_CUBE_GREEN_BOTTOM_MIDDLE (ID_SPRITE_CUBE + 2800)
#define ID_SPRITE_CUBE_GREEN_BOTTOM_END (ID_SPRITE_CUBE + 2900)

#define ID_SPRITE_CUBE_WHITE_TOP_BEGIN (ID_SPRITE_CUBE + 3100)
#define ID_SPRITE_CUBE_WHITE_TOP_MIDDLE (ID_SPRITE_CUBE + 3200)
#define ID_SPRITE_CUBE_WHITE_TOP_END (ID_SPRITE_CUBE + 3300)
#define ID_SPRITE_CUBE_WHITE_MID_BEGIN (ID_SPRITE_CUBE + 3400)
#define ID_SPRITE_CUBE_WHITE_MID_MIDDLE (ID_SPRITE_CUBE + 3500)
#define ID_SPRITE_CUBE_WHITE_MID_END (ID_SPRITE_CUBE + 3600)
#define ID_SPRITE_CUBE_WHITE_BOTTOM_BEGIN (ID_SPRITE_CUBE + 3700)
#define ID_SPRITE_CUBE_WHITE_BOTTOM_MIDDLE (ID_SPRITE_CUBE + 3800)
#define ID_SPRITE_CUBE_WHITE_BOTTOM_END (ID_SPRITE_CUBE + 3900)

#define ID_SPRITE_CUBE_PIPE_TOP_LEFT (ID_SPRITE_CUBE + 4100)
#define ID_SPRITE_CUBE_PIPE_TOP_RIGHT (ID_SPRITE_CUBE + 4200)
#define ID_SPRITE_CUBE_PIPE_BOTTOM_LEFT (ID_SPRITE_CUBE + 4300)
#define ID_SPRITE_CUBE_PIPE_BOTTOM_RIGHT (ID_SPRITE_CUBE + 4400)

#define ID_SPRITE_CUBE_BRICK (ID_SPRITE_CUBE + 5100)
#pragma endregion 

#pragma region BUSH
#define ID_SPRITE_BUSH 80000

#define ID_SPRITE_SMALL_BUSH 80001
#define ID_SPRITE_BUSH_SINGLE_LEFT (ID_SPRITE_BUSH + 1000)
#define ID_SPRITE_BUSH_SINGLE_RIGHT (ID_SPRITE_BUSH + 2000)
#define ID_SPRITE_BUSH_MULTI_LEFT (ID_SPRITE_BUSH + 3000)
#define ID_SPRITE_BUSH_MULTI_RIGHT (ID_SPRITE_BUSH + 4000)
#define ID_SPRITE_BUSH_BODY_LEFT (ID_SPRITE_BUSH + 5000)
#define ID_SPRITE_BUSH_BODY_RIGHT (ID_SPRITE_BUSH + 6000)
#define ID_SPRITE_BUSH_MID (ID_SPRITE_BUSH + 7000)

#pragma endregion 

#pragma region CLOUD DECOR
#define ID_SPRITE_CLOUDDECOR 90000

#define ID_SPRITE_CLOUDDECOR_TOP_LEFT (ID_SPRITE_CLOUDDECOR + 1000)
#define ID_SPRITE_CLOUDDECOR_TOP_MID (ID_SPRITE_CLOUDDECOR + 2000)
#define ID_SPRITE_CLOUDDECOR_TOP_RIGHT (ID_SPRITE_CLOUDDECOR + 3000)
#define ID_SPRITE_CLOUDDECOR_BOTTOM_LEFT (ID_SPRITE_CLOUDDECOR + 4000)
#define ID_SPRITE_CLOUDDECOR_BOTTOM_MID (ID_SPRITE_CLOUDDECOR + 5000)
#define ID_SPRITE_CLOUDDECOR_BOTTOM_RIGHT (ID_SPRITE_CLOUDDECOR + 6000)

#pragma endregion

#pragma region MYSTERY BOX
#define ID_SPRITE_MYSTERY_BOX 100000

#define ID_SPRITE_MYSTERY_BOX_ACTIVE (ID_SPRITE_MYSTERY_BOX + 1000)
#define ID_SPRITE_MYSTERY_BOX_UNACTIVE (ID_SPRITE_MYSTERY_BOX + 2000)

#pragma endregion

#pragma region MUSHROOM
#define ID_SPRITE_MUSHROOM 110000

#define ID_SPRITE_MUSHROOM_RED (ID_SPRITE_MUSHROOM + 1000)
#define ID_SPRITE_MUSHROOM_GREEN (ID_SPRITE_MUSHROOM + 2000)

#pragma endregion

#pragma region PIRANHA PLANT
#define ID_SPRITE_PIRANHA_PLANT 120000

#define ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED (ID_SPRITE_PIRANHA_PLANT + 1000)
#define ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED_LEFT_UP (ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED + 100)
#define ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED_LEFT_DOWN (ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED + 200)
#define ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED_RIGHT_UP (ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED + 300)
#define ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED_RIGHT_DOWN (ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_RED + 400)

#define ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN (ID_SPRITE_PIRANHA_PLANT + 2000)
#define ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN_LEFT_UP (ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN + 100)
#define ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN_LEFT_DOWN (ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN + 200)
#define ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN_RIGHT_UP (ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN + 300)
#define ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN_RIGHT_DOWN (ID_SPRITE_PIRANHA_PLANT_BIG_SHOOT_GREEN + 400)

#define ID_SPRITE_PIRANHA_PLANT_BIG_BITE_GREEN (ID_SPRITE_PIRANHA_PLANT + 3000)

#pragma endregion

#define ID_SPRITE_FIREBALL 130000

#define ID_SPRITE_SHADOW_DECOR 140000
#define ID_SPRITE_SHADOW_DECOR_TOP_RIGHT (ID_SPRITE_SHADOW_DECOR + 1000)
#define ID_SPRITE_SHADOW_DECOR_MID_RIGHT (ID_SPRITE_SHADOW_DECOR + 2000)
#define ID_SPRITE_SHADOW_DECOR_BOTTOM_LEFT (ID_SPRITE_SHADOW_DECOR + 3000)
#define ID_SPRITE_SHADOW_DECOR_BOTTOM_MID (ID_SPRITE_SHADOW_DECOR + 4000)
#define ID_SPRITE_SHADOW_DECOR_BOTTOM_RIGHT (ID_SPRITE_SHADOW_DECOR + 5000)

#pragma region KOOPA
#define ID_SPRITE_KOOPA 150000

#define ID_SPRITE_KOOPA_WALK (ID_SPRITE_KOOPA + 1000)
#define ID_SPRITE_KOOPA_SHELL (ID_SPRITE_KOOPA + 2000)
#define ID_SPRITE_KOOPA_DIE (ID_SPRITE_KOOPA + 3000)

#pragma endregion

#define ID_SPRITE_RACOONLEAF 160000
#define ID_SPRITE_RACOONLEAF_LEFT 160010
#define ID_SPRITE_RACOONLEAF_RIGHT 160020

#define ID_SPRITE_FLY_GOOMBA 170000
#define ID_SPRITE_FLY_GOOMBA_WALK (ID_SPRITE_FLY_GOOMBA + 1000)
#define ID_SPRITE_FLY_GOOMBA_DIE (ID_SPRITE_FLY_GOOMBA + 2000)

#define ID_SPRITE_WING 180000
#define ID_SPRITE_WING_CLOSE_LEFT 181000
#define ID_SPRITE_WING_CLOSE_RIGHT 182000
#define ID_SPRITE_WING_OPEN_LEFT 183000
#define ID_SPRITE_WING_OPEN_RIGHT 184000

#pragma region FLY KOOPA
#define ID_SPRITE_FLY_KOOPA 190000
#define ID_SPRITE_FLY_KOOPA_WALK (ID_SPRITE_FLY_KOOPA + 1000)
#define ID_SPRITE_FLY_KOOPA_SHELL (ID_SPRITE_FLY_KOOPA + 2000)
#define ID_SPRITE_FLY_KOOPA_DIE (ID_SPRITE_FLY_KOOPA + 3000)

#pragma endregion