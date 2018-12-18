#include "Game.h"



void Game::updateRenderedText(Texture*& text, const char * txt, Font*& textFont, SDL_Color textColor, SDL_Rect& rect)
{
	text->loadFromText(_renderer, txt, *textFont, textColor);
	rect.w = 20 * strlen(txt);
	rect.x = WINDOW_WIDTH / 2 - rect.w / 2;
	loadText->render(rect, SDL_FLIP_NONE);
	SDL_RenderPresent(_renderer);
}

Game::Game(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGTH, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL.";

	_renderer = renderer;
	_window = window;

	TTF_Init();

	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		ObjectTextures[i] = new Texture(_renderer, ObjData[i].filename, ObjData[i].row, ObjData[i].cols);
	}

	level = 0; //primer nivel
	lifes = MAX_LIFES;

	wallLeft = new Wall( Vector2D(0, 0), -1, WINDOW_HEIGTH,ObjectTextures[textureSide] );
	objectList.push_front(wallLeft);
	wallTop = new Wall( Vector2D((double)(ObjectTextures[textureSide]->getW()), 0) , WINDOW_WIDTH, -1, ObjectTextures[textureTopSide] );
	objectList.push_front(wallTop);
	wallRight = new Wall( Vector2D((double)(WINDOW_WIDTH - ObjectTextures[textureSide]->getW()), 0), -1, WINDOW_HEIGTH,ObjectTextures[textureSide] );
	objectList.push_front(wallRight);
	ball = new Ball(Vector2D{ WINDOW_WIDTH / 2, WINDOW_HEIGTH / 5 }, ObjectTextures[textureBall]->getW(), ObjectTextures[textureBall]->getH(), ObjectTextures[textureBall], this);
	objectList.push_front(ball);
	map = new BlocksMap(level, WINDOW_WIDTH, WINDOW_HEIGTH, ObjectTextures[textureBlocks], Vector2D{ (double) wallLeft->getW(), (double)wallTop->getH() });
	objectList.push_front(map);
	paddle = new Paddle(Vector2D{ WINDOW_WIDTH / 2, WINDOW_HEIGTH / 5 * 4 }, ObjectTextures[texturePaddle]->getW(), ObjectTextures[texturePaddle]->getH(), ObjectTextures[texturePaddle], WINDOW_WIDTH, wallLeft->getW());
	objectList.push_front(paddle);

}

void Game::runGame()
{
	int state = runMenu();
	if (state == 0)
	{
		run();
	}
	else if(state == 1)
	{
		loadGameFromFile();
		run();
	}
}


int Game::runMenu()
{
	int time;
	int x, y;
	textFont = new Font(filename, 20);
	const char* labels[NUM_MENU] = {"Start","Load Game"};
	
	for (int i = 0; i < NUM_MENU * 2; i++)
	{
		menus[i] = new Texture(_renderer);
	}

	bool onButton[NUM_MENU] = {false,false};
	SDL_Color color = { 255,255,255 };

	for (int i = 0; i < NUM_MENU; i++) // posicion par colores normales || posicion par colores onButton
	{
		menus[i]->loadFromText(_renderer, labels[i], *textFont, color);
	}

	SDL_Rect pos[NUM_MENU];

	for (int i = 0; i < NUM_MENU; i++)
	{
		pos[i].w = 20 * strlen(labels[i]);
		pos[i].h = 50;
	}

	pos[0].x = WINDOW_WIDTH / 2 - pos[0].w / 2;
	pos[0].y = WINDOW_HEIGTH / 3;
	

	pos[1].x = WINDOW_WIDTH / 2 - pos[1].w / 2;
	pos[1].y = WINDOW_HEIGTH / 3 + 50;

	SDL_Event event;
	while (true)
	{
		SDL_RenderClear(_renderer);

		startTime = SDL_GetTicks();

		for (int i = 0; i < NUM_MENU; i++)
		{
			menus[i]->render(pos[i], SDL_FLIP_NONE);
		}
		
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return -1;
				break;

			case SDL_MOUSEBUTTONDOWN:
				x = event.motion.x;
				y = event.motion.y;

				for (int i = 0; i < NUM_MENU; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
						y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						return i;
					}
				}

				break;
			}
		}

		SDL_RenderPresent(_renderer);

		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime);
	}
	
}

