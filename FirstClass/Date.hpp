#pragma once

#ifndef DATE_HPP
#define DATE_HPP

class Date {
public:
    Date() :Date(1, 1, 1) {}

    //Date() = default;
    //���������� ����������� ������������� ������� ����������� �� ���������

    //Date() = delete;
    //���������� ����������� ������������� ������������ ��������
    //������������ �� ���������

    //����������� ������ ���������� ������� �������� �������
    //�� ��������� ��������� �������� ������ ��� ��� ��� ���������� � ���������
    //���������� ������������� ����������� �� ��������� ���
    Date(int day, int month, int year)
        :day_(day),
        month_(month),
        year_(year)
    {}

    //�� ����� ��������� � ������ ������� ����� ��������� ������.
    //������ ���, ����������, � ������ ������ �� �������� ����� ��������� this
    //����� ����  � ���������� ��������� � ������.
    void SetYear(int year) {
        if (0 == year) {
            std::cerr << "year can't be 0\n";
            throw "year can't be 0\n";
        }
        this->year_ = year;
    }

    void SetDay(int day) {
        if (1< day)
        {
            std::cerr << "numeric value of day are lower than minimum " << 
                day << '\n';
            throw "numeric value of day are lower than minimum ";
        }
        if (31 < day && (1 == month_ || 3 == month_ || 5 == month_ ||
            7 == month_ || 8 == month_ || 10 == month_ || 12 == month_ ))
        {
            std::cerr << "numeric value of day are higher than maximum " <<
                day << '\n';
            throw "numeric value of day are higher than maximum ";
        }
        if (30 < day && ( 4 == month_ || 6 == month_ || 
            9 == month_ || 11 == month_))
        {
            std::cerr << "numeric value of day are higher than maximum " <<
                day << '\n';
            throw "numeric value of day are higher than maximum ";
        }
        if (29 < day && (2 == month_ ) && IsLeap())
        {
            std::cerr << "numeric value of day are higher than maximum " <<
                day << '\n';
            throw "numeric value of day are higher than maximum ";
        }
        if (28 < day && (2 == month_) && !IsLeap())
        {
            std::cerr << "numeric value of day are higher than maximum " <<
                day << '\n';
            throw "numeric value of day are higher than maximum ";
        }
        day_ = day;
    }

    void SetMonth(int month) {
        if (1 > month || 12 < month) {
            std::cerr << "new month is out of range " <<
                month << '\n';
            throw "new month is out of range ";
        }
        month_ = month;
    }


    bool IsLeap()const {
        return 0 == year_%4 && (0 != year_ % 100 || 0 == year_ % 400);
    }

    void Add(Time time);

    int GetYear() const {
        return year_;
    }

    int GetMonth()const {
        return month_;
    }

    int GetDay()const {
        return day_;
    }

    std::string GetData()const {
        return std::to_string(day_) + "." + std::to_string(month_) + "." +
            std::to_string(year_);
    }

    //� ����������� ������� ��������� ����� ����������� ��� ������������� �������
    friend bool operator==(const Date &a, const Date &b);

    friend void DoSomething(const Date &a);

private:
    int day_;
    int month_;
    int year_;
    //��� �������� ������ �� � �������� ������������ ���������� �������� ������
    //������� �������� ������ ����� �������� �����.
};

//������������� ������� ����� ������ � ��������� ����� ������
bool operator==(const Date &a, const Date &b) {
    return a.day_ == b.day_ && a.month_ == b.month_ && a.year_ == b.year_;
}

#endif // !DATE_HPP

