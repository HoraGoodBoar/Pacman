#ifndef H_GAMEOBJ
# define H_GAMEOBJ

#include "hge.h"
#include "hgesprite.h"
#include "DataStorage.h"

class GameObj{
public:
	hgeSprite *sprite;
	float x,y;
	int row,col;
	int type;
	GameObj(hgeSprite* _sprite,float _x, float _y);
	GameObj();
	void Render();
};

#endif