void Game::loadGameFromFile()
{
	SDL_RenderClear(_renderer);
	bool isRunning = true;
	SDL_Event ev;
	string text;
	loadText = new Texture(_renderer);
	SDL_Color color = {255,255,255};

	SDL_Rect position;
	position.w = position.h = 0;
	position.y = WINDOW_HEIGTH / 3;
	position.h = 20;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev))
		{
			SDL_RenderClear(_renderer);

			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.key.keysym.sym == SDLK_ESCAPE)
			{
				string confirmText = "Loading file : " + text;

				updateRenderedText(loadText, confirmText.c_str(), textFont, color, position);

				std::transform(text.begin(), text.end(), text.begin(), ::tolower);

				ifstream file2load;
				file2load.open(text);
				if (!file2load.is_open()) throw "Error loading this file" + text;
				else
				{
					for (auto const& i : objectList)
					{
						i->loadFromFile(file2load);
					}

					while (!file2load.eof())
					{
						loadRewardFromFile(file2load);
					}

					file2load.close();
					isRunning = false;
				}

			}
			else if (ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN)
			{
				if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
				{
					text = text.substr(0, text.length() - 1);
				}
				else if(ev.type == SDL_TEXTINPUT)
				{
					text += ev.text.text;
				}

				if (text.length() > 0)
				{
					updateRenderedText(loadText, text.c_str(), textFont, color, position);
				}

				SDL_RenderPresent(_renderer);
				

				cout << text << endl;
			}
		}
	}

}



void Game::saveGameToFile()
{
	SDL_RenderClear(_renderer);
	bool isRunning = true;
	SDL_Event ev;
	string text;
	saveText = new Texture(_renderer);
	SDL_Color color = { 255,255,255 };

	SDL_Rect position;
	position.w = position.h = 0;
	position.y = WINDOW_HEIGTH / 3;
	position.h = 20;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev))
		{
			SDL_RenderClear(_renderer);

			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_RenderClear(_renderer);
				string confirmText = "Saving file with name : " + text;

				updateRenderedText(saveText, confirmText.c_str(), textFont, color, position);

				std::transform(text.begin(), text.end(), text.begin(), ::tolower);

				ofstream output(text + ".txt");
				if (!output.is_open()) throw "Error loading this file" + text;
				else
				{
					for (auto const& i : objectList)
					{
						i->saveToFile(output);
					}

					output.close();
					isRunning = false;
					exit = true;
				}

			}
			else if (ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN)
			{
				if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
				{
					text = text.substr(0, text.length() - 1);
				}
				else if (ev.type == SDL_TEXTINPUT)
				{
					text += ev.text.text;
				}

				if (text.length() > 0)
				{
					updateRenderedText(loadText, text.c_str(), textFont, color, position);
				}

				SDL_RenderPresent(_renderer);


				cout << text << endl;
			}
		}
	}



}

void Game::setInitialState()
{
	ball->setIni();
	paddle->setIni();
}

void Game::manageLevel()
{
	level++;

	if (level > MAX_LEVELS - 1) win = true;
	else
	{
		setInitialState();
		map->loadLevel(level);
	}
}

void Game::playerDeath()
{
	lifes--;

	if (lifes <= 0) gameover = true;
	else
	{
		setInitialState();
	}
}

void Game::specificReward(string r, Vector2D& position, int width, int heigth)
{
	char c = r[0];
	int i = -1;

	switch (c)
	{
	case 'E':
		i = 0;
		break;
	case 'L':
		i = 1;
		break;
	case 'R':
		i = 2;
		break;
	case 'S':
		i = 3;
		break;
	}

	newReward(i, position, width, heigth);
}

void Game::randomReward(Block*& b)
{
	newReward(rand() % MAX_REWARDS, Vector2D{(double)b->getX(), (double)b->getY()},b->getW(), b->getH());
}

