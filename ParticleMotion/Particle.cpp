//
//  Particle.cpp
//  ParticleFlow
//
//  Created by Sahand Hariri on 9/22/15.
//  Copyright © 2015 Sahand Hariri. All rights reserved.
//

#include "Particle.hpp"

using namespace std;

Particle::Particle(int id, Domain* D, double mass, double x, double y, double vx, double vy, double fx, double fy){
    setID(id);
    setDomain(D);
    setMass(mass);
    setX(x);
    setY(y);
    setVx(vx);
    setVy(vy);
    setFx(fx);
    setFy(fy);
};


void Particle::setID(int id){
    _ID = id;
}
void Particle::setDomain(Domain* D){
    _Domain = D;
}
void Particle::setMass(double m){
    _Mass = m;
}
void Particle::setTime(double time){
    _Time = time;
}
void Particle::setFx(double fx){
    _Fx = fx;
}
void Particle::setFy(double fy){
    _Fy = fy;
}
void Particle::setVx(double vx){
    _Vx = vx;
}
void Particle::setVy(double vy){
    _Vy = vy;
}
void Particle::setX(double x){
    _X = x;
};
void Particle::setY(double y){
    _Y = y;
};
void Particle::setGx(double xf){
    _Gx = xf;
}
void Particle::setGy(double yf){
    _Gy = yf;
}
void Particle::setKE(double ke){
    _KE = ke;
}
void Particle::setPE(double pe){
    _PE = pe;
}

int Particle::getID(){
    return _ID;
}
Domain* Particle::getDomain(){
    return _Domain;
}
double Particle::getMass(){
    return _Mass;
}
double Particle::getTime(){
    return _Time;
}
double Particle::getFx(){
    return _Fx;
}
double Particle::getFy(){
    return _Fy;
}
double Particle::getVx(){
    return _Vx;
}
double Particle::getVy(){
    return _Vy;
}
double Particle::getX(){
    return _X;
}
double Particle::getY(){
    return _Y;
}
double Particle::getGx(){
    return _Gx;
}
double Particle::getGy(){
    return _Gy;
}
double Particle::getKE(){
    return _KE;
}
double Particle::getPE(){
    return _PE;
}

void Particle::Move(double dt){
    string domainType = _Domain->getType();
    
    double xp = _X;
    double yp = _Y;
    
    double vxp = _Vx;
    double vyp = _Vy;
    
    _Vx = _Vx + dt*(-0.0/_Mass *pow(_Vx,2) + _Fx/_Mass);
    _Vy = _Vy + dt*(-0.0/_Mass *pow(_Vy,2) + _Fy/_Mass);
    
    _X = _X + dt*_Vx;
    _Y = _Y + dt*_Vy;
    
    if (domainType == "Wall"){
        Wall(xp,yp,vxp,vyp,dt);
    } else if (domainType == "Torus") {
        _X = fmod(_X + _Domain->Boundary[0][1], _Domain->Boundary[0][1]);
        _Y = fmod(_Y + _Domain->Boundary[1][1], _Domain->Boundary[1][1]);
    }
    
}
double* Particle::Distance(Particle* p){
    double* r = new double[2];
    // order matters here.
    double xdiff = p->getX() - _X;
    double ydiff = p->getY() - _Y;
    r[0] = sqrtf(powf(xdiff,2) + powf(ydiff,2));
    r[1] = atan2f(ydiff, xdiff);
    return r;
};
double* Particle::Distance2(Particle* p){
    double* r = new double[2];
    // order matters here.
    double xdiff = _Domain->Boundary[0][1] - abs(p->getX() - _X);
    double ydiff = _Domain->Boundary[1][1] - abs(p->getY() - _Y);
    r[0] = sqrtf(powf(xdiff,2) + powf(ydiff,2));
    r[1] = atan2f(ydiff, xdiff);
    return r;
};

double* Particle::Dist(double x1, double x2, double y1, double y2){
    double* r = new double[2];
    // order matters here.
    double xdiff = x1-x2;
    double ydiff = y1-y2;
    r[0] = sqrtf(powf(xdiff,2) + powf(ydiff,2));
    r[1] = atan2f(ydiff, xdiff);
    return r;
};

