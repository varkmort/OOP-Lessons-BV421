#include <iostream>
#include <string>

#include <functional>
#include <algorithm>


#include <vector>
#include <thread>
#include <random>


//void PrintResult(int a, int b, int(*func)(int, int)) {
//	std::cout << "\n\nresult of your action is " << func(a, b);
//}

void PrintResult(int a, int b, std::function<int(int,int)> func) {
	std::cout << "\n\nresult of your action is " << func(a, b);
}


int Summ(int a, int b) { return a + b; }
int Multiply(int a, int b) { return a * b; }


class ArrayWrap {
public:

	std::vector<int> data;

	void initialize() {
		std::random_device rd;
		std::mt19937 prov(rd());
		std::uniform_int_distribution<int> distr(100, 999);
		for (auto& i : data)
		{
			i = distr(prov);
		}
	}

};


int main()
{
	std::vector<int> numbers(100);

	//[ ]( )->type{   }
	// |  |   |   	| - тело лямбда выражения. работает как у функции но может определять тип возврата
	// |  |   | - предписанный тип возврата. он не обязателен для лямбды но его отсутствие 
	// |  |		 может влиять на работу функции и приводить к некоторым ошибкам
	// |  | - аргументы. работают как аргументы в обычной функции
	// | - захват контекста. может принимать список переменных которые есть в месте создания лямба 
	//	   выражения. Имеет несколько режимов работы с контекстом

	//auto func1 = [](int a, int b) {
	//		if (a > 0) {
	//			return b + a;
	//		}
	//		else {
	//			return a > b;
	//		}
	//	};
	std::for_each(numbers.begin(),numbers.end(),
		[](int& val) {val = 100 + ::rand() % 900; }
		);

	std::for_each(numbers.begin(), numbers.begin()+20,
		[](const int& val) {std::cout << val << '\t'; }
	);

	int (*greg)(int, int) = Summ;
	std::cout << "\n\n" << Summ(numbers[0], numbers[1]);
	std::cout << "\n\n" << greg(numbers[0], numbers[1]);

	std::function<int(int, int)> fred = Summ;
	std::cout << "\n\n" << fred(numbers[0], numbers[1]);

	//char* (*(**foo[][8])())[];

	PrintResult(numbers[0], numbers[1], Summ);
	PrintResult(numbers[0], numbers[1], Multiply);
	PrintResult(numbers[0], numbers[1], greg);
	PrintResult(numbers[0], numbers[1], fred);
	PrintResult(numbers[0], numbers[1], 
		[](int a, int b)->int {return a % b; }
		);

	[=](int a, int b)mutable {
		int val = numbers.size();
		numbers[0] = a;
		numbers[1] = b;
		std::cout << "\n\n" << greg(numbers[0], numbers[1]);
		}(2,5);
	std::cout << '\n';
	std::for_each(numbers.begin(), numbers.begin() + 20,
		[](const int& val) {std::cout << val << '\t'; }
	);

	[&](int a, int b) {
		int val = numbers.size();		
		numbers[0] = a;
		numbers[1] = b;
		std::cout << "\n\n" << greg(numbers[0], numbers[1]);
		}(2, 5);

	std::cout << '\n';
	std::for_each(numbers.begin(), numbers.begin() + 20,
		[](const int& val) {std::cout << val << '\t'; }
	);


	ArrayWrap ourObj;
	ourObj.data.resize(1'000'000'000);
	//ourObj.initialize();

	

	std::thread tr(Summ, numbers[0], numbers[1]);
	tr.detach();
	//результат работы этого потока мы никогда не увидим

	int result{  };
	std::thread tr2([&result](int a, int b) 
		{
			result = Summ(a, b);
		
		}, numbers[0], numbers[1]);
	// мы можем гарантированно получить посчитанный результат в тот момент когда 
	// поток завершит свою работу и завершит в любой другой момент программы свою работу метод join

	std::thread tr3([&ourObj]() {
		ourObj.initialize();
		});

	//spending time
	std::this_thread::sleep_for(std::chrono::seconds(3));
	::system("cls");
	for (size_t i = 0; i < 10; i++)
	{
		std::cout << 1 + i << "seconds path\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		::system("cls");
	}

	tr2.join();
	std::cout << "2nd thread will finish calculation. result = " << result << "\n\n";

	tr3.join();

	std::cout << "3th thread will finish calculation. result:\n\n";
	std::cout << "first 20 nums:\n";
	std::for_each(ourObj.data.begin(), ourObj.data.begin() + 20,
		[](const int& val) {std::cout << val << '\t'; }
	);

	std::cout << "\n\nlast 20 nums:\n";
	std::for_each(ourObj.data.begin()+ (ourObj.data.size()-20), ourObj.data.end(),
		[](const int& val) {std::cout << val << '\t'; }
	);

}