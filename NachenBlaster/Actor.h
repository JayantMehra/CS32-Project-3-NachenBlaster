#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


//  Abstract class from which all game objects are derived
class Actor: public GraphObject {
public:
    Actor(int imageID, double startX, double startY,
          int dir, double size, int depth, StudentWorld* ptr, int status): GraphObject(imageID,startX,
                                                                     startY, dir, size, depth) {
        pointerToWorld = ptr;
        m_status = status;
    }
    
    int getStatus();
    void setStatus(int status);
    StudentWorld* getWorld();
    virtual void doSomething() = 0;
    virtual char typeOfActor() = 0;
    virtual char getFiredBy();
private:
    int m_status;
    StudentWorld* pointerToWorld;
};
//  END OF ACTOR ABSTRACT CLASS

//  CLASS NACHENBLASTER
class NachenBlaster: public Actor {
public:
    NachenBlaster(int imageID, double startX, double startY,
         int dir, double size, int depth, StudentWorld* ptr, int hit_points, int energy_points, int status): Actor(imageID,startX, startY, dir, size, depth, ptr, status) {
        m_hit_points = hit_points;
        m_energy_points = energy_points;
        m_flatulence_torpedoes = 0;
    }
    virtual void doSomething();
    virtual char typeOfActor();
    int getHitPoints();
    void setHitPoints(int hit_points);
    int getEnergyPoints();
    void setEnergyPoints(int energy_points);
    int getFlatulenceTorperdoes();
    void increaseFlatulenceTorpedoes();
private:
    int m_hit_points;
    int m_energy_points;
    int m_flatulence_torpedoes;
};
// END OF CLASS NACHENBLASTER


//  CLASS STAR
class Star: public Actor {
public:
    Star(int imageID, double startX, double startY,
         int dir, double size, int depth, StudentWorld* ptr, int status): Actor(imageID,startX,
                                                               startY, dir, size,depth, ptr, status) {}
    
    virtual void doSomething();
    virtual char typeOfActor();
};
//  END OF CLASS STAR

class Alien: public Actor {
public:
    Alien(int imageID, double startX, double startY,
          int dir, double size, int depth, StudentWorld* ptr, int hit_points,
          int flightPlan, double speed, int status): Actor(imageID,startX,
                                               startY, dir, size,depth, ptr, status){
        m_hit_points = hit_points;
        m_flight_plan = flightPlan;
        m_speed = speed;
    }
    virtual void doSomething();
    virtual char typeOfActor();
    bool collision();
    int getFlightPlan();
    void setFlightPlan(int f_p);
    double getSpeed();
    void setSpeed(double speed);
    int getHitPoints();
    void setHitPoints(int hit_points);
private:
    virtual bool checkForCollisionWithNB() = 0;
    virtual bool checkForCollisionWithProjectile() = 0;
    virtual bool fireProjectile() = 0;
    int m_hit_points;
    int m_flight_plan;
    double m_speed;
};

class Smallgon: public Alien {
public:
    Smallgon(int imageID, double startX, double startY,
          int dir, double size, int depth, StudentWorld* ptr, int hit_points,
          int flightPlan, double speed, int status): Alien(imageID,startX,
                                               startY, dir, size, depth, ptr, hit_points, flightPlan, speed, status){}
    virtual bool checkForCollisionWithNB();
    virtual bool checkForCollisionWithProjectile();
    virtual bool fireProjectile();
};

class Smoregon: public Alien {
public:
    Smoregon(int imageID, double startX, double startY,
             int dir, double size, int depth, StudentWorld* ptr, int hit_points,
             int flightPlan, double speed, int status): Alien(imageID,startX,
    startY, dir, size, depth, ptr, hit_points, flightPlan, speed, status){}
    virtual bool checkForCollisionWithNB();
    virtual bool checkForCollisionWithProjectile();
    virtual bool fireProjectile();
};

class Snagglegon: public Alien {
public:
    Snagglegon(int imageID, double startX, double startY,
             int dir, double size, int depth, StudentWorld* ptr, int hit_points,
             int flightPlan, double speed, int status): Alien(imageID,startX,
    startY, dir, size, depth, ptr, hit_points, flightPlan, speed, status){}
    virtual bool checkForCollisionWithNB();
    virtual bool checkForCollisionWithProjectile();
    virtual bool fireProjectile();
};

class Projectile: public Actor {
public:
    Projectile(int imageID, double startX, double startY, int dir,
               double size, int depth, StudentWorld* ptr, int status): Actor(imageID,startX, startY, dir, size, depth, ptr, status) {}
    virtual void doSomething();
    virtual char typeOfActor();
private:
    virtual void moveAndCheckForCollision() = 0;

};

class Cabage: public Projectile {
public:
    Cabage(int imageID, double startX, double startY,
              int dir, double size, int depth, StudentWorld* ptr, int status): Projectile (imageID, startX, startY, dir,
                                                                                           size, depth, ptr, status)
    {}
    //virtual void doSomething();
    virtual char typeOfActor();
    virtual void moveAndCheckForCollision();
};

