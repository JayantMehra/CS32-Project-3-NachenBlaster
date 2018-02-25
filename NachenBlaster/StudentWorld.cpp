#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

double euclideanDistance(double x1, double y1, double x2, double y2);
double collision(double x1, double y1, double x2, double y2, double r1, double r2);


GameWorld* createStudentWorld(string assetDir) {
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir) {
}

int StudentWorld::init() {
    
    shipsDestroyedSoFar = 0;
    currentShipsOnTheScreen = 0;
    maxShipsOnTheScreen = 4 + 0.5*getLevel();
    totalShipsToBeDestroyed = 6 + 4*getLevel();
    
    initializeStars();
    NachenB = new NachenBlaster(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, this, 50, 30, 1);

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
    
    if (shipsDestroyedSoFar == totalShipsToBeDestroyed)
        return GWSTATUS_FINISHED_LEVEL;
    
    if (!NachenB->getStatus()) {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    createNewStars();
    updateStatusBar();
    addShips();
    doSomething();
    deleteDeadActors();
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
    delete NachenB;
    for (int i = 0; i < actors.size(); i++) {
        delete actors[i];
        actors.erase(actors.begin() + i);
        i--;
    }
    NachenB = nullptr;
}

void StudentWorld::initializeStars() {
    for (size_t i = 0; i < 30; i++) {
        double x = randInt(0, VIEW_HEIGHT-1);
        double y = randInt(0, VIEW_HEIGHT-1);
        double size = (randInt(5, 50))/100.0;
        
        actors.push_back(new Star(IID_STAR,x,y,0,size,3,this, 1));
    }
}

void StudentWorld::createNewStars() {
    int newStarProbability = randInt(1, 15);
    if (newStarProbability == 13) {
        
        double x = VIEW_WIDTH-1;
        double y = randInt(0, VIEW_HEIGHT-1);
        double size = (randInt(5, 50))/100.0;
        
        actors.push_back(new Star(IID_STAR,x,y,0,size,3,this, 1));
    }
}

void StudentWorld::addShips() {
    if (currentShipsOnTheScreen < min(maxShipsOnTheScreen, totalShipsToBeDestroyed-shipsDestroyedSoFar)) {
        int s1 = 60;
        int s2 = 20 + getLevel()*5;
        int s3 = 5 + getLevel()*10;
        int s = s1+s2+s3;
        
        int rand = randInt(1, s);
        
        if (rand >= 1 && rand <= 60)
            actors.push_back(new Smallgon(IID_SMALLGON, VIEW_HEIGHT-1, randInt(1, VIEW_WIDTH-1), 0, 1.5, 1, this, 5*(1+(getLevel()-1)*0.1), 0, 2.0, 1));
        
        else if (rand > 60 && rand <= 60+s2)
            actors.push_back(new Smoregon(IID_SMOREGON, VIEW_HEIGHT-1, randInt(1, VIEW_WIDTH-1), 0, 1.5, 1, this, 5*(1+(getLevel()-1)*0.1), 0, 2.0, 1));
        
        else
            actors.push_back(new Snagglegon(IID_SNAGGLEGON, VIEW_HEIGHT-1, randInt(1, VIEW_WIDTH-1), 0, 1.5, 1, this, 10*(1+(getLevel()-1)*0.1), 0, 1.75, 1));
        
        currentShipsOnTheScreen++;
    }
}

void StudentWorld::updateStatusBar() {
    ostringstream oss;
    oss << "Lives: " << getLives();
    oss << setw(10) << "Health: ";
    oss << NachenB->getHitPoints() << "%";
    oss << setw(9) << "Score: ";
    oss << getScore();
    oss << setw(9) << "Level: ";
    oss << getLevel();
    oss << setw(11) << "Cabages: ";
    oss << NachenB->getEnergyPoints() << "%";
    oss << setw(13) << "Torpedoes: ";
    oss << NachenB->getFlatulenceTorperdoes();
    
    string GameStatusBar = oss.str();
    
    setGameStatText(GameStatusBar);
}

void StudentWorld::deleteDeadActors() {
    for (size_t i = 0; i < actors.size(); i++) {
        if (!actors[i]->getStatus()) {
            if (actors[i]->typeOfActor() == 'A')
                currentShipsOnTheScreen--;
            
            delete actors[i];
            actors.erase(actors.begin() + i);
            i--;
        }
    }
}

void StudentWorld::doSomething() {
    NachenB->doSomething();
    for (size_t i = 0; i < actors.size(); i++) {
        if (actors[i]->getStatus())
            actors[i]->doSomething();
    }
}

bool StudentWorld::AlienNBCollision(Alien* alien) {
    return collision(alien->getX(), alien->getY(), NachenB->getX(), NachenB->getY(), alien->getRadius(), NachenB->getRadius());
}

void StudentWorld::AlienNBCollisionAftermath(int damagePoints, int scoreIncrease, Alien* alien, char typeOfAlien) {
    NachenB->setHitPoints(-1*damagePoints);
    increaseScore(scoreIncrease);
    playSound(SOUND_DEATH);
    actors.push_back(new Explosion(IID_EXPLOSION, alien->getX(), alien->getY(), 0, 1, 0, this, 4));
    shipsDestroyedSoFar++;
    
    switch (typeOfAlien) {
        case '2': SmoregonDropGoodie(alien->getX(), alien->getY()); break;
        case '3': SnagglegonDropGoodie(alien->getX(), alien->getY()); break;
    }
}

bool StudentWorld::AlienProjectileCollision(Alien *alien, int scoreIncrease, char typeOfAlien) {
    for (size_t i = 0; i < actors.size(); i++) {
        if ((actors[i]->getStatus() && actors[i]->typeOfActor() == 'C') || (actors[i]->getStatus() && actors[i]->typeOfActor() == 'F' && actors[i]->getFiredBy() == 'N')) {
            if (collision(actors[i]->getX(), actors[i]->getY(), alien->getX(), alien->getY(), actors[i]->getRadius(), alien->getRadius())) {
                
                if (actors[i]->typeOfActor() == 'C')
                    alien->setHitPoints(-1*2);
                else
                    alien->setHitPoints(-1*8);
                
                actors[i]->setStatus(0);
                
                if (alien->getHitPoints() <= 0) {
                    alien->setStatus(0);
                    increaseScore(scoreIncrease);
                    playSound(SOUND_DEATH);
                    actors.push_back(new Explosion(IID_EXPLOSION, alien->getX(), alien->getY(), 0, 1, 0, this, 4));
                    shipsDestroyedSoFar++;
                    
                    switch (typeOfAlien) {
                        case '2': SmoregonDropGoodie(alien->getX(), alien->getY()); break;
                        case '3': SnagglegonDropGoodie(alien->getX(), alien->getY()); break;
                    }
                }
                else {
                    playSound(SOUND_BLAST);
                }
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::alienNearNachenBlaster(Alien *alien) {
    if (NachenB->getY() <= alien->getY() && abs(NachenB->getY()-alien->getY()) <= 4)
        return true;
    return false;
}

bool StudentWorld::turnipNBCollision(Turnip *turnip, int damagePoints) {
    if (collision(turnip->getX(), turnip->getY(), NachenB->getX(), NachenB->getY(), turnip->getRadius(),
                  NachenB->getRadius())) {
        NachenB->setHitPoints(-1*damagePoints);
        turnip->setStatus(0);
        return true;
    }
        
    return false;
}

bool StudentWorld::torpedoNBCollision(FlatulenceTorpedo *torpedo, int damagePoints) {
    if (collision(torpedo->getX(), torpedo->getY(), NachenB->getX(), NachenB->getY(), torpedo->getRadius(),
                  NachenB->getRadius()) && torpedo->getFiredBy() == 'S') {
        NachenB->setHitPoints(-1*damagePoints);
        torpedo->setStatus(0);
        return true;
    }
    
    return false;
}

bool StudentWorld::goodiePickup(Goodie *goodie, char type) {
    if (collision(goodie->getX(), goodie->getY(), NachenB->getX(), NachenB->getY(), goodie->getRadius(),
                  NachenB->getRadius())) {
        increaseScore(100);
        playSound(SOUND_GOODIE);
        goodie->setStatus(0);
        switch (type) {
            case 'E': incLives(); break;
            case 'R': NachenB->setHitPoints(10); break;
            case 'F': NachenB->increaseFlatulenceTorpedoes();
        }
        return true;
    }
    return false;
}

void StudentWorld::SmoregonDropGoodie(double x, double y) {
    int rand = randInt(1, 3);
    if (rand == 1) {
        int rand2 = randInt(1, 2);
        if (rand2 == 1)
            actors.push_back(new Repair(IID_REPAIR_GOODIE, x, y, 0, 0.5, 1, this, 1, 'R'));
        else
            actors.push_back(new FlatulenceTorpedo(IID_TORPEDO_GOODIE, x, y, 0, 0.5, 1, this, 1, 'F'));
    }
}

void StudentWorld::SnagglegonDropGoodie(double x, double y) {
    int rand = randInt(1, 6);
    if (rand == 1) {
        actors.push_back(new ExtraLife(IID_LIFE_GOODIE, x, y, 0, 0.5, 1, this, 1, 'E'));
    }
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

double collision(double x1, double y1, double x2, double y2, double r1, double r2) {
    return euclideanDistance(x1, y1, x2, y2) < 0.75*(r1+r2);
}

double euclideanDistance(double x1, double y1, double x2, double y2) {
    return sqrt((pow(x1-x2,2) + pow(y1-y2,2)));
}


