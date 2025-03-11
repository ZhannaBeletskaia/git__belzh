#include "Cook.h"
#include "Prep.h"

int main(int argc, char* argv[])
{
    int n_str = 0; //n_str номер строки с рецептом
    int i_arr[5]; // массив координат
    
    if (argc == 1)
    {
        std::cout << "Error: choose your menu, please" << std::endl;
        return 0;
    }

    if (argc == 2) // выбран десерт из меню
    {
        n_str = atoi(argv[1]); // 1 2 -80 -90 90
        if (ReadMenu(i_arr, n_str) == -1)
            return -1;
    }
    else // конструктор десерта: индивидуальный выбор основы, топпинга и канапе
    {
        Custom(i_arr, argv); 
    }

    Cook cook;
    cook.Start(i_arr);

    return 0;
}
