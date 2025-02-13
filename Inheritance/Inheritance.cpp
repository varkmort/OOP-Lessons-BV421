#include <iostream>
#include <string>

//  Наследование - механизм расширения функционала класса 
//                 путём сужения его специализации.
// 
//  Наследование - повторное использование кода уже существующих классов
//                 для построения новых классов
// 
//  классы - наследники. в виде объектов строятся поверх объекта родительского класса
//          этот вложеный объект анонимен но только через его присутствие возможна 
//          работа с доступными полями и методами родительского класса.
// 
//  в классе наследнике можно перегрузить или переопределить любой метод кроме 
//  конструкторов и деструктора
// 
//  доступность родительских компонентов определяется типом наследования
//      типы наследования: public protected private
//

class Base
{
public:
    Base() {
        std::cout << "Base default construct\n";
    }

    void Hello() {
        std::cout << "Hello\n";
    }
protected:
    void SmallTalk() {
        std::cout << "Huw are you\n";
    }

    void WhatIThink() {
        SelfThouds();
    }
private:
    void SelfThouds() {
        std::cout << "To be or not to be...\n";
    }
};

class Derived:public Base
{
public:
    Derived() {
        std::cout << "Derived default construct\n";
    }

    void Goodbuy() {
        std::cout << "Goodbuy\n";
    }
    void PublicSpeach() {
        SmallTalk();
    }

    void LoudThinking() {
        WhatIThink();
    }

};

// protected наследование
//      private часть родителя станет недоступной приватной частью наследника
//      protected часть родителя станет доступной приватной частью наследника
//      public часть родительского класса станет защищённой частью наследника
// 
// private наследование
//      private часть родителя станет недоступной приватной частью наследника
//      protected часть родителя станет доступной приватной частью наследника
//      public часть родительского класса станет приватной частью наследника
// 
// public наследование
//      private часть родителя станет недоступной приватной частью наследника
//      protected часть родителя станет доступной защищённой частью наследника
//      public часть родительского класса станет публичной частью наследника
//


class Animal {
public:
    Animal() 
    { 
        name_ = "beast"; 
        age_ = 0; 
    }
    Animal(std::string name,int age=0)
        :name_(name),
        age_(age)
    {}


    // ключевое слово virtual позволяет перегружать метод в наследниках
    // так чтобы он мог вызываться полиморфно
    virtual void MakeSound() const{
        std::cout << "noize\n";
    }

    void MeetBirthDay() {
        age_ += 1;
    }

    int GetAge()const {
        return age_;
    }

    std::string GetName()const {
        return name_;
    }

private:
    std::string name_;
    int age_;
};


class Duck:public Animal
{
public:
    Duck() :Animal("Duck",1) {}

    Duck(int age):Animal("Duck",age){}

    //std::string GetName()const {
    //    return "Duck";
    //}
    void MakeSound() const override
    {
        std::cout << "Quack!!!\n";
    }
};


void F01(const Animal *obj)
{
    std::cout << obj << '\n';
    //obj->MeetBirthDay();
    obj->MakeSound();
}

void F02(const Animal &obj)
{
    std::cout << &obj << '\n';
    obj.MakeSound();
}

void F03(const Animal obj)
{
    std::cout << &obj << '\n';
    obj.MakeSound();
}


class ADemoBase {
public:
    ADemoBase():ADemoBase(0,0){}
    ADemoBase(int a_val,int b_val):a(a_val),b(b_val){}

    virtual ~ADemoBase() = default;

    virtual int Action()const = 0;
    // выше создана pure virtual (истинно виртуальная) функция класса
    // для нас это означает что в данном классе этот метод не будет 
    // иметь реализации

protected:
    int a;
    int b;
};
// Наличие в классе хотя бы одного истинно виртуального метода делает класс
// абстрактным. Это накладывает следующие эфекты:
//  1 - в коде программы нельзя создать ни одного объекта данного класса
//              (компилятор считает этот тип данных неполным и при компиляции
//               недаёт с ними работать напрямую)
//  2 - все наследники класса которые не перегрузят(реализуют) даный метод
//      так же будут считаться абстрактными классами
//  3 - те наследники у которых истинно виртуальные методы перегружены работают 
//      как обычно и могут передоваться внутри программы по интерфейсу базового класса
// 
//  * - классы не содержащие полей а только истинно виртуальные методы принято называть
//      классы-интерфейсы и использовать в качестве интерфейсов при построении 
//      объектно ориентированных систем
// 
// часто применяемые приёмы нименовани классов:
//  1 - имена обычных классов делать односложными Существительными реже прилогательными
//  2 - Для абстрактных классов часто Первую букву названия ставять заглавной A: AName
//  3 - Для тех классов что будут использоваться только как интерфейс не создают
//      деструктор а в имени применяют прилогателные причастия добавляя в начало 
//      заглавную I:   IPrintable
//


class AMathOperator:public ADemoBase {
public:
    AMathOperator() = default;
    AMathOperator(int a_val, int b_val) :ADemoBase(a_val, b_val) {}
};

class MathFunction:public ADemoBase {
public:
    MathFunction() = default;
    MathFunction(int a_val,int b_val):ADemoBase(a_val,b_val){}
    int Action()const override {
        return ::pow(a, b);
    }
};

class Summ :public AMathOperator {
public:
    Summ() = default;
    Summ(int a_val, int b_val) :AMathOperator(a_val, b_val) {}

    int Action()const override { return a + b; }

};

class Multiply :public AMathOperator {
public:
    Multiply() = default;
    Multiply(int a_val, int b_val) :AMathOperator(a_val, b_val) {}

    int Action()const override { return a * b; }

};

void PrintOperation(const ADemoBase &obj) {
    std::cout << "\tResult: " << obj.Action() << '\n';
}

void Generate(ADemoBase **&place, int count) {
    ::srand(::time(NULL));
    place = new ADemoBase * [count] {};
    for (size_t i = 0; i < count; i++)
    {
        ADemoBase *tmp{};
        int type = ::rand() % 3;
        switch (type)
        {
        case 0: 
            tmp = new MathFunction(10 + ::rand() % 90, 1 + rand() % 8);
            break;
        case 1:
            tmp = new Summ(10 + ::rand() % 90, 1 + rand() % 8);
            break;
        case 2:
            tmp = new Multiply(10 + ::rand() % 90, 1 + rand() % 8);
        }
        place[i] = tmp;
    }
}

void Destroy(ADemoBase **&place, int count) {
    for (size_t i = 0; i < count; i++)
    {
        delete place[i];
    }
    delete[] place;
    place = nullptr;
}


int main()
{
    ADemoBase **place{};
    Generate(place, 10);
    for (size_t i = 0; i < 10; i++)
    {
        PrintOperation(*(place[i]));
    }
    Destroy(place, 10);

    Base base;
    base.Hello();
    Derived derived;
    derived.Hello();
    derived.Goodbuy();
    derived.PublicSpeach();
    derived.LoudThinking();

    Animal dog("Barky");
    dog.MakeSound();
    F01(&dog);
    F02(dog);
    F03(dog);

    Animal cat{ "Fluffy",1 };

    F01(&cat);

    Duck duck;
    std::cout << duck.GetName() <<' ';
    duck.MakeSound();
    duck.Animal::MakeSound();
    F01(&duck);
    F02(duck);
    F03(duck);
}