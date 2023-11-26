#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <ctime>
#include <cmath>
#include <Windows.h>
#include <vector>
class Printer
{
public:
	HANDLE hStdout;

	Printer(int width) {
		width_ = width;
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	~Printer() {}
	void print_cord(int x, int y, int value) {
		COORD destCoord;
		destCoord.X = x * (width_ + 1);
		destCoord.Y = y;
		SetConsoleCursorPosition(hStdout, destCoord);
		std::cout << value;
		std::cout.flush();
	}
private:
	int width_ = 0;

};
class matrix
{
public:
	int rows;
	int collumns;
	int k = 0;
	int* data = nullptr;
	int get_rnd_val() {
		/*return 1 + rand() % (collumns * rows);*/
		return k++;
	}
	matrix(int rows_, int collumns_)
		:rows(rows_)
		, collumns(collumns_) {
		data = new int[collumns * rows];
	}
	~matrix() {
		delete[] data;
	}
	int *get_end() {
		int* end = data + (rows * collumns - 1);
		return end;
	}
	int get_val_by_index(int column_index, int row_index) {
		int x = 1 * column_index;
		int y = collumns * row_index;
		int asd = *(data + x + y);
		return asd;
	}
	int *get_adres_by_index(int column_index, int row_index) {
		int x = 1 * column_index;
		int y = collumns * row_index;
		return data + x + y;
	}
	void fill_matr() {
		for (int *start = data; start <= get_end(); start++) {
			*start = 1 + rand() % (collumns * rows);
		}
	}
	void swap_squares(int square_0, int square_1) {
		auto a = get_square(square_0);
		auto b = get_square(square_1);
		for (int i = 0; i < a.size(); i++) {
			std::swap(*a[i], *b[i]);
		}
	}
	void print_all() {
		int s = 0;
		int v = 0;
		int z = collumns * rows;
		while (z > 0)
		{
			z = z / 10; ++v;
		}
		for (int* start = data; start <= get_end(); start++) {
			std::cout << std::setw(v) << *start << " ";
			s++;
			std::this_thread::sleep_for(std::chrono::microseconds(500));

			if (s % collumns == 0) {
				std::cout << "\n";
			}
		
		}
		std::cout << std::endl;
	}
	void fill_and_paint() {
		int s = 0;
		int v = 0;
		int z = collumns * rows;
		while (z > 0)
		{
			z = z / 10; ++v;
		}
		for (int* start = data; start <= get_end(); start++) {
			*start = 1 + rand() % (collumns * rows);
			std::cout << std::setw(v) << *start << " ";
			s++;
			std::this_thread::sleep_for(std::chrono::microseconds(50));
			//system("cls");

			if (s % collumns == 0) {
				std::cout << "\n";
			}
		}

	}
	std::vector<int*> get_square(int number) {
		int min_x = (number == 0 || number == 2) ? 0 : collumns / 2;
		int max_x = (number == 0 || number == 2) ? collumns / 2 : collumns;
		int min_y = (number == 0 || number == 1) ? 0 : rows / 2;
		int max_y = (number == 0 || number == 1) ? rows/2 : rows;
		std::vector<int*> square;
		for (int y = min_y; y < max_y; y++) {
			for (int x = min_x; x < max_x; x++) {
				square.push_back(get_adres_by_index(x, y));
			}
		}
		return square;
	}
	void set_value(int column_index, int row_index, int value_to_set) {
		int x = 1 * column_index;
		int y = collumns * row_index;
		int* start = data + x + y;
		*start = value_to_set;
		/*std::cout << "Индекс колонны " << column_index << " Индекс строчки " << row_index << std::endl;*/
	}
	void print_type_B() {
		int z = collumns * rows;
		int v = 0;
		while (z > 0)
		{
			z = z / 10; ++v;
		}
		Printer pr(v);
		int x = 0, y = 0;
		int iter = 0;
		while (true) {
			if (iter % 2 == 0) {
				for (y = 0; y < collumns; y++) {
					int random = get_rnd_val();
					set_value(x, y, random);
					pr.print_cord(x, y, random);
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
					if (x == rows - 1 and y == collumns - 1) {
						return;
					}
				}

				x++;
			}
			if (iter % 2 == 1) {
				for (y = collumns - 1; y > -1; y--) {
					int random = get_rnd_val();
					set_value(x, y, random);
					pr.print_cord(x, y, random);
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
					if (x == rows - 1 and y == 0) {
						return;
					}
				}

				x++;
			}
			iter++;
		}
	}
	void get_menu() {
		std::cout << "===========================================МЕНЮ===========================================" << std::endl;
		std::cout << "==========================================================================================" << std::endl;
		std::cout << "============= Введите цифру 1 чтобы заполнить и вывести матрицу по заданию 1 =============" << std::endl;
		std::cout << "=============== Введите цифру 2 чтобы переместить блоки матрицы по заданию 2 =============" << std::endl;
		std::cout << "===================== Введите цифру 3 чтобы отсортировать матрицу 3 ======================" << std::endl;
		std::cout << "======================= Введите цифру 4 чтобы выполнить задание 4 ========================" << std::endl;
	} 
	void print_type_A() {
		int z = collumns * rows;
		int v = 0;
		int count_iter = (collumns > rows) ? rows * 2 - 1 : rows + collumns - 1;
		while (z > 0)
		{
			z = z / 10; ++v;
		}
		Printer r(v);
		int min_x = 0,max_x = collumns, min_y = 0, max_y = rows;
		int x = 0, y = 0;
		int iter = 0;

		for (int i = 0; i < count_iter; i++) {
			
			/*int* min = (iter % 2) ? &min_x: &min_y;
			int* max = (iter % 2) ? &max_x : &max_y;
			int *c = (iter % 2) ?  &x : & y;*/
			int* from = nullptr;
			int* to = nullptr;
			int* c = nullptr;
			if (iter == 0) {
				from = &min_x;
				to = &max_x;
				c = &x;
				min_y++;
			}
			if (iter == 1){
				from = &min_y;
				to = &max_y;
				c = &y;
				max_x--;
			}
			if (iter == 2) {
				to = &min_x;
				from = &max_x;
				c = &x;
				max_y--;
			}
			if (iter == 3) {
				to = &min_y;
				from = &max_y;
				c = &y;
				min_x++;
			}
			if (iter == 0 || iter == 1) {
				for (*c = *from; *c < *to; ++*c) {
					int random = get_rnd_val();
					set_value(x, y, random);
					r.print_cord(x, y, random);
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
				}
				(*c)--;
			}
			if (iter == 2 || iter == 3) {
				for (*c = *from-1; *c >= *to; --*c) {
					int random = k++;
					set_value(x, y, random);
					r.print_cord(x, y, random);
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
				}
				(*c)++;
			}
			iter++;
			if (iter == 4) {
				iter = 0;
			}
		}
	}
private:

};


int main() {
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	int helper;
	int M, N;
	std::cout << "Введите M матрицы \n";
	std::cin >> M;
	std::cout << "Введите N матрицы \n";
	std::cin >> N;
	matrix a(M, N);
	int number;
	Printer end(1);
	a.get_menu();
	while (true) {
		std::cout << "Выбери номер задания \n";
		std::cin >> number;
		if (number == 0) {
			std::cout << "Введите M матрицы \n";
			std::cin >> M;
			std::cout << "Введите N матрицы \n";
			std::cin >> N;
			matrix a(M, N);
		}
		if (number == 1) {
			std::cout << "Выберите каким типом будет заполнена и выведена матрици A/B 1/2 \n";
			std::cin >> helper;
			if (helper == 1) {
				system("cls");
				a.print_type_A();
				end.print_cord(0, a.collumns, 0);
				a.get_menu();
			}
			else {
				system("cls");
				a.print_type_B();
				end.print_cord(0, a.collumns, 0);
				a.get_menu();
			}
		}
		if (number == 2) {
			std::cout << "выберите как будем перемещать a/b/c/d -> 1/2/3/4 \n";
			std::cin >> helper;
			if (helper == 1){
				a.print_all();
				std::cout << std::endl;
				a.swap_squares(0, 1);
				a.print_all();
				std::cout << std::endl;
				a.swap_squares(1, 3);
				a.print_all();
				std::cout << std::endl;
				a.print_all();
				std::cout << std::endl;
				a.swap_squares(3, 2);
				a.print_all();
				std::cout << std::endl;
				a.swap_squares(2, 0);
				a.print_all();
				std::cout << std::endl;

			}
			if (helper == 2) {
				a.print_all();
				std::cout << std::endl;
				a.swap_squares(0, 3);
				a.print_all();
				std::cout << std::endl;
				a.swap_squares(1, 2);
				a.print_all();
				std::cout << std::endl;
			}
			if (helper == 3) {
				a.print_all();
				std::cout << std::endl;
				a.swap_squares(0, 2);
				a.print_all();
				std::cout << std::endl;
				a.swap_squares(1, 3);
				a.print_all();
				std::cout << std::endl;
			}
			if (helper == 4) {
				a.print_all();
				std::cout << std::endl;
				a.swap_squares(0, 1);
				a.print_all();
				std::cout << std::endl;
				a.swap_squares(2, 3);
				a.print_all();
				std::cout << std::endl;
			}
		}
		if (number == 3) {
			for (int* i = a.data; i < a.get_end(); i++) {
				for (int* j = a.data; j < a.get_end(); j++) {
					if (*j > *(j + 1))
						std::swap(*j, *(j + 1));
				}
			}
		}
	}
	//Printer print;
	//print.print_cord(15, 20, 42);
	//print.print_cord(15, 21, 43);
	//a.fill_matr();
	//a.print_all();
	//a.set_value(3, 3, 99);
	//a.print_all();
	//std::cout << "\n";
	//a.print_test();
	//a.print_type_A();
	std::cout << std::endl;
	a.print_all();
	a.swap_squares(0, 1);
	a.swap_squares(2, 3);
	a.print_all();
	system("cls");
	a.print_type_A();
	return 0;

}