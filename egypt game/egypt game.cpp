// egypt game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;
void inputResorces();
void newTurn();
void checkSaves();

//---ресурсы города---
int nationCount;
float psenicaCount;
int landCount;
int turnCounter;

//---изменения ресурсов города---

int nationAdd;//прирост населения
int nationLost; //потери населения из-за еды
float nationDead; //% смертности
float P; //общий % смертности 

int landCost; //стоимость 1 акра

float psenicaAdd; //прирост пшеницы на 1 акре
float psenicaLost; //сколько шпеницы пожрали крысуки

bool leftGame;
bool fileExsists;

int inputLand; //ввод земель под покупку
int inputSentLand; //ввод земель под покупку
int inputFood; //ввод пшеницы на еду
int inputPsenica; //ввод пшеницы на заceивание
bool restartInput;

string path = "filename.txt";
string fileText;

//~~~~~~НАЧАЛО НОВОЙ ИГРЫ~~~~~~
void Restart() {
    system("cls");
    nationCount = 100;
    psenicaCount = 2800;
    landCount = 1000;
    turnCounter = 0;
    nationDead = 0;
    P = 0;
    leftGame = false;
    std::cout << "Мой повелитель, соизволь поведать тебе:"<< endl;
    std::cout << "    Население города сейчас составляет " << nationCount << " человек;"<< endl;
    std::cout << "    Мы собрали " << psenicaCount << " бушелей пшеницы;"<< endl;
    std::cout << "    Город сейчас занимает " << landCount << " акров;" << endl;
    inputResorces();
}
//~~~~~~ВВОД И ПРОВЕРКА РЕСУРСОВ~~~~~~
void inputResorces() {
    landCost = rand() % 10 + 17;
    std::cout << "    1 акр земли стоит сейчас " << landCost << " бушель.\n"<< endl;


    do {
        restartInput = true;
        std::cout << "\n" << "Сколько акров земли повелеваешь купить?";
        std::cin >> inputLand;
        std::cout << "Сколько акров земли повелеваешь продать?";
        std::cin >> inputSentLand;
        std::cout << "Сколько бушелей пшеницы повелеваешь съесть?";
        std::cin >> inputFood;
        std::cout << "Сколько акров земли повелеваешь засеять?";
        std::cin >> inputPsenica;
            if ((psenicaCount-(inputPsenica / 2 + inputFood + landCost * inputLand)+ inputSentLand*landCost >=0)&& (landCount- inputSentLand+ inputLand>0)) { restartInput = false; }
        std::cout << ""<< endl;
    } while (restartInput); //пока не введут верно, не продолжать игру

    psenicaCount = psenicaCount - (inputPsenica / 2 + inputFood + landCost * inputLand); //сколько потратили пшенички
    //std::cout <<"Пшенички осталось"<< psenicaCount << ""<< endl;
    
}
void newTurn() {
        std::cout <<"\n~~~~~~~~~~~~~~~~~~~~"<< turnCounter <<"~~~~~~~~~~~~~~~~~~~~"<< endl;
        std::cout << "Мой повелитель, соизволь поведать тебе:"<< endl;
        std::cout << "    В году " << turnCounter <<" твоего высочайшего правления:"<< endl;


        //~~~~~~СЧИТАЕМ КОЛИЧЕСТВО ЖИТЕЛЕЙ~~~~~~
        nationLost = nationCount - trunc(inputFood / 20); //КОЛИЧЕСТВО СМЕРТЕЙ от общего колва жителей отнимается колво выживших
        if (nationLost < 0) { nationLost = 0; }
        nationDead = (float)nationLost / nationCount*100;// % УБИТЫХ
        
        if (nationDead >= 45)  { //проверка на % убитых
        std::cout << "    Ты не смог накормить народ!"<< endl;
        std::cout << "    За это ты будешь казнен!"<< endl;
        std::cout << "    Ахахахах..."<< endl;
        turnCounter = 10;
        P = 666;
    }
    else {
       
        P = P + nationDead; //% СМЕРТЕЙ ЗА ВСЕ РАУНДЫ
        if (nationLost != 0) {
            std::cout << "    "<< nationLost << " человек умерли с голоду."<< endl;
        }

        //~~~СЧИТАЕМ УБЫЛЬ И ПРИРОСТ ПШЕНИЦЫ~~~
        landCount = landCount + inputLand- inputSentLand;
        psenicaAdd = rand() % 6+1; //ПРИРОСТ ПШЕНИЦЫ С 1 ПОЛЯ
        if (inputPsenica - nationCount * 10 > 0) {
            std::cout << "    Мы собрали " << psenicaAdd * nationCount * 10 << " бушелей пшеницы,";
            std::cout << "по " << psenicaAdd << " бушеля с акра;"<< endl;
        }
        else {
            std::cout << "    Мы собрали " << psenicaAdd * inputPsenica << " бушелей пшеницы,";
            std::cout << " по " << psenicaAdd << " бушеля с акра;"<< endl;
        }
        //~~~ПОСЧИТАЛИ ПРИРОСТ ПШЕНИЦЫ, ПРОДОЛЖАЕМ СЧИТАТЬ ЖИТЕЛЕЙ~~~

        nationAdd = nationLost / 2 + (5 - psenicaAdd) * psenicaAdd * inputPsenica / 600 + 1; //ПРИРОСТ НАСЕЛЕНИЯ

        if (nationAdd < 0) { nationAdd = 0; } //проверка необходимости сообщения
        else if (nationAdd > 50) {
            nationAdd = 50;
            std::cout << "    " << nationAdd << " человек прибыли в наш великий город;"<< endl;
        }
        else {
            std::cout << "    " << nationAdd << " человек прибыли в наш великий город;"<< endl;
        }

        nationCount = nationCount + nationAdd - nationLost; //ОБЩЕЕ НАСЕЛЕНИЕ

        if (rand() % 100 < 15) { //ПРИШЛА ЛИ ЧУМА
            std::cout << "    Чума уничтожила половину населения"<< endl;
            nationCount = trunc(nationCount / 2);
        }
        std::cout << "    Население города сейчас составляет " << nationCount << " человек;"<< endl;


        //~~~~~~СЧИТАЕМ КОЛИЧЕСТВО ПШЕНИЦЫ~~~~~~
        
        psenicaCount = psenicaCount + psenicaAdd * inputPsenica;
        psenicaLost = ceil(rand() % 8* psenicaCount/100); //СКОЛЬКО ПШЕНИЦЫ СЪЕЛИ КРЫСЫ
        std::cout << "    Крысы истребили " << psenicaLost << " бушелей пшеницы,";
        psenicaCount = psenicaCount - psenicaLost;
        std::cout << " оставив " << psenicaCount << " бушеля в амбарах;"<< endl;
        std::cout << "    Город сейчас занимает " << landCount << " акров;" << endl;



        //~~~~~~ОСТАНОВКА ИГРЫ~~~~~~
            cout << "\n" << "Повелитель! Хотите продолжить правление?" << endl;
            string answer;
            do {
                cout << "yes - да, no - нет" << endl;
                cin >> answer;
            } while (!(answer == "yes") && !(answer == "no"));
            if (answer == "no") {
                leftGame = true;
            }
            else {
                inputResorces();
            }
        


    }

}


