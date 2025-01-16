// AgregationAndResourceManagment.cpp 
// агрегация и управление ресурсами в классах
// 
// композиция класса - это общий термин обозначающий то что мы объединили какие-то
//  параметры(поля в классе)
// виды:
//  - агрегация
//  - композиция
// 
// Копозиция(тип связи) - компонент имеет общее время жизни с объектом в который вложен.
//                        Без этого компонента объект в который было вложение существовать
//                        не сможет.
// Агрегация - Вложенный по агрегации компонент имеет независимое время жизни
//             и объект в который он был вложен может не нести за его существование 
//             никакой ответственности.
//

#include <iostream>
#include <string>

struct Manager {
    std::string name;
};

class Employee {
public:
    Employee() = default;
    Employee(std::string name, Manager *departmentHead):
        name(name),
        departmentHead(departmentHead)
    {}

    std::string name;
    Manager *departmentHead;
};

int main0()
{
    Manager a{ "Gregory" };
    Manager b{ "Elvis" };

    //создали массив указателей для хранения адресов Сотрудников
    Employee **staf = new Employee*[5]{};// |--a|---

    //создали сотрудника в куче и адрес его нахождения записали в массив
    staf[0] = new Employee{ "Emely",&a }; // a|---|
    staf[1] = new Employee{ "Max",&a };
    staf[2] = new Employee{ "Alex",&b };
    staf[3] = new Employee{ "Katrin",&a };
    staf[4] = new Employee{ "Nikc",&b };

    std::cout << "Name: " << staf[3]->name << " Manager: " << staf[3]->departmentHead->name << '\n';
    (*staf[3]).name;//оператор -> заменяте собой доступ через разьминования через указатели
    
    staf[3]->departmentHead = &b;
    std::cout << "Name: " << staf[3]->name << " Manager: " << staf[3]->departmentHead->name << '\n';
    delete staf[3];
    staf[3] = nullptr;
    std::cout << "Name: " << staf[2]->name << " Manager: " << staf[2]->departmentHead->name << '\n';
    std::cout << "Manager: " << b.name << '\n';
    std::swap(staf[3], staf[4]);
    std::cout << "Name: " << staf[3]->name << " Manager: " << staf[3]->departmentHead->name << '\n';
    staf[4] = new Employee{ "Woodie",&a };
    std::cout << "Name: " << staf[4]->name << " Manager: " << staf[4]->departmentHead->name << '\n';
    staf[4]->departmentHead = nullptr;
    std::cout << "Name: " << staf[4]->name << " Manager: " << staf[4]->departmentHead->name << '\n';

    //в цикле освобождаем память от сотрудников
    for (size_t i = 0; i < 5; i++)
    {
        delete staf[i];
    }
    delete[] staf;//освободили память от массива(отдела)
    return 0;
}


struct Part {
    std::string name;
};

class Body {
public:
    Body() {
        heart = new Part{ "heart" };
        stomach = new Part{ "stomach" };
        liver = new Part{ "liver" };
        brain = new Part{ "brain" };
        std::cout << this << " Body object default construct\n";
    }

    //конструктор копирования
    Body(const Body &other) {
        heart = new Part;
        heart->name = other.heart->name;
        stomach = new Part;
        stomach->name = other.stomach->name;
        liver = new Part;
        liver->name = other.liver->name;
        brain = new Part;
        brain->name = other.brain->name;
        std::cout << this << " Body object copy construct\n";
    }

    Body operator=(const Body &other) {
        //такой способ копирования подходит когда размеры блоков данных разные
        delete this->heart;
        this->heart = new Part;
        heart->name = other.heart->name;
        //следующие варианты подойдут для одинаковых по размеру данных
        stomach->name = other.stomach->name;
        liver->name = other.stomach->name;
        brain->name = other.brain->name;
        return *this;
    }


    //дкструктор класса по умолчанию.
    //создаётся как метод начинающийся с символа ~ соеденнного с именем класса
    //деструктор у класса может быть только один и никогда не имеет аргументов
    ~Body() {
        delete heart;
        delete stomach;
        delete liver;
        delete brain;
        std::cout << this << " Body object default destruct\n";
    }

    void Print()const{
        std::cout << "Body: " << heart->name << ", " << stomach->name << ", " <<
            liver->name << ", " << brain->name << '\n';
    }

    Part *heart;
    Part *stomach;
    Part *liver;
    Part *brain;
};

void F00(Body obj) {
    obj.Print();
}


int main() {
    Body a;
    std::cout << &a << '\n';
    a.brain->name = "BRAINZ";
    Body *p = new Body;
    Body b;
    {
        delete p;
        Body c;
        F00(b);
    }
    Body d;
    d.Print();
    b = d = a;
    d.Print();
    int r,e,y,i;
    i = 9;
    r = e = y = i + 1;
    return 0;
}