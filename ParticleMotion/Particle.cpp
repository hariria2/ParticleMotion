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
    
    double xp = _X;
    double yp = _Y;
    
    double vxp = _Vx;
    double vyp = _Vy;
    
    _Vx = _Vx + dt*(-0.0/_Mass *pow(_Vx,2) + _Fx/_Mass);
    _Vy = _Vy + dt*(-0.0/_Mass *pow(_Vy,2) + _Fy/_Mass);
    
    _X = _X + dt*_Vx;
    _Y = _Y + dt*_Vy;
    
    Wall(xp,yp,vxp,vyp,dt);
    
    
    
    //    if(_X <= 0){
    //        _X = _Domain->Boundary[0][1] - _X;
    //    }else if(_X > _Domain->Boundary[0][1]) {
    //        _X = _X - _Domain->Boundary[0][1];
    //    }
    //
    //    if(_Y <= 0){
    //        _Y = _Domain->Boundary[1][1] - _Y;
    //    }else if(_Y > _Domain->Boundary[1][1]) {
    //        _Y = _Y - _Domain->Boundary[1][1];
    //    }
}
double* Particle::Distance(Particle* p){
    double* r = new double[2];
    // order matters here.
    double xdiff = p->getX() - _X;
    double ydiff = p->getY() - _Y;
    r[0] = sqrt(pow(xdiff,2) + pow(ydiff,2));
    r[1] = atan2(ydiff, xdiff);
    return r;
};
void Particle::ComputeParticleForce(vector<Particle*> part){
    double* dist = new double[2];
    
    for(auto p = part.cbegin(); p != part.cend(); ++p){
        dist = Distance(*p);
        
        if (dist[0] < 1e-10){
            _Fx += 0;
            _Fy += 0;
        }else {
            _Fx += (_Gx*_Mass*((*p)->getMass())/pow(dist[0],2))*cos(dist[1]);
            _Fy += (_Gy*_Mass*((*p)->getMass())/pow(dist[0],2))*sin(dist[1]);
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

