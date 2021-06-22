#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>


std::string add_zero(std::string original, size_t need_len);
int double_hash(std::string num, int i);

//читатели библиотеки
struct listener 
{
	std::string count_number;
	std::string seria;
	std::string year_join;
	std::string first_name, last_name, middle_name;
	std::string pasport_data;
	std::string adress;
	listener() 
	{
	}

	listener(std::string region_code,
		std::string seria,
		std::string num,
		std::string first_name,
		std::string middle_name,
		std::string last_name,
		std::string pasport_data,
		std::string adress) {
		this->count_number = add_zero(region_code, 4);
		this->seria = seria;
		this->year_join = add_zero(num, 2);
		this->first_name = first_name;
		this->middle_name = middle_name;
		this->last_name = last_name;
		this->pasport_data = pasport_data;
		this->adress = adress;
	}

	int compare(listener b) 
	{
		return std::string(seria + count_number + year_join).compare(std::string(b.count_number + b.seria + b.year_join));
	}

	std::string client_to_string() 
	{
		return first_name + " " + middle_name + " " + last_name + " Читательский билет: " +
			get_listener_bookd() + " Адрес: " + adress;
	}

	std::string get_listener_bookd() 
	{
		return seria + count_number + "-" + year_join;
	}

	int compare_bookd(std::string bookd) 
	{
		return get_listener_bookd().compare(bookd);
	}
};

//книги в библиотеке
struct book_data 
{
	std::string first_num_code, second_num_code;
	std::string name;
	std::string author;
	int year;
	bool is_have;
	bool empty;
	book_data() 
	{
		empty = true;
	}

	book_data(std::string first_num_code,
		std::string second_num_code,
		std::string name,
		std::string author,
		int year,
		bool is_have) {
		this->first_num_code = add_zero(first_num_code, 3);
		this->second_num_code = add_zero(second_num_code, 3);
		this->name = name;
		this->author = author;
		this->year = year;
		this->is_have = is_have;
		empty = false;
	}

	std::string book_to_string() 
	{
		std::string info_is_have;
		if (is_have)
		{
			info_is_have = "есть в наличии.";
		}
		else
		{
			info_is_have = "выдана на руки.";
		}

		return "Номер книги: " + get_num() + " Название: " + name + " Автор: " + author + " Год: " +
			std::to_string(year) + " В библиотеке: " + info_is_have;
	}

	std::string get_num() 
	{
		return first_num_code + "." + second_num_code;
	}

	int compare(book_data b) 
	{
		return get_num().compare(b.get_num());
	}

	int hash(int i)
	{
		return double_hash(get_num(), i);
	}
};

//данные о выданных книгах
struct ticket 
{
	std::string listener_bookd;
	std::string book_num;
	std::string take_time;
	std::string return_time;

	ticket() 
	{
	}

	ticket(std::string listener_bookd,
		std::string book_num,
		std::string take_time,
		std::string return_time) 
	{
		this->listener_bookd = listener_bookd;
		this->book_num = book_num;
		this->take_time = take_time;
		this->return_time = return_time;
	}

	int compare(ticket b)
	{
		return book_num.compare(b.book_num);
	}
};

//двунаправленный цикличный список
struct element 
{
	ticket data;
	element* next;
	element* prev;
};

//данные о читателях - авл-дерево
struct node
{
	listener key;
	int height;
	node* left;
	node* right;

	node(listener k) 
	{
		key = k;
		left = right = nullptr;
		height = 1;
	}
};

int hash_c = 7, hash_d = 17;
const int books_array_size = 1000;
const int months[]{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31 };		//количество дней в месяце
char chars[6] = { 'А', 'Ч', 'В','а','ч','в' };		//1 символ читательского билета
node* main_listener = nullptr;
element* head = nullptr;
int tickets_count = 0; 


