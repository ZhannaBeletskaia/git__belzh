#include <stdbool.h>
#include <map>
#include "./librisdk.h"
#include "Dessert.h"

//using namespace HX711;

char errorText[1000]; // текст ошибки. Передается как входной параметр,при возникновении ошибки в эту переменную будет записан текст ошибки

int logLevel = 2; // уровень логирования

struct device
{
    int i2c;        // дескриптор i2c
    int pwm;        // дескриптор pwm
    int body;       // дескриптор сервопривода тела
    int claw;       // дескриптор сервопривода клешни
    int claw_rotate;// дескриптор сервопривода поворота клешни
    int arrowR;     // дескриптор сервопривода правой стрелы
    int arrowL;     // дескриптор сервопривода левой стрелы
    int led;        // дескриптор светодиода
    int base0_push; // дескриптор рычага основы 1
    int base1_push; // дескриптор рычага основы 2
    int base2_push; // дескриптор рычага основы 3
    int base3_push; // дескриптор рычага основы 4
    int convo_base; // дескриптор конвейера для основ
    int convo_topping; // дескриптор конвейера для топпингов
    int convo_final;   // дескриптор конвейера для выдачи готового продукта
};

// инициализация структуры устройства
struct device robohand;

int body_start_pulse = 1500;        // стартовая позиция тела
int arrowR_start_pulse = 2000;      // стартовая возиция правой стрелы
int arrowL_start_pulse = 1000;      // стартовая позиция левой стрелы
int claw_start_pulse = 1000;        // стартовая позиция клешни
int claw_rotate_start_pulse = 1000;   // стартовая позиция клешни

int base0_push_start_pulse = 1500;        // стартовая позиция рычага основы 1
int base1_push_start_pulse = 1000;        // стартовая позиция рычага основы 2
int base2_push_start_pulse = 1000;        // стартовая позиция рычага основы 3
int base3_push_start_pulse = 1500;        // стартовая позиция рычага основы 4

int convo_base_start_pulse = 1500;        // стартовая позиция конвейера для основ
int convo_topping_start_pulse = 1500;        // стартовая позиция конвейера для топпингов
int convo_final_start_pulse = 1500;        // стартовая позиция конвейера для выдачи готового продукта

const int speed = 100;  // скорость в градусах в секунду

struct servo
{
    int* descriptor;    // дескриптор сервопривода
    int* startPosition; // стартовая позиция сервопривода
};

// массив дескрипторов сервоприводов
struct servo servos[12] = {
    &robohand.body,
    &body_start_pulse,
    &robohand.claw,
    &claw_start_pulse,
    &robohand.arrowR,
    &arrowR_start_pulse,
    &robohand.arrowL,
    &arrowL_start_pulse,
    &robohand.claw_rotate,
    &claw_rotate_start_pulse,
    &robohand.base0_push,
    &base0_push_start_pulse,
    &robohand.base1_push,
    &base1_push_start_pulse,
    &robohand.base2_push,
    &base2_push_start_pulse,
    &robohand.base3_push,
    &base3_push_start_pulse,
    &robohand.convo_base,
    &convo_base_start_pulse,
    &robohand.convo_topping,
    &convo_topping_start_pulse,
    &robohand.convo_final,
    &convo_final_start_pulse
};

// initServos - создает сервоприводы и линкует их
int Pastry::initServos()
{
    int errCode;
    char executor[] = "executor";
    char servodrive[] = "servodrive";
    char mg90s[] = "mg90s";

    //создаем 4 сервопривода и линкуем их к пинам 0-3
    for (int i = 0; i < 4; i++)
    {
        // создаем компонент сервопривода с конкретной моделью как исполняемое устройство и получаем дескриптор сервопривода
        errCode = RI_SDK_CreateModelComponent(executor, servodrive, mg90s, servos[i].descriptor, errorText);
        if (errCode)
        {
            return 1;
        }
        //связываем сервопривод с ШИМ,передаем дескриптор сервопривода и ШИМ
        errCode = RI_SDK_LinkServodriveToController(*servos[i].descriptor, robohand.pwm, i, errorText);
        if (errCode)
        {
            return 1;
        }
    }

    return 0;
}

