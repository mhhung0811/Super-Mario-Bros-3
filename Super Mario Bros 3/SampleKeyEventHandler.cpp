#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "UIMario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	CUIMario* uiMario = (CUIMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetUIPlayer();
	LPPLAYSCENE playScene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	if (mario->GetState() == MARIO_STATE_FLAP_FLOW) return;
	switch (KeyCode)
	{
	case DIK_W:
		if (playScene->GetSceneId() == 20)	
			CGame::GetInstance()->InitiateSwitchScene(40);
		else if (playScene->GetSceneId() == 30)
			CGame::GetInstance()->InitiateSwitchScene(20);
		else if (playScene->GetSceneId() == 40 && uiMario->Click())
			CGame::GetInstance()->InitiateSwitchScene(10);
		break;
	case DIK_UPARROW:
		if (playScene->GetSceneId() == 40 && !uiMario->IsMoving())
			uiMario->GoTop();
		mario->Teleport(1);
		break;
	case DIK_DOWNARROW:
		if (playScene->GetSceneId() == 40 && !uiMario->IsMoving())
			uiMario->GoBottom();
		mario->Teleport(0);
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_LEFTARROW:
		if (playScene->GetSceneId() == 40 && !uiMario->IsMoving())
			uiMario->GoLeft();
		break;
	case DIK_RIGHTARROW:
		if (playScene->GetSceneId() == 40 && !uiMario->IsMoving())
			uiMario->GoRight();
		break;
	case DIK_S:
		if (!mario->IsGrounded() && mario->GetLevel() == MARIO_LEVEL_RACOON)
			mario->Flap();
		else
			mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A:
		if (mario->GetLevel() == MARIO_LEVEL_RACOON)
			mario->SetState(MARIO_STATE_ATTACK);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetState() == MARIO_STATE_FLAP_FLOW) return;
	switch (KeyCode)
	{
	case DIK_S:
		if (mario->GetState() == MARIO_STATE_FLAP_FLOW)
			mario->SetState(MARIO_STATE_FLAP_FLOW_RELEASE);
		else 
			mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		if (mario->IsHoldingShell())
		{
			mario->SetState(MARIO_STATE_KICK);
		}
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->GetState() == MARIO_STATE_FLAP_FLOW) return;
	if (game->IsKeyDown(DIK_S))
	{		
		mario->SetState(MARIO_STATE_HOLD_JUMP);
	}

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}