class Turnip: public Projectile {
public:
    Turnip(int imageID, double startX, double startY,
           int dir, double size, int depth, StudentWorld* ptr, int status): Projectile (imageID, startX, startY, dir,
    size, depth, ptr, status)
    {}
    //virtual void doSomething();
    virtual char typeOfActor();
    virtual void moveAndCheckForCollision();
};

class FlatulenceTorpedo: public Projectile {
public:
    FlatulenceTorpedo(int imageID, double startX, double startY,
           int dir, double size, int depth, StudentWorld* ptr, int status, char firedBy): Projectile (imageID, startX, startY, dir,
                                                                                        size, depth, ptr, status)
    {
        m_fired_by = firedBy;
    }
    //virtual void doSomething();
    virtual char typeOfActor();
    virtual void moveAndCheckForCollision();
    char getFiredBy();
private:
    char m_fired_by;
};

class Explosion: public Actor {
public:
    Explosion(int imageID, double startX, double startY,
              int dir, double size, int depth, StudentWorld* ptr, int status): Actor(imageID,startX,
                                                                                     startY, dir, size,depth, ptr, status)
    {}
    virtual void doSomething();
    virtual char typeOfActor();
};

class Goodie: public Actor {
public:
    Goodie(int imageID, double startX, double startY, int dir,
               double size, int depth, StudentWorld* ptr, int status, char type): Actor(imageID,startX, startY, dir, size, depth, ptr, status) {
        m_type = type;
    }
    virtual void doSomething();
    virtual char typeOfActor() = 0;
    virtual char getType();
private:
    //virtual bool checkForPickup() = 0;
    char m_type;
};

class ExtraLife: public Goodie {
public:
    ExtraLife(int imageID, double startX, double startY, int dir,
              double size, int depth, StudentWorld* ptr, int status, char type) : Goodie(imageID, startX, startY, dir, size, depth, ptr, status, type)
    {}
    
    virtual char typeOfActor();
    
};

class Repair: public Goodie {
public:
    Repair(int imageID, double startX, double startY, int dir,
              double size, int depth, StudentWorld* ptr, int status, char type) : Goodie(imageID, startX, startY, dir, size, depth, ptr, status, type)
    {}
    
    virtual char typeOfActor();
    
};

class Torpedo: public Goodie {
public:
    Torpedo(int imageID, double startX, double startY, int dir,
           double size, int depth, StudentWorld* ptr, int status, char type) : Goodie(imageID, startX, startY, dir, size, depth, ptr, status, type)
    {}
    
    virtual char typeOfActor();
    
};

inline
char Actor::getFiredBy() {
    return '-';
}

inline
int Actor::getStatus() {
    return m_status;
}

inline
void Actor::setStatus(int status) {
    m_status = status;
}

inline
StudentWorld* Actor::getWorld() {
    return pointerToWorld;
}

inline
int NachenBlaster::getHitPoints() {
    int x = (100*m_hit_points)/50;
    return x;
}

inline
int NachenBlaster::getEnergyPoints() {
    int x = (100*m_energy_points)/30;
    return x;
}

inline
int NachenBlaster::getFlatulenceTorperdoes() {
    return m_flatulence_torpedoes;
}

inline
void NachenBlaster::increaseFlatulenceTorpedoes() {
    m_flatulence_torpedoes += 5;
}

inline
int Alien::getFlightPlan() {
    return m_flight_plan;
}

inline
void Alien::setFlightPlan(int f_p) {
    m_flight_plan = f_p;
}

inline
double Alien::getSpeed() {
    return m_speed;
}

inline
void Alien::setSpeed(double speed) {
    m_speed = speed;
}

inline
int Alien::getHitPoints() {
    return m_hit_points;
}

inline
void Alien::setHitPoints(int hit_points) {
    m_hit_points += hit_points;
}

inline
char NachenBlaster::typeOfActor() {
    return 'N';
}

inline
char Star::typeOfActor() {
    return 'S';
}

inline
char Alien::typeOfActor() {
    return 'A';
}

inline
char Explosion::typeOfActor() {
    return 'E';
}

inline
char Projectile::typeOfActor() {
    return 'P';
}

inline
char Cabage::typeOfActor() {
    return 'C';
}

inline
char Turnip::typeOfActor() {
    return 'T';
}

inline
char FlatulenceTorpedo::typeOfActor() {
    return 'F';
}

inline
char ExtraLife::typeOfActor() {
    return 'L';
}

inline
char Repair::typeOfActor() {
    return 'R';
}

inline
char Torpedo::typeOfActor() {
    return 'O';
}

inline
char Goodie::getType() {
    return m_type;
}

inline
char FlatulenceTorpedo::getFiredBy() {
    return m_fired_by;
}
#endif // ACTOR_H_

