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

    Duck(std::string name, int age = 0):Animal(name,age){}

    //std::string GetName()const {
    //    return "Duck";
    //}
    void MakeSound() const{
        std::cout << "Quack!!!";
    }
};

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
    Animal cat{ "Fluffy",1 };
    Duck duck;
    std::cout << duck.GetName() <<' ';
    duck.MakeSound();
}