void sort_tickets(int l, int r);
node* get_listener(node* p, std::string id);
bool check_string(std::string original);
int hash_first(std::string num);
int hash_second(std::string num);
bool is_substring(std::string official, std::string find);
void add(element*& head, ticket data);
ticket remove(element*& head, int pos);
element* get_element_at(element*& head, int pos);
void sort_tickets(int l, int r);
void delete_ticket_book_num(std::string book_id);
void delete_tickets_listener_bookd(std::string listener_bookd);
int height(node* p);
int bfactor(node* p);
void fixheight(node* p);
node* rotateright(node* p);
node* rotateleft(node* q);
node* balance(node* p);
node* insert(node* p, listener k);
node* findmin(node* p);
node* removemin(node* p);
//Хэш-таблица в программе
book_data* books_array = new book_data[books_array_size];
void look_all_listeners(node* p);
void remove_all(node*& p);
node* remove(node* p, std::string listener_bookd);
void find_listener_bookd(node* p, std::string listener_bookd);
void find_listener_name(node* p, std::string name);
void add_book(book_data a);
bool check_error();
std::string readDate();
void read_listener();
void read_book();
void look_all_books();
void delete_book(std::string num);
book_data* get_book(std::string num);
void find_book_num(std::string num);
void find_book_name(std::string name);
void read_ticket();
void return_ticket();
void add_book_library();
void remove_book_library();
void delete_all_books();
node* get_listener(node* p, std::string bookd);
void help_command();
short inputValidationShort(short min, short max);
bool inputValidation(char chr, bool message);

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);				// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);		// установка кодовой страницы win-cp 1251 в поток вывода
	unsigned short command;
	std::string str;
	while (true)
	{
		help_command();
		command = inputValidationShort(1, 17);
		switch (command)
		{
		case 1:
			read_listener();
			break;
		case 3:
			look_all_listeners(main_listener);
			break;
		case 2:
			std::cout << "Введите номер читательского билета вида ANNNN-YY,\n"
				<< "где A - тип доступа, NNNN - номер билета, YY год выдачи билета." << std::endl;
			std::cin.ignore((std::numeric_limits<short>::max)(), '\n');
			getline(std::cin, str);
			main_listener = remove(main_listener, str);
			break;
		case 4:
			remove_all(main_listener);
			while (head != nullptr) 
			{
				remove(head, 0);
			}
			break;
		case 5:
			std::cout << "Введите читательский билет: ANNNN-YY" << std::endl;
			std::cin.ignore();
			getline(std::cin, str);
			find_listener_bookd(main_listener, str);
			break;
		case 6:
			std::cout << "Ведите имя читателя: ";
			std::cin.ignore();
			std::cin >> str;
			std::cout << "----------" << std::endl;
			find_listener_name(main_listener, str);
			break;
		case 7:
			read_book();
			break;
		case 8:
			remove_book_library();
			break;
			//std::cout << "Введите номер книги 'NNN.MMM': ";
			//std::cin >> str;
			//delete_book(str);
			//break;
		case 9:
			look_all_books();
			break;
		case 10:
			delete_all_books();
			while (head != nullptr) {
				remove(head, 0);
			}
			break;
		case 11:
			std::cout << "Введите номер книги вида 'NNN.MMM': ";
			std::cin >> str;
			find_book_num(str);
			break;
		case 12:
			std::cin.clear();
			std::cout << "Введите название книги: " << std::endl;
			std::cin.ignore();
			getline(std::cin, str);
			find_book_name(str);
			break;
		case 13:
			read_ticket();
			break;
			//add_book_library();
			//break;
		case 14:
			return_ticket();
			break;
		case 15:
			
			break;
		case 16:
			
			break;
		default:
			break;
		}
		if (command == 17)
			break;
	}
	return 0;
}

bool check_string(std::string original) 
{
	bool flag = true;
	for (size_t i = 0; i < original.length(); ++i) {
		flag = false;
		for (int j = 0; j < 6; ++j) {
			if (original[i] == chars[j]) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			break;
		}
	}
	return flag;
}

