//Задание 1
// Необходимо создать класс Растений
// - Растение может состоять из 2 частей если оно будет кустом(ветки и листья)
// и из 3х частей если оно будет деревом(ствол, ветки и листья)
// - Части растений нужно реализовать как один класс.
// - Так как число частей разное в зависимости от типа то перечень частей можно хранить 
// либо в указателях либо в массиве частей
// 
// Для демонстрации работоспособности растения реализуйте метод вывода описания
// если компоненты класса будут хранится с помощью динамической памяти то необходимо
// реализовать конструкторы копирования и переноса а так же операторы присваивания
// копированием и переносом
//

#include <iostream>

#define G_VAR 3

#define name(type, name) type name;


class Part {
public:
    // методы помеченые как default будут предоставлены компилятором если 
    // программист не напишет их сам
    Part()=default;
    // Компилятор будет инорировать создание конструктора по умолчанию самостоятельно 
    // если у нас есть собственный реализованный конструктор с параметрами
    // (хотя бы один)
    Part(std::string name) :name_(name) {}
    Part(const Part &other) = default;
    ~Part() = default;
    Part &operator=(const Part &other) = default;
    // если от компилятора требуется создание  автогенерируемых методов то
    // они помечаются как default, если требуется явно их запредить то
    // отметка меняется на delete
    
    void SetName(std::string name) {
        name_ = name;
    }

    std::string GetName()const {
        return name_;
    }

    // тут мы учим программу действиям на случай когда между потоком вывода
    // и объектом класса Part оператор << 
    // это позволит выводить данные напрямую и в cout, и в файловые потоки, 
    // и в любые другие потоки вывода
    friend std::ostream &operator <<(std::ostream &out, const Part &obj) {
        out << obj.name_;
        return out;
    }
private:
    std::string name_;
};


class Plant {
public:
    Plant():Plant(Category::Bush){}
    //следующие 2 типа конструкторов это не очень хорошие но варианты выбрать
    //чем будет создованемый объект
    //Plant(int category);
    //Plant(std::string category);
    //======================================

    enum Category {
        Tree,
        Bush
    };

    Plant(Category cat) {
        if (cat == Category::Tree)
        {
            size_ = 3;
            parts_ = new Part[3]{ 
                std::string("Leaf"), 
                std::string("Log"), 
                std::string("Stick") };
            name_ = "Apple Tree";
        }
        else if (cat == Category::Bush){
            size_ = 2;
            parts_ = new Part[2]{
                std::string("Leaf"),
                std::string("Stick") };
            name_ = "Blueberry";
        }
    }

    Plant(std::string name, Category cat) :Plant(cat) {
        name_ = name;
    }

    Plant(const Plant &other) {
        name_ = other.name_;
        size_ = other.size_;
        parts_ = new Part[size_];
        for (size_t i = 0; i < size_; i++)
        {
            parts_[i] = other.parts_[i];
        }
    }

    Plant operator=(const Plant &other) {
        if (size_ != other.size_) {
            if (parts_!=nullptr) {
                delete[] parts_;
                size_ = other.size_;
                parts_ = new Part[size_];
            }
        }
        for (size_t i = 0; i < size_; i++){
            parts_[i] = other.parts_[i];
        }
        name_ = other.name_;
        return *this;
    }

    ~Plant() {
        if (parts_)
        {
            delete[] parts_;
        }
    }

    friend std::ostream &operator << (std::ostream &out, const Plant &obj) {
        out << obj.name_ << ":[";
        for (size_t i = 0; i < obj.size_; i++)
        {
            out << obj.parts_[i] << ((i < obj.size_ - 1) ? ", " : "");
        }
        out << "]";
        return out;
    }

    const Part & GetLeaf()const {
        return parts_[0];
    }

private:
    std::string name_;
    Part *parts_;
    int size_;
};


void F00(Plant::Category &var) {
    var = Plant::Category::Bush;
}

int main()
{
    Part part{ "Leaf" };
    operator<<(operator<<(operator<<(std::cout, part),"out text"),'\n');

    Plant pear{ "Pear",Plant::Category::Tree };
    std::cout << pear << '\n';

    Plant strawberry{ "strawberry",Plant::Category::Bush };
    std::cout << strawberry << '\n';
    std::cout << strawberry.GetLeaf().GetName();

    std::cout << Plant::Category::Tree;
    auto cat = Plant::Category::Tree;
    F00(cat);

    
}