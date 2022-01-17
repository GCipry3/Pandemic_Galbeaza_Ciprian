#include "Player.h"
SDL_Rect Player_Box;

int Player::Left_Right_flag;

Player::Player(const char* path, SDL_Renderer* renderer):  renderer(renderer)
{
    setTex(path);
}

void Player::setTex(const char* path)
{
    texture = TextureManager::LoadTexture(path, renderer);
}


void Player::init()
{
	backgroundFlag = 0;
	flip = SDL_FLIP_NONE;
    destRect.x = destRect.y = 0;
    destRect.w = destRect.h = P_W_H;
    Left_Right_flag = 1;
    transform.init();
}

void Player::Keyboard_Control()
{
	//KeyBind-urile
	//Playerul se deplaseaza de pe
	//Sageti sau
	//W=up , S=down , A=left , D=right
	//atacul se afla pe tasta Q sau SDLK_KP_PLUS (plusul de pe NumPad)
	SDL_PollEvent(&Game::event);
	if (event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_UP:
			transform.velocity.setY(-1);
			break;

		case SDLK_DOWN:
			transform.velocity.setY(1);
			break;

		case SDLK_LEFT:
			flip = SDL_FLIP_HORIZONTAL;
			transform.velocity.setX(-1);
			Left_Right_flag = 0;
			break;

		case SDLK_RIGHT:
			flip = SDL_FLIP_NONE;
			transform.velocity.setX(1);
			Left_Right_flag = 1;
			break;
		case SDLK_KP_PLUS:
			atackFlag = 1;
			backgroundFlag = 1;
			break;
		case SDLK_w:
			transform.velocity.setY(-1);
			break;

		case SDLK_s:
			transform.velocity.setY(1);
			break;

		case SDLK_a:
			flip = SDL_FLIP_HORIZONTAL;
			transform.velocity.setX(-1);
			Left_Right_flag = 0;
			break;

		case SDLK_d:
			flip = SDL_FLIP_NONE;
			transform.velocity.setX(1);
			Left_Right_flag = 1;
			break;
		case SDLK_q:
			atackFlag = 1;
			backgroundFlag = 1;
			break;
		case SDLK_ESCAPE:
			Game::isRunning = false;
			break;
		}
	}
	else
	{
		if (event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				transform.velocity.setY(0);
				break;

			case SDLK_DOWN:
				transform.velocity.setY(0);
				break;

			case SDLK_LEFT:
				transform.velocity.setX(0);
				break;

			case SDLK_RIGHT:
				transform.velocity.setX(0);
				break;

			case SDLK_KP_PLUS:
				atackFlag = 0;
				//backgroundFlag = 0;
				break;
			case SDLK_w:
				transform.velocity.setY(0);
				break;

			case SDLK_s:
				transform.velocity.setY(0);
				break;

			case SDLK_a:
				transform.velocity.setX(0);
				break;

			case SDLK_d:
				transform.velocity.setX(0);
				break;

			case SDLK_q:
				atackFlag = 0;
				//backgroundFlag = 0;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			}
		}
	}
}

void Player::update()
{
	Keyboard_Control();
	
	//update la pozitie in functie de coordonatele actuale si velocity 
	//dupa formula pos=pos+speed*velocity
	CoordComponent tempCoord = PositionComponent::PositionFromVelocity(transform.position, transform.velocity);

	SDL_Rect player_box;
	player_box.w = player_box.h = P_W_H-10;
	player_box.x = (int)tempCoord.X()+5;
	player_box.y = (int)tempCoord.Y()+5;

	//testam daca pozitia noua are coliziune cu Wall-urile
	bool ok = Collision::checkAllWallCollision(player_box);

	//incarcam in player->transform.position noua pozitie in cazul in care nu exista coliziune
	if (!ok) { transform.position.set(tempCoord.X(), tempCoord.Y()); }

	destRect.x = (int)transform.position.X();
	destRect.y = (int)transform.position.Y();
}


void Player::SetPos(float x, float y)
{
	transform.position.set(x, y);
}


void Player::draw()
{
	TextureManager::DrawF(texture, destRect, renderer, flip);
}
