﻿#include <iostream>
#include <string>
#include <vector>

#include <ctime>

#include "Date.hpp"
#include "Time.hpp"


void F00(const Date &obj) {
    obj.GetData();
    //можно вызвать те методы что мы пометели как const
}

void Example() {
    time_t time_var = time(NULL);


    Time a;
    Time b{ 1,1,1,1 };
    Time c{ 1,1,1 };
    Time d{ 1,1 };
    Time e{ 1 };
    int w;

    //Date::MyClass vasia;
    //vasia.e = 89;

}

class Integer {
public:
    Integer():Integer(false, 0u) {}

    Integer(bool sign, unsigned units):sign_(sign),units_(units) {}
    
    explicit Integer(int num) {                                     
        if (0 >= num) {                                                       
            sign_ = true;
            units_ = -1 * num;
        }
        else
        {
            sign_ = false;
            units_ = (unsigned) num;
        }
    }

    void Print()const {
        std::cout << (sign_ ? '-' : ' ') << units_ << '\n';
    }

    Integer Summ(Integer other)const{
        Integer result;
        //магия сложения
        return result;
    }

    Integer  operator+(const Integer &other)const {
        Integer result;
        if (sign_ == other.sign_) {
            result.sign_ = sign_;
            result.units_ = units_ + other.units_;
        }
        else
        {
            if (units_ > other.units_)
            {
                result.sign_ = sign_;
                result.units_ = units_ - other.units_;
            }
            else if (units_ < other.units_) {
                result.sign_ = other.sign_;
                result.units_ = other.units_ - units_;
            }
            else {
                result.sign_ = false;
                result.units_ = true;
            }
        }
        return result;
    }

    friend Integer operator-(const Integer &a, const Integer &b) {
        Integer tmp = b;
        tmp.sign_ = !tmp.sign_;
        return a + tmp;
    }

    void SetUnits(unsigned newUnits) {
        this->units_ = newUnits;
    }

    friend void DoSomething(const Integer &a);

    friend std::ostream &operator<<(std::ostream &out, const Integer &obj) {
        out << obj.units_;
    }

    friend std::istream &operator>>(std::istream &inS,  Integer &obj) {
        inS >> obj.units_;
        std::string tmp;
        std::getline(inS, tmp);
    }

private:
    bool sign_;
    unsigned units_;
};




//независисмо от того какой оператор вы перегружаете и как 
//следует соблюдать правила:
// 1. нельзя перегружать не существующие операторы
// 2. нельзя перегружать особые операторы: . & :: ?: new delete sizeof
// 3. нельзя перегружать поведение оператора со стандартными типами данных
// 
// 1) нельзя нарушать "контракт" оператора
// 2) нельзя изменять поведение оператора
// 
// *) не стоит перегружать опреаторы которые можно неправильно воспринять 
//    при работе с классом
// 
// -------------------
//  Лучше реализовывать операторы как дружественные функции если есть риск проблем
//      проблема может возникать при наследовании
//      когда класс - наследник сохраняет функционал но в делалях используется
//      не для тех целей что и родитель
//  





int main()
{
    Date current{ 24,12,2024 };
    std::cout << current.GetData() << '\n';
    //Date::GetData(); нельзя вызвать метод обработки данных без самих данных
    //вместилищем для данных является объект класса
    //у каждого из объектов своя версия хранимой информации
    //методы класса вызываются, как правило, от имени объекта класса

    Date obj;//создание незаполненных пользователем объектов класса
             //невозможно если нет конструктора по умолчанию
    std::cout << obj.GetData() << '\n';
    obj.SetYear(405);
    std::cout << obj.GetData() << '\n';
    if (obj == current) {
        std::cout << "This is a same date\n";
    }
    else {
        std::cout << "The date are different\n";
    }

    Integer a{ 4 };
    Integer b{ -6 };
    auto c = a + b;
    c = a.operator+(Integer(6));
    //c = 4 + b;//не может так как нет у int метода для сложения
    c = a - b;
    c = a - Integer(5);
    c = operator-(Integer(4), b);
    //при explicit конструкторе у класса становится невозможен его 
    //вызов компилятором в автоматическом режиме

    //DoSomething(a);
    //DoSomething(current);
    current.SetDay(22);
    current.SetMonth(2);
    std::cout << '\n' << current.GetData();

    Time time{ 1,15,10,600 };
    std::cout << '\n' << time.GetData();
    time.AddSeconds(72000);
    std::cout << '\n' << time.GetData();
    current.Add(time);

    std::cout << '\n' << current.GetData();
}