//добавление нулей в номер при недостаточном количестве цифр
std::string add_zero(std::string original, size_t need_len) {
	std::string temp = original;
	while (temp.length() < need_len)
	{
		temp = "0" + temp;
	}
	return temp;
}

//Основная хэш-функция в программе
int hash_first(std::string num) {
	int hash = 0;
	int pow = 1;
	for (size_t i = 0; i < num.length(); ++i) {
		hash += (num[i]) * pow;
		pow *= 3;
	}
	return hash;
}

//Дополнительная хэш-функция в программе
int hash_second(std::string num) 
{
	int hash = 0;
	int pow = 1;
	for (size_t i = 0; i < num.length(); ++i) 
	{
		hash += (num[i]) * pow;
		pow *= 2;
	}
	return hash;
}

//Суммирование значений основной и дополнительной хеш-функций в программе
int double_hash(std::string num, int i) 
{
	int temp = hash_first(num) + i * hash_second(num);
	if (temp < 0)
	{
		return -temp;
	}
	return temp;
}

//Прямой поиск слова в тексте
bool is_substring(std::string official, std::string find) 
{
	if (find.length() > official.length()) 
	{
		return false;
	}
	int start = 0;
	while (official.length() - start >= find.length()) 
	{
		for (size_t i = 0; i < find.length(); ++i) 
		{
			if (official[start + i] != find[i]) 
			{
				++start;
				break;
			}
			else 
			{
				if (i == find.length() - 1) 
				{
					return true;
				}
			}
		}
	}
	return false;
}

void add(element*& head, ticket data)
{
	element* cur = head;
	if (head == nullptr) 
	{
		head = new element();
		head->data = data;
		head->next = head->prev = head;
	}
	else
	{
		element* temp = new element();
		temp->data = data;
		temp->next = head;
		head->prev->next = temp;
		temp->prev = head->prev;
		head->prev = temp;
	}
	++tickets_count;
	sort_tickets(0, tickets_count - 1); //!!!!!!!!!!!!!!!!!
}

ticket remove(element*& head, int pos) 
{
	element* cur = head;
	int count = 0;
	while (count != pos)
	{
		cur = cur->next;
		++count;
	}
	ticket temp = cur->data;
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	delete cur;
	--tickets_count;
	return temp;
}

element* get_element_at(element*& head, int pos) 
{
	if (head == nullptr)
	{
		return nullptr;
	}
	element* cur = head;
	int count = 0;
	while (count != pos)
	{
		cur = cur->next;
		++count;
	}
	return cur;
}

//Быстрая сортировка (Хоара)
void sort_tickets(int l, int r)
{
	int i = l, j = r, middle = (l + r) / 2;
	ticket x = get_element_at(head, middle)->data;
	element* i_element = get_element_at(head, i), * j_element = get_element_at(head, j);
	do {
		while (i_element->data.compare(x) < 0)
		{
			i_element = i_element->next;
			++i;
		}
		while (j_element->data.compare(x) > 0)
		{
			j_element = j_element->prev;
			--j;
		}
		if (i <= j) 
		{
			ticket temp = i_element->data;
			i_element->data = j_element->data;
			j_element->data = temp;
			i_element = i_element->next;
			++i;
			j_element = j_element->prev;
			--j;
		}
	} while (i <= j);
	if (i < r) 
	{
		sort_tickets(i, r);
	}
	if (l < j) 
	{
		sort_tickets(l, j);
	}
}

void delete_ticket_book_num(std::string book_id)
{
	element* cur = head;
	int pos = 0;
	if (head == nullptr) 
	{
		std::cout << "Книги не существует." << std::endl;
	}
	else 
	{
		while (cur->next != head && cur->data.book_num.compare(book_id) != 0) 
		{
			cur = cur->next;
			++pos;
		}
		if (cur->data.book_num.compare(book_id) != 0) 
		{
			std::cout << "Книги не существует." << std::endl;
			return;
		}
		remove(head, pos);
		std::cout << "Удалено." << std::endl;
		sort_tickets(0, tickets_count - 1); //!!!!!!!!!!!!!!!!!!!!!
	}
}

