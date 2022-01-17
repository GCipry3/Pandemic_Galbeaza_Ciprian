#include "Game.h"
#include "Enemy.h"
#include "Player.h"
#include "Map.h"
#include "Powers.h"
#include "Windows.h"
#include <stdio.h>

///////////////////////
//Textures
SDL_Texture* startBackground;	//Background-ul de la inceputul jocului
SDL_Texture* startButton;		//Butonul de start
SDL_Texture* buttonsCoviduti[3];//Butoanele cu care selectam daca dorin 30/40/50 coviduti
SDL_Texture* buttonsMaps[3];	//Butoanele cu care selectam daca dorin Harta 1/2/3 

//Avand 3 harti disponibile si varianta de a selecta 3 numere diferite ce reprezinta covidutii
//vom avea teoretic posibilitatea la 9 variante de joc diferinte, dar in realitate ele sunt o infinitate, 
//deoarece covidutii si superputerile sunt generate pe pozitii random pe harta 

//Entities
Map* map; 
Player* player;
Enemy* enemy;
Powers* power;

//Static variables from Game
SDL_Event Game::event;
bool Game::isRunning;
SDL_Renderer* Game::renderer;

//Global variables
Uint32 buttons;	 //indicator pentru apasare click mouse
int mapIndex = 0;//selectare harta 1/2/3
int coviduti;	 //numarul de coviduti

//Music
Mix_Music* gMusic = NULL;
///////////////////////


Game::Game() //constructorul fara parametrii
{
	loseFlag = false;
	win=false;

	window=nullptr;

	startFlag=1;
	secondStartFlag=0;
	mapFlag=0;

	dstStartRect = {0,0,0,0};
}

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) :Game()
{
	this->init(); //vom genera un seed random pentru a folosi cu succes functia rand()

	int flags = 0; //flag pentru fullscreen
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;
		auto window = SDL_CreateWindow(title, xpos, ypos, width, height, flags); //creare Window
		if (window != nullptr)
		{
			std::cout << "Window created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //Creare Renderer
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true; //cat timp ( isRunning == true )jocul va rula
	}
	else
	{
		isRunning = false; //cand acesta va fi pe false jocul se va inchide si se va ajunge la this->clean() in main
	}

	map = new Map(renderer); //initializam harta cu renderer-ul static din Game

	player = new Player("assets/doctor1.png", renderer); //Cream playerul
	player->init(); //initializam player-ul
	player->SetPos(30,30); //setam pozitia acestuia in coltul din stanga sus langa ziduri

	//In toate instructiunile de mai joc vom folosi functia LoadTexture
	//pentru a incarca texturile in butoane, background-uri
	startBackground = TextureManager::LoadTexture("assets/covid_start.png", Game::renderer);
	startButton = TextureManager::LoadTexture("assets/Start_Button.png", Game::renderer);

	buttonsCoviduti[0] = TextureManager::LoadTexture("assets/30.png", Game::renderer);
	buttonsCoviduti[1] = TextureManager::LoadTexture("assets/40.png", Game::renderer);
	buttonsCoviduti[2] = TextureManager::LoadTexture("assets/50.png", Game::renderer);

	buttonsMaps[0] = TextureManager::LoadTexture("assets/map1.png", Game::renderer);
	buttonsMaps[1] = TextureManager::LoadTexture("assets/map2.png", Game::renderer);
	buttonsMaps[2] = TextureManager::LoadTexture("assets/map3.png", Game::renderer);
	
	//Load music
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) { isRunning = false; }
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) { isRunning = false; }

	gMusic = Mix_LoadMUS("assets/music.wav");
	if (Mix_PlayingMusic() == 0){Mix_PlayMusic(gMusic, -1);}
}

Game::~Game()
{
   delete player;
   delete enemy;
}


