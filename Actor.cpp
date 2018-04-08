#include "Actor.h"
#include "StudentWorld.h"
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


#include <iostream>
using namespace std;

const int HIT_BY_SHIP = 0;
const int HIT_BY_PROJECTILE = 1;

int Actor::getState() {
    return myState;
}

bool Actor::isAlien(){
    return amAlien;
}

bool Actor::isNachProjectile(){
    return amNachProjectile;
}
bool Actor::isAlienProjectile(){
    return amAlienProjectile;
}

void Actor::setAlien(bool alien){
    amAlien = alien;
}

void Actor::setNachProjectile(bool nachprojectile){
    amNachProjectile = nachprojectile;
}

void Actor::setAlienProjectile(bool alienprojectile){
    amAlienProjectile = alienprojectile;
}

StudentWorld* Actor::getWorld(){
    return myWorld;
}

void Actor::setState(int state){
    myState = state;
}

void Star::doSomething(){
    double newX = this->getX() - getTravelSpeed();
    if(newX>=0){
        this->moveTo(newX, this->getY());
    }else{
        this->setState(0);
    }
    
}

void NachenBlaster::setTorpedoes(int num){
    numTorpedoes = num;
}

int NachenBlaster::getTorpedoes(){
    return numTorpedoes;
}

void NachenBlaster::doSomething(){
    if(cabbagePoints<30) cabbagePoints++;
    //check if dead or should be dead
    if(this->getState()==0) return;
    
    DamageableObject* d = getWorld()->collidedWithAlien(this);
    if(d!=nullptr){
        getWorld()->playSound(SOUND_DEATH);
        d->sufferDamage(100, HIT_BY_SHIP);
    }
    if(getWorld()->collidedWithAlienProjectile(this)){
        getWorld()->playSound(SOUND_BLAST);
    }
    if(this->getHitPoints()<=0){
        this->setState(0);
    }
    
    int ch;
    //take input keys and move or fire things accordingly
    if(getWorld()->getKey(ch)){
        double newX = this->getX();
        double newY = this->getY();
        switch(ch){
            case  KEY_PRESS_LEFT:
                newX-=6;
                break;
            case KEY_PRESS_RIGHT:
                newX+=6;
                break;
            case KEY_PRESS_DOWN:
                newY-=6;
                break;
            case KEY_PRESS_UP:
                newY+=6;
                break;
            case KEY_PRESS_SPACE:
                getWorld()->playSound(SOUND_PLAYER_SHOOT);
                fireCabbage();
                break;
            case KEY_PRESS_TAB:
                fireTorpedo();
                break;
        }
        if(newX<0 || newY<0 || newX>=VIEW_WIDTH || newY>=VIEW_HEIGHT) return;
        this->moveTo(newX, newY);
    }
    
    //CHECK FOR COLLISIONS
    d = getWorld()->collidedWithAlien(this);
    if(d!=nullptr){
        getWorld()->playSound(SOUND_DEATH);
        d->sufferDamage(100, HIT_BY_SHIP);
    }
    if(getWorld()->collidedWithAlienProjectile(this)){
        getWorld()->playSound(SOUND_BLAST);
    }
    if(this->getHitPoints()<=0){
        this->setState(0);
    }
    
    
}

void NachenBlaster::fireCabbage(){
    if(cabbagePoints<5) return;
    cabbagePoints-=5;
    getWorld()->playSound(SOUND_TORPEDO);
    Actor* c = new Cabbage(getWorld(), getX()+12, getY());
    getWorld()->addActor(c);
}

void NachenBlaster::fireTorpedo(){
    if(getTorpedoes()>0){
        setTorpedoes(getTorpedoes()-1);
        getWorld()->playSound(SOUND_TORPEDO);
        Actor* c = new PlayerLaunchedTorpedo(getWorld(), getX()+12, getY());
        getWorld()->addActor(c);
    }
}

