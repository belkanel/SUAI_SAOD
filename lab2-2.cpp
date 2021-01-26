#include <iostream>
#include <cctype>

struct node
{
	int a;
	node* next;
};

bool verify_input(const char* arr, size_t n)
{
	int is_digit = 0;
	int dots_number = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == 0) break;
		is_digit = isdigit(arr[i]);
		if (!is_digit)
		{
			if (i == 0 && arr[i] == '-')
			{
				is_digit = 1;
				continue;
			}
		}
	}
	return is_digit;
}

int elem_number(node*& head)
{
	if (head == NULL) return 0;
	int i = 0;
	node* ptr = head;
	do {
		ptr = ptr->next;
		i++;
	} while (ptr != head);
	return i;
}

node* addnew(node*& last, int val)
{
	node* newitem = new node;
	newitem->a = val;
	if (last == NULL)
	{
		last = newitem;
		newitem->next = newitem;
	}
	else
	{
		newitem->next = last->next;
		last->next = newitem;
	}
	return newitem;
}

void addnode(int n, node*& head) {
	char x[100];
	node*& current = head;
	for (int i = 0; i < n; i++)
	{
		do
		{
			std::cout << "Введите элемент (" << i << "): ", std::cin >> x;
			if (!verify_input(x, 100)) std::cout << "Ошибка введите цифру!" << std::endl;
		} while (!verify_input(x, 100));
		current = addnew(current, atof(x));
	}
	if (n > 0) head = current->next;
}

node* get_by_index(int index, node*& head)
{
	node* ptr = head;
	for (int i = 0; i < index - 1; i++)ptr = ptr->next;
	return ptr;
}

void insert(int number, int val, node*& head)
{
	node* newitem = new(node);
	newitem->a = val;
	newitem->next = newitem;
	if (head == NULL)
	{
		head = newitem;
		return;
	}
	int n = elem_number(head);
	int previous = number;
	if (previous <= 0)previous = n;
	node* previousitem = get_by_index(previous, head);
	newitem->next = previousitem->next;
	previousitem->next = newitem;
	if (number == 0) head = newitem;
}

int average(node*& head, int n)
{
	int i = 0;
	int s = 0;
	node* ptr = head;
	do {
		s += ptr->a;
		ptr = ptr->next;
		i++;
	} while (i < n && ptr != head);
	return s / i;
}

node* list_averages(node*& head)
{
	node* ptr = head;
	node* result = NULL;
	int n = elem_number(head);
	if (n == 0) return NULL;
	while (n > 0)
	{
		result = addnew(result, average(head, n));
		n--;
	}
	return result->next;
}

void delete_data(int number, node*& head) {
	node* ptr = head;
	node* deleted = NULL;
	int n = elem_number(head);
	int previous = number - 2;
	if (previous < 0) previous = n - 1;
	for (int i = 0; i < previous; i++)ptr = ptr->next;
	deleted = ptr->next;
	ptr->next = (ptr->next)->next;
	delete(deleted);
	if (number == 1)
	{
		if (n == 1)head = NULL;
		else head = ptr->next;
	}
}

void printnode(node*& head) {
	node* ptr = head;
	do
	{
		std::cout << (ptr->a) << " ";
		ptr = ptr->next;
	} while (ptr != head);
	std::cout << std::endl;
}

int main() {
	setlocale(LC_ALL, "russian");
	int n, number;
	double q, dataitem;
	node* head = NULL;
	node* loop = NULL;
	char x[100];
	n = 0;
	int choose = 6;
	while (choose != 0)
	{
		std::cout << "1. Создать список" << std::endl;
		std::cout << "2. Добавить элемент в список" << std::endl;
		if (head != NULL)
		{
			std::cout << "3. Удалить элемент из списка" << std::endl;
			std::cout << "4. Получить список, содержащий среднее арифметическое всех элементов исходного списка и списков, последовательно уменьшающихся на один элемент." << std::endl;
			std::cout << "5. Вывести список на экран" << std::endl;
		}
		std::cout << "0. Выход" << std::endl;
		do
		{
			std::cout << "Выберите пункт: ", std::cin >> x;
		} while (!isdigit(x[0]));
		choose = atof(x);
		std::cout << "---------------------" << std::endl;
		std::cout << std::endl;

		switch (choose) {
		case 1: {
			do
			{
				std::cout << "Введите количествово элементов в списке: ", std::cin >> x;
			} while ((!isdigit(x[0])) || (x[0] == '0'));
			n = atof(x);
			addnode(n, head);
			break;
		}
		case 2: {
			do
			{
				std::cout << "Введите порядковый номер элемента от 0 до " << n << ", за которым расположить новый: ", std::cin >> x;
			} while ((!isdigit(x[0])) || (atof(x) < 0) || (atof(x) > n));
			number = atof(x);
			std::cout << " ";
			do
			{
				std::cout << "Введите новый элемент: ", std::cin >> x;
			} while (!verify_input(x, 100));
			dataitem = atof(x);
			insert(number, dataitem, head);
			n++;
			break;
		}
		case 3:
		{
			do
			{
				std::cout << "Введите номер элемента, который хотите удалить: ", std::cin >> x;
			} while ((!isdigit(x[0])) || (x[0] == '0') || (atof(x) < 0) || (atof(x) > n));
			number = atof(x);
			delete_data(number, head);
			n--;
			break;
		}
		case 4:
		{
			node* result = list_averages(head);
			printnode(result);
			break;
		}
		case 5:
		{
			printnode(head);
			break;
		}
		case 0:
		{
			return 0;
			break;
		}
		default:std::cout << "Error\n";
		}
	}

	system("pause");
	return 0;
}