void Game::update()
{
	//jocul va incepe in momentul in care avem urmatoarele 3 flag-uri pe 0
	//cat timp cel putin unul dintre ele este pe 1 , va insemna ca suntem in unul
	//din ecranele: start , selectare mapa , selectare coviduti

	if (startFlag == 0 && secondStartFlag==0 && mapFlag==0)
	{
		//Prima oara cand intram in joc pornim un counter pentru a vedea daca doctorul omoara covidutii in timp util
		//Cum noi am setat in main jocul pe 60 FPS inseamna ca la loseEnd se va adauga 60 la fiecare secunda
		//Deci cand loseEnd==3600 inseamna ca am ajung la 1 minut (acesta fiind timpul limita pentru omorarea covidutilor)
		static int loseEnd = 0;
		loseEnd++;
		if (loseEnd > 3600) { loseFlag = 1; }

		//Cand se intra in joc vom crea cate un Rect pentru player si enemy pentru a testa coliziunea lor
		SDL_Rect player_box;
		SDL_Rect enemy_box;
		player_box.x = player->transform.position.X();
		player_box.y = player->transform.position.Y() - 2;
		player_box.w = player_box.h = P_W_H; //P_W_H este o constanta ce reprezinta plyer_width_heigth

		//in urmatorul flag verificam daca castigam
		//Doctorul castiga in momentul in care toti covidutii sunt morti
		//Presupunem ca am castigat, iar daca se gaseste vreun covidut cu killedFlag=0 vom pune win pe 0
		//deci inca nu a castigat
		win = 1;
		for (int i = 0; i < coviduti; i++)
		{
			//se creaza Rect pentru enemy pentru verificare coliziunii dintre player si covidut
			enemy_box.x = enemy[i].position.X() * 20;
			enemy_box.y = enemy[i].position.Y() * 20;
			enemy_box.w = enemy_box.h = 35;

			//in caz de coliziune si de atack, covidutul va fi omorat(player->atackFlag == 1 atunci cand se apasa Q sau plus)
			if (Collision::checkCollision(enemy_box, player_box) && player->atackFlag == 1) { enemy[i].killedFlag = 1; }

			enemy[i].update();

			if (enemy[i].killedFlag == 0) { win = 0; }
		}
		/////////////////////WIN
		//mesaj de win in consola in caz de castig
		if (win) { cout << "CONGRATS!!! EVERYONE IS VACCINATED\n\tTHE PANDEMIC WAS DEFEATED\n\t\t>|===---\n"; }
		/////////////////////WIN

		//testam coliziunea dintre player si puteri
		if (Collision::checkCollision(player_box, power->destRect1) && player->atackFlag == 1) { power->destroyedFlag1 = 1; }
		if (Collision::checkCollision(player_box, power->destRect2) && player->atackFlag == 1) { power->destroyedFlag2 = 1; }

		//am explicat testul acesta in Powers.h
		if (power->destroyedFlag1 == 1 && power->usedFlag1 == 0) //putere ce omoara coviduti
		{
			int randomCovidut, aux;
			aux = rand() % 11 + 1; //vom omora intre 1 si 11 coviduti random :)
			power->usedFlag1 = 1;
			//dupa generarea in aux a unui nr random de coviduti intre 1 si 11 vom omora
			//cu adevarat in mod random aux coviduti vii
			for (int i = 0; i < aux; i++)
			{
				bool ok;
				do
				{
					ok = false;
					randomCovidut = rand() % coviduti;
					if (enemy[randomCovidut].killedFlag == 1)
					{
						ok = true;
					}
				} while (ok == true);
				enemy[randomCovidut].killedFlag = 1;
			}
		}

		//am explicat testul acesta in Powers.h
		if (power->destroyedFlag2 == 1 && power->usedFlag2 == 0) //random teleport la un covidut viu
		{
			int randomCovidut;
			power->usedFlag2 = 1;
			bool ok;
			do
			{
				ok = false;
				randomCovidut = rand() % coviduti;
				if (enemy[randomCovidut].killedFlag == 1)
				{
					ok = true;
				}
			} while (ok == true);
			player->transform.position.set(enemy[randomCovidut].position.X() * 20, enemy[randomCovidut].position.Y() * 20);
		}

		//update la superputeri si player
		power->update();
		player->update();
	}
	else
	{
		//In continuare , pana la finalul functiei update vom analiza celelalte cazuri
		//Cazurile in care unul sau mai mutle din flaguri din testul initial sunt puse pe 1
		//Aici facandu-se selectiile Pre-Game
		//Start Button-ul , selectarea hartii si selectarea numarului de coviduti

		CoordComponent mouseCoord=mousePosition(); //pozitia mouseului
		if (secondStartFlag == 0 && mapFlag == 0)
		{
			//verificare apasare cu mouseul pe butonul de start
			if (mouseCoord.X() < 550 && mouseCoord.X() > 350 && mouseCoord.Y() < 500 && mouseCoord.Y() > 300)
			{
				startFlag = 0;
				secondStartFlag = 1;
				SDL_Delay(150);
			}
			mouseCoord.set(0, 0); //pentru a nu influenta urmatorul if
		}
		if (secondStartFlag == 1 && mapFlag == 0)
		{
			//verificare apasare cu mouseul pe buton de select map
			if (mouseCoord.X() < 500 && mouseCoord.X() > 400 && mouseCoord.Y() < 500 && mouseCoord.Y() > 200)
			{
				if (mouseCoord.Y() < 300 && mouseCoord.Y() > 200) { mapIndex = 1; }
				if (mouseCoord.Y() < 400 && mouseCoord.Y() > 300) { mapIndex = 2; }
				if (mouseCoord.Y() < 500 && mouseCoord.Y() > 400) { mapIndex = 3; }
				mapFlag = 1;
				secondStartFlag = 0;
				map->LoadMapFromTemp(mapIndex);
				SDL_Delay(150); 
				mouseCoord = mousePosition(); //pentru a nu influenta urmatorul if
			}
		}
		if (mapFlag == 1)//odata ce harta e selectata , mai trebuie doar sa alegem si numarul de coviduti
		{
			//Selectare numar de coviduti
			//cout << "am intrat in if\n";
			//cout << mouseCoord.X() << " " << mouseCoord.Y() << "\n";
			if (mouseCoord.X() < 500 && mouseCoord.X() > 400 && mouseCoord.Y() < 500 && mouseCoord.Y() > 200)
			{
				if (mouseCoord.Y() < 300 && mouseCoord.Y() > 200) { coviduti = 30;}
				if (mouseCoord.Y() < 400 && mouseCoord.Y() > 300) { coviduti = 40;}
				if (mouseCoord.Y() < 500 && mouseCoord.Y() > 400) { coviduti = 50;}

				enemy = new Enemy[coviduti];
				for (int i = 0; i < coviduti; i++)
				{
					enemy[i].setRenderer(renderer);
					enemy[i].init();
				}
				power = new Powers(renderer);
				power->init();
				power->setRenderer(Game::renderer);
				mapFlag = 0;
				SDL_Delay(150);
			}
		}
	}
}