void Cabbage::doSomething(){
    //check if dead or should be dead
    if(this->getState()==0) return;
    if(this->getX()+getTravelSpeed()>=VIEW_WIDTH){
        this->setState(0);
        return;
    }
    
    //collision check
    DamageableObject* d = getWorld()->collidedWithAlien(this);
    if(d!=nullptr){
        d->sufferDamage(2, HIT_BY_PROJECTILE);
        this->setState(0);
        return;
    }
    
    //move and rotate
    double newX = getX();
    newX+=getTravelSpeed();
    if(newX<0 || newX>=VIEW_WIDTH) return;
    this->moveTo(newX, getY());
    this->setDirection(getDirection()+20);
    
    //collision check
    d = getWorld()->collidedWithAlien(this);
    if(d!=nullptr){
        d->sufferDamage(2, HIT_BY_PROJECTILE);
        this->setState(0);
        return;
    }
}

//FINISH THIS
void FlatulenceTorpedo::doSomething(){
    //check if dead or should be dead
    if(this->getState()==0) return;
    if(this->getX()-getTravelSpeed()<0 || this->getX()+getTravelSpeed()>=VIEW_WIDTH){
        this->setState(0);
        return;
    }
    
    //collisions
    if(this->getDirection()==0){
        DamageableObject* d = getWorld()->collidedWithAlien(this);
        if(d!=nullptr){
            d->sufferDamage(8, HIT_BY_PROJECTILE);
            this->setState(0);
            return;
        }

    }else{
        DamageableObject* d = getWorld()->collidedWithNach(this);
        if(d!=nullptr){
            d->sufferDamage(8, HIT_BY_PROJECTILE);
            this->setState(0);
            return;
        }
    }
    
    int newX;
    int newY = getY();
    //movement
    if(getDirection()==0){
        newX = getX()+getTravelSpeed();
    }else{
        newX = getX()-getTravelSpeed();
    }
    moveTo(newX, newY);
    
    //collisions
    if(this->getDirection()==0){
        DamageableObject* d = getWorld()->collidedWithAlien(this);
        if(d!=nullptr){
            d->sufferDamage(8, HIT_BY_PROJECTILE);
            this->setState(0);
            return;
        }
        
    }else{
        DamageableObject* d = getWorld()->collidedWithNach(this);
        if(d!=nullptr){
            d->sufferDamage(8, HIT_BY_PROJECTILE);
            this->setState(0);
            return;
        }
    }

}

void Turnip::doSomething(){
    //check if dead or needs to be dead
    if(this->getState()==0) return;
    if(this->getX()-getTravelSpeed()<0){
        this->setState(0);
        return;
    }
    //check for collision
    DamageableObject* d = getWorld()->collidedWithNach(this);
    if(d!=nullptr){
        d->sufferDamage(2, HIT_BY_PROJECTILE);
        this->setState(0);
        return;
    }
    
    //move and rotate
    double newX = getX();
    newX-=getTravelSpeed();
    if(newX<0 || newX>=VIEW_WIDTH) return;
    this->moveTo(newX, getY());
    this->setDirection(getDirection()+20);
    
    //collision check
    d = getWorld()->collidedWithNach(this);
    if(d!=nullptr){
        d->sufferDamage(2, HIT_BY_PROJECTILE);
        this->setState(0);
        return;
    }
}

void Alien::doSomething(){
    //check if dead or should be dead
    if(getState()==0){
        return;
    }
    if(getX() < 0){
        setState(0);
        return;
    }
    if(getHitPoints()<=0){
        setState(0);
        getWorld()->addActor(new Explosion(getWorld(), getX(), getY()));
        return;
    }
    
    if(checkForCollisions()) return;

    //direction
    setFlightPath();
    
    //fire turnip
    if(fireProjectile()) return;
    
    //movement
    if(getTravelDirection()==135){
        moveTo(getX()-getTravelSpeed(),getTravelSpeed()+getY());
    }else if(getTravelDirection()==225){
        moveTo(getX()-getTravelSpeed(),getY()-getTravelSpeed());
    }else if(getTravelDirection()==180){
        moveTo(getX()-getTravelSpeed(),getY());
    }
    
    setFlightPlanLength(getFlightPlanLength()-1);
    
    if(checkForCollisions()) return;
//
}

