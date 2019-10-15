#include "Ghost.h"
#include "PacmanObj.h"
#include "AutoPacmanObj.h"
#include <vector>

class MapsController{
	const static int COLUMN = DataStorage::COLUMN_MAP;
	const static int ROW	= DataStorage::ROW_MAP;
public:

	void SetupMap();
	void SetupWalls(HGE * _hge);

	byte **map;

	int scoreMap;

	std::vector <GameObj> walls;
	std::vector <Ghost> ghost;

	PacmanObj player;
	AutoPacmanObj autoplayer;

	MapsController();
	~MapsController();

	void Setup(HGE * _hge);
	void RenderMap(float dt);
	bool PossibleMove(int obj_col,int obj_row,int direction,int type,int currentPosGhost=0);
	bool TypeRadius(int _col,int _row, int _direction, int _radius, int _typeFind);
	bool GhostEatPacman();
};