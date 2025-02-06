#include <iostream>
#include <string>

class Base {
public:
    Base(){}

    void F00() {
        std::cout << "hello";
        Print();
    }

    static void F01() {
        std::cout << "hello";
    }

    // static делает метод возможным к вызову без существующих объектов класса
    // в нутри него доступны для работы только те компоненты класса 
    // которые тоже объявлены как static
    static void Print() {
        // static меняет время жизни переменной на время жизни программы
        // инициализация происходит во время первого обращения
        static int var{};

        std::cout << field;
        F01();
        //F00();

    }

    //static объявляет что в классе будет статическое поле
    // оно доступно из статических и обычных методов класса но его значение всегда 
    // общее для всех пользователей и объетов класса
    // В классе содежится только объявление
    // Создавать это поле нужно отдельно
    static int field;
};

int Base::field{ 7 };

// static ограничивает доступность глобальных переменных и 
// функций только своим кодовым файлом
static void F00(){}


class Singleton {
public:
    void WorkLoad(){}
    //static Singleton &GetInstance() {
    //    static Singleton instance;
    //    return instance;
    //}

    static Singleton *getInstance() {
        if (!instance_) {
            instance_ = new Singleton;
        }
        return instance_;
    }

protected:
    Singleton() = default;//конструкторы все какие нужны должны быть тут
    //Singleton(int);
    Singleton(const Singleton &other) = delete;
    Singleton &operator=(const Singleton &other) = delete;

    static Singleton *instance_;

private:
    //поля класса которые нужны объекту
};

Singleton *Singleton::instance_ = nullptr;


class Apple
{
public:
    Apple() :Apple("none", 0.0)
    {
    }

    Apple(std::string color, double weigth) :color_(color), weigth_(weigth) 
    {
        count_++;
    }

    Apple(const Apple &other) {
        color_ = other.color_;
        weigth_ = other.weigth_;
        count_++;
    }

    ~Apple()
    {
        count_--;
    }

    static int Count() {
        return count_;
    }
    std::string Color()const { return color_; }
    double Weigth()const { return weigth_; }
    friend std::ostream &operator<<(std::ostream &out, const Apple &obj) {
        return out << "Apple " << obj.color_ << " " << obj.weigth_ << " g";
    }
private:
    std::string color_;
    double weigth_;
    static int count_;
};
int Apple::count_{};


void Print(Apple obj) {
    std::cout << "Current apple: " << Apple::Count() << '\n';
    std::cout << obj << '\n';
}

void PrintRef(const Apple &obj) {
    std::cout << "Current apple: " << Apple::Count() << '\n';
    std::cout << obj << '\n';
}

void Print(Apple *obj) {
    std::cout << "Current apple: " << Apple::Count() << '\n';
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << obj[i] << '\n';
    }
}

void F01(Singleton obj){}

int main()
{
   /* std::cout << "Current apple: " << Apple::Count() << '\n';
    Apple obj;
    std::cout << obj << '\n';
    std::cout << "Current apple: " << obj.Count() << '\n';
    Apple *pObj = nullptr;
    std::cout << "Current apple: " << Apple::Count() << '\n';
    pObj = new Apple{"pink", 35.2};
    Print(*pObj);
    std::cout << "Current apple: " << Apple::Count() << '\n';
    std::cout << *pObj << '\n';
    PrintRef(obj);
    Apple arr[10];
    std::cout << "Current apple: " << Apple::Count() << '\n';
    Print(arr);
    delete pObj;
    std::cout << "Current apple: " << Apple::Count() << '\n';*/

    Singleton &ref = *(Singleton::getInstance());
    ref.WorkLoad();

    //Singleton obj(ref);
    //F01(obj);
}   