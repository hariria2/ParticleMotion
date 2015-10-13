//
//  Architect.hpp
//  ParticleFlow
//
//  Created by Sahand Hariri on 9/23/15.
//  Copyright © 2015 Sahand Hariri. All rights reserved.
//

#ifndef Architect_hpp
#define Architect_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include "Domain.hpp"
#include "Particle.hpp"
#include "Storage.hpp"
#include "Visualization.hpp"
#include <unistd.h>


class Architect{
    
public:
    
    Architect(Domain* D, vector<Particle*> ps, double dt, double te, Visualization* vis, Storage* db);
    
    int _StorageQ = 0;
    
    void setTime(double time);
    void setTimeStep(double dt);
    void setEndTime(double te);
    void setParticles(vector<Particle*> ps);
    void setStorage(Storage* storage);
    void setVisualization(Visualization* vis);
    
    double getTime();
    double getTimeStep();
    double getEndTime();
    vector<Particle*> getParticles();
    Visualization* getVisualization();

    void Update(int storageq);
    void Update();
    void Simulate();
    void ComputeParticleForce(vector<Particle*>);
    double* Distance(Particle* p1, Particle* p2);
    
    void PrepDB();
    
private:
    
    double _Time;
    double _TimeStep;
    double _EndTime;
    vector<Particle*> _Particles;
    Domain _Domain;
    vector<vector<int>> _ParticleForceMatrixX;
    vector<vector<int>> _ParticleForceMatrixY;
    Storage* _Storage;
    Visualization* _Visualization;
    
    
};


#endif /* Architect_hpp */
