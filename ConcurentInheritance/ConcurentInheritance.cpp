//  При множественном наследовании возникает ситуация
//  что один базовый класс является супер-классом
//  для потомков третьего и далее порядка по разным 
//  линиям наследования.
//  Это приводин к некоторым конфликтам и потенциальным 
//  ошибкам в логике работы программы
//

#include <iostream>
#include <string>

class Vehicle {
public:
    Vehicle():Vehicle("",0.f,0.f){}
    Vehicle(std::string name, float length, float width)
        :name_(name),
        length_(length),
        width_(width)
    {}
    virtual ~Vehicle() = default;

    void SetName(std::string name) { name_ = name; }
    void SetLength(float length) { length_ = length; }
    void SetWidth(float width) { width_ = width; }

    std::string GetName()const { return name_; }
    float GetLength()const { return length_; }
    float GetWidth()const { return width_; }

    virtual void Move() { std::cout << "move\n"; }

private:
    std::string name_;
    float length_;
    float width_;
};

class Bike:virtual public Vehicle {
public:
    Bike() :Vehicle("bike", 2.3f, 30.f){}
    Bike(std::string name, float length, float width)
        :Vehicle(name, length, width)
    {}

    void Move()override
    { 
        std::cout << "scrrr-scrrr\n"; 
    }
};

class Automobile :virtual public Vehicle {
public:
    Automobile()
        :Vehicle("car",3.f,2500.f),
        engine_("gasoline"),
        id_(-1)
    {}
    Automobile(
        std::string name, 
        float length, 
        float width,
        std::string engine,
        int id)
        :Vehicle(name, length, width),
        engine_(engine),
        id_(id)
    {}

    void SetEngine(std::string engine) { engine_ = engine; }
    std::string GetEngine()const { return engine_; }

    const int getId()const { return id_; }

    void Move()override
    {
        std::cout << "wroom-wroom\n";
    }
protected:
    Automobile(std::string engine, int id)
        :Vehicle(),
        engine_(engine),
        id_(id)
    {}
private:
    std::string engine_;
    const int id_;
};

class MotoBike final:public Bike, public Automobile {
public:
    MotoBike():Vehicle(), Bike(), Automobile(){}

    MotoBike(
        std::string name, 
        float length, 
        float width, 
        std::string engine, 
        int id)

        :Vehicle(name, length, width),
        Bike(), 
        Automobile(engine, id)
    {
        //SetEngine(engine);
    }

    void Move()override
    {
        std::cout << "scrrr-wroom\n";
    }

    friend std::ostream &operator<<(std::ostream &out, const MotoBike &obj) {
        return out << obj.GetName() << " " << obj.GetLength() << " " <<
            obj.GetWidth() << " " << obj.GetEngine() << " " <<
            obj.getId();
    }
};

void F00(Vehicle& ref){
    ref.Move();
}

int main()
{
    MotoBike obj1;
    MotoBike obj2{"stells",2.3f,0.75f,"turbo",15};

    std::cout << obj1 << '\n';
    std::cout << obj2 << '\n';

    obj2.SetWidth(0.7f);
    ///

    std::cout << obj2 << '\n';

    obj1.SetName("Kama");
    std::cout << obj1 << '\n';
   // F00(obj2);

    return 0;
}