#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Texture.h"
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "BlocksMap.h"
#include "Wall.h"
#include "checkML.h"
#include "ArkanoidObject.h"
#include "Reward.h"
#include "Reward_TypeE.h"
#include "Reward_TypeL.h"
#include "Reward_TypeR.h"
#include "Reward_TypeS.h"
#include "Font.h"
#include <list>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


class Game
{
private:

	static const int NUM_TEXTURES = 6;
	static const int FRAME_RATE = 7;
	static const int WINDOW_WIDTH = 600;
	static const int WINDOW_HEIGTH = 600;
	static const int MAX_LEVELS = 3;
	static const int MAX_LIFES = 3;
	static const int MAX_REWARDS = 4;
	static const int NUM_MENU = 2;
	int level;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	bool win = false, gameover = false, exit = false;

	

	list<ArkanoidObject*> objectList;
	list<MovingObject*> deathList;

	enum TextureName 
	{
		textureBall, textureBlocks, texturePaddle, textureSide, textureTopSide, textureRewards
	};

	struct ArkanoidObjData
	{
		string filename;
		int row;
		int cols;
	};

	ArkanoidObjData ObjData[NUM_TEXTURES] = 
	{
		{"images/ball.png", 1, 1},
		{"images/bricks.png", 2, 3},
		{"images/paddle.png", 1, 1},
		{"images/side.png", 1, 1},
		{"images/topside.png", 1, 1},
		{"images/rewards.png", 10, 8}
	};

	Texture** ObjectTextures = new Texture*[NUM_TEXTURES];

	Ball* ball;
	Paddle* paddle;
	BlocksMap* map;

	Wall* wallLeft;
	Wall* wallTop;
	Wall* wallRight;


	int startTime = 0, frameTime = 0;

	SDL_Event event;

	const char* filename = "font.ttf";
	Font* textFont;
	Texture* menus[NUM_MENU];
	Texture* loadText;
	Texture* saveText;
	
	void updateRenderedText(Texture*& text, const char* txt, Font*& textFont, SDL_Color textColor, SDL_Rect& rect);
	

public:

	int lifes;

	Game(SDL_Window* window, SDL_Renderer* renderer);

	void runGame(); //gestiona que escena se representa(juego/menu/carga de partida)
	int runMenu(); //bucle del menu
	void loadGameFromFile(); //carga un nivel a partir de un archivo
	void saveGameToFile(); //guarda un nivel en un archivo
	void setInitialState(); //situa a los MovingObject en su posicion original
	void manageLevel(); //maneja si avanzar de nivel o salir del juego al superar todos los niveles
	void playerDeath(); //se encarga de restar una vida y de recargar el nivel
	void killObject(MovingObject* movObj); //añade a un MovingObject determinado de la lista de objetos a una lista de objetos a destruir
	void cleanGame(); //destruye los objetos
	void specificReward(string r, Vector2D& position, int width, int heigth);//crea un Reward especifico
	void randomReward(Block*& b);// crea un objeto de tipo reward
	void newReward(int type, Vector2D& position, int width, int heigth);//crea los rewards
	void loadRewardFromFile(ifstream& levelFile);
	void run(); //bucle principal del juego
	void render(); //renderiza el juego
	void update(); //actualiza la posicion de todos los objetos
	void handleEvents(); //maneja los eventos capturados
	bool collides(SDL_Rect& ballRect, Vector2D& ballVel, Vector2D& collVector); //maneja las colisiones del juego
	void clear();//destruye el juego


	~Game();
};

