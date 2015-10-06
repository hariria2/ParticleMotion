//
//  Domain.cpp
//  ParticleFlow
//
//  Created by Sahand Hariri on 9/23/15.
//  Copyright © 2015 Sahand Hariri. All rights reserved.
//

#include "Domain.hpp"


Domain::Domain(int id, int boundary[2][2], string type){
    
    setID(id);
    setBoundary(boundary);
    setType(type);
    
}

void Domain::setID(int id){
    _ID = id;
}
void Domain::setBoundary(int b[2][2]){
    for (int ii=0; ii<2; ii++){
        for (int jj=0; jj<2; jj++){
            Boundary[ii][jj] = b[ii][jj];
        }
    }
}
void Domain::setType(string t){
    _Type = t;
}

int Domain::getID(){
    return _ID;
}
string Domain::getType(){
    return _Type;
}