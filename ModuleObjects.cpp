#include "ModuleObjects.h"
#include "ModuleSceneGame.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneCongrats.h"
#include "ModuleSound.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL_timer.h"
#include <string>


ModuleObjects::ModuleObjects()
{
}


ModuleObjects::~ModuleObjects()
{
}



bool ModuleObjects::Init() {
	
	//Tree left
	tree1.PushBack({ 219, 0, 31, 32 });
	tree1.PushBack({ 251, 0, 30, 32 });
	tree1.speed = 0.0f;

	//Tree right
	tree2.PushBack({ 178,46,31,32 });
	tree2.PushBack({ 209,46,30,32 });
	tree2.speed = 0.0f;

	//Bridge animamtion
	bridge.PushBack({691, 79, 64, 32});

	//Rock animation
	rock.PushBack({ 825,83,28,11 });

	//Rock after bridge 
	rock2.PushBack({358, 0, 31, 17});

	//box

	box.PushBack({535, 0, 20, 16});
	box.PushBack({536, 23, 20, 16});
	box.speed = 0.04f;


	//box side of the canon

	box2.PushBack({471, 0, 21, 17});
	box2.PushBack({ 494 ,0, 21, 16 });
	box2.speed = 0.04f;

	//box individual
	box3.PushBack({ 424, 0, 11, 10 });
	box3.PushBack({ 439 ,0, 11, 10});
	box3.speed = 0.04f;



	helix1.PushBack({ 785, 419, 96, 33 });
	helix1.PushBack({ 875, 459, 96, 33 });
	helix1.PushBack({ 800, 553, 79, 21 });
	helix1.PushBack({ 857, 503, 42, 45 });
	helix1.PushBack({ 865, 588, 26, 27 });
	helix1.PushBack({ 877, 393, 79, 21 });
	
	helix1.loop = true;
	helix1.speed = 0.25f;
	
	helicopter1.PushBack({ 710,440,64,82 });
	helicopter1.PushBack({ 713,662,56,68 });
	helicopter1.PushBack({ 799,914,48,55 });
	helicopter1.loop = false;

	helicopter2.PushBack({ 799,914,48,55 });
	helicopter2.PushBack({ 713,662,56,68 });
	helicopter2.PushBack({ 710,440,64,82 });
	helicopter2.speed = 0.5f;
	helicopter2.loop = false;



	return true;


}

