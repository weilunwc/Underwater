#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

class Vec
{

public:
        double x = 0;
    double y = 0;
    double z = 0;
    Vec(){};
    Vec(double initx, double inity, double initz){
        x = initx;
        y = inity;
        z = initz;  
    }/*
    Vec(const Vec &p1){
        x = p1.x;
        y = p1.y;
        z = p1.z;
    }
    
    Vec &operator=(const Vec &other){
        x = other.x;
        y = other.y;
        z = other.z;   
        return *this;
    }*/
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    double getZ(){
        return z;
    }
};


class Square
{
    
public: 
    Vec points[4];
    Square(){
        for (int i = 0; i < 4; i++){
            points[i] = Vec();
        }
    }/*
    Square(const Square &p1){
        for(int i = 0; i < 4; i++){
            points[i] = p1.points[i];
        }
    }
    Square &operator=(const Square &other){
        for(int i = 0; i < 4; i++){
            points[i] = other.points[i];
        }
        return *this;
    }*/
    Square(Vec p1, Vec p2, Vec p3, Vec p4);

    /*void updatePoints(std::vector<Vec> inpoints){
        for (int i = 0; i < 4; i++){
            points[i] = inpoints[i];
        }
    }*/

};

Square::Square(Vec p1, Vec p2, Vec p3, Vec p4){
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
}


class Robot
{
public:
    double x,y,z;
    double h,p,b;
    double wid,hei,len;
    Square sides[6];
    Robot(double inw, double inh, double inl);
    void Draw();
    void updatePos(double x1, double y1, double z1);
    void UpdateRot(double h1, double p1, double b1);
    void Init();
};
Robot::Robot(double inw, double inh, double inl){
    x = 0;
    y = 0;
    z = 0;
    h = 0;
    p = 0;
    b = 0;
    vector<Vec> newpoints;
    newpoints.push_back(Vec());
};

class Site {
public:
    int i = 3;
    Site(){};
    Site(int sd){
        i = sd;
    }
    
};

class BigSite{
public:
    Site news[4];
    BigSite(){
        news[0] = Site();
        printf("%d\n",news[0].i);
        vector<Site> blah;
        blah.push_back(Site(2));
        news[0] = Site(4);
    }
    BigSite(Site other){
        news[0] = other;
        printf("%d\n",news[0].i);
    }
};

int main() {
    vector<Site> listofsites;
    vector<BigSite> sdsds;
    Site newsite;
    newsite.i = 10;
    BigSite biggy(newsite);
    sdsds.push_back(BigSite());
    
    return 0;
}