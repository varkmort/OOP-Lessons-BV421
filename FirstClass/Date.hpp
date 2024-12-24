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

    int GetYear() const {
        return year_;
    }

    std::string GetData()const {
        return std::to_string(day_) + "." + std::to_string(month_) + "." +
            std::to_string(year_);
    }

    //� ����������� ������� ��������� ����� ����������� ��� ������������� �������
    friend bool operator==(const Date &a, const Date &b);

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

