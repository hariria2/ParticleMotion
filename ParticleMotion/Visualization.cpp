//
//  Visualization.cpp
//  ParticleFlow
//
//  Created by Sahand Hariri on 10/5/15.
//  Copyright © 2015 Sahand Hariri. All rights reserved.
//


#include "Visualization.hpp"
using namespace std;

Visualization::Visualization(int x, int y){
    setX(x);
    setY(y);
}

void Visualization::setWindow(){
    _window = glfwCreateWindow(_X, _Y, "My Awesome Real-Time OpenGL Animation", NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
}
void Visualization::setX(int x){
    _X = x;
}
void Visualization::setY(int y){
    _Y = y;
}

GLFWwindow* Visualization::getWindow(){
    return _window;
}


void Visualization::Init(){
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    setWindow();
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(_window, key_callback);
}
void Visualization::Render(vector<Particle*> parts){
    int width, height;
    glPointSize(10.f);
    glEnable(GL_POINT_SMOOTH);
    glfwGetFramebufferSize(_window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for(auto p = parts.cbegin(); p != parts.cend(); ++p){
        glColor3f(1.f, 0.5f, 0.5f); glVertex3f(2.*(*p)->getX()/640. - 1, 2.*(*p)->getY()/480. - 1, 0.);
    }
    glEnd();
    glfwSwapBuffers(_window);
    glfwPollEvents();
}


void Visualization::error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
void Visualization::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
