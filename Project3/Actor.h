#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject{
public:
    Actor(StudentWorld* world, int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0):GraphObject(imageID, startX, startY, dir, size, depth), myWorld(world){setAlien(false);}
    virtual void doSomething() = 0;
    int getState();
    void setState(int state);
    StudentWorld* getWorld();
    bool isAlien();
    bool isNachProjectile();
    bool isAlienProjectile();
    void setAlien(bool alien);
    void setNachProjectile(bool nachprojectile);
    void setAlienProjectile(bool alienprojectile);
    void setTravelSpeed(const double speed);
    double getTravelSpeed() const;
private:
    int myState = 1; //1 means alive, 0 means dead
    StudentWorld* myWorld;
    bool amAlien = false;
    bool amNachProjectile = false;
    bool amAlienProjectile = false;
    double travelSpeed;
};

class Star: public Actor{
public:
    Star(StudentWorld* world, double startX, double startY):Actor(world, IID_STAR, startX, startY, 0, randInt(5,50)/100.0, 3){setTravelSpeed(1);}
    void doSomething();
};

class DamageableObject: public Actor{
public:
    DamageableObject(StudentWorld* world, double imageID, double startX, double startY, int dir, double size, int depth):Actor(world, imageID, startX, startY, dir, size, depth){ }
    double getHitPoints() const;
    void setHitPoints(const double p);
    void sufferDamage(double amount, int cause);
private:
    double hitPoints;
};

class NachenBlaster: public DamageableObject{
public:
    NachenBlaster(StudentWorld* world):DamageableObject(world, IID_NACHENBLASTER, 0, 128,  0, 1.0, 0), cabbagePoints(30), numTorpedoes(0){setTravelSpeed(6); setHitPoints(50);}
    void doSomething();
    int getTorpedoes();
    void setTorpedoes(int num);
    int getCabbagePoints();
private:
    int cabbagePoints;
    void fireCabbage();
    void fireTorpedo();
    int numTorpedoes;
};

class Projectile: public Actor{
public:
    Projectile(StudentWorld* world, int imageID, double startX, double startY, int dir): Actor(world, imageID, startX, startY, dir, 0.5, 1) {}
    virtual void doSomething() = 0;
private:
};
    
class Cabbage: public Projectile{
public:
    Cabbage(StudentWorld* world, double startX, double startY):Projectile(world, IID_CABBAGE, startX, startY, 0){setTravelSpeed(8); setNachProjectile(true);}
    virtual void doSomething();
};

class FlatulenceTorpedo: public Projectile{
public:
    FlatulenceTorpedo(StudentWorld* world, double startX, double startY, int imageDir):Projectile(world, IID_TORPEDO, startX, startY, imageDir){setTravelSpeed(8);}
    virtual void doSomething();
};

class PlayerLaunchedTorpedo: public FlatulenceTorpedo{
public:
    PlayerLaunchedTorpedo(StudentWorld* world, double startX, double startY):FlatulenceTorpedo(world, startX, startY, 0){setNachProjectile(true); }
};

class AlienLaunchedTorpedo: public FlatulenceTorpedo{
public:
    AlienLaunchedTorpedo(StudentWorld* world, double startX, double startY):FlatulenceTorpedo(world, startX, startY, 180){}
};

class Turnip: public Projectile{
public:
    Turnip(StudentWorld* world, double startX, double startY):Projectile(world, IID_TURNIP, startX, startY, 0){
        setTravelSpeed(6);
        setAlienProjectile(true);
    }
    virtual void doSomething();
};

class Alien: public DamageableObject{
public:
    Alien(StudentWorld* world, int imageID, double startX, double startY):DamageableObject(world, imageID, startX, startY, 0, 1.5, 1) {setAlien(true); setTravelDirection(180);}
    void setFlightPlanLength(const double length);
    double getFlightPlanLength() const;
    void setTravelDirection(const double direction);
    double getTravelDirection() const;
    virtual void doSomething();
    virtual bool fireProjectile();
    virtual bool checkForCollisions()=0;
    virtual void setFlightPath();
private:
    double flightPlanLength;
    double travelDirection = 0;
};

class Smallgon: public Alien{
public:
    Smallgon(StudentWorld* world, double startX, double startY);
    virtual bool checkForCollisions();

};

class Smoregon: public Alien{
public:
    Smoregon(StudentWorld* world, double startX, double startY);
    virtual bool fireProjectile();
    virtual bool checkForCollisions();
    void dropGoodie();
};

class Snagglegon: public Alien{
public:
    Snagglegon(StudentWorld* world, double startX, double startY);
    virtual bool fireProjectile();
    virtual bool checkForCollisions();
    virtual void setFlightPath();
    void dropGoodie();
};

class Explosion: public Actor{
public:
    Explosion(StudentWorld* world, double startX, double startY): Actor(world, IID_EXPLOSION, startX, startY, 0, 1, 0){ currentTick = 1;}
    virtual void doSomething();
private:
    int currentTick;
};

class Goodie: public Actor{
public:
    Goodie(StudentWorld* world, int imageID, double startX, double startY):Actor(world, imageID, startX, startY, 0, 0.5, 1){ setTravelSpeed(0.75);}
};

class ExtraLifeGoodie: public Goodie{
public:
    ExtraLifeGoodie(StudentWorld* world, double startX, double startY):Goodie(world, IID_LIFE_GOODIE, startX, startY){ }
    virtual void doSomething();
};

class RepairGoodie: public Goodie{
public:
    RepairGoodie(StudentWorld* world, double startX, double startY):Goodie(world, IID_REPAIR_GOODIE, startX, startY){ }
    virtual void doSomething();
};

class FlatulenceTorpedoGoodie: public Goodie{
public:
    FlatulenceTorpedoGoodie(StudentWorld* world, double startX, double startY):Goodie(world, IID_TORPEDO_GOODIE, startX, startY){ }
    virtual void doSomething();
};
#endif // ACTOR_H_
