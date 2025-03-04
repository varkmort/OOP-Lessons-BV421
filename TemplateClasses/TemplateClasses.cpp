// Шаблонные классы
// 
// В С++ можно создавать шаблоны:
//  - Функций(мотоды классов считаются)
//  - Структур
//  - Объединений
//  - Классов
//  - Переорпеделений типов
//      using как поределение нового типа может быть шаблоном
// 
// Шаблоны классов выгодно создавать когда у вас есть общее поведение
// для разных потенциальных типов полей класса.
// 
//  - несобственные типы данных 
//  - структуры данных(например коллекции)
// Это самые частые гости для реализации в виде шаблонов
//

#include <iostream>

//template<typename MyIdentifier>
//using t_time =  MyIdentifier;
//
//using t_time2 = float;

//шаблон умного указателя
//  Проблема: обычные указатели не умеют ни создавать объекты классов ни 
//            чистить память от объекта на который они указывали.
//            Это затавляет программиста тратить время отладки программы 
//            на проверки корректного освобождения памяти во всех случаях 
//            потери указателя из программы
//
void Example() {
    int *p_var = new int{ 3 };
	if(p_var==nullptr)
	{
		delete p_var;
		::exit(-1);
	}
	/*
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	*/
	if (*p_var == 5)
	{
		delete p_var;
		throw -2;
	}
	/*
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	*/
	if (*p_var == 3)
	{
		delete p_var;
		return;
	}

	std::cout << "We are heppy, Julls?";
	delete p_var;
}
// Для того чтобы не заниматься поиском и анализом всех случаев уничтожения 
// указателя в коде, применяются владеющие умные указатели.
// В их поведение заложена очистка памяти от более не используемых объектов
// в куче.
//


// библиотека memory содержит 4 умных указателя
//	auto_ptr
//  unique_ptr
//  shared_ptr
//  weak_ptr
// 

template <typename Type>
class smart_ptr {
public:
	smart_ptr() {
		data_ = new Type{};
	}
	smart_ptr(Type * obj) {
		data_ = new Type{*obj};
	}
	smart_ptr(Type obj) {
		data_ = new Type{ obj };
	}
	smart_ptr(const smart_ptr &) = delete;
	smart_ptr(smart_ptr &&) = delete;
	~smart_ptr() {
		if (data_)
		{
			delete data_;
		}
	}

	Type &operator*() { return *data_; }
	const Type &operator*()const { return *data_; }

	Type *operator->() { return data_; }
	const Type *operator->()const { return data_; }

	smart_ptr &operator=(const smart_ptr &) = delete;
	smart_ptr &operator=(smart_ptr &&) = delete;
private:
	Type *data_;
};

//no owning variant
template <>
class smart_ptr<void>{
public:
	smart_ptr() {
		data_ = nullptr;
	}
	smart_ptr(void *obj) {
		data_ = obj;
	}

	smart_ptr(const smart_ptr &) = default;
	~smart_ptr() = default;

	smart_ptr &operator=(const smart_ptr &) = default;
private:
	void *data_;
};

class Test {
public:
	Test():value(0)
	{
		std::cout << "test " << this << " default construct\n";
	}

	Test(int val) :value(val) {
		value = val;
		std::cout << "test " << this << " param construct\n";
	}

		Test(const Test&obj) :value(obj.value) {
			std::cout << "test " << this << " copy construct\n";
		}

	~Test(){
		std::cout << "test " << this << " default destruct\n";
	}

	int value;
};

void F00(smart_ptr<void> ptr) {

}

int Example2()
{
    //t_time<unsigned short> var;
	smart_ptr<Test> s_ptr{Test(5)};
	smart_ptr<float> s_ptr2{4.6f};
	//  |       |аргумент шаблона
	//  | название шаблона
	
	std::cout << s_ptr->value << "\n";
	std::cout << *s_ptr2 << "\n";

	smart_ptr<void> s_ptr3;





	void *p_void = malloc(4);
	s_ptr3 = p_void;
	F00(p_void);
	delete p_void;
	return 0;
}



//	Шаблоны структур данных
//		типы структур данных(коллекций):
//			линейные массивы				+ array vector
//			списки
//				однонаправленные списки		+ forward_list
//				двунаправленные списки		+ list
//				кольцевые списки
//			деревья
//				бинарные деревья			+ set map и производные
//				красно-чёрные деревья
//				деревья отрезков		   +- deque
//			графы 
// 
//		по поведению:
//			очереди
//				FIFO +		queue
//				FILO +		stack
//