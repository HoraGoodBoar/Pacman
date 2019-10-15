#include "GameObj.h"

class PacmanObj:public GameObj{
public:
	PacmanObj();
	HTEXTURE close;
	HTEXTURE open;
	int direction;
	int changeTexture;
	int score;
	float speed;
	bool isMove;
	byte XP;
	void Render(float dt,bool t);
	void LoadTexture(HGE * _hge);
	void Setup();
};