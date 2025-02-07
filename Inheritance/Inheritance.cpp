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

int main()
{
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