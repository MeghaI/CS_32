#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <vector>
using namespace std;


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    virtual ~StudentWorld();
    void addActor(Actor* a);
    NachenBlaster* getNach();
    bool collided(Actor* a1, Actor* a2);
    DamageableObject* collidedWithAlien(Actor* a1);
    NachenBlaster* collidedWithNach(Actor* a1);
    bool collidedWithNachProjectile(Actor* a1);
    bool collidedWithAlienProjectile(Actor* a1);
private:
    vector<Actor*> myActors;
    NachenBlaster* myBlaster;
    int deadShips;
};

#endif // STUDENTWORLD_H_
