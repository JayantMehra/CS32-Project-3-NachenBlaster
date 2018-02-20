#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;



GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
}

int StudentWorld::init() {
    
    //  CREATE STARS
    initializeStars();
    NachenB = new NachenBlaster(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, this, 50, 30);
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
    
    createNewStars();
    ostringstream oss;
    oss << "Lives: " << getLives();
    //<< setw(10) << "Health: " << "100%" << setw(9) << "Score: " << 24530 << setw(9) << "Level: " << getLevel() <<
    //setw(12) << "Cabages: " << "80%" << setw(13) << "Torpedoes: " << "4\n";
    oss << setw(10) << "Health: ";
    oss << "100%";
    oss << setw(9) << "Score: ";
    oss << 24530;
    oss << setw(9) << "Level: ";
    oss << getLevel();
    oss << setw(11) << "Cabages: ";
    oss << "80%";
    oss << setw(13) << "Torpedoes: ";
    oss << "4\n";
    
    string GameStatusBar = oss.str();
    
    setGameStatText(GameStatusBar);
    
    NachenB->doSomething();
    for (size_t i = 0; i < actors.size(); i++) {
        if (actors[i]->getStatus())
            actors[i]->doSomething();
    }
    
    for (size_t i = 0; i < actors.size(); i++) {
        if (!actors[i]->getStatus()) {
            delete actors[i];
            actors.erase(actors.begin() + i);
            i--;
        }
    }
    
    //decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}

void StudentWorld::initializeStars() {
    for (size_t i = 0; i < 30; i++) {
        
        double x = randInt(0, VIEW_HEIGHT-1);
        double y = randInt(0, VIEW_HEIGHT-1);
        double size = (randInt(5, 50))/100.0;
        
        actors.push_back(new Star(IID_STAR,x,y,0,size,3,this));
    }
}

void StudentWorld::createNewStars() {
    int newStarProbability = randInt(1, 15);
    if (newStarProbability == 13) {
        
        double x = VIEW_WIDTH-1;
        double y = randInt(0, VIEW_HEIGHT-1);
        double size = (randInt(5, 50))/100.0;
        
        actors.push_back(new Star(IID_STAR,x,y,0,size,3,this));
    }
}
