//
//  Visualization.hpp
//  ParticleFlow
//
//  Created by Sahand Hariri on 10/5/15.
//  Copyright © 2015 Sahand Hariri. All rights reserved.
//

#ifndef Visualization_hpp
#define Visualization_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>
#include "Particle.hpp"

using namespace std;

class Visualization{
public:
    Visualization(int x, int y);
    
    void setWindow();
    void setX(int x);
    void setY(int y);
    
    void Init();
    void Render(vector<Particle*> parts);
    
    
    GLFWwindow* getWindow();
    
private:
    
    GLFWwindow* _window;
    
    int _X;
    int _Y;
    
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    
};




#endif /* Visualization_hpp */
