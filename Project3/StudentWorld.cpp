
#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include "Actor.h"

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
}

int StudentWorld::init()
{
    deadShips = 0;
    for(int i = 0; i<30; i++){
        myActors.push_back(new Star(this, randInt(0, VIEW_WIDTH-1), randInt(0, VIEW_HEIGHT-1)));
    }
    myBlaster = new NachenBlaster(this);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    
    
    
    vector<Actor*>::iterator it;
    int currentShips = 0;
    for(it = myActors.begin(); it!=myActors.end(); it++){
        (*it)->doSomething();   //ACTORS DO SOMETHING
        if((*it)->getState()==0){
            if((*it)->getX()>=0 && (*it)->isAlien()) deadShips++;
            delete *it;
            it = myActors.erase(it);
            it--;
        }else{
            if((*it)->isAlien()) currentShips++;
        }
        if(myBlaster->getState()==0){
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        if(deadShips>= (6 + (4 * getLevel()))){
            return GWSTATUS_FINISHED_LEVEL;
        }
    }
    int chance = randInt(1,15);
    if(chance==15){
        myActors.push_back(new Star(this, VIEW_WIDTH-1, randInt(0, VIEW_HEIGHT-1)));
    }
    myBlaster -> doSomething(); //BLASTER DOES SOMETHING
    int totalNeedDestroyed = 6+(4*getLevel());
    int remainingShips = totalNeedDestroyed - deadShips;
    int maxShips = 4 + (0.5*getLevel());
    if(currentShips < min(maxShips, remainingShips)){
        int S1 = 60;
        int S2 = 20 + getLevel() * 5;
        int S3 = 5 + getLevel() * 10;
        int S = S1 + S2 + S3;
        int chance = randInt(1, S);
        if(chance <= S1){
            myActors.push_back(new Smallgon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT-1)));
        }else if (chance <= S1 + S2){
            myActors.push_back(new Smoregon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT-1)));
        }else{
            myActors.push_back(new Snagglegon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT-1)));
        }
    }
    
    int health = static_cast<int>(((myBlaster->getHitPoints())*100.0)/50);
    int cabbages =static_cast<int>(((myBlaster->getCabbagePoints())*100.0)/30);
    setGameStatText("Lives: "+to_string(getLives())+" Health: "+to_string(health)+"% Score: "+to_string(getScore())+" Level: "+to_string(getLevel())+" Cabbages: "+to_string(cabbages)+"% Torpedoes: "+to_string(myBlaster->getTorpedoes()));

    
    return GWSTATUS_CONTINUE_GAME;
}

StudentWorld::~StudentWorld(){
    this->cleanUp();
}

void StudentWorld::cleanUp()
{
    delete myBlaster;
    myBlaster = nullptr;
     vector<Actor*>::iterator it;
    for(it = myActors.begin(); it!=myActors.end(); it++){
            delete *it;
            it = myActors.erase(it);
            it--;
    }
}

void StudentWorld::addActor(Actor *a){
    myActors.push_back(a);
}
bool StudentWorld::collided(Actor* a1, Actor* a2){
    int x1 = a1->getX();
    int x2 = a2->getX();
    int y1 = a1->getY();
    int y2 = a2->getY();
    int R1 = a1->getRadius();
    int R2 = a2->getRadius();
    double distance = sqrt(((x1-x2)*(x1-x2)) + ((y1-y2)*(y1-y2)));
    return distance<.75*(R1+R2);
}

DamageableObject* StudentWorld::collidedWithAlien(Actor* a1){
    vector<Actor*>::iterator it;
    for(it = myActors.begin(); it!=myActors.end(); it++){
        if((*it)->isAlien()){
            if(collided(*it, a1)){
                Actor* a = *it;
                DamageableObject* d = static_cast<DamageableObject*>(a);
                return d;
            }
        }
    }
    return nullptr;
}

NachenBlaster* StudentWorld::collidedWithNach(Actor* a1){
    if(collided(a1, myBlaster)) return myBlaster;
    return nullptr;
}

bool StudentWorld::collidedWithNachProjectile(Actor* a1){
    vector<Actor*>::iterator it;
    for(it = myActors.begin(); it!=myActors.end(); it++){
        if((*it)->isNachProjectile()){
            if(collided(*it, a1)){
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::collidedWithAlienProjectile(Actor* a1){
    vector<Actor*>::iterator it;
    for(it = myActors.begin(); it!=myActors.end(); it++){
        if((*it)->isAlienProjectile()){
            if(collided(*it, a1)){
                return true;
            }
        }
    }
    return false;
}

NachenBlaster* StudentWorld::getNach(){
    return myBlaster;
}