bool ModuleObjects::Start() {
	bool ret = true;
	sprite_graphics = App->textures->Load("Images/sprites.png");
	level_dimensions = App->scene_game->getLevelDimensions(); //This is the lower limit of the level (y)

	helipoint.x = (SCREEN_WIDTH / 2) - 15;
	helipoint.y = 1908;
	reduction = 1;
	helicopter = helicopter1;

	if (App->scene_game->getLevel() == 1)
	{
		// Collisions of the rock at the upper left corner at the beggining of the game
		App->collision->AddCollider({ 20, 8 + level_dimensions.y, 10, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 30, 11 + level_dimensions.y, 2, 19 }, COLLIDER_WALL);
		App->collision->AddCollider({ 32, 16 + level_dimensions.y, 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 37, 20 + level_dimensions.y, 5, 10 }, COLLIDER_WALL);
		App->collision->AddCollider({ 42, 20 + level_dimensions.y , 4, 8 }, COLLIDER_WALL);

		// Palm trees collisions
		App->collision->AddCollider({ 218, 152 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 170, -24 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 144, -24 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 160, -40 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 42, -217 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 154, -233 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 32, -233 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 154, -618 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 32, -618 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 97, -681 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 98, 24 + level_dimensions.y , 4, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 97, -106 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 97, -298 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 160, -361 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 225, -425 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 34, 152 + level_dimensions.y , 4, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 161, 217 + level_dimensions.y , 4, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 170, 233 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 145, 233 + level_dimensions.y , 4, 9 }, COLLIDER_WALL);

		//Collisions of the rock at the right at the beggining of the game
		App->collision->AddCollider({ 196, 74 + level_dimensions.y , 45, 23 }, COLLIDER_WALL);
		App->collision->AddCollider({ 201, 70 + level_dimensions.y , 35, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 204, 66 + level_dimensions.y , 33, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 214, 64 + level_dimensions.y , 24, 2 }, COLLIDER_WALL);

		//Collisions of the 2nd rock at the right 
		App->collision->AddCollider({ 196, -151 + level_dimensions.y , 48, 38 }, COLLIDER_WALL);
		App->collision->AddCollider({ 203, -166 + level_dimensions.y , 40, 15 }, COLLIDER_WALL);
		App->collision->AddCollider({ 215, -173 + level_dimensions.y , 40, 7 }, COLLIDER_WALL);

		//Collisions of the rock at the middle of the before the bridge 
		App->collision->AddCollider({ 84, -482 + level_dimensions.y , 87, 17 }, COLLIDER_WALL);
		App->collision->AddCollider({ 89, -497 + level_dimensions.y , 80, 15 }, COLLIDER_WALL);
		App->collision->AddCollider({ 114, -505 + level_dimensions.y , 41, 8 }, COLLIDER_WALL);
		App->collision->AddCollider({ 126, -511 + level_dimensions.y , 24, 6 }, COLLIDER_WALL);

		//Collisions of the big rock at the left before the bridge
		App->collision->AddCollider({ 20, -448 + level_dimensions.y , 35, 80 }, COLLIDER_WALL);
		App->collision->AddCollider({ 55, -438 + level_dimensions.y , 22 ,50 }, COLLIDER_WALL);

		//Collisions of the bridge
		App->collision->AddCollider({ 20, -850 + level_dimensions.y , 78, 78 }, COLLIDER_WALL);
		App->collision->AddCollider({ 159, -850 + level_dimensions.y , 80 ,78 }, COLLIDER_WALL);

		//Collisions for the lake
		App->collision->AddCollider({ 20, -171 + level_dimensions.y , 16, 1 }, COLLIDER_WATER);

		//Collisions for the bunkers
		App->collision->AddCollider({ 128, -289 + level_dimensions.y , 60, 10 }, COLLIDER_WALL);
		App->collision->AddCollider({ 192, -738 + level_dimensions.y , 52, 10 }, COLLIDER_WALL);

		//Collisions of the trees and lake of the left down corner
		App->collision->AddCollider({ 20, 213 + level_dimensions.y , 66, 25 }, COLLIDER_WALL);
		App->collision->AddCollider({ 20, 238 + level_dimensions.y , 66, 18 }, COLLIDER_WATER);
		App->collision->AddCollider({ 20, 210 + level_dimensions.y , 65, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 20, 208 + level_dimensions.y ,  63, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 20, 201 + level_dimensions.y , 59, 7 }, COLLIDER_WALL);
		App->collision->AddCollider({ 20, 199 + level_dimensions.y , 58, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 20, 192 + level_dimensions.y , 56, 7 }, COLLIDER_WALL);

		//Collisions of the rocks after the bridge
		App->collision->AddCollider({ 17, 710, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 65, 646, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 113, 742, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 225, 678, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 161, 613, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 17, 517, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 112, 517, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 209, 517, 28, 3 }, COLLIDER_WALL);
		

		//Collisions for thetrinches after the bridge
		App->collision->AddCollider({ 0, 418, 59, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({130, 448, 89, 6 }, COLLIDER_WALL);
		App->collision->AddCollider({ 100, 320, 51, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 6, 290, 83, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 197, 225, 50, 3 }, COLLIDER_WALL);


		//Colliders for the final door
		App->collision->AddCollider({ 0, 0, 87, 43 }, COLLIDER_WALL);
		App->collision->AddCollider({ 170, 0, 86, 43 }, COLLIDER_WALL);

		//Colliders for the box
		App->collision->AddCollider({ 148, 1336, 20, 16 }, COLLIDER_BOX);
		App->collision->AddCollider({ 140, 430, 20, 16 }, COLLIDER_BOX);
		App->collision->AddCollider({ 30, 274,	 20, 16 }, COLLIDER_BOX);
		
		App->collision->AddCollider({ 195, 900, 21, 17 }, COLLIDER_BOX);
		App->collision->AddCollider({ 200, 212, 11, 10 }, COLLIDER_BOX);

		

	}


	if (sprite_graphics == nullptr)
		ret = false;


	return ret;
}



update_status ModuleObjects::Update() {
	if (App->scene_game->getLevel() == 1)
	{
		App->render->Blit(sprite_graphics, 208, 128 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 19, 128 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 83, 0 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		//Group of three palms
		App->render->Blit(sprite_graphics, 146, 193 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 160, 209 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 130, 209 + level_dimensions.y , &tree1.GetCurrentFrame().rect);

		//Groups of three palms
		App->render->Blit(sprite_graphics, 130, -49 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 160, -49 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 146, -65 + level_dimensions.y , &tree1.GetCurrentFrame().rect);

		//Group of three palms
		App->render->Blit(sprite_graphics, 1, -240 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 32, -240 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 17, -256 + level_dimensions.y , &tree1.GetCurrentFrame().rect);

		App->render->Blit(sprite_graphics, 82, -129 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 82, -320 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 144, -257 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 146, -385 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 210, -449 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 144, -642 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 18, -642 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 82, -706 + level_dimensions.y , &tree1.GetCurrentFrame().rect);

		//Bridge sprite
		App->render->Blit(sprite_graphics, 96, 802, &bridge.GetCurrentFrame().rect);		
		
		//Rocks sprites
		App->render->Blit(sprite_graphics, 112, -925, &rock.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 15, -957, &rock.GetCurrentFrame().rect);

		//Rock after bridge
		App->render->Blit(sprite_graphics, 15, 696, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 112, 728, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 224, 663, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 64, 632, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 160, 600, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 16, 503, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 111, 503, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 208, 503, &rock2.GetCurrentFrame().rect);


		//Boxes
		App->render->Blit(sprite_graphics, 148, 1336, &box.GetCurrentFrame().rect);
		
		App->render->Blit(sprite_graphics, 195, 900, &box2.GetCurrentFrame().rect);

		App->render->Blit(sprite_graphics, 140, 430, &box.GetCurrentFrame().rect);

		App->render->Blit(sprite_graphics, 200, 212, &box3.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 30, 274, &box.GetCurrentFrame().rect);

		if (App->scene_game->intro == true)
		{
			if (droping == false)
			{
				
				if (helipoint.y > 1800)
				{
					helipoint.y = helipoint.y - 1;
					helicopter.speed = 0;
				}
				else if (helipoint.y <= 1800 && helipoint.y != helipoint.y - reduction)
				{

						helipoint.y = helipoint.y - reduction;
						reduction = reduction - 0.01f;
					
				}
				else if (helipoint.y == helipoint.y - reduction)
				{
					helicopter.speed = 0.05;
					if (helicopter.Finished() == true)
					{
						droping = true;	
						helicopter = helicopter2;
					}
					
				}
			}
			else if (helipoint.y >= 1708 - SCREEN_HEIGHT - 82)
			{
	
				helipoint.y = helipoint.y - reduction;
				helicopter.speed = 0.05f;
				reduction = reduction + 0.01f;
			}
			else
			{
				App->scene_game->intro = false;
			}
				
		
			App->render->Blit(sprite_graphics, helipoint.x, helipoint.y, &helicopter.GetCurrentFrame().rect);
		
		}

	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleObjects::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleObjects::CleanUp() {
	bool ret = true;
	
	
	App->collision->Disable();
	App->enemies->Disable();

	ret = App->textures->Unload(sprite_graphics);

	

	return ret;
}