bool Smallgon::checkForCollisions(){
    //CHECK FOR COLLISIONS: NACH PROJECTILE
    if(getWorld()->collidedWithNachProjectile(this)){
        if(getHitPoints()<=0){
            getWorld()->increaseScore(250);
            setState(0);
            getWorld()->playSound(SOUND_DEATH);
            getWorld()->addActor(new Explosion(getWorld(), getX(), getY()));
            return true;
        }else{
            getWorld()->playSound(SOUND_BLAST);
        }
    }
    //CHECK FOR COLLISIONS: NACH
    DamageableObject* d = getWorld()->collidedWithNach(this);
    if(d!=nullptr){
        d->sufferDamage(5, HIT_BY_SHIP);
        this->setState(0);
        getWorld()->increaseScore(250);
        getWorld()->addActor(new Explosion(getWorld(), getX(), getY()));
        return true;
    }
    return false;
}

//add goodies
bool Smoregon::checkForCollisions(){
    //CHECK FOR COLLISIONS: NACH PROJECTILE
    if(getWorld()->collidedWithNachProjectile(this)){
        if(getHitPoints()<=0){
            getWorld()->increaseScore(250);
            setState(0);
            getWorld()->playSound(SOUND_DEATH);
            getWorld()->addActor(new Explosion(getWorld(), getX(), getY()));
            dropGoodie();
            return true;
        }else{
            getWorld()->playSound(SOUND_BLAST);
        }
    }
    //CHECK FOR COLLISIONS: NACH
    DamageableObject* d = getWorld()->collidedWithNach(this);
    if(d!=nullptr){
        d->sufferDamage(5, HIT_BY_SHIP);
        this->setState(0);
        getWorld()->increaseScore(250);
        getWorld()->addActor(new Explosion(getWorld(), getX(), getY()));
        dropGoodie();
        return true;
    }
    
    return false;
}

void Smoregon::dropGoodie(){
    int rand = randInt(1,3);
    if(rand==1){
        int rand2 = randInt(1,2);
        if(rand2==1){
            getWorld()->addActor(new FlatulenceTorpedoGoodie(getWorld(), getX(), getY()));
        }else{
            getWorld()->addActor(new RepairGoodie(getWorld(), getX(), getY()));
        }
    }
}

void Snagglegon::dropGoodie(){
    int rand = randInt(1,6);
    if(rand==1){
        getWorld()->addActor(new ExtraLifeGoodie(getWorld(), getX(), getY()));
    }
}

//add goodies
bool Snagglegon::checkForCollisions(){
    //CHECK FOR COLLISIONS: NACH PROJECTILE
    if(getWorld()->collidedWithNachProjectile(this)){
        if(getHitPoints()<=0){
            getWorld()->increaseScore(1000);
            setState(0);
            getWorld()->playSound(SOUND_DEATH);
            getWorld()->addActor(new Explosion(getWorld(), getX(), getY()));
            dropGoodie();
            return true;
        }else{
            getWorld()->playSound(SOUND_BLAST);
        }
    }
    //CHECK FOR COLLISIONS: NACH
    DamageableObject* d = getWorld()->collidedWithNach(this);
    if(d!=nullptr){
        d->sufferDamage(5, HIT_BY_SHIP);
        this->setState(0);
        getWorld()->increaseScore(1000);
        getWorld()->playSound(SOUND_DEATH);
        getWorld()->addActor(new Explosion(getWorld(), getX(), getY()));
        dropGoodie();
        return true;
    }
    return false;
}

