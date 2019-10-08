#include "GameObj.h"

GameObj::GameObj(hgeSprite* _sprite,float _x, float _y){
	this->sprite  = _sprite ;
	this->x = _x;
	this->y = _y;
}
GameObj::GameObj():sprite(0), x(0), y(0), type(0), row(0), col(0){

};
void GameObj::Render(){
	this->sprite->Render( this->x, this->y );
}