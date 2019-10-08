#include <hge.h>
#include <hgesprite.h>
#include <hgefont.h>
#include <string> 
#include <sstream>
#include "MapsController.h"

HGE *hge = 0;
hgeFont *scoreLabel;

HEFFECT  effectGamaOver;
HEFFECT  effectGamaWin;
HSTREAM  musicBg;

MapsController map;

int timeGameOver = DataStorage::TIME_GAMEOVER;
int Record=0;

bool isRunGame=false;

bool FrameFunc()
{
	if (isRunGame &&  map.GhostEatPacman() || map.scoreMap==map.player.score){
		timeGameOver = (int)hge->Timer_GetTime();

	}

	if( timeGameOver -(int)hge->Timer_GetTime() <= 0  && timeGameOver -(int)hge->Timer_GetTime() >= -DataStorage::TIME_SHOW_ENDGAME ){
		if(isRunGame){
			hge->Stream_Free(musicBg);

			isRunGame = false;

			scoreLabel->SetScale(3);

			hge->Gfx_BeginScene();
			hge->Gfx_Clear(0);

			if(map.scoreMap == map.player.score){
				hge->Effect_Play(effectGamaWin);

				scoreLabel->Render(500, 300, HGETEXT_CENTER, TEXT_WIN);
			}
			else{
				hge->Effect_Play(effectGamaOver);

				scoreLabel->Render(500, 300, HGETEXT_CENTER, TEXT_GAMEOVER);
			}

			hge->Gfx_EndScene();
			
			scoreLabel->SetScale(1.5);

			if(map.player.score>Record){
				Record=map.player.score;
			}

			map.walls.clear();
			map.ghost.clear();
			map.player.Setup();
			map.Setup(hge);
		}
		else if(timeGameOver -(int)hge->Timer_GetTime() == -DataStorage::TIME_SHOW_ENDGAME){
			timeGameOver += DataStorage::TIME_GAMEOVER + DataStorage::TIME_SHOW_ENDGAME;
			isRunGame = true;
			musicBg = hge->Stream_Load("Sound/MusicBG.MOD");
			hge->Stream_Play(musicBg, 1);
		}
	}
	else{
		if(!map.player.isMove){
			if ( hge->Input_GetKeyState(HGEK_LEFT) && map.map[map.player.row][map.player.col - 1] !=0){
				map.player.direction = 0;
			}
			else if( hge->Input_GetKeyState(HGEK_RIGHT) && map.map[map.player.row][map.player.col + 1] != 0){
				map.player.direction = 1;
			}
			else if( hge->Input_GetKeyState(HGEK_UP) && map.map[map.player.row - 1][map.player.col] != 0){
				map.player.direction = 3;
			}
			else if( hge->Input_GetKeyState(HGEK_DOWN) && map.map[map.player.row + 1][map.player.col] != 0){
				map.player.direction = 2;
			}
		}

		float dt = hge->Timer_GetDelta();

		hge->Gfx_BeginScene();
		hge->Gfx_Clear(0);

		map.RenderMap(dt);
		
		std::stringstream scoretext;
		std::stringstream timetext;
		std::stringstream recordtext;

		scoretext  << map.player.score;
		timetext   << timeGameOver -(int)hge->Timer_GetTime();
		recordtext << (map.player.score > Record ? map.player.score : Record);

		std::string text = "Score : \n\n"+scoretext.str() + "\n\nTime : \n\n"+timetext.str() +"\n\nRecord : \n\n" + recordtext.str();
		
		scoreLabel->Render(900, 200, HGETEXT_CENTER, text.data());
		
		hge->Gfx_EndScene();
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
 
  if(hge->System_Initiate())
  {
	map.Setup(hge);
	srand(time(NULL));
	scoreLabel= new hgeFont(FONT_TEXT);
	scoreLabel->SetScale(1.5);
	isRunGame = true;


	effectGamaOver = hge->Effect_Load("Sound/GameOver.wav");
	effectGamaWin = hge->Effect_Load("Sound/GameWin.wav");

	musicBg = hge->Stream_Load("Sound/MusicBG.MOD");
	hge->Stream_Play(musicBg,1);

	hge->System_Start();
	
  }
  
  hge->Texture_Free(map.player.open);
  hge->Texture_Free(map.player.close);

  for(int i = 0; i < map.ghost.size(); ++i){
	  hge->Texture_Free(map.ghost[i].texture);
  }

  hge->Effect_Free(effectGamaOver);
  hge->Effect_Free(effectGamaWin);
  hge->Stream_Free(musicBg);

  hge->System_Shutdown();
  hge->Release();

  return 0;
}