// initDevice - инициализация библиотеки и устройств
int Pastry::initDevice()
{
    int errCode; //код ошибки
    char executor[] = "executor";
    char connector[] = "connector";
    char pwm[] = "pwm";
    char cp2112[] = "cp2112";
    char ch341[] = "ch341";
    char pca9685[] = "pca9685";
    char led[] = "led";
    char ky016[] = "ky016";

    // Инициализируем SDK
    errCode = RI_SDK_InitSDK(logLevel, errorText);
    if (errCode)
    {
        return 1;
    }

    // создаем компонент с конкретной моделью как исполняемое устройство,получаем дескриптор сервопривода
    errCode = RI_SDK_CreateModelComponent(connector, pwm, pca9685, &robohand.pwm, errorText);
    if (errCode)
    {
        return 1;
    }

    // создаем компонент i2c адаптера
    // создаем i2c адаптер модели ch341 и связать с ним ШИМ
    errCode = RI_SDK_CreateModelComponent(connector, pwm, ch341, &robohand.i2c, errorText);
    if (errCode)
    {
        return 1;
    }

    //связываем i2c адаптер с ШИМ по адресу 0x40
    errCode = RI_SDK_LinkPWMToController(robohand.pwm, robohand.i2c, 0x40, errorText);
    if (errCode)
    {
        // Если не получается то пробуем создать i2c адаптер модели cp2112
        errCode = RI_SDK_CreateModelComponent(connector, pwm, cp2112, &robohand.i2c, errorText);
        if (errCode)
        {
            return 1;
        }

        //связываем i2c адаптер с ШИМ по адресу 0x40
        errCode = RI_SDK_LinkPWMToController(robohand.pwm, robohand.i2c, 0x40, errorText);
        if (errCode)
        {
            return 1;
        }
    }

    // создаем компонент светодиода с конкретной моделью (ky016) как исполняемое устройство и получаем дескриптор светодиода
    errCode = RI_SDK_CreateModelComponent(executor, led, ky016, &robohand.led, errorText);
    if (errCode)
    {
        return 1;
    }

    //связываем светодиод адаптер с ШИМ,передаем значения трех пинов к которым подключен светодиод
    errCode = RI_SDK_LinkLedToController(robohand.led, robohand.pwm, 15, 14, 13, errorText);
    if (errCode)
    {
        return 1;
    }

    //инициализируем сервоприводы
    errCode = initServos();
    if (errCode)
    {
        return 1;
    }

    return 0;

}

// startPosition - переводит сервопривод в стартовое положение
int Pastry::startPosition(struct servo s)
{
    int errCode; //код ошибки
    //выполняем поворот сервопривода в заданный угол,передаем дескриптор сервопривода,значение угла
    errCode = RI_SDK_exec_ServoDrive_TurnByPulse(*s.descriptor, *s.startPosition, errorText);
    if (errCode)
    {
        return 1;
    }

    //небольшая пауза для последовательного движения
    Sleep(250);
    return 0;
};
// startPositionAllServo - переводит все сервоприводы в стартовую позицию
int Pastry::startPositionAllServo()
{
    int errCode; //код ошибки

    //приводим сервоприводы в стартовое положение
    for (int i = 0; i < 4; i++)
    {
        errCode = startPosition(servos[i]);
        if (errCode)
        {
            return 1;
        }
    }

    //небольшая пауза для последовательного движения
    Sleep(500);
    return 0;
};

// rotateBody - вращение тела в указанный угол
int Pastry::rotateBody(int angle, int speed)
{
    int errCode; //код ошибки

    //выполняем поворот на заданный угол,передаем дескриптор тела,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.body, angle, speed, false, errorText);
    if (errCode)
    {
        cout << "Error rotate body" << endl;
        return -1;
    }

    return 0;
}

