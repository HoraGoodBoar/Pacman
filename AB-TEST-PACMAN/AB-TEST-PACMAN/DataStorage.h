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
	static const int PACMAN_SPEED		=	220;
	static const int GHOST_SPEED		=	100;
	static const int SIZE_TEXTURE		=	32;
	static const int MARGIN				=	48;

#define  TEXTURE_PACMAN_OPEN	"Texture/pacman_open.png"
#define  TEXTURE_PACMAN_CLOSE	"Texture/pacman_close.png"
#define  TEXTURE_FOOD			"Texture/food.png"
#define  TEXTURE_WALL			"Texture/wall.png"
#define  TEXT_GAMEOVER			"GAME OVER"
#define  TEXT_WIN				"! YOU WIN GAME !"
#define  TEXT_TITLE				"AB-TEST-PACMAN"
#define  FONT_TEXT				"font1.fnt"
#define  TEXTURE_GHOST_1		"Texture/Ghost_0.png"
#define  TEXTURE_GHOST_2		"Texture/Ghost_1.png"
#define  TEXTURE_GHOST_3		"Texture/Ghost_2.png"
#define  TEXTURE_BGMENU			"Texture/bg.png"
#define  TEXTURE_CURSOR			"Texture/cursor.png"
};