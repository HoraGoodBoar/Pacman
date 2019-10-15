#include "GameController.h"

HGE *hge = 0;

GameController game;

bool FrameFunc()
{
	if(game.isPlayGame){
		game.PlayGame();
	}
	else {
		return game.ShowMenu();
	}
	
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  hge = hgeCreate(HGE_VERSION);
  hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
  hge->System_SetState(HGE_WINDOWED, true);
  hge->System_SetState(HGE_USESOUND, true);
  hge->System_SetState(HGE_WINDOWED, true);
  hge->System_SetState(HGE_HIDEMOUSE, false);
  hge->System_SetState(HGE_TITLE, TEXT_TITLE);
  hge->System_SetState(HGE_FPS, DataStorage::WINDOW_FPS);
  hge->System_SetState(HGE_SCREENWIDTH, DataStorage::WINDOW_WIDTH);
  hge->System_SetState(HGE_SCREENHEIGHT, DataStorage::WINDOW_HEIGHT);
 
  if(hge->System_Initiate()){
	game.Setup(hge);

	hge->System_Start();
  }

  
  hge->System_Shutdown();
  hge->Release();

  return 0;
}