// get - взять предмет
int Pastry::get(int arrowR_over_position, int arrowL_over_position, int arrowR_position, int arrowL_position, int claw_clenched_position)
{
    int errCode; //код ошибки
    int claw_unclenched_position = 110;

    //выполняем поворот на заданный угол,передаем дескриптор стрелы,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.arrowR, arrowR_over_position, speed, false, errorText); // позиция правой клешни над компонентом
    if (errCode)
    {
        cout << "Error get 1" << endl;
        return -1;
    }

    //выполняем поворот на заданный угол,передаем дескриптор стрелы,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.arrowL, arrowL_over_position, speed, false, errorText); // позиция левой клешни над компонентом
    if (errCode)
    {
        cout << "Error get 2" << endl;
        return -1;
    }

    //выполняем поворот на заданный угол,передаем дескриптор клешни,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.claw, claw_unclenched_position, speed, false, errorText); // клешня разжата
    if (errCode)
    {
        cout << "Error get 3" << endl;
        return -1;
    }

    //выполняем поворот на заданный угол,передаем дескриптор стрелы,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.arrowR, arrowR_position, speed, false, errorText); // позиция правой клешни захвата компонентом
    if (errCode)
    {
        cout << "Error get 4" << endl;
        return -1;
    }

    //выполняем поворот на заданный угол,передаем дескриптор стрелы,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.arrowL, arrowL_position, speed, false, errorText); // позиция левой клешни захвата компонентом
    if (errCode)
    {
        cout << "Error get 5" << endl;
        return -1;
    }

    //выполняем поворот на заданный угол,передаем дескриптор клешни,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.claw, (-1) * claw_clenched_position, speed, false, errorText); // сжатие клешни
    if (errCode)
    {
        cout << "Error get 6" << endl;
        return -1;
    }

    return 0;
}

//put - положить предмет
int Pastry::put(int arrowR_position, int arrowL_position, int claw_unclenched_position)
{
    int errCode;

    //выполняем поворот на заданный угол,передаем дескриптор стрелы,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.arrowR, arrowR_position, speed, false, errorText); // 
    if (errCode)
    {
        cout << "error put 1" << endl;
        return -1;
    }
    
    //выполняем поворот на заданный угол,передаем дескриптор стрелы,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.arrowL, arrowL_position, speed, false, errorText); // 
    if (errCode)
    {
        cout << "Error put 2" << endl;
        return -1;
    }

    //выполняем поворот на заданный угол,передаем дескриптор клешни,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.claw, claw_unclenched_position, speed, false, errorText); // разжать
    if (errCode)
    {
        cout << "Error put 3" << endl;
        return -1;
    }

    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.arrowL, (-1) * arrowL_position, speed, false, errorText); // приподняться после того, как положил
    if (errCode)
    {
        cout << "Error put 4" << endl;
        return -1;
    }

    return 0;
}

int Dessert_in_box::rotateConvo(int n_convo, int angle)
{
    int errCode; 
    std::map<int, int> convos_angles;

    convos_angles[0] = robohand.convo_base; 
    convos_angles[1] = robohand.convo_topping;
    convos_angles[2] = robohand.convo_final;

    // поворот конвейера на указанный угол
    // errCode = RI_SDK_exec_ServoDrive_Turn(convos_angles[n_convo], angle, speed, true, errorText);
    /*if (errCode)
    {
        return 1;
    }*/

    cout << "Convo " << n_convo << " finished moving." << endl;

    return 0;
}

int Dessert_in_box::bring_base(int n_base, int angle) // i_arr[3]
{
    int errCode; //код ошибки

    std::map<int, int> push_base; // словарь для хранения соответствия номерам основ дескрипторов сервпроприводов, которые выталкивают основы на конвейер

    push_base[0] = robohand.base0_push;
    push_base[1] = robohand.base1_push;
    push_base[2] = robohand.base2_push;
    push_base[3] = robohand.base3_push;

    if(n_base == 0 || n_base == 3)
    {
       // errCode = RI_SDK_exec_ServoDrive_Turn(push_base[n_base], GetBase03Angle(), speed, true, errorText);
       // Sleep(500);
       // errCode = RI_SDK_exec_ServoDrive_Turn(push_base[n_base], (-1) * GetBase03Angle(), speed, true, errorText); // возврат рычага
        cout << "Dessert base push " << n_base << " finished moving." << endl;
    }
    else
    {
       // errCode = RI_SDK_exec_ServoDrive_Turn(push_base[n_base], GetBase12Angle(), speed, true, errorText);
       // Sleep(500);
       // errCode = RI_SDK_exec_ServoDrive_Turn(push_base[n_base], (-1) * GetBase12Angle(), speed, true, errorText); // возврат рычага
        cout << "Dessert base push " << n_base << " finished moving." << endl;
    }

   /* if (errCode != 0)
    {
        cout << "Error push " << endl;
        return 1;
    }*/

    rotateConvo(0, angle); // конвейер везет основу до точки захвата

    return 0;
}