void delete_tickets_listener_bookd(std::string listener_bookd)
{
	element* cur = head;
	int pos = 0;
	if (head == nullptr) 
	{
		std::cout << "Книги не существует" << std::endl; //!!!!!!!!!!!!!!!!!!!!!!
	}
	else 
	{
		do {
			while (cur->next != head && cur->data.listener_bookd.compare(listener_bookd) != 0) 
			{
				cur = cur->next;
				++pos;
			}
			if (cur->data.listener_bookd.compare(listener_bookd) != 0) 
			{
				std::cout << "Книги не существует" << std::endl; //!!!!!!!!!!!!!!!!!!!!!!
				return;
			}
			cur = cur->next;
			remove(head, pos);
		} while (head != nullptr && cur != head);
		std::cout << "Удалено." << std::endl;
		if (tickets_count > 1) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
			sort_tickets(0, tickets_count - 1);
		}
	}
}

int height(node* p)
{
	return p ? p->height : 0;
}

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p)
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q)
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p)
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}

node* insert(node* p, listener k)
{
	if (!p)
	{
		std::cout << "Читатель добавлен." << std::endl;
		return new node(k);
	}
	int comp = k.compare(p->key);
	if (comp == 0) 
	{
		std::cout << "Читатель уже существует." << std::endl;
		return balance(p);
	}
	if (comp < 0)
	{
		p->left = insert(p->left, k);
	}
	else
	{
		p->right = insert(p->right, k);
	}
	return balance(p);
}

node* findmin(node* p)
{
	return p->left ? findmin(p->left) : p;
}

node* removemin(node* p)
{
	if (p->left == 0) 
	{
		return p->right;
	}
	p->left = removemin(p->left);
	return balance(p);
}

//Обратный обход дерева
void look_all_listeners(node* p) 
{
	if (!p) {
		return;
	}
	look_all_listeners(p->left);
	look_all_listeners(p->right);
	std::cout << p->key.client_to_string() << std::endl << "---" << std::endl;
}

//
void remove_all(node*& p) 
{
	if (!p) 
	{
		return;
	}
	remove_all(p->left);
	remove_all(p->right);
	delete p;
	p = nullptr;
}

