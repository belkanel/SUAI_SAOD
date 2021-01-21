#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>

using namespace std;

const int n = 2000; //кол-во сегментов хеш-таблицы
const int m = 6; //длина ключа
const int m1 = 7; //длина ключа +1
const int tour = 11; //кол-во итераций поиска
const int c = 1; //шаг при разрешении коллизии

int hashi(char key[m1]) 
{ //возвращает номер позиции
	long rez = 0;
	for (int i = 0; i < m; i++)
		rez += pow(double(key[i]), 2);
	rez %= n;
	return rez;
}

void htinf(char t[n][m1]) 
{
	fstream file("hash.txt", ios_base::out);
	if (!file.is_open()) {
		cerr << "Не открыть файл\n";
			return;
	}
	file.seekg(0);
	for (int i = 0; i < n; i++) {
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
	fstream file("stat.txt", ios_base::out);
	if (!file.is_open()) {
		cerr << "Не открыть файл\n";
		return;
	}
	file.seekg(0);
	for (int i = 0; i < n; i++) {
		file << t[i] << '\n';
	}
	file.close();
}

bool add(char t[n][m1], char k[m1]) 
{
	int id;
	id = hashi(k);
	for (int i = 0; i < tour; i++) {
		id = id + i * c; if (id >= n) break;
		if (!strcmp(t[id], "\0")) {
			strcpy_s(t[id], k); return true;
		}
	} return false;
}

short find(char t[n][m1], char k[m1]) 
{
	int id;
	for (unsigned long i = 0; i < n * tour; i++) {
		id = hashi(k) + i * c;
		if (id >= n) break;
		if (!strcmp(t[id], "\0")) return -1;
		if (!strcmp(t[id], k)) return id;
	} return -1;
}

bool del(char t[n][m1], char k[m1]) 
{
	if (find(t, k) == -1) return false;
	for (int i = 0; i < m1; i++) {
		strcpy_s(t[find(t, k)], "\0");
	}
	return true;
}

void print(char t[n][m1])
{
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (int j = 0; j < m1; j++)
		{
			if (t[i][0] == '\0')
			{
				cout << "\n";
				break;
			}
			else if (t[i][j] == '\0')
				cout << "\n";
			else cout << t[i][j];
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int keys[n]; //массив результатов
	char key[m1]; //ключ
	int choice = 12;
	char tab[n][m1];
	char x[100];

	while (choice != 0) {
		cout << "МЕНЮ\n";
		cout << "1. Создать хеш-таблицу\n";
		cout << "2. Заполнить таблицу\n";
		cout << "3. Добавить элементы в хеш-таблицу\n";
		cout << "4. Просмотреть хеш-таблицу\n";
		cout << "5. Поиск элемента в хеш-таблице\n";
		cout << "6. Удалить элемент из хеш-таблицы\n";
		cout << "7. Сохранить хеш таблицу в файл\n";
		cout << "8. Сохранить результаты в файл\n";
		cout << "0. Выход\n"; cout << "\n";

		do {
			cout << "Выберите пункт: ", cin >> x;
		} while (!isdigit(x[0]));
		choice = atof(x);
		cout << "---------------------\n";
		cout << "\n";

		switch (choice) {
		case 1: 
		{ //обнуление результирующего массива
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m1; j++) tab[i][j] = '\0';
				keys[i] = 0;
			}
			break;
		}
		case 2: 
		{
			//запись эксперементальных данных в массив keys
			for (int i = 0; i < n * 3; i++) { //генерация случайного ключа
				for (int j = 0; j < m; j++) {
					if (j == 1 || j == 2 || j == 3)
						key[j] = '0' + rand() % ('9' - '0');
					else key[j] = 'A' + rand() % ('Z' - 'A');
				}
				key[m] = '\0';
				keys[hashi(key)]++;
				add(tab, key);
			} break;
		}
		case 3: 
		{ 
			bool t;
			int q = 1;
			int r = 0;
			do {
				for (int i = 0; i < n; i++)
					for (int j = 0; j < m; j++) {
						if (tab[i][j] != '\0') { q = 0; }
						else { q = 1; }
					}
				if (q == 0) {
					cout << "Переполнение!\n";
					break;
				}
				else {
					cout << "Ввод ключа. Для выхода наберите EXIT\n";
					cout << " -> ", cin >> key;
					if (key[0] == 'E') if (key[1] == 'X') if (key[2] ==
						'I') if (key[3] == 'T') break;
					for (int j = 0; j < m; j++) {
						if (j == 1 || j == 2 || j == 3) if
							(isdigit(key[j])) {
							t = true;
						}
						else { t = false; break; }
						else if (j == 0 || j == 4 || j == 5) if
							(isalpha(key[j])) {
							t = true;
						}
						else { t = false; break; }
						else { t = false; break; }
					}
					if (t == true) {
						if (add(tab, key)) { cout << "Добавлено\n"; }
						else { cout << "Ошибка\n"; }
					}
					else { cout << "Ошибка\n"; break; }
				}
			} while (1);
			break;
		}
		case 4: 
		{ 
			print(tab);
				break;
		} 
		case 5: 
		{ 
			cout << "Введите ключ: ", cin >> key;
				if (find(tab, key) != -1) {
					cout << "Позиция: " << find(tab, key) << "\n";
				}
				else 
				{ 
					cout << "Не найден\n"; 
				} 
				break;
		}
		case 6: 
		{ 
			cout << "Введите ключ: ", 
				cin >> key;
				if (del(tab, key)) {
					cout << "Удалено\n";
				}
				else 
				{
					cout << "Ошибка\n"; 
				}
				break;
		} 
		case 7: 
		{ 
			htinf(tab);
			break;
		} 
		case 8:
		{ 
			stinf(keys); 
			break;
		}

		case 0: 
		{ 
			break;
		}
		default:std::cout << "Ошибка\n";
		}
	}
	system("pause");
	return 0;
}