bool Alien::fireProjectile(){
    if(getWorld()->getNach()->getX()<getX() && (((getWorld()->getNach()->getY()-getY()) * (getWorld()->getNach()->getY()-getY())) <= 16)){
        int rand = randInt(1, (20/getWorld()->getLevel()+5));
        if(getWorld()->getNach()->getX() < getX() && ((getY()-getWorld()->getNach()->getY())*(getY()-getWorld()->getNach()->getY())<=16)&& rand==1){
            getWorld()->addActor(new Turnip(getWorld(), getX()-14, getY()));
            getWorld()->playSound(SOUND_ALIEN_SHOOT);
            return true;
        }
    }
    return false;
}

//add GOODIES
bool Smoregon::fireProjectile(){
    if(Alien::fireProjectile()) return true;
        int rand = randInt(1, (20/getWorld()->getLevel()+5));
        if(getWorld()->getNach()->getX() < getX() && ((getY()-getWorld()->getNach()->getY())*(getY()-getWorld()->getNach()->getY())<=16)&& rand==1){
            setTravelDirection(180);
            setFlightPlanLength(VIEW_WIDTH);
            setTravelSpeed(5);
        }
    return false;
}

void Alien::setFlightPath(){
    if(getY()<=0 || getY()>=VIEW_HEIGHT-1 || getFlightPlanLength()<=0){
        if(getY()>=VIEW_HEIGHT-1){
            setTravelDirection(225);
        }else if(getY()<=0){
            setTravelDirection(135);
        }else{
            int rand = randInt(1,3);
            if(rand==1){
                setTravelDirection(180);
            }else if(rand==2){
                setTravelDirection(135);
            }else if(rand==3){
                setTravelDirection(225);
            }
        }
        setFlightPlanLength(randInt(1,32));
    }
}

//fire flatulence torpedo
bool Snagglegon::fireProjectile(){
    if(getWorld()->getNach()->getX()<getX() && (((getWorld()->getNach()->getY()-getY()) * (getWorld()->getNach()->getY()-getY())) <= 16)){
        int rand = randInt(1, (15/getWorld()->getLevel()+10));
        if(getWorld()->getNach()->getX() < getX() && ((getY()-getWorld()->getNach()->getY())*(getY()-getWorld()->getNach()->getY())<=16) && rand==1){
            getWorld()->addActor(new AlienLaunchedTorpedo(getWorld(), getX()-14, getY()));
            getWorld()->playSound(SOUND_TORPEDO);
            return true;
        }
    }
    return false;
}

void Snagglegon::setFlightPath(){
    if(getY()<=0 || getY()>=VIEW_HEIGHT-1){
        if(getY()>=VIEW_HEIGHT-1){
            setTravelDirection(225);
        }else if(getY()<=0){
            setTravelDirection(135);
        }
    }
}

void DamageableObject::setHitPoints(const double p){
    hitPoints = p;
}

double DamageableObject::getHitPoints() const{
    return hitPoints;
}

void DamageableObject::sufferDamage(double amount, int cause){
    setHitPoints(getHitPoints()-amount);
    if(cause==HIT_BY_SHIP)  getWorld()->playSound(SOUND_DEATH);
    if(cause==HIT_BY_PROJECTILE) getWorld()->playSound(SOUND_BLAST);
}

void Alien::setFlightPlanLength(const double length){
    flightPlanLength = length;
}

double Alien::getFlightPlanLength() const{
    return flightPlanLength;
}

void Actor::setTravelSpeed(const double speed){
    travelSpeed = speed;
}

double Actor::getTravelSpeed() const{
    return travelSpeed;
}


void Alien::setTravelDirection(const double direction){
    travelDirection = direction;
}

double Alien::getTravelDirection() const{
    return travelDirection;
}

Smallgon::Smallgon(StudentWorld* world, double startX, double startY): Alien(world, IID_SMALLGON, startX, startY){
    setHitPoints(5 *(1 + ((getWorld()->getLevel())-1) * 0.1));
    setFlightPlanLength(0);
    setTravelSpeed(2);
}

Smoregon::Smoregon(StudentWorld* world, double startX, double startY): Alien(world, IID_SMOREGON, startX, startY){
    setHitPoints(5 *(1 + ((getWorld()->getLevel())-1) * 0.1));
    setFlightPlanLength(0);
    setTravelSpeed(2);
}

