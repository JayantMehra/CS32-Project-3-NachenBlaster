#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp


class Actor;
class NachenBlaster;
class Alien;
class Cabage;
class Turnip;
class FlatulenceTorpedo;
class Goodie;

class StudentWorld : public GameWorld {
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void addActor(Actor* newActor);
    bool AlienNBCollision(Alien* alien);
    void AlienNBCollisionAftermath(int damagePoints, int scoreIncrease, Alien* alien, char typeOfAlien);
    bool AlienProjectileCollision(Alien *alien, int scoreIncrease, char typeOfAlien);
    bool alienNearNachenBlaster(Alien* alien);
    bool turnipNBCollision(Turnip* turnip, int damagePoints);
    bool torpedoNBCollision(FlatulenceTorpedo* torpedo, int damagePoints);
    bool goodiePickup(Goodie* goodie, char type);
    ~StudentWorld();

private:
    void initializeStars();
    void createNewStars();
    void updateStatusBar();
    void addShips();
    void deleteDeadActors();
    int doSomething();
    void SmoregonDropGoodie(double x, double y);
    void SnagglegonDropGoodie(double x, double y);
    
    std::vector<Actor*> actors;
    NachenBlaster* NachenB;
    int shipsDestroyedSoFar;
    int totalShipsToBeDestroyed;
    int maxShipsOnTheScreen;
    int currentShipsOnTheScreen;
    int scoreOnCurrentLevel;
};

inline
void StudentWorld::addActor(Actor *newActor) {
    actors.push_back(newActor);
}

#endif // STUDENTWORLD_H_
