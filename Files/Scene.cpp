#include "Scene.h"
#include "Collision.h"
#include "Player.h"
#include "Fixture.h"
#include "Prop.h"


Scene::Scene(Graphics& graphics, int w, int h) : width(w), height(h)
{
	camera.reset(new Camera(0, 480));

	collision_component = std::make_unique<Collision>();

	Sprite BackGround(graphics, "Files/Background.bmp", 0, 0, 640, 480);

	std::shared_ptr<Player> player = std::make_shared<Player>(graphics, 320, 240);
	camera_subject = player;
	entity_queue.push_back(player);
	game_actor_queue.push_back(player);

	std::shared_ptr<Prop> scaffold = std::make_shared<Prop>(graphics, 500, 150);
	entity_queue.push_back(scaffold);


	std::shared_ptr<Fixture> platform = std::make_shared<Fixture>(graphics, 350, 150, 50, 35);

	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 400, 230, 100, 35);


	entity_queue.push_back(platform);//All game objects are in the entity queue
	//All gameActors are in game_actor_queue
	platform = std::make_shared<Fixture>(graphics, 35, 10, 2100, 35);
	entity_queue.push_back(platform);

	platform = std::make_shared<Fixture>(graphics, 600, 260, 100, 35);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 800, 260, 100, 35);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 1000, 260, 100, 35);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 1200, 260, 100, 35);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 1400, 260, 100, 35);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 1600, 350, 100, 35);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 1900, 435, 100, 35);
	entity_queue.push_back(platform);

	platform = std::make_shared<Fixture>(graphics, 0, 380, 50, 400);
	entity_queue.push_back(platform);

	//short blocks for walking~~~~~~~~~~~~~~~ 

	platform = std::make_shared<Fixture>(graphics, 140, 90, 20, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 160, 90, 20, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 180, 90, 20, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 200, 90, 20, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 220, 90, 20, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 240, 90, 20, 10);
	entity_queue.push_back(platform);

	platform = std::make_shared<Fixture>(graphics, 105, 125, 1, 20);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 105, 138, 1, 10);
	entity_queue.push_back(platform);


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*
	std::shared_ptr<Fixture> platform = std::make_shared<Fixture>(graphics, 10, 300, 600, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 10, 150, 600, 10);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 20, 120, 10, 300);
	entity_queue.push_back(platform);
	platform = std::make_shared<Fixture>(graphics, 590, 120, 10, 300);
	entity_queue.push_back(platform);*/

	AllSprites.push_back(BackGround);
}


Scene::~Scene()
{
}

void Scene::draw(const Graphics& graphics) const
{
	AllSprites[0].draw(graphics, 0, 0);
	camera->draw(graphics);
	
}

void Scene::update(int elapsed_time_ms)
{

	//check collisions
	//list of collisions for each entity is set
	for (auto &entity1 : entity_queue) {
		for (auto &entity2 : entity_queue) {
			if (entity1 != entity2) {
				std::shared_ptr<CollisionData> data;
				data = collision_component->getCollisionData(*entity1, *entity2, elapsed_time_ms);
				if (data != nullptr)
				{
					entity1->addCollision(std::move(data));
				}
			}
		}
	}

	//call update on each entity
	for (auto &entity : entity_queue) {
		entity->update(elapsed_time_ms);
	}

	camera->update(*this, elapsed_time_ms);
}

void Scene::executeCommands(std::vector<std::shared_ptr<Command>>& command_queue)
{
	for (auto command : command_queue) {
		game_actor_queue[0]->handleCommand(*command);
	}
}