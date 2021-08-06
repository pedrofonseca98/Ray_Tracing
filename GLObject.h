#ifndef GLObject_h
#define GLObject_h

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <sstream>

#include "GLVector.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define PI 3.141592653589
#define WIDTHBYTES(bits) (((bits)+31)/32*4)

Vec3f WHITE(1);
Vec3f BLACK(0);




class Ray{
    public:

        Vec3f origin;//A posição da fonte de luz
        Vec3f direction;//O vetor de direção da luz foi padronizado
        float intense;

        Ray(Vec3f &o, Vec3f &d, float i=1.0f):origin(o),intense(i){
            direction = d.normalize();
        }

        Vec3f getPoint(float t){
            return origin + direction * t;
        }
};

    //Câmera
class Camera{
public:
    Vec3f eye;
    Vec3f center;
    Vec3f up;
    float FOV;
    Camera(Vec3f e, Vec3f c, Vec3f u, int fov):eye(e),center(c),up(u), FOV(fov/180.0*PI){
    }
    //Algoritmo de luz 
    Ray generateRay(int i, int j, int width, int height){
        Vec3f a = eye - center;
        Vec3f w = a.normalize();
        Vec3f b = up;
        Vec3f u = b.cross(w);
        u = u.normalize();
        Vec3f v = w.cross(u);
        float alpha = tan(FOV/2)*(i-width/2)/(width/2);
        float beta = tan(FOV/2)*(j-height/2)/(height/2);
        Vec3f direction = u*alpha+v*beta-w;
        Ray ray(eye, direction);
        return ray;
    }
};

class Material {
    public:

        float Ka, Kd, Ks; // Coeficiente de luz ambiente, difusa e especular
        int shininess;

        Material(float Ka = 0.3, float Kd = 0.8, float Ks = 0.5, int shininess = 6) : Ka(Ka), Kd(Kd), Ks(Ks), shininess(shininess) {}

};


class Object {

public:

    Vec3f surfaceColor;
    Vec3f emissionColor; // Para a fonte de luz

    float transparency;

    Material material;


    float Ka; // Coeficiente de reflexão de luz ambiente
    float Kd; // Coeficiente de reflexão difusa
    float Ksp; // Coeficiente de reflexão especular
    int Fsp; // Indice de reflexão especular (sunshineness)



    Object(Vec3f sc,
        float trans,
        Vec3f ec = BLACK,
        Material material = Material(0.3, 0.8, 0.5, 6))
        : surfaceColor(sc),emissionColor(ec), transparency(trans), material(material){}
    virtual bool intersect(Ray &ray, float &t1, float &t2) const = 0;
    virtual Vec3f nhit(Vec3f &phit) const = 0;

    virtual Vec3f getTextureColor(Vec3f &phit) const=0;
};


    


#endif /* GLObject_h */