int Dessert_in_box::get_topping(int arrowL_topping_position)
{
    int errCode; //код ошибки
    int claw_unclenched = 80;

    //errCode = RI_SDK_exec_ServoDrive_Turn(robohand.claw_rotate, 180, speed, false, errorText); // поворот клешни на 180 градусов к топпингам
    //if (errCode)
    //{
    //    cout << "Error get topping 0" << endl;
    //    return 1;
    //}

    cout << "Claw's rotated up to 180 degree" << endl;

    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.arrowL, arrowL_topping_position, speed, false, errorText); // подъем к конвейеру с топпингами 
    if (errCode)
    {
        cout << "Error get topping 1" << endl;
        return 1;
    }

    //выполняем поворот на заданный угол,передаем дескриптор клешни,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.claw, claw_unclenched, speed, false, errorText); // клешня разжата 
    if (errCode)
    {
        cout << "Error get topping 2" << endl;
        return 1;
    }

    Sleep(500);

    //выполняем поворот на заданный угол,передаем дескриптор клешни,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.claw, (-1) * claw_unclenched, speed, false, errorText); // сжатие клешни 
    if (errCode)
    {
        cout << "Error get topping 3" << endl;
        return 1;
    }

    Sleep(1000);

    //выполняем поворот на заданный угол,передаем дескриптор клешни,угол,скорость и асинхронный режим работы
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.claw, claw_unclenched, speed, false, errorText); // клешня разжата 
    if (errCode)
    {
        cout << "Error get topping 4" << endl;
        return 1;
    }

    Sleep(500);

    //errCode = RI_SDK_exec_ServoDrive_Turn(robohand.claw_rotate, -180, speed, false, errorText); // возврат клешни 
    //if (errCode)
    //{
    //    cout << "Error get topping 5" << endl;
    //    return 1;
    //}

    cout << "Claw's rotated up to -180 degree" << endl;

    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.arrowL, (-1) * arrowL_topping_position, speed, false, errorText); // опуститься на исходную точку 
    if (errCode)
    {
        cout << "Error get topping 6" << endl;
        return 1;
    }

    return 0;
}

int Dessert_in_box::get_canape(string fname, int init_angle) // угол, в котором нах-ся канапэ 
{
    int errCode; //код ошибки
    struct Points // координаты шпажек на реальной платформе
    {
        int x;
        int y;
    };
    struct Points p;

    vector<Points> canapes; // массив координат

    // Физические координаты нахождения канапе
    Points p1{ -30, 60 }; canapes.push_back(p1); // если в наличии есть канапе из первой строки матрицы  
    Points p2{ -50, 40 }; canapes.push_back(p2); // из второй  
    Points p3{ -70, 30 }; canapes.push_back(p3); // из третьей 

    int coord = 0, angle = 0; // координата от исходной точки и угол, где находится эта исходная точка
    bool br = false;

    string s;
    fstream in(fname);
    if (!in.is_open())
    {
        cout << "Error: couldn't open the file Canape." << endl;
        return -1;
    }

    for (int i = 0; i < 3; ++i) // поиск первой канапешки в наличии в матрице
    {
        for (int j = 0; j < 3; ++j)
        {
            in >> s;
            if (s == "1")
            {
                angle = j; // столбцы матрицы
                coord = i; // строки матрицы
                in << "0";
                br = true;
                break;
            }
            else
                continue;
        }
        if (br)
            break;
    }

    if (!br)
    {
        cout << "Sorry! There's no canape left :( Please, choose another option" << endl;
        return -1;
    }

    in.close();

    angle *= 10; // если 0 - останется init_angle, если нет, то будет сдвиг на 10 градусов
    if (init_angle < 0)
        init_angle -= angle;
    else
        init_angle += angle;

    rotateBody(init_angle, speed); // поворот башни к матрице с канапе

    int arrowR_at_canape = -30;
    int arrowL_at_canape = 20;

    get(canapes[coord].x, canapes[coord].y, arrowR_at_canape, arrowL_at_canape, 120);

    Sleep(500);

    // для удобства поднимем канапе повыше, они наверняка длинные
    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.arrowL, (-5) * arrowL_at_canape, speed, false, errorText); // позиция левой клешни над компонентом 
    if (errCode)
    {
        cout << "Error get canape 6" << endl;
        return 1;
    }

    errCode = RI_SDK_exec_ServoDrive_Turn(robohand.arrowR, (-1) * arrowR_at_canape, speed, false, errorText); // позиция правой клешни над компонентом
    if (errCode)
    {
        cout << "Error get canape 7" << endl;
        return 1;
    }

    rotateBody(-init_angle, speed); // возврат в рабочую область

    return 0;
}

