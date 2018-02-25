#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


void Star::doSomething() {

    double currentX = getX();
    double currentY = getY();
    
    moveTo(currentX-1, currentY);
    
    if (getX() == -1)
        setStatus(0);
}

void NachenBlaster::setHitPoints(int hit_points) {
    m_hit_points += hit_points;
    if (m_hit_points > 50)
        m_hit_points = 50;
}

void NachenBlaster::doSomething() {
    if (!getStatus())
        return;
    
    if (m_hit_points <= 0)
        setStatus(0);
    
    if (m_energy_points < 30)
        m_energy_points++;
    
    int val;
    getWorld()->getKey(val);
    
    
    //  MOVE OR SHOOT
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
            break;
        case KEY_PRESS_SPACE: {
            if (m_energy_points >= 5) {
                getWorld()->addActor(new Cabage(IID_CABBAGE, getX()+12, getY(), 0, 0.5, 1, getWorld(), 1));
                m_energy_points -= 5;
                getWorld()->playSound(SOUND_PLAYER_SHOOT);
            }
        }
            break;
        case KEY_PRESS_TAB: {
            if (m_flatulence_torpedoes > 0) {
                getWorld()->addActor(new FlatulenceTorpedo(IID_TORPEDO, getX()+12, getY(), 0, 0.5, 1, getWorld(), 1, 'N'));
                m_flatulence_torpedoes--;
                getWorld()->playSound(SOUND_TORPEDO);
            }
        }
    }
    
    if (m_energy_points < 30)
        m_energy_points++;
}

void Explosion::doSomething() {
    setSize(getSize()*1.5);
    int set = getStatus() - 1;
    setStatus(set);
}

void Alien::doSomething() {
    
    if (!getStatus())
        return;
    
    if (getX() < 0) {
        setStatus(0);
        return;
    }
    
    if (m_hit_points <= 0) {
        setStatus(0);
        return;
    }
    
    if (checkForCollisionWithNB())
        return;
    
    if (checkForCollisionWithProjectile())
        return;
    
    if (getFlightPlan() == 0 || getY() == 0 || getY() == VIEW_HEIGHT-1) {
        if (getY() >= VIEW_HEIGHT-1)
            setDirection(225);  // DOWN AND LEFT
        else if (getY() <= 0)
            setDirection(135);   // UP AND LEFT
        else {
            int randomDirection = randInt(1, 3);
            switch (randomDirection) {
                case 1 : setDirection(0); break;
                case 2 : setDirection(225); break;
                case 3 : setDirection(135);
            }
        }
        setFlightPlan(randInt(1, 32));
    }
    
    if (getWorld()->alienNearNachenBlaster(this)) {
        if (fireProjectile())
            return;
    }
    
    setFlightPlan(getFlightPlan()-1);
    double speed = getSpeed();
    if (getDirection() == 225)
        moveTo(getX() - speed, getY() - speed);
    
    else if (getDirection() == 135)
        moveTo(getX() - speed, getY() + speed);
    
    else
        moveTo(getX() - speed, getY());
    
    if (checkForCollisionWithNB())
        return;
    
    if (checkForCollisionWithProjectile())
        return;
}

bool Smallgon::checkForCollisionWithNB() {
    if (getWorld()->AlienNBCollision(this)) {
        getWorld()->AlienNBCollisionAftermath(5, 250, this, '1');
        setStatus(0);
        return true;
    }
    return false;
}

bool Smallgon::checkForCollisionWithProjectile() {
    if (getWorld()->AlienProjectileCollision(this, 250, '1'))
        return true;
    return false;
}

bool Smallgon::fireProjectile() {
    int rand = randInt(1, (20/getWorld()->getLevel())+5);
    if (rand == 1) {
        getWorld()->addActor(new Turnip(IID_TURNIP, getX()-14, getY(), 0, 0.5, 1, getWorld(), 1));
        getWorld()->playSound(SOUND_ALIEN_SHOOT);
        return true;
    }
    return false;
}

bool Smoregon::checkForCollisionWithNB() {
    if (getWorld()->AlienNBCollision(this)) {
        getWorld()->AlienNBCollisionAftermath(5, 250, this, '2');
        setStatus(0);
        return true;
    }
    return false;
}

bool Smoregon::checkForCollisionWithProjectile() {
    if (getWorld()->AlienProjectileCollision(this, 250, '2'))
        return true;
    return false;
}

bool Smoregon::fireProjectile() {
    int rand = randInt(1, (20/getWorld()->getLevel())+5);
    if (rand == 1) {
        getWorld()->addActor(new Turnip(IID_TURNIP, getX()-14, getY(), 0, 0.5, 1, getWorld(), 1));
        getWorld()->playSound(SOUND_ALIEN_SHOOT);
        return true;
    }
    if (rand == 2) {
        setDirection(0);
        setFlightPlan(VIEW_WIDTH);
        setSpeed(5);
    }
    return false;
}


bool Snagglegon::checkForCollisionWithNB() {
    if (getWorld()->AlienNBCollision(this)) {
        getWorld()->AlienNBCollisionAftermath(15, 1000, this, '3');
        setStatus(0);
        return true;
    }
    return false;
}

bool Snagglegon::checkForCollisionWithProjectile() {
    if (getWorld()->AlienProjectileCollision(this, 1000, '3'))
        return true;
    return false;
}

bool Snagglegon::fireProjectile() {
    int rand = randInt(1, (15/getWorld()->getLevel())+10);
    if (rand == 1) {
        getWorld()->addActor(new FlatulenceTorpedo(IID_TORPEDO, getX()-14, getY(), 180, 0.5, 1, getWorld(), 1, 'S'));
        getWorld()->playSound(SOUND_ALIEN_SHOOT);
        return true;
    }
    return false;
}


void Projectile::doSomething() {
    if (!getStatus())
        return;
    
    if (getX() >= VIEW_WIDTH) {
        setStatus(0);
        return;
    }
    
    moveAndCheckForCollision();
}

void Cabage::moveAndCheckForCollision() {

    moveTo(getX()+8, getY());
    setDirection(getDirection()-20);
}

void Turnip::moveAndCheckForCollision() {
    
    if (getWorld()->turnipNBCollision(this, 2))
        return;
    
    moveTo(getX()-6, getY());
    setDirection(getDirection()-20);
}

void FlatulenceTorpedo::moveAndCheckForCollision() {
    
    if (getWorld()->torpedoNBCollision(this, 8))
        return;
    
    if (getFiredBy() == 'S')
        moveTo(getX()-8, getY());
    else
        moveTo(getX()+8, getY());
    
}

void Goodie::doSomething() {
    if (!getStatus())
        return;
    
    if (getX() <= 0 || getY() <= 0){
        setStatus(0);
        return;
    }
    
    if (getWorld()->goodiePickup(this, m_type))
        return;
    
    moveTo(getX()-0.75, getY()-0.75);
    
    if (getWorld()->goodiePickup(this, m_type))
        return;
    
}

