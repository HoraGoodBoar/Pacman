#include "GameObj.h"
#include <ctime>

class Ghost:public GameObj{
public:
	Ghost();
	HTEXTURE texture;
	int direction;
	int previousType;
	float speed;
	bool isMove;
	void Render(float dt,bool t);
	void LoadTexture(HGE * _hge);
	void Setup();
};