float Dessert_in_box::check(float init_w) // работа с тензодатчиком через АЦП HX711
{
    // Создать объект SimpleHX711, используя GPIO пин 2 как дата пин, пин 3 как клок пин, 1 как отсчетную единицу и 0 как отступ 
    //SimpleHX711 hx(2, 3, 1, 0);
    // отображать вес в граммах
    //hx.setUnit(Mass::Unit::G);
    //if (hx.weight(seconds(1)) > init_weight) // если текущий вес (значения, собранные в течение секунды) больше исходного, вернуть текущий
    //    return hx.weight(seconds(1));
    //else
    //{
    //    cout << "Error weight " << endl;
    //    return -1;
    //}

    float current_w;
    cout << "What's the current weight? " << endl;
    cin >> current_w;

    if (current_w > init_w) // если текущий вес больше исходного, вернуть текущий
        return current_w;
    else
    {
        cout << "Error weight " << endl;
        return -1;
    }
}

// destructServos - уничтожает сервоприводы
int Pastry::destructServos()
{
    int errCode; //код ошибки
    for (int i = 0; i < 4; i++)
    {
        errCode = RI_SDK_DestroyComponent(*servos[i].descriptor, errorText);
        if (errCode)
        {
            return 1;
        }
    }

    return 0;
    
}

// destruct - уничтожает все компоненты и библиотеку
int Pastry::destruct()
{
    int errCode; //код ошибки
    //выполняем одиночное свечение светодиодом,передаем дескриптор светодиода,3 параметра цвета(RGB), и включаем асинхронный режим работы
    errCode = RI_SDK_exec_RGB_LED_SinglePulse(robohand.led, 255, 0, 0, 0, true, errorText);
    if (errCode)
    {
        cout << "Error: destructor 1" << endl;
        return 1;
    }
    //уничтожаем сервоприводы
    errCode = destructServos();
    if (errCode)
    {
        cout << "Error: destructor 2" << endl;
        return 1;
    }
    //останавливаем свечение светодиода с определенным дескриптором
    errCode = RI_SDK_exec_RGB_LED_Stop(robohand.led, errorText);
    if (errCode)
    {
        cout << "Error: destructor 2" << endl;
        return 1;
    }
    //удаляем компонент светодиода по дескриптору
    errCode = RI_SDK_DestroyComponent(robohand.led, errorText);
    if (errCode)
    {
        cout << "Error: destructor 3" << endl;
        return 1;
    }
    //сбрасываем все порты на ШИМ
    errCode = RI_SDK_sigmod_PWM_ResetAll(robohand.pwm, errorText);
    if (errCode)
    {
        cout << "Error: destructor 4" << endl;
        return 1;
    }
    //удаляем компонент ШИМ
    errCode = RI_SDK_DestroyComponent(robohand.pwm, errorText);
    if (errCode)
    {
        cout << "Error: destructor 5" << endl;
        return 1;
    }
    //удаляем компонент i2c
    errCode = RI_SDK_DestroyComponent(robohand.i2c, errorText);
    if (errCode)
    {
        cout << "Error: destructor 6" << endl;
        return 1;
    }
    //удаляем sdk со всеми компонентами в реестре компонентов
    errCode = RI_SDK_DestroySDK(true, errorText);
    if (errCode)
    {
        cout << "Error: destructor 7" << endl;
        return 1;
    }
    return 0;
    
}
