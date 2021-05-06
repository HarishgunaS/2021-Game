#include "ECSManager.h"
void ECSManager::render(SDL_Rect* camera)
{
    //maybe change to render based on collision buckets??
    for (const auto& pair : graphicsComponents)
    {
        GraphicsComponent* graphics = pair.second;
        //make more robust obviously
        if (physicsComponents[pair.first] != NULL)
        {
            PhysicsComponent* physics = physicsComponents[pair.first];
            if (SDL_HasIntersection(physics->position, camera) == SDL_TRUE)
            {
                physics->position->x = physics->position->x - camera->x;
                physics->position->y = physics->position->y - camera->y;
                SDL_RenderCopy(renderer, graphics->texture, NULL, physics->position);
                physics->position->x = physics->position->x + camera->x;
                physics->position->y = physics->position->y + camera->y;
            }
        }
    }
    if (speaking)
    {
        speech->render(renderer);
    }
}
void ECSManager::input(SDL_Event e)
{
    PhysicsComponent* physics = physicsComponents[inputControlled];
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            physics->yVelocity = (-1.0 * physics->speed);
            //physics->setXVelocity(0);
            break;
        case SDLK_DOWN:
            physics->yVelocity = (physics->speed);
            //physics->setXVelocity(0);
            break;
        case SDLK_LEFT:
            physics->xVelocity = (-1.0 * physics->speed);
            //physics->setYVelocity(0);
            break;
        case SDLK_RIGHT:
            physics->xVelocity = (physics->speed);
            //physics->setYVelocity(0);
            break;
        default:
            break;
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            physics->yVelocity = (0);
            break;
        case SDLK_DOWN:
            physics->yVelocity = (0);
            break;
        case SDLK_LEFT:
            physics->xVelocity = (0);
            break;
        case SDLK_RIGHT:
            physics->xVelocity = (0);
            break;
        case SDLK_c:
            unspeak();
        default:
            break;
        }
    }
}
void ECSManager::update(Uint32 deltaT)
{
    //bool killing = false;
    //Uint32 toKill = 0;
    if (speaking)
    {
        return;
    }
    for (const auto& pair : physicsComponents)
    {
        
        PhysicsComponent* physics = pair.second;
        //make more robust obviously


        //grid bucket to check around
        int previousBucketX = (physics->collider->x + physics->collider->w / 2) / world->size;
        int previousBucketY = (physics->collider->y + physics->collider->h / 2) / world->size;

        //move temp x y if within borders
        if (physics->x + physics->xVelocity * deltaT >= 0 && physics->x + physics->position->w + physics->xVelocity * deltaT <= world->WORLD_WIDTH)
        {
            physics->x += physics->xVelocity * deltaT;
        }
        if (physics->y + physics->yVelocity * deltaT >= 0 && physics->y + physics->position->h + physics->yVelocity * deltaT <= world->WORLD_HEIGHT)
        {
            physics->y += physics->yVelocity * deltaT;
        }

        //new collider of future position
        SDL_Rect* newCollider = new SDL_Rect();
        newCollider->w = physics->collider->w;
        newCollider->h = physics->collider->h;
        newCollider->x = physics->x;
        newCollider->y = physics->y;

        bool collisionOccurred = false;
        Uint32 collidedID = 0;
        for (int i = previousBucketX - 2; i < previousBucketX + 2; i++)
        {
            if (i < 0 || i >= world->w)
            {
                continue;
            }
            for (int j = previousBucketY - 2; j < previousBucketY + 2; j++)
            {
                if (j < 0 || j >= world->h)
                {
                    continue;
                }
                for (int k = 0; k < 2; k++)
                {
                    //std::cout << i << " " << j << " " << k << std::endl;
                    Uint32 id = world->collisionBuckets[i][j][k];
                    if (id != pair.first && id != -1)
                    {
                        //check collisions
                        if ((SDL_HasIntersection(newCollider, physicsComponents[id]->collider)))
                        {
                            collisionOccurred = true;
                            collidedID = id;
                        }
                    }
                }
            }
        }
        delete newCollider;
        newCollider = NULL;
        if (!collisionOccurred)
        {
            physics->position->x = physics->x;
            physics->position->y = physics->y;
            physics->collider->x = physics->x;
            physics->collider->y = physics->y;

            int x = (physics->collider->x + physics->collider->w / 2) / world->size;
            int y = (physics->collider->y + physics->collider->h / 2) / world->size;

            if (world->collisionBuckets[previousBucketX][previousBucketY][0] == pair.first)
            {
                world->collisionBuckets[previousBucketX][previousBucketY][0] = -1;
            }
            else if (world->collisionBuckets[previousBucketX][previousBucketY][1] == pair.first)
            {
                world->collisionBuckets[previousBucketX][previousBucketY][1] = -1;
            }
            else
            {
                //PRINT ERROR!
            }

            if (world->collisionBuckets[x][y][0] == -1)
            {
                world->collisionBuckets[x][y][0] = pair.first;
            }
            else if (world->collisionBuckets[x][y][1] == -1)
            {
                world->collisionBuckets[x][y][1] = pair.first;
            }
            else
            {
                //PRINT ERROR!
            }
        }
        else
        {
            

            physics->x = physics->position->x;
            physics->y = physics->position->y;
        }
        
        
    }
    //if (killing) kill(toKill);
}
void ECSManager::kill(Uint32 id)
{

    if (id == inputControlled)
    {
        //game over
    }

    PhysicsComponent* physics = physicsComponents[id];
    int x = (physics->collider->x + physics->collider->w / 2) / world->size;
    int y = (physics->collider->y + physics->collider->h / 2) / world->size;
    if (world->collisionBuckets[x][y][0] == id)
    {
        world->collisionBuckets[x][y][0] = -1;
    }
    else if (world->collisionBuckets[x][y][1] == id)
    {
        world->collisionBuckets[x][y][1] = -1;
    }

    printf("killing now\n");
    delete physicsComponents[id];
    physicsComponents.erase(id);
    delete combatComponents[id];
    combatComponents.erase(id);
    delete graphicsComponents[id];
    graphicsComponents.erase(id);
    printf("finished killing\n");
}
ECSManager::ECSManager(SDL_Renderer* r, World* w, TTF_Font* f, SDL_Color c)
{
    speech = new Text(f, c);
    loadWorld(w);
    renderer = r;
    speech->setText("demo", renderer);
    speech->setPosition(10, 800 - speech->getRect()->h);

}
void ECSManager::loadWorld(World* w)
{
    world = w;
}

