#include <string> 
static class DataStorage{
public:
	static const int ROW_MAP			=	21;
	static const int COLUMN_MAP			=	23;
	static const int TIME_GAMEOVER		=	100;
	static const int TIME_SHOW_ENDGAME	=	5;
	static const int WINDOW_WIDTH		=	1024;
	static const int WINDOW_HEIGHT		=	768;
	static const int WINDOW_FPS			=	100;
	static const int PACMAN_SPEED		=	150;
	static const int AUTOPACMAN_SPEED	=	150;
	static const int GHOST_SPEED		=	100;
	static const int SIZE_TEXTURE		=	32;
	static const int MARGIN				=	48;
	static const int RADIUS_AUTOPACMAN	=	3;
	static const int RADIUS_TOUCH		=	32;

#define  TEXTURE_PACMAN_OPEN		"Texture/pacman_open.png"
#define  TEXTURE_PACMAN_CLOSE		"Texture/pacman_close.png"
#define  TEXTURE_AUTOPACMAN_OPEN	"Texture/autopacman_open.png"
#define  TEXTURE_AUTOPACMAN_CLOSE	"Texture/autopacman_close.png"
#define  TEXTURE_FOOD				"Texture/food.png"
#define  TEXTURE_WALL				"Texture/wall_1.png"
#define  TEXT_GAMEOVER				"GAME OVER"
#define  TEXT_WIN					"! YOU WIN GAME !"
#define  TEXT_TITLE					"AB-TEST-PACMAN"
#define  FONT_TEXT					"font1.fnt"
#define  TEXTURE_GHOST_1			"Texture/Ghost_0.png"
#define  TEXTURE_GHOST_2			"Texture/Ghost_1.png"
#define  TEXTURE_GHOST_3			"Texture/Ghost_2.png"
#define  TEXTURE_BGMENU				"Texture/bg.png"
#define  TEXTURE_BGGAME				"Texture/bggame.png"
#define  TEXTURE_CURSOR				"Texture/cursor.png"
#define  TEXTURE_LIFE				"Texture/life.png"
#define  FILE_PATH					"datastorage.txt"

	static int LoadFile(HGE * _hge, char * _section, char * _name){
		int answer = _hge->Ini_GetInt(_section,_name, 0);
		return answer;
	}

	static void SaveToFile(HGE * _hge, int _value, char * _section, char * _name){
		_hge->Ini_SetInt(_section,_name,_value);
	}
};