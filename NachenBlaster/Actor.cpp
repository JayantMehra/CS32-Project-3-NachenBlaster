#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


void Star::doSomething() {
    double currentX = getX();
    double currentY = getY();
    
    //double moveBy = randInt(9.5, 10)/10.0;
    
    moveTo(currentX-1, currentY);
    
    if (getX() == -1)
        setStatus(0);
}

void NachenBlaster::doSomething() {
    if (!getStatus())
        return;
    
    int val;
    getWorld()->getKey(val);
    
    switch(val) {
        case KEY_PRESS_LEFT: {
            if (getX()-6 >= 0)
                moveTo(getX()-6, getY());
        }
            break;
        case KEY_PRESS_RIGHT: {
            if (getX()+6 < VIEW_WIDTH)
                moveTo(getX()+6, getY());
        }
            break;
        case KEY_PRESS_DOWN: {
            if (getY()-6 >= 0)
                moveTo(getX(), getY()-6);
        }
            break;
        case KEY_PRESS_UP: {
            if (getY()+6 < VIEW_HEIGHT)
                moveTo(getX(), getY()+6);
        }
    }
}

