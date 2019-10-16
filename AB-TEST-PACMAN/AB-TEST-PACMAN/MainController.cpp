#include "GameController.h"

HGE *hge = 0;

GameController game;

bool FrameFunc()
{
	if( hge->Input_GetKeyState(HGEK_LBRACKET) && game.isMusic == true ){
		game.isMusic = false;

		hge->Effect_Free(game.effectGamaOver);
		hge->Effect_Free(game.effectGamaWin);
		hge->Effect_Free(game.snd);
		hge->Stream_Free(game.musicBg);

		hge->System_SetState(HGE_USESOUND, game.isMusic);
	}
	else if(  hge->Input_GetKeyState(HGEK_RBRACKET) && game.isMusic == false )
	{
		game.isMusic = true;

		hge->System_SetState(HGE_USESOUND, game.isMusic);

		game.effectGamaOver = hge->Effect_Load("Sound/GameOver.wav");
		game.effectGamaWin = hge->Effect_Load("Sound/GameWin.wav");
		game.musicBg = hge->Stream_Load("Sound/MusicBG.MOD");
		game.snd=hge->Effect_Load("menu.wav");
		hge->Stream_Play(game.musicBg,1);
	}

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
  hge->System_SetState(HGE_INIFILE, "datastorage.txt");
 
  if(hge->System_Initiate()){
	game.Setup(hge);

	hge->System_Start();
  }

  DataStorage::SaveToFile(hge, game.Record ,"Game","Record");  
  hge->System_Shutdown();
  hge->Release();

  return 0;
}

