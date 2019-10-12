#include <hge.h>
#include <hgesprite.h>
#include "hgefont.h"
#include <string>
#include <sstream>
#include "hgegui.h"
#include "menuitem.h"
#include "MapsController.h"
#include <math.h>


void PlayGame();
bool ShowMenu();

HGE *hge = 0;

hgeFont *scoreLabel;

HEFFECT  effectGamaOver;
HEFFECT  effectGamaWin;
HSTREAM  musicBg;

HEFFECT				snd;
HTEXTURE			tex;
hgeQuad				quad;

hgeGUI				*gui;
hgeFont				*fnt;
hgeSprite			*spr;

MapsController map;

int timeGameOver = DataStorage::TIME_GAMEOVER;
int Record=0;

bool isRunGame	= false;
bool isPlayGame = false;

bool FrameFunc()
{
	if(isPlayGame){
		PlayGame();
	}
	else {
		return ShowMenu();
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

	quad.tex=hge->Texture_Load("bg.png");
	tex=hge->Texture_Load("cursor.png");
	snd=hge->Effect_Load("menu.wav");

	if(!quad.tex || !tex || !snd)
	{
		hge->System_Shutdown();
		return 0;
	}

	// Animation
	quad.blend=BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;

	for(int i=0;i<4;i++)
	{
		quad.v[i].z=0.5f;
		quad.v[i].col=0xFFFFFFFF;
	}

	quad.v[0].x=0; quad.v[0].y=0; 
	quad.v[1].x=DataStorage::WINDOW_WIDTH; quad.v[1].y=0; 
	quad.v[2].x=DataStorage::WINDOW_WIDTH; quad.v[2].y=DataStorage::WINDOW_HEIGHT; 
	quad.v[3].x=0; quad.v[3].y=DataStorage::WINDOW_HEIGHT; 
	// Animation
		
	fnt=new hgeFont("font1.fnt");
	fnt->SetScale(1.5);
	spr=new hgeSprite(tex,0,0,32,32);

	gui=new hgeGUI();

	gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,DataStorage::WINDOW_WIDTH/2,280,0.0f,"Play"));
	gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,DataStorage::WINDOW_WIDTH/2,360,0.2f,"Exit"));

	gui->SetCursor(spr);

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

void PlayGame(){
if ((isRunGame &&  map.GhostEatPacman()) || map.scoreMap==map.player.score){
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
			map.scoreMap=0;
			map.Setup(hge);
		}
		else if(timeGameOver -(int)hge->Timer_GetTime() == -DataStorage::TIME_SHOW_ENDGAME){
			timeGameOver += DataStorage::TIME_GAMEOVER + DataStorage::TIME_SHOW_ENDGAME;
			isRunGame = true;
			musicBg = hge->Stream_Load("Sound/MusicBG.MOD");
			hge->Stream_Play(musicBg, 1);
			isPlayGame=false;
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
}

bool ShowMenu(){
	float dt = hge->Timer_GetDelta();
	int id;
	static int lastid=0;

	id = gui->Update(dt);
	if(id == -1)
	{
		switch(lastid)
		{
			case 1:
				timeGameOver += (int)hge->Timer_GetTime();
				isPlayGame=true;
				break;
			case 2:  return true;
		}
	}
	else if(id) { 
		lastid = id;
		gui->Leave(); 
	}

	// Animation
	static float t=0.0f;
	float tx,ty;
	t+=dt;
	tx=50*cosf(t/60);
	ty=50*sinf(t/60);

	quad.v[0].tx=tx;         quad.v[0].ty=ty;
	quad.v[1].tx=tx+DataStorage::WINDOW_WIDTH/200; quad.v[1].ty=ty;
	quad.v[2].tx=tx+DataStorage::WINDOW_WIDTH/200; quad.v[2].ty=ty+DataStorage::WINDOW_HEIGHT/200;
	quad.v[3].tx=tx;         quad.v[3].ty=ty+DataStorage::WINDOW_HEIGHT/200;
	// Animation

	hge->Gfx_BeginScene();
	hge->Gfx_RenderQuad(&quad);
	gui->Render();
	hge->Gfx_EndScene();

	return false;
}