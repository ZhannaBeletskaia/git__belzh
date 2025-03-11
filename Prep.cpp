#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Prep.h"

// функция заполнит массив в соответствии с выбором пользователя
int Custom(int* i_arr, char* argv[])
{
    i_arr[0] = atoi(argv[1]); // добавить в массив номер основы

    std::map<int, int> convo_base_angle;

    convo_base_angle[0] = -90;
    convo_base_angle[1] = -45;
    convo_base_angle[2] = 45;
    convo_base_angle[3] = 90;

    i_arr[3] = convo_base_angle[atoi(argv[1])]; // добавить в массив угол от компонента на конвейера до основы сколько проехать

    i_arr[4] = atoi(argv[2]) * (-45); // добавить в массив номер топпинга

    std::map<int, int> canape_angle;

    canape_angle[1] = -60;
    canape_angle[2] = 40;
    canape_angle[3] = 70;

    i_arr[1] = atoi(argv[3]); // добавить в массив номер текст. документа с матрицей канапе 
    i_arr[2] = canape_angle[atoi(argv[3])]; // добавить в массив начальный угол, нахождения канапе

    return 0;
}

int ReadMenu(int i_arr[], int n_str)
{
    int n = -1, i = 0;
    std::string s;
    std::string s_arr[5];

    std::ifstream in("menu.txt");
    if (!in.is_open())
    {
        std::cout << "Error: couldn't open the file menu." << std::endl;
        return -1;
    }

    while (in >> s)
    {
        if (++n != ((n_str - 1) * 5))
            continue;
        else
        {
            --n;
            s_arr[i] = s;
            i++;
        }

        if (i == 5) break;
    }

    std::cout << std::endl;

    for (int j = 0; j < 5; ++j)
    {
        i_arr[j] = stoi(s_arr[j]);
    }

    return 0;
}