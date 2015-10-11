//
//  main.cpp
//  ParticleFlow
//
//  Created by Sahand Hariri on 9/22/15.
//  Copyright © 2015 Sahand Hariri. All rights reserved.
//

#include <iostream>
#include <string>
#include <random>
//#include <unistd.h>
#include "Particle.hpp"
#include "Domain.hpp"
#include "Architect.hpp"
#include "Storage.hpp"
#include <sys/time.h>

using namespace std;

void example1();

int main(int argc, const char * argv[]) {
    
    //example1();
    
    timeval a;
    timeval b;
    
    gettimeofday(&a, 0);

    example1();
    
    gettimeofday(&b, 0);
    cout << "difference: " << (b.tv_sec - a.tv_sec) << endl;

    return 0;
}

void example1(){
    
    
    int xdim = 640;
    int ydim = 480;
    int MyB[2][2]   = {{0, xdim},{0, ydim}};
    string type = "Wall";
    Domain D(0, MyB, type);
    
    //Particle(id, Domain, mass,x,y,vx,vy, fx,fy)
    
    int numPart = 10;
    vector<Particle*> parts;
    double x;
    double y;
    double vx;
    double vy;
    double m;
    
    
    for (int ii = 0; ii<numPart; ii++){
        unsigned seed = (unsigned int) chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator(seed);
        uniform_real_distribution<double> Distx(200,300);
        double xr  = Distx(generator);
        uniform_real_distribution<double> Disty(150,250);
        double yr  = Disty(generator);
        
        if (ii%2 == 0){
            x = xr;
            y = yr;
            vx = 0;
            vy = 0;
            m = 20;
        }else{
            x = xr;
            y = yr;
            vx = 0;
            vy = 0;
            m = 20;
        }
        Particle *p = new Particle(ii+1, &D, m, x, y, vx, 0, 0., 0.);
        p->setGx(0.1);
        p->setGy(0.1);
        parts.push_back(p);
        usleep(1000);
    }
    
    
    
    string ver;
    //cout << "Please enter version number: ";
    //cin >> ver;
    Visualization vis(xdim,ydim);
    //Storage storage("localhost", "root", "", "anchorDB", ver);
    Architect archie(&D, parts, 0.1, 100, &vis);
    
    cout << "X before simulation: " << parts.back()->getX() << endl;
    cout << "Y before simulation: " << parts.back()->getY() << endl;
    archie.Simulate();
    
    cout << "X after simulation: " << parts.back()->getX() << endl;
    cout << "Y after simulation: " << parts.back()->getY() << endl;
    
}