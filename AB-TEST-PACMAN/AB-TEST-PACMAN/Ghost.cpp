#include "Ghost.h"

void Ghost::Render(float dt,bool t){
	if(t){
		switch(direction){
			case 0:{
				this->x -= speed * dt;
				if(this->x < (float)(col * DataStorage::SIZE_TEXTURE + DataStorage::MARGIN+DataStorage::SIZE_TEXTURE *0.5)){
					this->x = (float)(col * DataStorage::SIZE_TEXTURE + DataStorage::MARGIN+DataStorage::SIZE_TEXTURE *0.5);
					isMove=false;
				}
			}break;
			case 1:{
				this->x += speed * dt;
				if(this->x > (float)(col * DataStorage::SIZE_TEXTURE + DataStorage::MARGIN + DataStorage::SIZE_TEXTURE *0.5)){
					this->x = (float)(col * DataStorage::SIZE_TEXTURE + DataStorage::MARGIN + DataStorage::SIZE_TEXTURE *0.5);
					isMove = false;
				}
			}break;
			case 2:{
				this->y += speed * dt;
				if(this->y > (float)(row * DataStorage::SIZE_TEXTURE + DataStorage::MARGIN + DataStorage::SIZE_TEXTURE *0.5)){
					this->y = (float)(row * DataStorage::SIZE_TEXTURE + DataStorage::MARGIN + DataStorage::SIZE_TEXTURE *0.5);
					isMove = false;
				}
			}break;
			case 3:{
				this->y -= speed * dt;
				if(this->y < (float)(row * DataStorage::SIZE_TEXTURE + DataStorage::MARGIN + DataStorage::SIZE_TEXTURE *0.5)){
					this->y = (float)(row * DataStorage::SIZE_TEXTURE + DataStorage::MARGIN + DataStorage::SIZE_TEXTURE *0.5);
					isMove = false;
				}
			}break;
		}
	}
	this->sprite->Render( this->x, this->y);
}

Ghost::Ghost(): speed(DataStorage::GHOST_SPEED), previousType(1), isMove(false){
	GameObj::GameObj();
	GameObj::type = 3;
	direction = rand()%4;
}

void Ghost::LoadTexture(HGE * _hge){
	switch(rand()%3){
		case 0 : texture	= _hge->Texture_Load(TEXTURE_GHOST_1); break;
		case 1 : texture	= _hge->Texture_Load(TEXTURE_GHOST_2); break;
		case 2 : texture	= _hge->Texture_Load(TEXTURE_GHOST_3); break;
	}
	sprite->SetTexture(texture);
}

void Ghost::Setup(){
	isMove = false;
	direction = rand()%3;
}