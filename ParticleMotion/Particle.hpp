//
//  Particle.hpp
//  ParticleFlow
//
//  Created by Sahand Hariri on 9/22/15.
//  Copyright © 2015 Sahand Hariri. All rights reserved.
//

#ifndef Particle_hpp
#define Particle_hpp



#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "Domain.hpp"

using namespace std;

class Particle{
    
public:
    
    Particle(int id, Domain* D, double mass, double x, double y, double vx, double vy, double xf, double yf);
    
    void setID(int id);
    void setDomain(Domain* D);
    void setMass(double m);
    void setTime(double time);
    void setFx(double fx);
    void setFy(double fy);
    void setVx(double vx);
    void setVy(double vy);
    void setX(double x);
    void setY(double y);
    void setGx(double xf);
    void setGy(double yf);
    void setKE(double ke);
    void setPE(double pe);
    
    int getID();
    Domain* getDomain();
    double getMass();
    double getTime();
    double getFx();
    double getFy();
    double getVx();
    double getVy();
    double getX();
    double getY();
    double getGx();
    double getGy();
    double getKE();
    double getPE();
    
    void Move(double dt);
    double* Distance(Particle* p);
    double* Distance2(Particle* p);
    double* Dist(double x1, double x2, double y1, double y2);
    void ComputeParticleForce(vector<Particle*> part);
    void ComputeWallForce();
    void ComputeKE();
    void ComputePE();
    void Wall(double xp, double yp, double vxp, double vyp, double dt);
    
private:
    
    int _ID;
    Domain* _Domain;
    double _Mass;
    double _Time;
    double _Fx;
    double _Fy;
    double _Vx;
    double _Vy;
    double _X;
    double _Y;
    double _Gx;
    double _Gy;
    double _KE;
    double _PE;
    
    
};



#endif /* Particle_hpp */
