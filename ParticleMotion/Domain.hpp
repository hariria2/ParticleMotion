//
//  Domain.hpp
//  ParticleFlow
//
//  Created by Sahand Hariri on 9/23/15.
//  Copyright © 2015 Sahand Hariri. All rights reserved.
//

#ifndef Domain_hpp
#define Domain_hpp

#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class Domain{
    
public:
    int Boundary[2][2];
    
    Domain(int id, int boundary[2][2], string type);
    
    void setID(int id);
    void setBoundary(int b[2][2]);
    void setType(string t);
    
    int getID();
    string getType();
    
    
private:
    
    int _ID;
    string _Type;
    
    
};

#endif /* Domain_hpp */
