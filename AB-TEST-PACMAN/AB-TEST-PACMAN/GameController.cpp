#include "GameController.h"

GameController::GameController(){
	hge = nullptr;
	gui = nullptr;
	fnt = nullptr;

	isRunGame	= false;
	isPlayGame	= false;
	isMusic		= true;

	Record=0;

	timeGameOver = DataStorage::TIME_GAMEOVER;
}

GameController::~GameController(){
	hge->Effect_Free(effectGamaOver);
	hge->Effect_Free(effectGamaWin);
	hge->Effect_Free(snd);
	hge->Stream_Free(musicBg);
}

void GameController::Setup(HGE *_hge){
	this->hge = _hge;

	map.Setup(hge);
	srand(time(NULL));
	scoreLabel= new hgeFont(FONT_TEXT);
	scoreLabel->SetColor(0xFFFFE060);
	scoreLabel->SetScale(1);
	isRunGame = true;


	effectGamaOver = hge->Effect_Load("Sound/GameOver.wav");
	effectGamaWin = hge->Effect_Load("Sound/GameWin.wav");

	musicBg = hge->Stream_Load("Sound/MusicBG.MOD");
	hge->Stream_Play(musicBg,1);

	quad.tex=hge->Texture_Load(TEXTURE_BGMENU);
	snd = hge->Effect_Load("menu.wav");
	
	bgGame = new hgeSprite(_hge->Texture_Load(TEXTURE_BGGAME), 0, 0, DataStorage::WINDOW_WIDTH, DataStorage::WINDOW_HEIGHT);

	// Animation
	quad.blend=BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;

	for(int i=0;i<4;i++)
	{
		quad.v[i].z=0.5f;
		quad.v[i].col=0xFFFFFFFF;
	}

	quad.v[0].x=0;							quad.v[0].y=0; 
	quad.v[1].x=DataStorage::WINDOW_WIDTH;	quad.v[1].y=0; 
	quad.v[2].x=DataStorage::WINDOW_WIDTH;	quad.v[2].y=DataStorage::WINDOW_HEIGHT; 
	quad.v[3].x=0;							quad.v[3].y=DataStorage::WINDOW_HEIGHT; 
	// Animation
		
	fnt=new hgeFont("font1.fnt");
	fnt->SetScale(1.5);

	gui=new hgeGUI();

	gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,DataStorage::WINDOW_WIDTH*0.5,280,0.0f,"Play"));
	gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,DataStorage::WINDOW_WIDTH*0.5,360,0.2f,"Exit"));

	gui->SetFocus(1);

	Record = DataStorage::LoadFile(_hge,"Game","Record");
}

void GameController::PlayGame(){
	if ((isRunGame &&  map.GhostEatPacman()) || map.scoreMap == (map.player.score + map.autoplayer.score) ){
		timeGameOver = (int)hge->Timer_GetTime();

	}

	if( timeGameOver -(int)hge->Timer_GetTime() <= 0  && timeGameOver -(int)hge->Timer_GetTime() >= -DataStorage::TIME_SHOW_ENDGAME ){
		if(isRunGame){
			hge->Stream_Free(musicBg);

			isRunGame = false;

			scoreLabel->SetScale(3);

			hge->Gfx_BeginScene();
			hge->Gfx_Clear(0);
			
			if(map.scoreMap == (map.player.score + map.autoplayer.score)){
				hge->Effect_Play(effectGamaWin);
				bgGame->Render(0,0);
				scoreLabel->Render(500, 300, HGETEXT_CENTER, TEXT_WIN);
			}
			else{
				hge->Effect_Play(effectGamaOver);
				bgGame->Render(0,0);
				scoreLabel->Render(500, 300, HGETEXT_CENTER, TEXT_GAMEOVER);
			}

			hge->Gfx_EndScene();
			
			scoreLabel->SetScale(1);

			if(map.player.score>Record){
				Record = map.player.score;
			}

			map.walls.clear();
			map.ghost.clear();
			map.player.Setup();
			map.autoplayer.Setup();
			map.scoreMap=0;
			map.Setup(hge);


		}
		else if(timeGameOver -(int)hge->Timer_GetTime() == -DataStorage::TIME_SHOW_ENDGAME){
			timeGameOver += DataStorage::TIME_GAMEOVER + DataStorage::TIME_SHOW_ENDGAME;
			isRunGame = true;
			musicBg = hge->Stream_Load("Sound/MusicBG.MOD");
			hge->Stream_Play(musicBg, 1);
			isPlayGame=false;
			gui->SetFocus(1);
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

		bgGame->Render(0,0);
		map.RenderMap(dt);

		if(map.player.score>Record){
			Record = map.player.score;
		}
		
		std::stringstream scoretext;
		std::stringstream timetext;
		std::stringstream recordtext;
		std::stringstream infoautopacman;
		std::stringstream xppacman;
		std::stringstream xpautopacman;

		scoretext			<< map.player.score;
		xppacman			<< (int)map.player.XP;
		timetext			<< timeGameOver -(int)hge->Timer_GetTime();
		recordtext			<< Record ;
		infoautopacman		<< map.autoplayer.score;
		xpautopacman		<< (int)map.autoplayer.XP;

		std::string text =  "Pacman score : \n\n"+scoretext.str() + 
							"\n\nPacman XP : \n\n"+xppacman.str() + 
							"\n\nTime : \n\n"+timetext.str() +
							"\n\nRecord : \n\n" + recordtext.str() + 
							"\n\n AutoPacman score : \n\n" + infoautopacman.str() +
							"\n\n AutoPacman XP : \n\n" + xpautopacman.str();
		
		scoreLabel->Render(900, 100, HGETEXT_CENTER, text.data());
		
		hge->Gfx_EndScene();
	}
}

bool GameController::ShowMenu(){
	float dt = hge->Timer_GetDelta();
	int id;
	static int lastid=0;

	id = gui->Update(dt);
	if(id == -1)
	{
		switch(lastid)
		{
			case 1:
				timeGameOver = (int)hge->Timer_GetTime() + DataStorage::TIME_GAMEOVER;
				gui->Enter();
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