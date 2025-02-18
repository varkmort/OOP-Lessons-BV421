#include <iostream>
#include <iomanip>
//  Множественное наследование
// 
// Множественное наследование во многих ООП языках 
// программирования запрещено на уровне компиляции кода
// Но остаётся возможной реализация множества разных
// интерфейсов(в тексте программы это выглядит тоже как
// наследование от множества классов)
// 
// Такой подход называется "Наследуем один раз, реализуем 
// то что необходимо"
// 
// В программах на С++ тоже рекомендуется придерживаться 
// такой модели но так как в этом языке множественное
// наследование присутствует изза него могут возникать 
// следующие проблемы:
//  - общие имена полей и методов в родительских классах
//      - либо пользователь ткакого класса должен в ручную
//        указывать метод кого из родителей он собирается
//        применить(если имена методов совпадают).
//        либо требуется перегрузить этот метод 
//        непосредственно в в классе наследнике 
//  - проблема с упровлением объектами наследниками через
//    указатели на родительский класс
//      - ВСЕ родители такого множественного наследника должны
//        иметь виртуальный деструктор 
//  - Возможность возникновения "Ромбовидного наследования"
//

class BaseA {
public:
    int value;
    void SetValue(int a) { value = a; }
    int GetValue()const { return value; }
    virtual ~BaseA() {
        std::cout << "BaseA destroyed\n";
    } 
};

class BaseB {
public:
    int value;
    void SetValue(int a) { value = a; }
    int GetValue()const { return value; }
    virtual ~BaseB(){
        std::cout << "BaseB destroyed\n";
    }

};

class Derived :public BaseA, public BaseB
{
public:
    int GetValue()const { return BaseA::GetValue(); }
    void SetValue(int a) { BaseA::SetValue(a); }
    ~Derived()override
    {
        std::cout << "Derived destroyed\n";
    }
};


void PrintValue(const BaseB &obj) {
    std::cout << obj.GetValue();
}


class IPrintable {
public:
    IPrintable() = delete;
    ~IPrintable() = delete;
    virtual void Print()const = 0;
};

class INamed {
public:
    INamed() = delete;
    ~INamed() = delete;
    virtual const char * GetName()const = 0;
};

//наследованеи от интерфейсов(реализация)
//самый частоиспользуемый и безопасный ваниант 
//множественного наследования
class Base:public INamed, public IPrintable
{};

int Example1()
{
    Derived* p_obj = new Derived;
    std::cout << sizeof(Derived) <<'\n';

    p_obj->BaseA::SetValue(77);
    p_obj->BaseB::SetValue(77);
    int &ref1 = (*p_obj).BaseA::value;
    int &ref2 = p_obj->BaseB::value;

    std::cout << p_obj << '\n';

    BaseA *p_base = p_obj;
    std::cout << p_base << '\n';

    unsigned long long address = (unsigned)(p_obj);
    std::cout << std::hex << address << '\n';

    auto p_add = &address;

    delete p_base;
    //new new[]
    // malloc calloc

    // delete delete[]
    // free


    return 0;
}


class Engine{};
class Car{};
class Sit{};
class Wheel{};

class Vheacle
{
public:
    Wheel wheels[4];
};

