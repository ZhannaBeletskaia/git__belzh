#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
//#include <hx711/common.h>

using namespace std;

class Pastry // абстрактный базовый класс
{
public:
    Pastry(){}
    ~Pastry(){}

    int initDevice();
    int initServos();
    int startPosition(struct servo s);
    int startPositionAllServo();
    int rotateBody(int angle, int speed);
    int get(int arrowR_over_position, int arrowL_over_position, int arrowR_position, int arrowL_position, int claw_clenched_position);
    int put(int arrowR_position, int arrowL_position_put, int claw_clenched_position);
    virtual float check(float init_w)  = 0;
    int destructServos();
    int destruct();

};

class Dessert_in_box : virtual public Pastry // наследуемся как от виртуального на случай, если будут еще производные классы и они будут наследоваться от нескольких классов
{
public:
    
    Dessert_in_box() 
    {
        initDevice();
        startPositionAllServo();
    };
    ~Dessert_in_box()
    {
        destruct();
    }

    int GetBase03Angle()
    {
        return base03_angle;
    }
    int GetBase12Angle()
    {
        return base12_angle;
    }
    
    int rotateConvo(int n_convo, int angle);
    int bring_base(int n_base, int angle);
    int get_topping(int arrowL_topping_position);
    int get_canape(string fname, int init_angle);
    float check(float init_w) override;

private:
    int base03_angle = 60;
    int base12_angle = 100;
};