#pragma once
#include <unordered_map>
#include "Components/GraphicsComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/CombatComponent.h"
#include "Components/DialogueComponent.h"
#include <string>
#include "World.h"
#include "Text.h"
#include <iostream>
#include <stdio.h>
#ifdef _WIN32
#include <SDL.h>
#endif

#ifdef linux
#include <SDL2/SDL.h>
#endif
class ECSManager
{
public:
	ECSManager(SDL_Renderer* renderer, World* w, TTF_Font* f, SDL_Color c);

	void loadWorld(World* w);
	void setInputControlled(Uint32 id);
	Uint32 generateEntity();
	Uint32 generateEntity(std::string name);
	
	void addGraphicsComponent(Uint32 id, GraphicsComponent* graphics);
	void addPhysicsComponent(Uint32 id, PhysicsComponent* physics);
	void addCombatComponent(Uint32 id, CombatComponent* combat);
	
	void kill(Uint32 id);
	
	void update(Uint32 deltaT);
	void render(SDL_Rect* camera);
	
	void input(SDL_Event e);
	
	PhysicsComponent* getPhysicsComponent(Uint32 id);
	Uint32 getIDfromName(std::string name)
	{
		return namedEntities[name];
	}
	void speak(std::string text, Uint32 id);
	void speak(std::string text);
private:
	World* world;
	Uint32 currentID = 0;
	Uint32 inputControlled = 0;
	std::unordered_map<Uint32, PhysicsComponent*> physicsComponents;
	std::unordered_map<Uint32, GraphicsComponent*> graphicsComponents;
	std::unordered_map<Uint32, CombatComponent*> combatComponents;
	std::unordered_map<std::string, Uint32> namedEntities;
	Text* speech;
	bool speaking;
	void printCollisionBuckets();
	SDL_Renderer* renderer;
	void unspeak();
};