void Game::draw()
{
	SDL_RenderClear(renderer);

	if(win==0 && loseFlag==0) //jocul ruleaza cat timp player-ul nu a pierdut si nici nu a castigat
	{
		if (startFlag == 0 && secondStartFlag == 0 && mapFlag == 0)
		{
			//render la mapa
			map->DrawMap();
			//render la player
			player->draw();
			//render la superputeri pe harta
			power->draw();
			//render la enemies
			for (int i = 0; i < coviduti; i++) { enemy[i].draw(); }

			static int cnt = 0;
			//render la animatia de atack (aruncare seringi in jurul playerului)
			if (player->backgroundFlag == 1 && cnt < 30) //afisare seringi timp de 0.5 secunde
			{
				cnt++;
				SDL_Rect dstBackground;
				SDL_Texture* background;
				//P_W_H = player_width_heigth
				dstBackground = { (int)player->transform.position.X() - 10,(int)player->transform.position.Y() - 10,P_W_H + 20,P_W_H + 20 };
				background = TextureManager::LoadTexture("assets/s.png", renderer);
				TextureManager::Draw(background, dstBackground, renderer);
			}
			else
			{
				//dupa cele 0.5 secunde se reseteaza conterul si flag-ul de background
				//pentru a putea fi disponibile la urmatoarul atac
				cnt = 0;
				player->backgroundFlag = 0;
			}
		}
		else
		{
			//In continuare avem render la butoane
			//Butoane de :Start, Selectare harta si Selectare nr coviduti
			if (secondStartFlag == 0 && mapFlag == 0)
			{
				//afisare start button
				TextureManager::Draw(startBackground, { 0,0,900,800 }, Game::renderer);
				TextureManager::Draw(startButton, { SCREEN_WIDTH / 2 - 100,SCREEN_HEIGHT / 2 - 100,200,200 }, Game::renderer);
			}
			else
			{
				//afisare butoane selectare mapa
				TextureManager::Draw(startBackground, { 0,0,900,800 }, Game::renderer);
				TextureManager::Draw(buttonsMaps[0], { SCREEN_WIDTH / 2 - 50,SCREEN_HEIGHT / 2 - 200,100,100 }, Game::renderer);
				TextureManager::Draw(buttonsMaps[1], { SCREEN_WIDTH / 2 - 50,SCREEN_HEIGHT / 2 - 100,100,100 }, Game::renderer);
				TextureManager::Draw(buttonsMaps[2], { SCREEN_WIDTH / 2 - 50,SCREEN_HEIGHT / 2 ,100,100 }, Game::renderer);
			}
			if (mapFlag == 1)
			{
				//afisare butoane selectare numar de coviduti
				TextureManager::Draw(startBackground, { 0,0,900,800 }, Game::renderer);
				TextureManager::Draw(buttonsCoviduti[0], { SCREEN_WIDTH / 2 - 50,SCREEN_HEIGHT / 2 - 200,100,100 }, Game::renderer);
				TextureManager::Draw(buttonsCoviduti[1], { SCREEN_WIDTH / 2 - 50,SCREEN_HEIGHT / 2 - 100,100,100 }, Game::renderer);
				TextureManager::Draw(buttonsCoviduti[2], { SCREEN_WIDTH / 2 - 50,SCREEN_HEIGHT / 2 ,100,100 }, Game::renderer);
			}
		}
	}
	else
	{
		//in momentul in care unul din flag-urile initiale este pus pe 1 
		//inseamna ca playerul a castigat sau a pierdut

		if (loseFlag == 0 && win==1) 
		{
			//cu ajutorul lui cnt vom avea un counter pentru secunde
			//cand cnt ajunge la 60 vom avea o secunda
			static int cnt2 = 0;
			cnt2++;

			//Afisare Ecran de WIN
			SDL_Texture* winTex = TextureManager::LoadTexture("assets/win.png", renderer);//Win_background
			TextureManager::Draw(winTex, { 0,0,900,800 }, renderer);

			//60 reprezinta o secunda (deoarece avem 60FPS) deci 30000=60*500 seconds , dupa ce se 
			//termina cele 500 de secunde jocul se inchide (mai exact se va inchide WIN background-ul)
			if (cnt2 == 30000)
			{
				isRunning = false;
			}
		}
		else
		{
			static int cnt2 = 0;
			cnt2++;

			//60 reprezinta o secunda (deoarece avem 60FPS)  deci 30000=60*500 seconds , dupa ce se 
			//termina cele 500 de secunde jocul se inchide (mai exact se va inchide LOSE background-ul)
			if (cnt2 == 30000)
			{
				isRunning = false;
			}
			SDL_Texture* loseTex = TextureManager::LoadTexture("assets/end.png", renderer); //Lose_background
			TextureManager::Draw(loseTex, { 0,0,900,800 }, renderer);

		}
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() 
{
	//dealocare memorie pentru window si renderer
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}

void Game::init()
{
	srand(time(NULL)); //generare seed random
	dstStartRect = { 0,0,0,0 };
}
void Game::handleEvents() {
	//verificam apasare buton rosu X
	switch (Game::event.type)
	{
	case SDL_QUIT: {
		Game::isRunning = false;
		break;
	}
	default:
		break;
	}
}

CoordComponent Game::mousePosition()
{
	//Aceasta functie returneaza positia mouse-ului intr-un mod mai special 
	//In momentul in care click-ul nu este apasat se va transmite un object de timp CoordComponent
	//Cu coordonatele 0,0, deoarece pe mine ma intereseaza doar coordonatele din momentul apasarii click-ului
	int x, y;
	CoordComponent coord;
	CoordComponent NullCoord;
	NullCoord.set(0, 0);
	SDL_PumpEvents();
	buttons = SDL_GetMouseState(&x, &y);
	coord.set(x, y);
	//cout << x << ' ' << y << '\n';
	if ((buttons & SDL_BUTTON_LMASK) != 0) {
		SDL_Log("Mouse Button 1 (left) is pressed.");
		cout << "Coords: " << x << ' ' << y << '\n';
		return coord;
	}
	return NullCoord;
}

