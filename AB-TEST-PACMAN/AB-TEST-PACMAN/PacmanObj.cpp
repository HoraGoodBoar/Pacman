#include "PacmanObj.h"

void PacmanObj::Render(float dt,bool t){
	if(t){
		switch(direction){
			case 0:{
				this->sprite->SetFlip(true,false);
				this->x-=speed*dt;
				if(this->x < (float)(col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE/2)){
					this->x = (float)(col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE/2);
					isMove=false;
				}
				this->sprite->RenderEx( this->x, this->y,0);
			}break;
			case 1:{
				this->x+=speed*dt;
				if(this->x > (float)(col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE/2)){
					this->x = (float)(col*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE/2);
					isMove=false;
				}
				this->sprite->SetFlip(false,false);
				this->sprite->RenderEx( this->x, this->y,0);
			}break;
			case 2:{
				this->y+=speed*dt;
				if(this->y > (float)(row*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE/2)){
					this->y = (float)(row*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE/2);
					isMove=false;
				}
				this->sprite->SetFlip(false,false);
				this->sprite->RenderEx( this->x, this->y,240);
			}break;
			case 3:{
				this->y-=speed*dt;
				if(this->y < (float)(row*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE/2)){
					this->y = (float)(row*DataStorage::SIZE_TEXTURE+DataStorage::MARGIN+DataStorage::SIZE_TEXTURE/2);
					isMove=false;
				}
				this->sprite->SetFlip(true,false);
				this->sprite->RenderEx( this->x, this->y,90);
			}break;
			default:this->sprite->Render( this->x, this->y);
		}
	}
	else{
		this->sprite->Render( this->x, this->y);
	}

	if(changeTexture<= DataStorage::WINDOW_FPS/2){
		sprite->SetTexture(close);
	}
	else if(changeTexture <=DataStorage::WINDOW_FPS){
		sprite->SetTexture(open);
	}
	else{
		changeTexture=0;
	}
	++changeTexture;
}

PacmanObj::PacmanObj(): direction(-1),speed(DataStorage::PACMAN_SPEED),isMove(false),changeTexture(0),score(0){
	GameObj::GameObj();
	GameObj::type = 2;
	changeTexture=0;
}
void PacmanObj::LoadTexture(HGE * _hge){
	open	= _hge->Texture_Load(TEXTURE_PACMAN_OPEN);
	close	= _hge->Texture_Load(TEXTURE_PACMAN_CLOSE);
}

void PacmanObj::Setup(){
	isMove=false;
	score=0;
	direction=-1;
	speed=DataStorage::PACMAN_SPEED;
}