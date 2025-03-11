#include "Cook.h"
#include "Dessert.h"

float curr;

int Cook::Storage_check(int i_arr[], string fname)
{
    int s, t;
    bool empty = true; // для канапе
    vector<int> temp; // для обновления информации о наличии основ и топпингов
    ifstream in("count.txt");
    if (!in.is_open())
        cout << "Error: couldn't open the file Count." << endl;

    t = i_arr[4] / 45; // порядковый номер топпинга на конвейере
    t += 3; // номер топпинга, i_arr[0] - номер основы

    for (int i = 0; i < 7; ++i) //проверяем наличие основы и топпинга
    {
        in >> s;
        if (i < 4)
        {
            if (i == i_arr[0]) // нашлась нужная основа для проверки наличия остатков
                if (s < 1)
                {
                    cout << "Sorry! We are out of stock for this dessert base :( Please, choose another option." << endl;
                    return -1;
                }
                else
                {
                    s--;
                    temp.push_back(s);
                    continue;
                }
            else
                temp.push_back(s);
        }
        else
        {
            if (i == t) // нашелся нужный топпинг для проверки наличия остатков
                if (s < 1)
                {
                    cout << "Sorry! We are out of stock for this dessert topping :( Please, choose another option." << endl;
                    return -1;
                }
                else
                {
                    s--;
                    temp.push_back(s);
                }
            else
                temp.push_back(s);
        }

    }

    ofstream out("count.txt");

    for (int i = 0; i < temp.size(); ++i) // перезапись массива с новыми данными о наличии
        out << temp[i] << " ";

    ifstream file_in(fname); // открываем файл с канапе
    if (!file_in.is_open())
        cout << "Error: couldn't open the file Canape." << endl;

    for (int i = 0; i < 9; ++i)
    {
        file_in >> s;
        if (s == 1) // единица означает наличие
        {
            empty = false;
            break;
        }
    }

    if (empty)
    {
        cout << empty << " Sorry! We are out of stock for this dessert canape :( Please, choose another option." << endl;
        return -1;
    }

    return 0;
}

int Cook::Base(Dessert_in_box &dessert, int i_arr[])
{
    const int arrowR_over_position = -30; // позиция правой стрелы над компонентом
    const int arrowL_over_position = -10; // позиция левой стрелы над компонентом
    const int arrowR_position = -75; // позиция правой стрелы для захвата компонента
    const int arrowL_position = 55; // позиция левой стрелы для захвата компонента
    const int arrowL_position_put = 45; // позиция левой стрелы для действия "положить" компонент
    const int claw_clenched_position = 40; // позиция сжатой клешни

    dessert.bring_base(i_arr[0], i_arr[3]); // доставка основы десерта до точки захвата с конвейера роботом

    dessert.rotateBody(110, 100); // поворт в точку захвата

    dessert.get(arrowR_over_position, arrowL_over_position, arrowR_position, arrowL_position, claw_clenched_position); // забрать основу

    Sleep(800);

    dessert.rotateBody(-110, 100); // возврат в рабочую зону

    Sleep(800);
    
    dessert.put((-1) * arrowR_position, arrowL_position - 10, claw_clenched_position); // положить основу перед собой

    dessert.startPositionAllServo(); // вернуться в начальное положение

    // проверка, на месте ли основа, если нет - заканчиваем этот цикл готовки, чтоб начать снова
    curr = dessert.check(0.0);

    if (curr == -1)
    {
        cout << "Error: failed to get the base" << endl;
        return -1;
    }

    Sleep(800);

    return 0;
}

int Cook::Topping(Dessert_in_box& dessert, int i_arr[])
{
    const int arrowL_topping_position = -40;

    dessert.rotateConvo(1, i_arr[4]); // провернуть конвейер с топпингом в точку захвата 

    dessert.get_topping(arrowL_topping_position); // выдавить топпинг на основу

    dessert.rotateConvo(1, (-1) * i_arr[4]); // вернуть конвейер в исходную позицию

    dessert.startPositionAllServo();

    // проверка, есть ли топпинг
    float temp = curr;
    curr = dessert.check(curr);
    if (curr == -1)
    {
        cout << "Error: failed to get the topping" << endl;
        curr = temp;
        return -1;
    }

    Sleep(800);

    return 0;
}

int Cook::Canape(Dessert_in_box& dessert, int i_arr[], string fname)
{
    const int arrowR_position = 40;
    const int arrowL_position = 20;
    const int claw_clenched_position = 70;

    if(dessert.get_canape(fname, i_arr[2]) == -1) // взять шпажку с фруктами/ шоколадом/ маршмеллоу
        return -2; 

    Sleep(800);

    dessert.put(arrowR_position, arrowL_position, claw_clenched_position); // положить канапе в основу с топпингом

    float temp = curr;
    curr = dessert.check(curr);
    if (curr == -1)
    {
        cout << "Error: failed to get the canape" << endl;
        dessert.startPositionAllServo(); // возврат робота в среднее положение
        curr = temp;
        return -1;
    }

    return 0;
}

int Cook::Start(int i_arr[])
{
    int err = 0, attempts_count = 0;
    bool success = false;
    string fname = to_string(i_arr[1]) + ".txt"; // считываем из меню номер матрицы с канапе и создаем строку с названием файла
    
    if (Storage_check(i_arr, fname) == -1) // проверка наличия остатков
        return -1;

    Dessert_in_box dessert;

    while (attempts_count < 3)
    {
        if (Base(dessert, i_arr) == -1)
        {
            cout << "Error Base" << endl;
            std::cout << "\a";
            attempts_count++;
        }
        else
        {
            success = true;
            break;
        }
    }

    if (!success)
    {
        cout << "Something's wrong. I'm calling an operator" << endl;
        
        //system("mail_tmanage.exe");
       
        return -1;
    }
    
    success = false;
    attempts_count = 0;
    while (attempts_count < 3)
    {
        if (Topping(dessert, i_arr) == -1)
        {
            cout << "Error Topping" << endl;
            std::cout << "\a";
            attempts_count++;
        }
        else
        {
            success = true;
            break;
        }
    }  

    if (!success)
    {
        cout << "Something's wrong. I'm calling an operator" << endl;
        
        //system("mail_tmanage.exe");

        return -1;
    }

    err = Canape(dessert, i_arr, fname);
    while (err == -1)
    {
        cout << "Error Canape" << endl;
        std::cout << "\a";
        err = Canape(dessert, i_arr, fname);
    }

    if (err == -2) return -1;

    dessert.rotateConvo(2, Get_release_angle()); // готовый десерт отправляется покупателю
    dessert.startPositionAllServo(); // возврат робота в среднее положение

    cout << "Your dessert is ready! Enjoy!" << endl;

    return 0;
}