void Game::newReward(int type, Vector2D& position, int width, int heigth)
{
	switch (type)
	{
	case 0: //type E
		objectList.push_back(new Reward_TypeE(position, width, heigth, ObjectTextures[textureRewards], this, paddle, WINDOW_HEIGTH));
		break;
	case 1: //type L
		objectList.push_back(new Reward_TypeL(position, width, heigth, ObjectTextures[textureRewards], this, paddle, WINDOW_HEIGTH));
		break;
	case 2: //type R
		objectList.push_back(new Reward_TypeR(position, width, heigth, ObjectTextures[textureRewards], this, paddle, WINDOW_HEIGTH));
		break;
	case 3: //type S
		objectList.push_back(new Reward_TypeS(position, width, heigth, ObjectTextures[textureRewards], this, paddle, WINDOW_HEIGTH));
		break;
	}
}

void Game::loadRewardFromFile(ifstream& levelFile)
{
	string r;
	double x, y;
	int width, heigth;
	levelFile >> r;
	levelFile >> x;
	levelFile >> y;
	levelFile >> width;
	levelFile >> heigth;

	specificReward(r, Vector2D{x,y},width,heigth);
}

void Game::killObject(MovingObject* movObj)
{
	//objectList.remove(movObj);
	deathList.push_front(movObj);
}

void Game::cleanGame()
{
	for (auto  &i:deathList)
	{
		objectList.remove(i);
		delete i;
		i = nullptr;
	}

	deathList.clear();
}

void Game::run()
{
	while (!exit && !win && !gameover) {
		startTime = SDL_GetTicks();
		handleEvents();
		update();
		render();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime);
	}
}

void Game::render()
{
	SDL_RenderClear(_renderer);

	for (auto const& i : objectList) 
	{
		i->render();
	}
	
	SDL_RenderPresent(_renderer);
}

void Game::update()
{
	for (auto const& i : objectList)
	{
		i->update();
	}


	cleanGame();

	if (ball->getY() >= WINDOW_HEIGTH)
		playerDeath();

}

void Game::handleEvents()
{
	while (SDL_PollEvent(&event) && !exit)
	{

		paddle->handleEvent(event);

		if (event.type == SDL_QUIT) exit = true;
		else if(event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_s)
			{
				saveGameToFile();
			}
		}
	}
}

bool Game::collides(SDL_Rect& ballRect, Vector2D& ballVel, Vector2D& collVector)
{
	//Es llamado desde el método Update de Ball y llama al método Collides de Map pasandole los parametros por referencia
	if (ballRect.x >= 0 && ballRect.x <= WINDOW_WIDTH && ballRect.y >= 0 && ballRect.y < WINDOW_HEIGTH)
	{
		//caso en el que la pelota rebota con los bloques
		Block* block = map->handleCollisions(ballRect, ballVel, collVector);
		if (block != nullptr)
		{
			map->destroyBlock(block);
			if (map->totalBlocks() == 0)
			{
				manageLevel();
			}

			if ((rand() % 100) < 50)
			{
				randomReward(block);
			}

			return true;
		}

		SDL_Rect* ballRectPunt = &ballRect;

		if (paddle->handleCollisions(ballRectPunt, ballVel, collVector, WINDOW_WIDTH))
		{
			return true;
		}

		//caso en el que la pelota rebota con las paredes

		for (auto const& i : objectList)
		{
			if (dynamic_cast<Wall*>(i) != nullptr)
			{
				Wall* w = dynamic_cast<Wall*>(i);

				if (w->handleCollision(ballRectPunt, ballVel, collVector, WINDOW_WIDTH))
				{
					return true;
				}
			}
		}
		return false;

	}

	return false;
}

void Game::clear()
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		delete ObjectTextures[i];
		ObjectTextures[i] = nullptr;
	}

	delete ObjectTextures;
	ObjectTextures = nullptr;

	delete textFont;
	textFont = nullptr;

	delete loadText;
	loadText = nullptr;

	for (int i = 0; i < NUM_MENU; i++)
	{
		delete menus[i];
		menus[i] = nullptr;
	}


	for (auto const& i : objectList)
	{
		delete i;
	}

	delete _window;
	_window = nullptr;

	delete _renderer;
	_renderer = nullptr;

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();


	
}

Game::~Game()
{
	clear();
}
