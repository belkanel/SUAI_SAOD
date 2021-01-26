#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>

const int n = 2000;		//кол-во сегментов хеш-таблицы
const int m = 6;		//длина ключа
const int m1 = 7;		//длина ключа +1
const int tour = 11;		//кол-во итераций поиска
const int c = 1;		//шаг при разрешении коллизии

int hashi(char key[m1])		//возвращает номер позиции 
{ 
	long rez = 0;
	for (int i = 0; i < m; i++)
		rez += pow(double(key[i]), 2);
	rez %= n;
	return rez;
}

void htinf(char t[n][m1]) 
{
	std::fstream file("hash.txt", std::ios_base::out);

	if (!file.is_open())		//ошибка, если файл не открывается
	{
		std::cerr << "Не открыть файл." << std::endl;
		return;
	}

	file.seekg(0);
	for (int i = 0; i < n; i++) 
	{
		{ file << i << ": ";
		for (int j = 0; j < m; j++)
			if (t[i][j] == '\0')
				break;
			else
				file << t[i][j];
		file << '\n';
		}
	}
	file.close();
}

void stinf(int t[n]) 
{
	std::fstream file("stat.txt", std::ios_base::out);
	if (!file.is_open()) 
	{
		std::cerr << "Не открыть файл." << std::endl;
		return;
	}
	file.seekg(0);
	for (int i = 0; i < n; i++) 
	{
		file << t[i] << '\n';
	}
	file.close();
}

bool add(char t[n][m1], char k[m1]) 
{
	int id;
	id = hashi(k);
	for (int i = 0; i < tour; i++)
	{
		id = id + i * c; 
		if (id >= n) 
			break;
		if (!strcmp(t[id], "\0")) 
		{
			strcpy_s(t[id], k); 
			return true;
		}
	} 
	return false;
}

short find(char t[n][m1], char k[m1]) 
{
	int id;
	for (unsigned long i = 0; i < n * tour; i++) 
	{
		id = hashi(k) + i * c;
		if (id >= n) 
			break;
		if (!strcmp(t[id], "\0")) 
			return -1;
		if (!strcmp(t[id], k)) 
			return id;
	} 
	return -1;
}

bool del(char t[n][m1], char k[m1]) 
{
	if (find(t, k) == -1) 
		return false;
	for (int i = 0; i < m1; i++) 
	{
		strcpy_s(t[find(t, k)], "\0");
	}
	return true;
}

void print(char t[n][m1])
{
	for (int i = 0; i < n; i++) 
	{
		std::cout << i << ": ";
		for (int j = 0; j < m1; j++)
		{
			if (t[i][0] == '\0')
			{
				std::cout << std::endl;
				break;
			}
			else if (t[i][j] == '\0')
				std::cout << std::endl;
			else 
				std::cout << t[i][j];
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int keys[n];		//массив результатов
	char key[m1];		//ключ
	int choice = 12;
	char tab[n][m1];
	char x[100];

	while (choice != 0) {
		std::cout << "МЕНЮ" << std::endl;
		std::cout << "1. Создать хеш-таблицу" << std::endl;
		std::cout << "2. Заполнить таблицу" << std::endl;
		std::cout << "3. Добавить элементы в хеш-таблицу" << std::endl;
		std::cout << "4. Просмотреть хеш-таблицу" << std::endl;
		std::cout << "5. Поиск элемента в хеш-таблице" << std::endl;
		std::cout << "6. Удалить элемент из хеш-таблицы" << std::endl;
		std::cout << "7. Сохранить хеш таблицу в файл" << std::endl;
		std::cout << "8. Сохранить результаты в файл" << std::endl;
		std::cout << "0. Выход" << std::endl;
		std::cout << std::endl;

		do {
			std::cout << "Выберите пункт: ", std::cin >> x;
		} while (!isdigit(x[0]));
		choice = atof(x);
		std::cout << "---------------------" << std::endl;
		std::cout << std::endl;

		switch (choice) 
		{
		case 1: 
		{ 
			//обнуление результирующего массива
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m1; j++) 
					tab[i][j] = '\0';
					keys[i] = 0;
			}
			std::cout << "Хеш-таблица создана." << std::endl;
			break;
		}
		case 2: 
		{
			//запись эксперементальных данных в массив keys
			for (int i = 0; i < n * 3; i++) 
			{ //генерация случайного ключа
				for (int j = 0; j < m; j++) 
				{
					if (j == 1 || j == 2 || j == 3)
						key[j] = '0' + rand() % ('9' - '0');
					else
						key[j] = 'A' + rand() % ('Z' - 'A');
				}
				key[m] = '\0';
				keys[hashi(key)]++;
				add(tab, key);
			} 
			std::cout << "Хеш-таблица заполнена." << std::endl;
			break;
		}
		case 3: 
		{ 
			bool t;
			int q = 1;
			do {
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < m; j++)
					{
						if (tab[i][j] != '\0')
						{
							q = 0;
						}
						else
						{
							q = 1;
							std::cout << "Свободная позиция " << i << std::endl;
							break;
						}
					}
					if (q == 1)
					{
						break;
					}
				}
				if (q == 0)
				{
					std::cout << "Переполнение!" << std::endl;
					break;
				}
				else 
				{
					std::cout << "Ввод ключа. Для выхода наберите EXIT" << std::endl;
					std::cout << " -> ", std::cin >> key;
					if (key[0] == 'E') 
						if (key[1] == 'X') 
							if (key[2] == 'I') 
								if (key[3] == 'T')
									break;
					for (int j = 0; j < m; j++) 
					{
						if (j == 1 || j == 2 || j == 3) 
							if (isdigit(key[j])) 
							{
								t = true;
							}
							else 
							{
								t = false; 
								break; 
							}
						else if (j == 0 || j == 4 || j == 5) 
							if (isalpha(key[j])) 
								{
									t = true;
								}
							else
							{ 
								t = false; 
								break; 
							}
					}
					if (t == true) {
						if (add(tab, key)) 
						{ 
							std::cout << "Добавлено" << std::endl;
							break;
						}
						else 
						{ 
							std::cout << "Ошибка 1" << std::endl;
							break;
						}
					}
					else
					{ 
						std::cout << "Ошибка 2" << std::endl;
						break;
					}
				}
			} 
			while (1);
			break;
		}
		case 4: 
		{ 
			print(tab);
				break;
		} 
		case 5: 
		{ 
			std::cout << "Введите ключ: ", std::cin >> key;
				if (find(tab, key) != -1) 
				{
					std::cout << "Позиция: " << find(tab, key) << std::endl;
				}
				else 
				{ 
					std::cout << "Не найден" << std::endl;
				} 
				break;
		}
		case 6: 
		{ 
			std::cout << "Введите ключ: ",
				std::cin >> key;
				if (del(tab, key)) 
				{
					std::cout << "Удалено" << std::endl;
				}
				else 
				{
					std::cout << "Ошибка" << std::endl;
				}
				break;
		} 
		case 7: 
		{ 
			htinf(tab);
			std::cout << "Хеш-таблица записана в файл." << std::endl;
			break;
		} 
		case 8:
		{ 
			stinf(keys);
			std::cout << "Данные записаны в файл." << std::endl;
			break;
		}

		case 0: 
		{ 
			break;
		}
		default:std::cout << "Ошибка." << std::endl;
		}
	}

	system("pause");
	return 0;
}