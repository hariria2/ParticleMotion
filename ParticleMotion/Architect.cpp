//
//  Architect.cpp
//  ParticleFlow
//
//  Created by Sahand Hariri on 9/23/15.
//  Copyright © 2015 Sahand Hariri. All rights reserved.
//

#include "Architect.hpp"



using namespace std;

Architect::Architect(Domain* D, vector<Particle*> ps, double dt, double te, Visualization* vis):_Domain(*D)
{
    setTime(0);
    setTimeStep(dt);
    setEndTime(te);
    setParticles(ps);
    setVisualization(vis);
    //setStorage(storage);
    
};

void Architect::setTime(double time){
    _Time = time;
}
void Architect::setTimeStep(double dt){
    _TimeStep = dt;
}
void Architect::setEndTime(double te){
    _EndTime = te;
}
void Architect::setParticles(vector<Particle*> ps){
    _Particles = ps;
}
void Architect::setStorage(Storage* storage){
    _Storage = storage;
}
void Architect::setVisualization(Visualization* vis){
    _Visualization = vis;
}

double Architect::getTime(){
    return _Time;
}
double Architect::getTimeStep(){
    return _TimeStep;
}
double Architect::getEndTime(){
    return _EndTime;
}
vector<Particle*> Architect::getParticles(){
    return _Particles;
}
Visualization* Architect::getVisualization(){
    return _Visualization;
}


//void Architect::Update(){
//    string SQLStatement1;
//    string SQLStatement2;
//    double TotalKE;
//    double TotalPE;
//    double TotalVx;
//    double TotalVy;
//    double TotalFx;
//    double TotalFy;
//    for(auto p = _Particles.cbegin(); p != _Particles.cend(); ++p){
//
//        SQLStatement1 = SQLStatement1 + "(NULL, " +
//        to_string((*p)->getID()) + ", " +
//        to_string((*p)->getTime()) + ", " +
//        to_string((*p)->getX())  + ", " +
//        to_string((*p)->getY())  + ", " +
//        to_string((*p)->getVx()) + ", " +
//        to_string((*p)->getVy()) + ", " +
//        to_string((*p)->getFx()) + ", " +
//        to_string((*p)->getFy()) + ", " +
//        to_string((*p)->getKE()) + ", " +
//        to_string((*p)->getPE()) +
//        "),";
//
//        (*p)->ComputeParticleForce(_Particles);
//        (*p)->ComputeKE();
//        (*p)->ComputePE();
//        TotalKE += (*p)->getKE();
//        TotalPE += (*p)->getPE();
//        TotalVx += (*p)->getVx();
//        TotalVy += (*p)->getVy();
//        TotalFx += (*p)->getFx();
//        TotalFy += (*p)->getFy();
//
//        //(*p)->ComputeWallForce();
//        (*p)->Move(_TimeStep);
//        (*p)->setTime(_Time);
//    }
//    SQLStatement1.pop_back();
//    SQLStatement2 = "(Null, " +
//    to_string(_Time) + ", " +
//    to_string(TotalKE) + ", " +
//    to_string(TotalPE) + ", " +
//    to_string(TotalVx) + ", " +
//    to_string(TotalVy) + ", " +
//    to_string(TotalFx) + ", " +
//    to_string(TotalFy) + ")";
//
//
//    _Storage -> InsertValue("ParticleData",SQLStatement1, true);
//    _Storage -> InsertValue("SystemData"  ,SQLStatement2, true);
//    _Time += _TimeStep;
//
//}

void Architect::Update(){
    
    double TotalKE;
    double TotalPE;
    double TotalVx;
    double TotalVy;
    double TotalFx;
    double TotalFy;
    for(auto p = _Particles.cbegin(); p != _Particles.cend(); ++p){
        
        (*p)->ComputeParticleForce(_Particles);
        (*p)->ComputeKE();
        (*p)->ComputePE();
        TotalKE += (*p)->getKE();
        TotalPE += (*p)->getPE();
        TotalVx += (*p)->getVx();
        TotalVy += (*p)->getVy();
        TotalFx += (*p)->getFx();
        TotalFy += (*p)->getFy();
        
        //(*p)->ComputeWallForce();
        (*p)->Move(_TimeStep);
        (*p)->setTime(_Time);
    }
    
    _Time += _TimeStep;
    
}

void Architect::Simulate(){
    //PrepDB();
    _Visualization->Init();
    while (!glfwWindowShouldClose(_Visualization->getWindow())){
        
        
        cout << "time " << _Time << "!" << endl;
        
        _Visualization->Render(_Particles);
        Update();
        
    }
    
}

void Architect::PrepDB(){
    
    
    // ====================>>>>DomainData<<<========================== //
    // Domain
    _Storage->InsertValue("Domain",
                          "NULL, " +
                          to_string((_Domain.Boundary)[0][0]) + ", " +
                          to_string((_Domain.Boundary)[0][1]) + ", " +
                          to_string((_Domain.Boundary)[1][0]) + ", " +
                          to_string((_Domain.Boundary)[1][1]));
    
    // =====================>>>End of DomainData<<<========================= //
    
    // =====================>>>Particle Data<<<================================= //
    unsigned long ps = _Particles.size();
    
    cout << "Prepping tables for " << ps << " Particles. Please wait..." << endl;
    for(auto p = _Particles.cbegin(); p != _Particles.cend(); ++p) {
        
        _Storage->InsertValue("Particles",
                              "NULL, "        +
                              to_string((*p)->getMass()) + ", "  +
                              to_string((*p)->getX()) + ", "  +
                              to_string((*p)->getY()) + ", "  +
                              to_string(((*p)->getDomain())->getID()));
    }
    
    
    // =====================>>>End of Particle Data<<<========================== //
    
    
}
