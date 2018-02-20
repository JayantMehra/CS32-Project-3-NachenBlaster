#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp


class Actor;
class NachenBlaster;

class StudentWorld : public GameWorld {
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void initializeStars();
    void createNewStars();

private:
    std::vector<Actor*> actors;
    NachenBlaster* NachenB;
};

#endif // STUDENTWORLD_H_
