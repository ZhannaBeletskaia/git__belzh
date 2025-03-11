#pragma once
#include <iostream>

class Cook
{
    friend class Dessert_in_box;
public:
    Cook() {};
    
    int Get_release_angle()
    {
        return release_angle;
    }

    int Start(int i_arr[]);
    int Base(class Dessert_in_box& dessert, int i_arr[]);
    int Topping(class Dessert_in_box& dessert, int i_arr[]);
    int Canape(class Dessert_in_box& dessert, int i_arr[], std:: string fname);
    int Storage_check(int i_arr[], std::string fname);
private:
    int release_angle; // угол поворота от точки сборки до точки выдачи клиенту
};