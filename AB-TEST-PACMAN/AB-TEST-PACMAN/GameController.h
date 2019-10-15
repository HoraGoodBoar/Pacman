#include <hge.h>
#include <hgesprite.h>
#include "hgefont.h"
#include <string>
#include <sstream>
#include "hgegui.h"
#include "menuitem.h"
#include "MapsController.h"
#include <math.h>


class GameController{
public:

	GameController();
	~GameController();

	void Setup(HGE *_hge);
	void PlayGame();
	bool ShowMenu();

	
	HGE *hge;

	hgeFont *scoreLabel;
	hgeFont	*fnt;

	HEFFECT  effectGamaOver;
	HEFFECT  effectGamaWin;
	HEFFECT	snd;

	HSTREAM  musicBg;

	hgeQuad	quad;

	hgeGUI	*gui;

	MapsController map;

	int timeGameOver;
	int Record;

	bool isRunGame;
	bool isPlayGame;

};