#include "MapsController.h"

MapsController::MapsController():scoreMap(0){
}

MapsController::~MapsController(){
	for(int i = 0; i < ROW; ++i)
	{
		delete[] map[i];
	}
	delete map;
}

void MapsController::RenderMap(float dt){
	for(int i = 0; i < walls.size(); ++i){
		walls[i].Render();
	}

	player.Render( dt, PossibleMove( player.col, player.row, player.direction,player.type ) );
	autoplayer.Render( dt, PossibleMove( autoplayer.col, autoplayer.row, autoplayer.direction, autoplayer.type )  );

	for(int i = 0; i < ghost.size(); ++i){
		ghost[i].Render(dt, PossibleMove( ghost[i].col, ghost[i].row, ghost[i].direction,ghost[i].type, i));
	}
}

void MapsController::SetupMap(){
	this->map = new byte * [ ROW ];
	for(int i = 0; i < ROW; ++i){
		map[i]=new byte[COLUMN]();
	}
	// 0 wall
	// 1 food
	// 2 pacman
	// 3 ghost
	// 4 zero
	// 5 autopacman
	// 6 zeronotmap
	// 7 life
	byte _map[ROW][COLUMN]={ 
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 0}, // 1
		{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // 2
		{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // 3
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 0}, // 4
		{ 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0}, // 5
		{ 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, // 6
		{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // 7
		{ 6, 6, 6, 6, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 6, 6, 6, 6}, // 8
		{ 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0}, // 9 
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1}, // 10  
		{ 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0}, // 9
		{ 6, 6, 6, 6, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 6, 6, 6, 6}, // 8
		{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // 7
		{ 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, // 6
		{ 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0}, // 5
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // 4
		{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // 3
		{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // 2
		{ 0, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 3, 1, 1, 5, 1, 3, 0}, // 1
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // 0

	} ;
	
	for(int i = 0; i < ROW; ++i){
		for(int j = 0; j < COLUMN; ++j){
			this->map[i][j] = _map[i][j];
		}
	}
}

void MapsController::SetupWalls(HGE * _hge){
	for(int i = 0; i < ROW; ++i){
		for(int j = 0; j < COLUMN; ++j){
			switch(map[i][j]){
				case 0 : {
					walls.push_back(GameObj());
					walls[walls.size()-1].sprite=new hgeSprite( _hge->Texture_Load(TEXTURE_WALL), 0, 0, DataStorage::SIZE_TEXTURE, DataStorage::SIZE_TEXTURE );
					walls[walls.size()-1].x= (float)(j*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN);
					walls[walls.size()-1].y= (float)(i*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN);
					walls[walls.size()-1].row = i;
					walls[walls.size()-1].col = j;
					walls[walls.size()-1].type=0;
				}break;
				case 1:{
					walls.push_back(GameObj());
					walls[walls.size()-1].sprite=new hgeSprite( _hge->Texture_Load(TEXTURE_FOOD), 0, 0, DataStorage::SIZE_TEXTURE, DataStorage::SIZE_TEXTURE );
					walls[walls.size()-1].x= (float)(j*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN);
					walls[walls.size()-1].y= (float)(i*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN);
					walls[walls.size()-1].row = i;
					walls[walls.size()-1].col = j;
					walls[walls.size()-1].type=1;
					++scoreMap;
				}break;
				case 2:{
					player.sprite = new hgeSprite( _hge->Texture_Load(TEXTURE_PACMAN_CLOSE), 0, 0, DataStorage::SIZE_TEXTURE, DataStorage::SIZE_TEXTURE );
					player.LoadTexture(_hge);
					player.row = i;
					player.col = j;
					player.x = (float)(player.col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
					player.y = (float)(player.row*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
					
					player.sprite->SetHotSpot(DataStorage::SIZE_TEXTURE*0.5,DataStorage::SIZE_TEXTURE*0.5);
					player.type = 2;
					player.direction=2;
				}break;
				case 3:{
					walls.push_back(GameObj());
					walls[walls.size()-1].sprite=new hgeSprite( _hge->Texture_Load(TEXTURE_FOOD), 0, 0, DataStorage::SIZE_TEXTURE, DataStorage::SIZE_TEXTURE );
					walls[walls.size()-1].x= (float)(j*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN);
					walls[walls.size()-1].y= (float)(i*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN);
					walls[walls.size()-1].row = i;
					walls[walls.size()-1].col = j;
					walls[walls.size()-1].type=1;
					++scoreMap;

					ghost.push_back(Ghost());
					ghost[ghost.size()-1].sprite = new hgeSprite( _hge->Texture_Load(TEXTURE_GHOST_2), 0, 0, DataStorage::SIZE_TEXTURE, DataStorage::SIZE_TEXTURE );
					ghost[ghost.size()-1].LoadTexture(_hge);
					ghost[ghost.size()-1].row = i;
					ghost[ghost.size()-1].col = j;
					ghost[ghost.size()-1].x = (float)(ghost[ghost.size()-1].col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
					ghost[ghost.size()-1].y = (float)(ghost[ghost.size()-1].row*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
					
					ghost[ghost.size()-1].sprite->SetHotSpot(DataStorage::SIZE_TEXTURE*0.5,DataStorage::SIZE_TEXTURE*0.5);
					ghost[ghost.size()-1].type = 3;
					ghost[ghost.size()-1].speed=DataStorage::GHOST_SPEED;
				}break;
				case 5:{
					autoplayer.sprite = new hgeSprite( _hge->Texture_Load(TEXTURE_AUTOPACMAN_CLOSE), 0, 0, DataStorage::SIZE_TEXTURE, DataStorage::SIZE_TEXTURE );
					autoplayer.LoadTexture(_hge);
					autoplayer.row = i;
					autoplayer.col = j;
					autoplayer.x = (float)(autoplayer.col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
					autoplayer.y = (float)(autoplayer.row*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
					
					autoplayer.sprite->SetHotSpot(DataStorage::SIZE_TEXTURE*0.5,DataStorage::SIZE_TEXTURE*0.5);
					autoplayer.type = 5;   
				}break;
				case 7:{
					walls.push_back(GameObj());
					walls[walls.size()-1].sprite=new hgeSprite( _hge->Texture_Load(TEXTURE_LIFE), 0, 0, DataStorage::SIZE_TEXTURE, DataStorage::SIZE_TEXTURE );
					walls[walls.size()-1].x= (float)(j*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN);
					walls[walls.size()-1].y= (float)(i*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN);
					walls[walls.size()-1].row = i;
					walls[walls.size()-1].col = j;
					walls[walls.size()-1].type=7;	   
				}break;
			}
		}
	}
}

void MapsController::Setup(HGE * _hge){
	
	SetupMap();
	SetupWalls(_hge);
}

bool MapsController::PossibleMove(int obj_col,int obj_row,int direction,int type,int currentPosGhost ){
	bool answer=false;

	if(type==2){
		if(!player.isMove){
			switch(direction){
				case 0:{
					// якщо проходить в телепорт
					if(obj_col==0 && obj_row==10){
						player.col=COLUMN-1;
						player.x=(float)(player.col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);

						for(int i=0;i<walls.size(); ++i){
							if(walls[i].row==obj_row && walls[i].col==player.col && walls[i].type==1){
								walls.erase(walls.begin()+i);
								++player.score;
								break;
							}
							else if(walls[i].row==obj_row && walls[i].col==player.col && walls[i].type==7){
								walls.erase(walls.begin()+i);
								++player.XP;
								break;
							}
						}
					}
					//
					if(obj_col - 1 >= 0 && map[obj_row][obj_col-1]!=0)
					{
						answer=true;
						player.isMove=true;
						--player.col;
						map[obj_row][obj_col-1] = 2;
						map[obj_row][obj_col]   = 4;

						for(int i=0;i<walls.size(); ++i){
							if(walls[i].row==obj_row && walls[i].col==obj_col-1 && walls[i].type==1 ){
								walls.erase(walls.begin()+i);
								++player.score;
								break;
							}
							else if(walls[i].row==obj_row && walls[i].col==obj_col-1 && walls[i].type==7 ){
								walls.erase(walls.begin()+i);
								++player.XP;
								break;
							}
						}
						
					}
				}break;
				case 1:{
					// якщо проходить в телепорт
					if(obj_col==COLUMN-1 && obj_row==10){
						player.col=0;
						player.x=(float)(player.col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
						for(int i=0;i<walls.size(); ++i){
							if(walls[i].row==obj_row && walls[i].col==0 && walls[i].type==1){
								walls.erase(walls.begin()+i);
								++player.score;
								break;
							}
							else if(walls[i].row==obj_row && walls[i].col==0 && walls[i].type==7){
								walls.erase(walls.begin()+i);
								++player.XP;
								break;
							}
						}
					}
					//
					if(obj_col+1<COLUMN && map[obj_row][obj_col+1]!=0)
					{
						answer=true;
						player.isMove=true;
						++player.col;
						map[obj_row][obj_col+1]=2;
						map[obj_row][obj_col]=4;

						for(int i=0;i<walls.size(); ++i){
							if(walls[i].row==obj_row && walls[i].col==obj_col+1 && walls[i].type==1){
								walls.erase(walls.begin()+i);
								++player.score;
								break;
							}
							else if(walls[i].row==obj_row && walls[i].col==obj_col+1 && walls[i].type==7){
								walls.erase(walls.begin()+i);
								++player.XP;
								break;
							}
						}
					}
				}break;
				case 2:{
					if(obj_row+1 < ROW && map[obj_row+1][obj_col]!=0)
					{
						answer=true;
						player.isMove=true;
						++player.row;
						map[obj_row+1][obj_col]=2;
						map[obj_row][obj_col]=4;

						for(int i=0;i<walls.size(); ++i){
							if(walls[i].row==obj_row+1 && walls[i].col==obj_col && walls[i].type==1){
								walls.erase(walls.begin()+i);
								++player.score;
								break;
							}
							else if(walls[i].row==obj_row+1 && walls[i].col==obj_col && walls[i].type==7){
								walls.erase(walls.begin()+i);
								++player.XP;
								break;
							}
						}
					}
				}break;
				case 3:{
					if(obj_row-1>=0 && map[obj_row-1][obj_col]!=0)
					{
						answer=true;
						player.isMove=true;
						--player.row;
						map[obj_row-1][obj_col]=2;
						map[obj_row][obj_col]=4;
		
						for(int i=0;i<walls.size(); ++i){
							if(walls[i].row==obj_row-1 && walls[i].col==obj_col && walls[i].type==1){
								walls.erase(walls.begin()+i);
								++player.score;
								break;
							}
							else if(walls[i].row==obj_row-1 && walls[i].col==obj_col && walls[i].type==7){
								walls.erase(walls.begin()+i);
								++player.XP;
								break;
							}
						}
					}
				}break;
			}
		}
		else{
			answer=true;
		}
		
	}

	else if(type==3){
		if(!ghost[currentPosGhost].isMove){
			// якщо проходить в телепорт
			if( direction == 0 && obj_col==0 && obj_row==10){
				ghost[currentPosGhost].isMove=true;
				ghost[currentPosGhost].col=COLUMN-1;
				ghost[currentPosGhost].x=(float)(ghost[currentPosGhost].col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
				map[obj_row][obj_col] = ghost[currentPosGhost].previousType;
				ghost[currentPosGhost].previousType = map[obj_row][COLUMN-1];
				map[obj_row][COLUMN-1] = ghost[currentPosGhost].type;
			}
			else if( direction == 1 && obj_col==COLUMN-1 && obj_row==10){
				ghost[currentPosGhost].isMove=true;
				ghost[currentPosGhost].col=0;
				ghost[currentPosGhost].x=(float)(ghost[currentPosGhost].col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
				map[obj_row][obj_col] = ghost[currentPosGhost].previousType;
				ghost[currentPosGhost].previousType = map[obj_row][0];
				map[obj_row][0] = ghost[currentPosGhost].type;
				
			}
			//
			else{
				bool top,down,right,left;
				top = down = right = left = false;

				left	= (obj_col - 1 >= 0 && map[obj_row][obj_col - 1] != 0);
				right	= (obj_col + 1 < COLUMN && map[obj_row][obj_col + 1] !=0);
				down	= (obj_row + 1 < ROW && map[obj_row + 1][obj_col] != 0);
				top		= (obj_row - 1 >= 0 && map[obj_row - 1][obj_col] != 0);
				
				switch(direction){
					case 0 : case 1 : {
						if(top && down){
							direction = 2 + rand()%2;
						}
						else if(top){
							direction=3;
						}
						else if(down){
							direction=2;
						}
						else{
							if(direction == 0 && left){
								direction =0;
							}
							else if(direction == 1 && right){
								direction =1;
							}
							else if(left){
								direction = 0;
							}
							else if(right){
								direction = 1;
							}
						}
					}break;
					case 2 : case 3 :{
						if(left && right){
							direction= rand()%2;
						}
						else if(left){
							direction=0;
						}
						else if(right){
							direction=1;
						} 
						else{
							if(direction == 3 && top){
								direction =3;
							}
							else if(direction == 2 && down){
								direction =2;
							}
							else if(top){
								direction = 3;
							}
							else if(down){
								direction = 2;
							}
						}
					}break;
				}

				ghost[currentPosGhost].direction=direction;

				switch(direction){
					case 0:{
						answer=true;
						ghost[currentPosGhost].isMove=true;
						--ghost[currentPosGhost].col;

						map[obj_row][obj_col] = ghost[currentPosGhost].previousType;
						ghost[currentPosGhost].previousType = map[obj_row][obj_col-1];
						map[obj_row][obj_col-1] = ghost[currentPosGhost].type;
					}break;
					case 1:{
						answer=true;
						ghost[currentPosGhost].isMove=true;
						++ghost[currentPosGhost].col;

						map[obj_row][obj_col] = ghost[currentPosGhost].previousType;
						ghost[currentPosGhost].previousType = map[obj_row][obj_col+1];
						map[obj_row][obj_col+1] = ghost[currentPosGhost].type;
					}break;
					case 2:{
						answer=true;
						ghost[currentPosGhost].isMove=true;
						++ghost[currentPosGhost].row;

						map[obj_row][obj_col] = ghost[currentPosGhost].previousType;
						ghost[currentPosGhost].previousType = map[obj_row+1][obj_col];
						map[obj_row+1][obj_col] = ghost[currentPosGhost].type;
					}break;
					case 3:{
						answer=true;
						ghost[currentPosGhost].isMove=true;
						--ghost[currentPosGhost].row;

						map[obj_row][obj_col] = ghost[currentPosGhost].previousType;
						ghost[currentPosGhost].previousType = map[obj_row-1][obj_col];
						map[obj_row-1][obj_col] = ghost[currentPosGhost].type;
					}break;
				}
			}
		}
		else{
			answer=true;
		}
	}
	else if(type==5){
		if(!autoplayer.isMove){
			// якщо проходить в телепорт
			if( direction == 0 && obj_col==0 && obj_row==10){
				autoplayer.isMove=true;
				autoplayer.col=COLUMN-1;
				autoplayer.x=(float)(autoplayer.col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);

				map[obj_row][obj_col] = 4;
				map[obj_row][COLUMN-1] = autoplayer.type;

				for(int i=0;i<walls.size(); ++i){
					if(walls[i].row==obj_row && walls[i].col==player.col && walls[i].type==1){
						walls.erase(walls.begin()+i);
						++autoplayer.score;
						break;
					}
					else if(walls[i].row==obj_row && walls[i].col==player.col && walls[i].type==7){
						walls.erase(walls.begin()+i);
						++autoplayer.XP;
						break;
					}
				}
			}
			else if( direction == 1 && obj_col==COLUMN-1 && obj_row==10){
				autoplayer.isMove=true;
				autoplayer.col=0;
				autoplayer.x=(float)(autoplayer.col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);

				map[obj_row][obj_col] = 4;
				map[obj_row][0] = autoplayer.type;

				for(int i=0;i<walls.size(); ++i){
					if(walls[i].row==obj_row && walls[i].col==0 && walls[i].type==1){
						walls.erase(walls.begin()+i);
						++autoplayer.score;
						break;
					}
					else if(walls[i].row==obj_row && walls[i].col==0 && walls[i].type==7){
						walls.erase(walls.begin()+i);
						++autoplayer.XP;
						break;
					}
				}
			}
			//
			else{
				bool top,down,right,left;
				top = down = right = left = false;

				left	= (obj_col - 1 >= 0 && map[obj_row][obj_col - 1] != 0		&& TypeRadius(autoplayer.col,autoplayer.row, 0, DataStorage::RADIUS_AUTOPACMAN, 3) );
				right	= (obj_col + 1 < COLUMN && map[obj_row][obj_col + 1] !=0	&& TypeRadius(autoplayer.col,autoplayer.row, 1, DataStorage::RADIUS_AUTOPACMAN, 3) );
				down	= (obj_row + 1 < ROW && map[obj_row + 1][obj_col] != 0		&& TypeRadius(autoplayer.col,autoplayer.row, 2, DataStorage::RADIUS_AUTOPACMAN, 3) );
				top		= (obj_row - 1 >= 0 && map[obj_row - 1][obj_col] != 0		&& TypeRadius(autoplayer.col,autoplayer.row, 3, DataStorage::RADIUS_AUTOPACMAN, 3) );
				
				switch(direction){
					case 0 : case 1 : {
						if(top && down){
							direction = 2 + rand()%2;
						}
						else if(top){
							direction=3;
						}
						else if(down){
							direction=2;
						}
						else{
							if(direction == 0 && left){
								direction =0;
							}
							else if(direction == 1 && right){
								direction =1;
							}
							else if(left){
								direction = 0;
							}
							else if(right){
								direction = 1;
							}
						}
					}break;
					case 2 : case 3 :{
						if(left && right){
							direction= rand()%2;
						}
						else if(left){
							direction=0;
						}
						else if(right){
							direction=1;
						} 
						else{
							if(direction == 3 && top){
								direction =3;
							}
							else if(direction == 2 && down){
								direction =2;
							}
							else if(top){
								direction = 3;
							}
							else if(down){
								direction = 2;
							}
						}
					}break;
				}

				autoplayer.direction=direction;

				switch(direction){
					case 0:{
						answer=true;
						autoplayer.isMove=true;
						--autoplayer.col;

						map[obj_row][obj_col] = 4;
						map[obj_row][obj_col-1] = autoplayer.type;

						for(int i=0;i<walls.size(); ++i){
							if(walls[i].row==obj_row && walls[i].col==obj_col-1 && walls[i].type==1 ){
								walls.erase(walls.begin()+i);
								++autoplayer.score;
								break;
							}
							else if(walls[i].row==obj_row && walls[i].col==obj_col-1 && walls[i].type==7){
								walls.erase(walls.begin()+i);
								++autoplayer.XP;
								break;
							}
						}
					}break;
					case 1:{
						answer=true;
						autoplayer.isMove=true;
						++autoplayer.col;

						map[obj_row][obj_col] = 4;
						map[obj_row][obj_col+1] = autoplayer.type;
						for(int i=0;i<walls.size(); ++i){
							if(walls[i].row==obj_row && walls[i].col==obj_col+1 && walls[i].type==1 ){
								walls.erase(walls.begin()+i);
								++autoplayer.score;
								break;
							}
							else if(walls[i].row==obj_row && walls[i].col==obj_col+1 && walls[i].type==7){
								walls.erase(walls.begin()+i);
								++autoplayer.XP;
								break;
							}
						}
					}break;
					case 2:{
						answer=true;
						autoplayer.isMove=true;
						++autoplayer.row;

						map[obj_row][obj_col] = 4;
						map[obj_row+1][obj_col] = autoplayer.type;

						for(int i=0;i<walls.size(); ++i){
							if(walls[i].row==obj_row+1 && walls[i].col==obj_col && walls[i].type==1){
								walls.erase(walls.begin()+i);
								++autoplayer.score;
								break;
							}
							else if(walls[i].row==obj_row+1 && walls[i].col==obj_col && walls[i].type==7){
								walls.erase(walls.begin()+i);
								++autoplayer.XP;
								break;
							}
						}
					}break;
					case 3:{
						answer=true;
						autoplayer.isMove=true;
						--autoplayer.row;

						map[obj_row][obj_col] = 4;
						map[obj_row-1][obj_col] = autoplayer.type;

						for(int i=0;i<walls.size(); ++i){
							if(walls[i].row==obj_row-1 && walls[i].col==obj_col && walls[i].type==1){
								walls.erase(walls.begin()+i);
								++autoplayer.score;
								break;
							}
							else if(walls[i].row==obj_row-1 && walls[i].col==obj_col && walls[i].type==7){
								walls.erase(walls.begin()+i);
								++autoplayer.XP;
								break;
							}
						}
					}break;
				}
			}
		}
		else{
			answer=true;
		}
	}

	
	return answer;
}

bool MapsController::GhostEatPacman(){
	bool answer = false;
	
	if(player.col == autoplayer.col && player.row == autoplayer.row){
		if(player.direction == 0 || player.direction == 1){
			if(player.x + 32 >= autoplayer.x && player.x - 32 <= autoplayer.x){
				int _x=-1,_y=-1;
				while(true){
					_x = rand()% DataStorage::COLUMN_MAP;
					_y = rand()% DataStorage::ROW_MAP;
					if(map[_y][_x]!=0 && map[_y][_x]!=3 && map[_y][_x]!=6 ){
						if(map[_y][_x]==1)
						{
							for(int i=0;i<walls.size(); ++i){
								if(walls[i].row==_y && walls[i].col==_x && walls[i].type==1){
									walls.erase(walls.begin()+i);
									++player.score;
									break;
								}
							}
						}
						map[_y][_x]=player.type;
						player.col=_x;
						player.row=_y;
						player.x = (float)(_x*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
						player.y = (float)(_y*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
						break;
					}
				}

				_x=-1,_y=-1;
				while(true){
					_x = rand()% DataStorage::COLUMN_MAP;
					_y = rand()% DataStorage::ROW_MAP;
					if(map[_y][_x]!=0 && map[_y][_x]!=3 && map[_y][_x]!=6){
						if(map[_y][_x]==1)
						{
							for(int i=0;i<walls.size(); ++i){
								if(walls[i].row==_y && walls[i].col==_x && walls[i].type==1){
									walls.erase(walls.begin()+i);
									++autoplayer.score;
									break;
								}
							}
						}
						map[_y][_x]=autoplayer.type;
						autoplayer.col=_x;
						autoplayer.row=_y;
						autoplayer.x = (float)(_x*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
						autoplayer.y = (float)(_y*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
						break;
					}
				}

				player.isMove=false;
				autoplayer.isMove=false;
			}
		}
		else if(player.direction == 2 || player.direction == 3){
			if( player.y + 32 >= autoplayer.y && player.y - 32 <= autoplayer.y ){
				int _x=-1,_y=-1;
				while(true){
					_x = rand()% DataStorage::COLUMN_MAP;
					_y = rand()% DataStorage::ROW_MAP;
					if(map[_y][_x]!=0 && map[_y][_x]!=3 && map[_y][_x]!=6){
						if(map[_y][_x]==1)
						{
							for(int i=0;i<walls.size(); ++i){
								if(walls[i].row==_y && walls[i].col==_x && walls[i].type==1){
									walls.erase(walls.begin()+i);
									++player.score;
									break;
								}
							}
						}
						map[_y][_x]=player.type;
						player.col=_x;
						player.row=_y;
						player.x = (float)(_x*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
						player.y = (float)(_y*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
						break;
					}
				}

				_x=-1,_y=-1;
				while(true){
					_x = rand()% DataStorage::COLUMN_MAP;
					_y = rand()% DataStorage::ROW_MAP;
					if(map[_y][_x]!=0 && map[_y][_x]!=3 && map[_y][_x]!=6){
						if(map[_y][_x]==1)
						{
							for(int i=0;i<walls.size(); ++i){
								if(walls[i].row==_y && walls[i].col==_x && walls[i].type==1){
									walls.erase(walls.begin()+i);
									++autoplayer.score;
									break;
								}
							}
						}
						map[_y][_x]=autoplayer.type;
						autoplayer.col=_x;
						autoplayer.row=_y;
						autoplayer.x = (float)(_x*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
						autoplayer.y = (float)(_y*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE*0.5);
						break;
					}
				}

				player.isMove=false;
				autoplayer.isMove=false;
			}
		}
	}

	for(int i = 0; i < ghost.size(); ++i){
		if(player.col == ghost[i].col && player.row == ghost[i].row){
			if(player.direction == 0 || player.direction == 1){
				if(player.x + 32 >= ghost[i].x && player.x - 32 <= ghost[i].x){
					if(player.XP>1)
					{
						--player.XP;
						ghost.erase(ghost.begin()+i);
						break;
					}
					answer = true;
					break;
				}
			}
			else if(player.direction == 2 || player.direction == 3){
				if( player.y + 32 >= ghost[i].y && player.y - 32 <= ghost[i].y ){
					if(player.XP>1)
					{
						--player.XP;
						ghost.erase(ghost.begin()+i);
						break;
					}
					answer = true;
					break;
				}
			}
		}
	}

	for(int i = 0; i < ghost.size(); ++i){
		if(autoplayer.col == ghost[i].col && autoplayer.row == ghost[i].row){
			if(autoplayer.direction == 0 || autoplayer.direction == 1){
				if(autoplayer.x + 32 >= ghost[i].x && autoplayer.x - 32 <= ghost[i].x){
					if(autoplayer.XP>1)
					{
						--autoplayer.XP;
						ghost.erase(ghost.begin()+i);
						break;
					}
					answer = true;
					break;
				}
			}
			else if(autoplayer.direction == 2 || autoplayer.direction == 3){
				if( autoplayer.y + 32 >= ghost[i].y && autoplayer.y - 32 <= ghost[i].y ){
					if(autoplayer.XP>1)
					{
						--autoplayer.XP;
						ghost.erase(ghost.begin()+i);
						break;
					}
					answer = true;
					break;
				}
			}
		}
	}

	return answer;
}

bool MapsController::TypeRadius(int _col,int _row, int _direction, int _radius, int _typeFind){
	bool answer = true;
	switch(_direction){
		case 0:{   
			for(int i = 0; i <= _radius; ++i){
				if(_col - i <= 0){
					break;
				}
				if(map[_row][_col - i]==_typeFind){
					answer = false;
					break;
				}
			}
		}break;
		case 1:{
			for(int i = 0; i <= _radius; ++i){
				if(_col + i >= DataStorage::COLUMN_MAP){
					break;
				}
				if(map[_row][_col + i]==_typeFind){
					answer = false;
					break;
				}
			}
		}break;
		case 2:{
			for(int i = 0; i <= _radius; ++i){
				if(_row + i >= DataStorage::ROW_MAP){
					break;
				}
				if(map[_row + i][_col]==_typeFind){
					answer = false;
					break;
				}
			}
		}break;
		case 3:{
			 for(int i = 0; i <= _radius; ++i){
				if(_row - i <= 0){
					break;
				}
				if(map[_row - i][_col]==_typeFind){
					answer = false;
					break;
				}
			}
		}break;
	}

	return answer;
}