//~~~~~~СОХРАНЕНИЕ ИГРЫ~~~~~~
void saveGame() {
        ofstream MyFile(path, std::fstream::trunc);

        MyFile << turnCounter << endl;
        MyFile << nationCount << endl;
        MyFile << psenicaCount << endl;
        MyFile << landCount << endl;
        MyFile << P;
        MyFile.close();
}


//~~~~~~ПРОВЕРКА НАЛИЧИЯ СОХРАНЕНИЯ~~~~~~
void checkSaves() {
    ifstream MyFile(path);

    if (MyFile.is_open()) {
        fileExsists = true;
        cout << "Повелитель! Не желаете ли продолжить прошлое правление?" << endl;
        string answer;
        do {
            cout << "yes - да, no - нет" << endl;
            cin >> answer;
        } while (!(answer == "yes") && !(answer == "no"));
        if (answer == "yes") {
            int i = 0;
            while (getline(MyFile, fileText, '\n')) {
                switch (i)
                {
                case 0:
                    turnCounter = std::stoi(fileText);
                case 1:
                    nationCount = std::stoi(fileText);
                case 2:
                    psenicaCount = std::stof(fileText);
                case 3:
                    landCount = std::stoi(fileText);
                case 4:
                    P = std::stoi(fileText);
                }
                i++;
            }
            std::cout << "Мой повелитель, соизволь поведать тебе:" << endl;
            std::cout << "    Население города сейчас составляет " << nationCount << " человек;" << endl;
            std::cout << "    Мы собрали " << psenicaCount << " бушелей пшеницы;" << endl;
            std::cout << "    Город сейчас занимает " << landCount << " акров;" << endl;
            inputResorces();
        }
        MyFile.close();
    }
    else {
        fileExsists = false;
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    checkSaves();
    for (turnCounter; turnCounter < 10; turnCounter++) {
        if (turnCounter == 0) {
            Restart();
        }
        else {
            newTurn();
        }
        if (leftGame) {
            saveGame();
            break; 
        }
    }












    if (turnCounter >= 10) {
        std::cout << "\n#########################################" << endl;
        std::cout << "Конец игры!" << endl;

        if (P == 666) {
            std::cout << "R.I.P." << endl;
        }
        else {
            if (P / turnCounter > 33 && landCount / nationCount < 7) {
                std::cout << "\nИз-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. Теперь вы вынуждены влачить жалкое существование в изгнании!" << endl;
            }
            else if (P / turnCounter > 10 && landCount / nationCount < 9) {
                std::cout << "\nВы правили железной рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем." << endl;
            }
            else if (P / turnCounter > 3 && landCount / nationCount < 10) {
                std::cout << "\nВы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова!" << endl;
            }
            else {
                std::cout << "\nФантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше!!!" << endl;
            }
        }
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
