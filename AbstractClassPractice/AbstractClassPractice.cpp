/*
Создайте абстрактный класс Animal, который содержит:
— приватные поля name и age,
— методы toString, getName, getAge, возвращающие значение полей name и age,
— конструктор принимающий name и age.
Создайте классы Lion и Monkey, наследующие класс Animal и имеющие дополнительные 
поля и методы:
— Monkey: color и getColor
— Lion: bodyLength и getBodyLength
Также каждый из этих классов добавляет свой параметр в строке возвращаемой методом 
toString() Например: Класс Lion добавит к строке ", bodyLength= 5".
Создайте класс Zoo, содержащий в себе:
— список животных,
— метод add, принимающий любой класс, который наследует Animal,
— метод getSize, возвращающий количество животных,
— метод getReport, возвращающий номер каждого животного и его строковое 
представление в новой строке.

*/
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class AAnimal {
public:
    AAnimal():AAnimal("none",0) {}
    AAnimal(std::string name, int age):_name(name),_age(age){}

    virtual std::string toString()const=0;
    std::string getName()const { return _name; }
    int getAge()const { return _age; }

    void setName(std::string name){ _name = name; }
    void setAge(int age) { _age = age; }


private:
    std::string _name;
    int _age;
};

class Monkey :public AAnimal {
public:
    Monkey():Monkey("none",0,"white") {}
    Monkey(std::string name, int age, std::string color)
        :AAnimal(name, age),
        _color(color)
    {}
    
    std::string getColor()const { return _color; }
    void setColor(std::string color) { _color = color; }
   
    std::string toString()const override
    {
        std::string result{ "monkey " };
        result = _color + " " + result;
        result += "named: " + getName();
        result += " " + std::to_string(getAge()) + " age old.";
        return result;

        return  _color + " monkey named: " + getName() +
            " " + std::to_string(getAge()) + " age old.";
    }

private:
    std::string _color;
};

class Lion :public AAnimal {
public:
    Lion():Lion("none",0,1) {}
    Lion(std::string name, int age, int bodyLength)
    {
        setName(name);
        setAge(age);
        setBodyLength(bodyLength);
        _bodyLength = bodyLength;
    }


    int getBodyLength()const { return _bodyLength; }
    void setBodyLength(int bodyLength) { _bodyLength = bodyLength; }

    std::string toString()const override
    {
        std::string result{ "lion " };
        result = std::to_string(_bodyLength) + " feet length " + result;
        result += "named: " + getName();
        result += " " + std::to_string(getAge()) + " age old.";
        return result;
    }

private:
    int _bodyLength;
};

//— список животных,
//— метод add, принимающий любой класс, который наследует Animal,
//— метод getSize, возвращающий количество животных,
//— метод getReport, возвращающий номер каждого животного и его строковое
//представление в новой строке.
class Zoo {
public:
    Zoo():_animals(nullptr),_size(0){}
    ~Zoo() {
        if (_animals) {
            for (int i = 0; i < _size; i++)
            {
                delete _animals[i];
            }
            delete[] _animals;
        }
    }

    int getSize()const { return _size; }

    void add(AAnimal *animal) {
        AAnimal **tmp = new AAnimal * [_size + 1] {};
        for (size_t i = 0; i < _size; i++)
        {
            tmp[i] = _animals[i];
        }
        tmp[_size++] = animal;
        std::swap(tmp, _animals);
        if (tmp) { delete[]tmp; }
    }

    std::string getReport()const {
        std::stringstream out_str;
        for (size_t i = 0; i < _size; i++)
        {
            out_str << "Animal" << std::setw(4) << i + 1 << ": ";
            out_str << _animals[i]->toString() << '\n';
        }
        return out_str.str();
    }


private:
    AAnimal **_animals;
    int _size;
};



int main()
{
    Zoo zoo;
    zoo.add(new Lion  { "Cewy",     3,  4 });
    zoo.add(new Lion  { "Chester",  1,  6 });
    zoo.add(new Monkey{ "Chuppy",   6,  "Green"});
    zoo.add(new Lion  { "king",     5,  3 });
    zoo.add(new Monkey{ "Gledis",   3,  "Yellow" });
    zoo.add(new Monkey{ "Zappy",    8,  "Black" });

    Monkey *mk=new Monkey{ "Greg",   2,  "Red" };
    zoo.add(mk);

    std::cout << zoo.getReport();

    return 0;
}