//
node* remove(node* p, std::string listener_bookd)
{
	if (!p) return nullptr;
	int comp = listener_bookd.compare(p->key.get_listener_bookd());
	if (comp < 0)
	{
		p->left = remove(p->left, listener_bookd);
	} 
	else if (comp > 0)
	{
		p->right = remove(p->right, listener_bookd);
	} 
	else	// k == p->key
	{
		node* q = p->left;
		node* r = p->right;
		delete_tickets_listener_bookd(p->key.get_listener_bookd());
		delete p;
		if (!r) 
		{
			return q;
		}
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

//
void find_listener_bookd(node* p, std::string listener_bookd)
{
	if (!p) 
	{
		std::cout << "Нет читателя" << std::endl;
		return;
	}
	int comp = listener_bookd.compare(p->key.get_listener_bookd());
	if (comp < 0)
	{
		find_listener_bookd(p->left, listener_bookd);
	} 
	else if (comp > 0) 
	{
		find_listener_bookd(p->right, listener_bookd);
	}
	else // k == p->key
	{
		std::cout << p->key.client_to_string() << std::endl;
		//look_all_ticket_at_listener(p -> key);
	}
}

//поиск читателя по имени
void find_listener_name(node* p, std::string name)
{
	if (!p)
	{
		return;
	}
	if (is_substring(p->key.first_name, name) ||
		is_substring(p->key.middle_name, name) ||
		is_substring(p->key.last_name, name)) 
	{
		std::cout << p->key.client_to_string() << std::endl;
		std::cout << "----------" << std::endl;
	}
	find_listener_name(p->left, name);
	find_listener_name(p->right, name);
}

//
void add_book(book_data a) 
{
	int hs;
	int i = 0;
	while (true) 
	{
		hs = a.hash(i) % books_array_size;
		if (books_array[hs].empty) 
		{
			books_array[hs] = a;
			break;
		}
		else if (books_array[hs].compare(a) == 0)
		{
			std::cout << "Книга уже существует." << std::endl;
			return;
		}
		++i;
	}
}

//проверка ошибки ввода
bool check_error() 
{
	if (std::cin.fail())
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Ошибка ввода." << std::endl;
		return true;
	}
	return false;
}

//ввод даты
std::string readDate()
{
	std::string input;
	std::string res;
	int day, month, year;

	std::cout << "Ввод дня: ";
	std::cin >> day;
	if (!std::cin.fail())
	{
		if (day <= 0)
		{
			std::cout << "Ошибка ввода дня." << std::endl;
			return "";
		}
	}

	std::cout << "Ввод месяца: ";
	std::cin >> month;

	if (!std::cin.fail())
	{
		if (month <= 0 || month > 12)
		{
			std::cout << "Ошибка ввода месяца." << std::endl;
			return "";
		}
		if (months[month - 1] <= day)
		{
			std::cout << "Ошибка ввода дня." << std::endl;
			return "";
		}
	}
	std::cout << "Ввод года: ";
	std::cin >> year;
	
	if (!std::cin.fail()) 
	{
		if (year <= 1900 || year >= 2025) 
		{
			std::cout << "Ошибка ввода года.";
			return "";
		}
		return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
	}
	return "";
}

//добавление читателя
void read_listener()
{
	int count_number = 0;
	char seria[3];
	int year_join = 0;
	std::string first_name, last_name, middle_name;
	std::string pasport_data;
	std::string adress;
	std::string input;
	bool is_error;
	int count = 0;
	std::cin.ignore((std::numeric_limits<short>::max)(), '\n');
	do {
		std::cout << "Введите номер читательского билета 'ANNNN-YY': " << std::endl;
		getline(std::cin, input);
		is_error = check_error();
		if (!is_error)
		{
			count = sscanf(input.c_str(), "%1s%4d-%2d", seria, &count_number, &year_join);
			if (count != 3) 
			{
				std::cout << "Ошибка читательского билета." << std::endl;
			}
		}
	} while (is_error || count != 3 || !check_string(seria));
	do {
		std::cout << "Введите имя, фамилию и отчество: " << std::endl;
		std::cin >> first_name >> middle_name >> last_name;
		is_error = check_error();
		if (!is_error)
		{
			getline(std::cin, input);
			if (!input.empty())
			{
				std::cout << "Ошибка ввода имени." << std::endl;
			}
		}
	} while (is_error || !input.empty());
	do {
		std::cout << "Введите данные паспорта: ";
		getline(std::cin, pasport_data);
		if (pasport_data.empty()) 
		{
			std::cout << "Ошибка ввода данных паспорта." << std::endl;
		}
	} while (pasport_data.empty());
	do {
		std::cout << "Введите адрес: ";
		getline(std::cin, adress);
		if (adress.empty()) 
		{
			std::cout << "Ошибка ввода адреса." << std::endl;
		}
	} while (adress.empty());
	listener client = listener(std::to_string(count_number),
		std::string(seria),
		std::to_string(year_join),
		first_name,
		middle_name,
		last_name,
		pasport_data,
		adress);
	//delete region_code, num;
	//delete[] seria;
	main_listener = insert(main_listener, client);
}

//добавление книги
void read_book() 
{
	int first_num_code = 0, second_num_code = 0;
	std::string name;
	std::string author;
	int year;
	bool is_have;
	std::string input;
	bool is_error;
	int count = 0;
	do {
		std::cout << "Введите номер книги 'NNN.MMM': " << std::endl;
		std::cin.ignore((std::numeric_limits<short>::max)(), '\n');
		getline(std::cin, input);
		is_error = check_error();
		if (!is_error) 
		{
			count = sscanf(input.c_str(), "%3d.%3d", &first_num_code, &second_num_code);
			if (count != 2) 
			{
				std::cout << "Ошибка ввода номера книги." << std::endl;
			}
		}
	} while (is_error || count != 2);
	do {
		std::cout << "Введите название книги: ";
		//std::cin >> name;
		getline(std::cin, name);
		is_error = check_error();
		if (is_error)
		{
			getline(std::cin, input);
			if (!input.empty())
			{
				std::cout << "Ошибка в названии книги." << std::endl;
			}
		}
	} while (is_error || input.empty());
	do {
		std::cout << "Введите автора книги: ";
		getline(std::cin, author);
		//std::cin >> author;
		is_error = check_error();
		if (is_error)
		{
			getline(std::cin, input);
			if (!input.empty()) 
			{
				std::cout << "Ошибка ввода имени автора." << std::endl;
			}
		}
	} while (is_error || input.empty());
	do {
		std::cout << "Введите год издания книги: ";
		std::cin >> year;
		is_error = check_error();
		if (is_error) 
		{
			getline(std::cin, input);
			if (!input.empty())
			{
				std::cout << "Ошибка ввода года издания." << std::endl;
			}
		}
	} while (is_error || input.empty());
	is_have = true;
	book_data book = book_data(
		std::to_string(first_num_code),
		std::to_string(second_num_code),
		name,
		author,
		year,
		is_have);
	add_book(book);
}

//показать все книги
void look_all_books()
{
	int num = 0;
	for (int i = 0; i < books_array_size; ++i) 
	{
		if (!books_array[i].empty)
		{
			std::cout << ++num << ". " << books_array[i].book_to_string() << std::endl;
		}
	}
}

//удаление книги
void delete_book(std::string num) 
{
	int hs;
	int i = 0;
	while (true)
	{
		hs = double_hash(num, i) % books_array_size;
		if (books_array[hs].empty)
		{
			std::cout << "Нет книг по введенному номеру." << std::endl;
			return;
		}
		else if (books_array[hs].get_num().compare(num) == 0) 
		{
			delete_ticket_book_num(num);
			books_array[hs] = book_data();
			std::cout << "Книга удалена." << std::endl;
			return;
		}
		++i;
	}
}

//данные о книге
book_data* get_book(std::string num) 
{
	int hs;
	int i = 0;
	while (true) 
	{
		hs = double_hash(num, i) % books_array_size;
		if (books_array[hs].empty || books_array[hs].get_num().compare(num) == 0) 
		{
			return &books_array[hs];
		}
		++i;
	}
}

//поиск книги по номеру
void find_book_num(std::string num) 
{
	book_data* temp = get_book(num);
	if (temp->empty) 
	{
		std::cout << "Нет книг по введенному номеру." << std::endl;
	}
	else 
	{
		std::cout << temp->book_to_string() << std::endl;
	}
}

//поиск книги по названию
void find_book_name(std::string name)
{
	int num = 0;
	for (int i = 0; i < books_array_size; ++i) 
	{
		if (!books_array[i].empty)
		{
			++num;
			if (books_array[i].name.compare(name) == 0) 
			{
				std::cout << num << ". " << books_array[i].book_to_string() << std::endl;
			}
		}
	}
}

//выдача книги читателю
void read_ticket() 
{
	int count_number = 0;
	char seria[3];
	int year_join = 0;
	std::string input;
	bool is_error;
	int count = 0, count_try = 0;
	node* p = nullptr;
	do {
		count_try = 0;
		std::cout << "Введите номер читательского билета 'ANNNN-YY': " << std::endl;
		std::cin.ignore((std::numeric_limits<short>::max)(), '\n');
		getline(std::cin, input);
		is_error = check_error();
		if (!is_error) 
		{
			count = sscanf(input.c_str(), "%1s%4d-%2d", seria, &count_number, &year_join);
			if (count != 3) 
			{
				std::cout << "Ошибка ввода читательского билета." << std::endl;
				//count_try++;
			}
			else 
			{
				p = get_listener(main_listener, seria + add_zero(std::to_string(count_number), 4) + "-" +
					add_zero(std::to_string(year_join), 2));
			}
		}
		//count_try++;
	} while (is_error || count != 3 || p == nullptr);
	int first_num_code = 0, second_num_code = 0;
	book_data* book = nullptr;
	do {
		count_try = 0;
		std::cout << "Введите номер книги 'NNN.MMM': " << std::endl;
		getline(std::cin, input);
		is_error = check_error();
		if (!is_error) 
		{
			count = sscanf(input.c_str(), "%3d.%3d", &first_num_code, &second_num_code);
			if (count != 2) 
			{
				std::cout << "Ошибка ввода номера." << std::endl;
				//count_try++;
			}
			else 
			{
				book = get_book(add_zero(std::to_string(first_num_code), 3) + "." +
					add_zero(std::to_string(second_num_code), 3));
				if (!book->empty && !book->is_have)
				{
					std::cout << "Книга отсутствует в библиотеке." << std::endl;
					return;
				}
			}
		}
		//count_try++;
	} while (is_error || count != 2 || book->empty || !book->is_have);
	std::string take_date;
	do {
		std::cout << "Ведите день взятия книги читателем: " << std::endl;
		take_date = readDate();
	} while (take_date.empty());
	std::string return_date;
	do {
		std::cout << "Введите день возврата книги читателем: " << std::endl;
		return_date = readDate();
	} while (return_date.empty());
	book->is_have = false;
	ticket tick = ticket(p->key.get_listener_bookd(),
		book->get_num(),
		take_date,
		return_date);
	add(head, tick);
	std::cout << "Книга выдана читателю." << std::endl;
	//delete first_num_code, second_num_code, num, region_code;
	//delete[] first_code, seria, second_code;
}

//возврат книги в библиотеку
void return_ticket() 
{
	std::string input;
	bool is_error;
	int count = 0;
	int first_num_code = 0, second_num_code = 0;
	book_data* book = nullptr;
	std::cin.ignore((std::numeric_limits<short>::max)(), '\n');
	do {
		std::cout << "Введите номер книги 'NNN.MMM' для возврата " << std::endl;
		getline(std::cin, input);
		is_error = check_error();
		if (!is_error) 
		{
			count = sscanf(input.c_str(), "%3d.%3d", &first_num_code, &second_num_code);
			if (count != 2)
			{
				std::cout << "Ошибка ввода номера." << std::endl;
			}
			else 
			{
				book = get_book(add_zero(std::to_string(first_num_code), 3) + "." +
					add_zero(std::to_string(second_num_code), 2));
				if (!book->empty && !book->is_have) 
				{
					std::cout << "Книга возвращена в библиотеку." << std::endl;
					//book->is_have = true;
					//delete first_num_code, second_num_code;
					//delete[] first_code, second_code;
					return;
				}
			}
		}
	} while (is_error || count != 2 || book->empty || book->is_have);
	book->is_have = true;
	//delete first_num_code, second_num_code;
	//delete[] first_code, second_code;
	delete_ticket_book_num(book->get_num());
}


//добавление номера книги в библиотеку?
void add_book_library() 
{
	int first_num_code = 0, second_num_code = 0;
	std::string input;
	bool is_error;
	int count = 0;
	do {
		std::cout << "Ввод книги по номеру 'NNN.MMM': " << std::endl;
		getline(std::cin, input);
		is_error = check_error();
		if (!is_error) 
		{
			count = sscanf(input.c_str(), "%3d.%3d", &first_num_code, &second_num_code);
			if (count != 2)
			{
				std::cout << "Ошибка ввода номера" << std::endl;
			}
		}
	} while (is_error || count != 2);
	book_data* book = get_book(add_zero(std::to_string(first_num_code), 3) + "." +
		add_zero(std::to_string(second_num_code), 2));
	if (!book->empty)
	{
		if (book->is_have)
		{
			book->is_have = false;
		}
	}
	//delete first_num_code, second_num_code;
	//delete[] first_code, second_code;
}

//удаление книги по номеру
void remove_book_library() 
{
	int first_num_code = 0, second_num_code = 0;
	std::string input;
	bool is_error;
	int count = 0;
	do {
		std::cout << "Введите номер книги 'NNN.MMM': " << std::endl;
		getline(std::cin, input);
		is_error = check_error();
		if (!is_error) 
		{
			count = sscanf(input.c_str(), "%3d.%3d", &first_num_code, &second_num_code);
			if (count != 2)
			{
				std::cout << "Ошибка ввода номера" << std::endl;
			}
		}
	} while (is_error || count != 2);
	book_data* book = get_book(add_zero(std::to_string(first_num_code), 3) + +"." +
		add_zero(std::to_string(second_num_code), 2));
	if (!book->empty) 
	{
		if (!book->is_have)
		{
			book->is_have = true;
		}
	}
	//delete first_num_code, second_num_code;
	//delete[] first_code, second_code;
}

//удаление всех книг из библиотеки
void delete_all_books()
{
	delete[] books_array;
	books_array = new book_data[books_array_size];
	std::cout << "Все книги удалены." << std::endl;
}

node* get_listener(node* p, std::string bookd)
{
	if (!p) 
	{
		return nullptr;
	}
	int comp = p->key.get_listener_bookd().compare(bookd);
	if (comp == 0)
	{
		return p;
	}
	if (comp < 0)
	{
		return get_listener(p->left, bookd);
	}
	else
	{
		return get_listener(p->right, bookd);
	}
}

//интерфейс команд
void help_command()
{
	std::cout << "Команды: \n";
	std::cout << "\t1. Добавление нового читателя.\n";
	std::cout << "\t2. Удаление читателя.\n";
	std::cout << "\t3. Вывести весь список читателей.\n";
	std::cout << "\t4. Удалить весь список читателей.\n";
	std::cout << "\t5. Поиск по номеру читательского билета.\n";
	std::cout << "\t6. Поиск по имени читателя.\n";
	std::cout << "\t7. Добавить книгу.\n";
	std::cout << "\t8. Удалить книгу.\n";
	std::cout << "\t9. Отобразить список книг.\n";
	std::cout << "\t10. Удалить все книги.\n";
	std::cout << "\t11. Поиск книги по номеру.\n";
	std::cout << "\t12. Поиск книги по названию.\n";
	std::cout << "\t13. Выдать книгу читателю..\n";
	std::cout << "\t14. Вернуть книгу в библиотеку.\n";
	//std::cout << "\t15. Показать список выданных книг.\n";
	//std::cout << "\t16. Сохранить данные.\n";
	std::cout << "\t17. Выход из программы.\n";
	std::cout << "Введите номер команды.\n";
	std::cout << "Команда: ";
};

//ввод команд меню
short inputValidationShort(short min, short max) 
{
	while (true) 
	{
		unsigned short temp = max + 10; char chr; std::cin >> chr;
		if (inputValidation(chr, true)) 
		{
			std::cin >> temp;
			if (temp >= min && temp <= max) 
			{ 
				return temp; 
			}
			else
			{
				std::cout << "Введенное значение выходит за рамки допустимого диапазона!" << std::endl;
				std::cout << "Допустимый диапозон: " << min << " - " << max << std::endl; 
				//устанавливает максимальное кол-во элементов для игнорирования, \n разделитель, после которого cin перестает игнорировать
			}
		}
		else
		{
			std::cout << "Некорректный ввод!" << std::endl;
		}
	}
}

//проверка валидности ввода
bool inputValidation(char chr, bool message) 
{
	if (isdigit(static_cast<unsigned char>(chr)))
	//проверка, является ли символ десятичной цифрой и обход проблемы с кириллицей
	{
		if (message)
		{
			std::cin.unget(); //возврат символа обратно в поток
			return true;
		}
	}
	else
	{
		return false;
	}
}
 