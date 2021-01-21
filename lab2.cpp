#include <iostream>
#include <list>
#include <conio.h>
#include <ctype.h>

std::list<char> lis;
char temp;

void outs()         //функция отображения списка
{
    for (auto it = lis.begin(); it != lis.end(); it++) {

        std::cout << *it;
    }
}

void ins()      //функция ввода списка
{
    do {
        temp = _getch();
        std::cout << temp;
        lis.push_back(temp);
    } while (temp != '.');
}

void searchsdel(char a)     //функция поиска спецсимвола и удаления символов
{
    auto i = lis.begin()++;
    while (i != lis.end())
    {
        if (*i == a)
        {
            if (i != lis.begin())
            {
                i--;
                lis.erase(i++);
            }
            lis.erase(i++);
        }
        else
            i++;
    }
}

int main()
{
    setlocale(LC_ALL, "ru");

    std::cout << "Введите данные в список" << std::endl;
    ins();       //Ввод данных в список 
    std::cout << std::endl;

    std::cout << "Список имеет вид " << std::endl;
    outs();     //Отображение списка 
    std::cout << std::endl;

    std::cout << "Введите спец символ" << std::endl;
    std::cin >> temp;
    searchsdel(temp);       //поиск спец символа и выполнение действия из задания 

    std::cout << std::endl;
    std::cout << "Список после обработки" << std::endl;
    outs();     //Отображение списка 
    std::cout << std::endl;

    int check;
    while (true) {
        std::cout << "1 Добавить новый элемент" << std::endl;
        std::cout << "2 Показать список" << std::endl;
        std::cout << "3 Повторная обработка списка" << std::endl;
        std::cout << "4 Выход из программы" << std::endl;
        std::cin >> check;
        switch (check)
        {
        case 1:
            std::cout << "Введите новый элемент " << std::endl;
            ins();
            std::cout << std::endl;
            break;
        case 2:
            outs();
            std::cout << std::endl;
            break;
        case 3:
            std::cout << "Введите спец символ для обработки" << std::endl;
            std::cin >> temp;
            searchsdel(temp);
            outs();
            std::cout << std::endl;
            break;
        case 4:      //выйти из программы
            return 0;
            break;

        }
    }

    system("pause");
    return 0;
}