void ECSManager::setInputControlled(Uint32 id)
{
    inputControlled = id;
}

Uint32 ECSManager::generateEntity()
{
    return currentID++;
}

void ECSManager::addGraphicsComponent(Uint32 id, GraphicsComponent* graphics)
{
    graphicsComponents[id] = graphics;
}
void ECSManager::addPhysicsComponent(Uint32 id, PhysicsComponent* physics)
{
    physicsComponents[id] = physics;
}
void ECSManager::addCombatComponent(Uint32 id, CombatComponent* combat)
{
    combatComponents[id] = combat;
}

Uint32 ECSManager::generateEntity(std::string name)
{
    Uint32 id = generateEntity();
    namedEntities[name] = id;
    return id;
}


void ECSManager::printCollisionBuckets()
{
    for (int i = 0; i < world->w; i++)
    {
        for (int j = 0; j < world->h; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                Uint32 id = world->collisionBuckets[i][j][k];
                if (id != -1)
                {
                    std::cout << id << " " << i << " " << j << " " << k << std::endl;
                }
            }
        }
    }
}
PhysicsComponent* ECSManager::getPhysicsComponent(Uint32 id)
{
    return physicsComponents[id];
}


void ECSManager::speak(std::string text)
{
    speaking = true;
    speech->setText(text, renderer);
}
void ECSManager::speak(std::string text, Uint32 id)
{

    // if (id != -1)
    // {
    //     return;
    // }
    speak(text);

}
void ECSManager::unspeak()
{
    speaking = false;
}