Snagglegon::Snagglegon(StudentWorld* world, double startX, double startY):Alien(world, IID_SNAGGLEGON, startX, startY){
    setHitPoints(10 *(1 + ((getWorld()->getLevel())-1) * 0.1));
    setTravelDirection(225);
    setTravelSpeed(1.75);
}

void Explosion::doSomething(){
    setSize(1.5*getSize());
    currentTick++;
    
    if(currentTick>=5){
        setState(0);
    }
}

void ExtraLifeGoodie::doSomething(){
    //check if dead or needs to die
    if(this->getState()==0) return;
    if(this->getX()-getTravelSpeed()<0){
        this->setState(0);
        return;
    }
    
    //collisions
    NachenBlaster* d = getWorld()->collidedWithNach(this);
    if(d!=nullptr){
        getWorld()->increaseScore(100);
        this->setState(0);
        getWorld()->playSound(SOUND_GOODIE);
        getWorld()->incLives();
        return;
    }

    //move
    double newX = getX()-getTravelSpeed();
    double newY = getY()-getTravelSpeed();
    moveTo(newX, newY);
    
    //collisions
    d = getWorld()->collidedWithNach(this);
    if(d!=nullptr){
        getWorld()->increaseScore(100);
        this->setState(0);
        getWorld()->playSound(SOUND_GOODIE);
        getWorld()->incLives();
        return;
    }
}

void RepairGoodie::doSomething(){
    //check if dead or needs to die
    if(this->getState()==0) return;
    if(this->getX()-getTravelSpeed()<0){
        this->setState(0);
        return;
    }
    
    //collisions
    NachenBlaster* d = getWorld()->collidedWithNach(this);
    if(d!=nullptr){
        getWorld()->increaseScore(100);
        this->setState(0);
        getWorld()->playSound(SOUND_GOODIE);
        if(getWorld()->getNach()->getHitPoints()<=40){
            int currentPoints =getWorld()->getNach()->getHitPoints();
            getWorld()->getNach()->setHitPoints(10+currentPoints);
        }
        return;
    }
    
    //move
    double newX = getX()-getTravelSpeed();
    double newY = getY()-getTravelSpeed();
    moveTo(newX, newY);
    
    //collisions
    d = getWorld()->collidedWithNach(this);
    if(d!=nullptr){
        getWorld()->increaseScore(100);
        this->setState(0);
        getWorld()->playSound(SOUND_GOODIE);
        if(getWorld()->getNach()->getHitPoints()<=40){
            int currentPoints =getWorld()->getNach()->getHitPoints();
            getWorld()->getNach()->setHitPoints(10+currentPoints);
        }
        return;
    }

}

void FlatulenceTorpedoGoodie::doSomething(){
    //check if dead or needs to die
    if(this->getState()==0) return;
    if(this->getX()-getTravelSpeed()<0){
        this->setState(0);
        return;
    }
    
    //collisions
    NachenBlaster* d = getWorld()->collidedWithNach(this);
    if(d!=nullptr){
        getWorld()->increaseScore(100);
        this->setState(0);
        getWorld()->playSound(SOUND_GOODIE);
        int currentTorpedoes =getWorld()->getNach()->getTorpedoes();
        getWorld()->getNach()->setTorpedoes(5+currentTorpedoes);
        return;
    }
    
    //movement
    double newX = getX()-getTravelSpeed();
    double newY = getY()-getTravelSpeed();
    moveTo(newX, newY);
    
    //collisions
    //collisions
    d = getWorld()->collidedWithNach(this);
    if(d!=nullptr){
        getWorld()->increaseScore(100);
        this->setState(0);
        getWorld()->playSound(SOUND_GOODIE);
        int currentTorpedoes =getWorld()->getNach()->getTorpedoes();
        getWorld()->getNach()->setTorpedoes(5+currentTorpedoes);
        return;
    }
    
}

int NachenBlaster::getCabbagePoints(){
    return cabbagePoints;
}