void Particle::ComputeParticleForce(vector<Particle*> part){
    double* dist = new double[2];
    double* d1 = new double[2];
    double* d2 = new double[2];
    double* d3 = new double[2];
    double* d4 = new double[2];
    double bx1 = _Domain->Boundary[0][0];
    double bx2 = _Domain->Boundary[0][1];
    double by1 = _Domain->Boundary[1][0];
    double by2 = _Domain->Boundary[1][1];
    
    string domainType = _Domain->getType();
    
    for(auto p = part.cbegin(); p != part.cend(); ++p){
        dist = Dist((*p)->getX(),_X, (*p)->getY(),_Y);
        
        
        if (domainType=="Wall"){
            if (dist[0] < 1e-10){
                _Fx += 0;
                _Fy += 0;
            }else {
                _Fx += -(_Gx*_Mass*((*p)->getMass())/powf(dist[0],2))*cosf(dist[1]);
                _Fy += -(_Gy*_Mass*((*p)->getMass())/powf(dist[0],2))*sinf(dist[1]);
            }
        } else if (domainType=="Torus"){
            
            d1 = Dist((*p)->getX()-bx1,_X-bx1,(*p)->getY()-by1, _Y-by1);
            d2 = Dist((*p)->getX()-bx1,_X-bx2,(*p)->getY()-by1, _Y-by2);
            d3 = Dist((*p)->getX()-bx1,bx1-_X,(*p)->getY()-by1, by1-_Y);
            d4 = Dist(bx2-(*p)->getX(),_X-bx2,by2-(*p)->getY(), _Y-by2);
            
            if (d1[0] < 1e-10){
                _Fx += 0;
                _Fy += 0;
            }else {
                _Fx += -_Gx*_Mass*((*p)->getMass())*(cosf(d1[1])/powf(d1[0],2)+cosf(d2[1])/powf(d2[0],2)+cosf(d3[1])/powf(d3[0],2)+cosf(d4[1])/powf(d4[0],2));
                _Fy += -_Gy*_Mass*((*p)->getMass())*(sinf(d1[1])/powf(d1[0],2)+sinf(d2[1])/powf(d2[0],2)+sinf(d3[1])/powf(d3[0],2)+sinf(d4[1])/powf(d4[0],2));
            }
        }
    }
}
void Particle::ComputeWallForce(){
    double topDist = _Domain->Boundary[1][1] - _Y;;
    double bottomDist = _Y - _Domain->Boundary[1][0];
    double leftDist = _X - _Domain->Boundary[0][0];
    double rightDist = _Domain->Boundary[0][1] - _X;
    
    if (topDist < 1e-1){
        if (_Vy >0){
            _Vy = -_Vy;
        }
        _Fy += 0;
    }
    if (bottomDist < 1e-1){
        if (_Vy < 0){
            _Vy = -_Vy;
        }
        _Fy += 0;
    }else{
        //_Fy += -10*_YFactor*_Mass/pow(topDist,2);
        //_Fy +=  10*_YFactor*_Mass/pow(bottomDist,2);
    }
    if (leftDist < 1e-1){
        if (_Vx < 0){
            _Vx = -_Vx;
        }
    }
    if (rightDist < 1e-1){
        if (_Vx > 0){
            _Vx = -_Vx;
        }
    }
    
}
void Particle::ComputeKE(){
    
    double Vsqrd = pow(_Vx,2)+pow(_Vy,2);
    _KE = 0.5*_Mass*Vsqrd;
}
void Particle::ComputePE(){
    
}
void Particle::Wall(double xp, double yp, double vxp, double vyp, double dt){
    if (xp > _Domain->Boundary[0][0] & _X < _Domain->Boundary[0][0]){
        _Vx = -vxp;
        _X = xp + dt*_Vx;
    }else if(xp < _Domain->Boundary[0][1] & _X > _Domain->Boundary[0][1]){
        _Vx = -vxp;
        _X = xp + dt*_Vx;
    }
    if (yp > _Domain->Boundary[1][0] & _Y < _Domain->Boundary[1][0]){
        _Vy = -vyp;
        _Y = yp + dt*_Vy;
    }else if(yp < _Domain->Boundary[1][1] & _Y > _Domain->Boundary[1][1]){
        _Vy = -vyp;
        _Y = yp + dt*_Vy;
    }
}

