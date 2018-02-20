#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class Actor: public GraphObject {
public:
    Actor(int imageID, double startX, double startY,
          int dir, double size, int depth, GameWorld* ptr): GraphObject(imageID,startX,
                                                                     startY, dir, size,depth) {
        pointerToWorld = ptr;
        m_status = 1;
    }
    
    bool getStatus();
    void setStatus(bool status);
    GameWorld* getWorld();
    virtual void doSomething() = 0;
private:
    bool m_status;
    GameWorld* pointerToWorld;
};

class NachenBlaster: public Actor {
public:
    NachenBlaster(int imageID, double startX, double startY,
         int dir, double size, int depth, GameWorld* ptr, int hit_points, int energy_points): Actor(imageID,startX,
                                                                 startY, dir, size,depth, ptr) {
        m_hit_points = hit_points;
        m_energy_points = energy_points;
    }
    virtual void doSomething();
private:
    int m_hit_points;
    int m_energy_points;
};

class Star: public Actor {
public:
    Star(int imageID, double startX, double startY,
         int dir, double size, int depth, GameWorld* ptr): Actor(imageID,startX,
                                                               startY, dir, size,depth, ptr) {}
    
    virtual void doSomething();
};


inline
bool Actor::getStatus() {
    return m_status;
}

inline
void Actor::setStatus(bool status) {
    m_status = status;
}

inline
GameWorld* Actor::getWorld() {
    return pointerToWorld;
}

#endif // ACTOR_H_
