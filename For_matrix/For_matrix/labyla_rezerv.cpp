#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <ctime>
#include <cmath>
#include <Windows.h>
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
		destCoord.X = x*width_;
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
	int* data = nullptr;
	int get_rnd_val() {
		return 1 + rand() % (collumns * rows);
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
	void fill_matr() {
		for (int *start = data; start <= get_end(); start++) {
			*start = 1 + rand() % (collumns * rows);
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
			std::cout << std::setw(v) << *start << " " << start << " ";
			s++;
			std::this_thread::sleep_for(std::chrono::microseconds(500));
			//system("cls");

			if (s % collumns == 0) {
				std::cout << "\n";
			}
		}
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
	void set_value(int column_index, int row_index, int value_to_set) {
		int x = 1 * column_index;
		int y = collumns * row_index;
		int* start = data + x + y;
		*start = value_to_set;
		/*std::cout << "Индекс колонны " << column_index << " Индекс строчки " << row_index << std::endl;*/
	}
	void good_fill_print() {
		int z = collumns * rows;
		int v = 0;
		int count_iter = (collumns > rows) ? rows * 2 - 1 : rows + collumns - 1;
		while (z > 0)
		{
			z = z / 10; ++v;
		}
		Printer r(v);
		int min_x = 0,max_x = collumns-1, min_y = 0, max_y = rows-1;
		int x = 0, y = 0;
		int iter = 0; // Сделать пересислением

		for (int i = 0; i < count_iter; i++) {
			
			/*int* min = (iter % 2) ? &min_x: &min_y;
			int* max = (iter % 2) ? &max_x : &max_y;
			int *c = (iter % 2) ?  &x : & y;*/
			int* min = nullptr;
			int* max = nullptr;
			int* c = nullptr;
			if (iter == 0) {
				min = &min_x;
				max = &max_x;
				c = &x;
				min_y++;
			}
			if (iter == 1){
				min = &min_y;
				max = &max_y;
				c = &y;
				max_x--;
			}
			if (iter == 2) {
				min = &min_x;
				max = &max_x;
				c = &x;
				max_y--;
			}
			if (iter == 3) {
				min = &min_y;
				max = &max_y;
				c = &y;
				min_x++;
			}
			//if (max_x == min_x && max_y == min_y) {
			//}
			// Записать значение в матрицу по нужной координате
			// Распечатать значение в нужной координате
			// Вычислить следующую координату
			for ( *c = *min; *c < *max; ++*c) {
				int random = get_rnd_val();
				set_value(x, y, random);
				if (iter == 0) {
					r.print_cord(x,min_y, random);
				}
				if (iter == 1) {
					r.print_cord(max_x * (v+1), y, random);
				}
				if (iter == 2) {
					r.print_cord((collumns*(v+1) - x * (v + 1) - (v + 1)) - (v+1), max_y, random);
				}
				if (iter == 3) {
					r.print_cord((min_x-1)*(v+1), rows - y, random);
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			iter++;
			if (iter == 4) {
				iter = 0;
			}
		}
	}
	void print_test() {
		int x = 0;
		int y = 0;
		int s = 1;
		int v = 0;
		int z = collumns * rows;
		while (z > 0)
		{
			z = z / 10; ++v;
		}
		for (int* start = data + x + y * rows; start <= get_end(); start++) {
			s++;
			std::cout << std::setw(v+1) << " " << *start;
			x++;
			std::this_thread::sleep_for(std::chrono::microseconds(5000));
			if (x == collumns and s%2 == 1) {
				x = 0;
				y++;
				std::cout << "\n";
			}
		}
	}

private:

};


int main() {

	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	//Printer print;
	//print.print_cord(15, 20, 42);
	//print.print_cord(15, 21, 43);
	matrix a(6,6);
	//a.fill_matr();
	//a.print_all();
	//a.set_value(3, 3, 99);
	//a.print_all();
	//std::cout << "\n";
	//a.print_test();
	a.good_fill_print();
	return 0;
}