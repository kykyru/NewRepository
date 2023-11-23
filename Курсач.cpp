#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class element {
public:

	static int number, sum;
	static float  average;
	int data, row, column;
	element* right, * left, * top, * bottom;

	element(int udata) {
		data = udata;
		number++;
		sum += data;
		average = float(sum) / float(number);

		right = 0;
		left = 0;
		top = 0;
		bottom = 0;
	}

	element& operator[](int column) {
		element* node = this;
		for (int i = 0; i < column; i++) {
			node = node->right;
		}
		return *node;
	}

	void reini() {
		element::sum -= this->data;
		cout << "Введите новое значение ячейки : ";
		cin >> this->data;

		element::sum += this->data;
		element::average = float(element::sum) / float(element::number);
	}

};
int element::number = 0;
float element::average = 0;
int element::sum = 0;

class matrix {

	void create(bool choise) {

		for (int i = 0; i < size_row; i++) {
			for (int j = 0; j < size_column; j++) {

				switch (choise)
				{
				case true:
					cout << "Введите желаемое значение элемента " << i << ' ' << j << " : ";
					cin >> udata;
					break;

				default:
					udata = rand() % 89 + 10;
					break;
				}

				if (head_row == 0) {
					now = new element(udata);

					if (i == 0) {
						head = now;
						head_row = now;
					}
					else {
						head_row = now;
						now->top = up;
						up->bottom = now;
					}
				}
				else {
					prev = now;
					now->right = new element(udata);
					now = now->right;
					now->left = prev;
					if (i > 1) {
						up = up->right;
						now->top = up;
						up->bottom = now;
					}
				}
			}
			up = head_row;
			head_row = 0;
		}
		tail = now;
	}

public:
	int size_row, size_column, udata;
	element* tail = 0, * head = 0, * head_row = 0, * up = 0, * down = 0, * now = 0, * prev = 0;

	matrix(int user_size_row, int user_size_column, bool choise) {
		size_row = user_size_row;
		size_column = user_size_column;
		create(choise);
	}

	element& operator[](int row) {
		now = head;
		for (int i = 0; i < row; i++) {
			now = now->bottom;
		}
		return *now;
	}

};

ostream& operator<<(ostream& out, const matrix& point) {
	//нужно добавить геттеры и сеттеры
	element* now = point.head, * down = point.head->bottom;

	for (int i = 0; i < point.size_row; i++) {

		for (int j = 0; j < point.size_column; j++) {
			out << now->data << "  ";
			now = now->right;
		}
		out << endl << endl;
		if (i < point.size_row - 1) {
			now = down;
			down = down->bottom;
		}

	}

	out << "Кол-во элементов: " << point.head->number << endl << "Сумма элементов: " << point.head->sum << endl << "Среднее значение: " << point.head->average;
	return out;
}
ostream& operator<<(ostream& out, const element& point) {

	out << point.data;
	//out << "Значение конкретретного элемента " << point.row << ' ' << point.column << ": " << point.data << endl << "Сумма всех существующих элементов: " << point.sum << endl << "Всего элементов: " << point.number << endl << "Их среднее значение: " << point.average;
	return out;
}

void main() {

	setlocale(LC_ALL, "ru");
	srand(time(0));
	matrix a(2,2, true);

	cout << a << endl << endl << endl;
	cout << a[2][1] << endl << endl << endl;

	for (int i = 0; i < a.size_row; i++) {
		for (int j = 0; j < a.size_column; j++) {
			cout << a[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
	a[0][0].reini();
	cout << a << endl << endl << endl;
}

/*Двумерный список
Обязательные поля :
 Номер строки(назначается автоматически);
 Номер столбца(назначается автоматически);
 Значение ячейки(считывается из файла или задаётся случайно);
 Сумма всех значений ячеек;
 Среднее значение всех ячеек;
 Счётчик количества ячеек.
Возможности класса :
 Автоматическая инициализация при создании экземпляра;
 Возможность ручной инициализации значения ячеек;
 Вывод данных на экран;
 Ручная смена значения ячейки с пересчётом зависимых полей
Возможности программы :
 Выбор размера «массива»(не более 10х10);
 Вывод всех экземпляров;
 Вывод одного экземпляра с заданным расположением;
 Вывод выбранной строки или столбца в прямом и обратном направлении с подсчётом суммы и среднего выведенных значений;.........................
 Фильтр вывода экземпляров(например только чётные, больше 5 и пр.);...........................................................................
 Поиск кратчайшего пути до выбранного экземпляра;.............................................................................................
 Добавление / удаление строк и столбцов;......................................................................................................
 Меню пользователя, позволяющее использовать все возможности программы и класса, узнать информацию об авторе, а также выйти из программы......

Требования к программе :
 Организация данных в виде созданного вручную списка;
 Каждая ячейка должна иметь связь с каждой соседней(т.е. 4 связи);
 Обязательное использование принципов ООП(особенно инкапсуляции);.............................................................................
 Максимально предусмотренные ошибки пользователя;.............................................................................................
 Использование статических методов, константных методов, и параметров по умолчанию;...........................................................
 Перегрузка квадратных скобочек для работы со списком;
 Красивое оформление.*/