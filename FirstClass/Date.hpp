#pragma once

#ifndef DATE_HPP
#define DATE_HPP

class Date {
public:
    Date() :Date(1, 1, 1) {}

    //Date() = default;
    //Инктрукция компилятору принудиткльно создать конструктор по умолчанию

    //Date() = delete;
    //Инктрукция компилятору принудительно игнорировать создание
    //конструктора по умолчанию

    //конструктор класса определяет правила создания объекта
    //он настолько необходим объектам класса что при его отсутствии в программе
    //компилятор предоставляет конструктор по умолчанию сам
    Date(int day, int month, int year)
        :day_(day),
        month_(month),
        year_(year)
    {}

    //мы видим изменения в данных объекта после отработки метода.
    //потому что, фактически, с полями класса мы работаем через указатель this
    //через него  и происходят изменения в данных.
    void SetYear(int year) {
        if (0 == year) {
            std::cerr << "year can't be 0\n";
            throw "year can't be 0\n";
        }
        this->year_ = year;
    }

    int GetYear() const {
        return year_;
    }

    std::string GetData()const {
        return std::to_string(day_) + "." + std::to_string(month_) + "." +
            std::to_string(year_);
    }

    //В большинстве случаев операторы лучше перегружать как дружественные функции
    friend bool operator==(const Date &a, const Date &b);

private:
    int day_;
    int month_;
    int year_;
    //при создании класса мы в процессе инкапсуляции определяем перечень данных
    //будущих объектов класса через описание полей.
};

//Дружественные функции имеют доступ к приватной части класса
bool operator==(const Date &a, const Date &b) {
    return a.day_ == b.day_ && a.month_ == b.month_ && a.year_ == b.year_;
}

#endif // !DATE_HPP

