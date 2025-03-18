//  Сериализация данных
// Сериализация - процесс преобразования данных программы
//  в форму удобную для считывания, хранения и передачи.
// Сериализация в человекочитаемой форме кодирует данные в виде текста
//  который можно формально считать зашифрованным стандартным способом
//  тем же способом можно проводить и "дешифровку"
// Самые знаковые форматы для индустрии:
//      - INI
//      - CSV
//      - XML
//      - JSON
//

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <string>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
//#include <queue>
//#include <stack>

#include <algorithm>
#include <chrono>
#include <type_traits>
#include <typeinfo>


struct CarOwner {
    std::string name;
    int age;
    int count_of_cars;
};

std::ostream& operator<<(std::ostream& out, const CarOwner& obj) {
    return out << "name: " << obj.name << ", age: " << obj.age <<
        ", cars in ownership: " << obj.count_of_cars;
}

int main2()
{
    //read from csv
    std::vector<CarOwner> records;
    std::ifstream inputF("table.csv");//создали поток для забора данных
    if (inputF.is_open()) 
    {
        {
            std::string tmp;
            std::getline(inputF, tmp, '\n');
        }
        while (!inputF.eof()) {
           
            std::string line;
            std::getline(inputF, line, '\n');

            if (line.size()) {
                std::stringstream line_data(line);
                
                CarOwner tmp;
                std::string raw_data;
                std::getline(line_data, raw_data, ';');
                tmp.name = raw_data;
                std::getline(line_data, raw_data, ';');
                tmp.age = std::stoi(raw_data);
                std::getline(line_data, raw_data, ';');
                tmp.count_of_cars = std::stoi(raw_data);

                records.emplace_back(tmp);

                //records.push_back(tmp);

                //std::getline(inputF, raw_data, '\n');
            }
        }
    }
    inputF.close();
    for (auto& i : records)
    {
        std::cout << i << '\n';
    }

    for (size_t i = 0; i < records.size(); i++)
    {
        std::cout << records[i].name << '\n';
    }

    //records.erase(records.begin() + 1);
    ////records.clear();
    //for (auto& i : records)
    //{
    //    std::cout << i << '\n';
    //}
    ////=============================
    //std::ofstream outputF("table.csv");
    //if (outputF.is_open()) {
    //    outputF << "name;age;count_of_cars;\n";
    //    for (auto& i : records)
    //    {
    //        outputF << i.name << ';' << i.age << 
    //            ';' << i.count_of_cars << ";\n";
    //    }
    //}

    return 0;
}


class Record {
public:
    Record() :Record("",'Ж',0) {}
    Record(std::string name, char sex, int count)
        :name_(name),
        sex_(sex),
        count_(count)
    {}


    friend std::ostream& operator<<(std::ostream& out, const Record& obj) {
        return out << obj.name_ << ';' << obj.sex_ << ';' << obj.count_ << ';';
    }
    
    std::string GetName()const { return name_; }
    char GetSex()const { return sex_; }
    int GetCount()const { return count_; };

    void SetName(std::string name) { name_ = name; }
    void SetSex(char sex) { sex_ = sex; }
    void SetCount(int count) { count_ = count; }


private:
    std::string name_;
    char sex_;
    int count_;
};

bool OurMeasuring(const Record lsv, const Record rsv) {
    return lsv.GetCount() < rsv.GetCount();
}

auto func = [](const Record& lsv, const Record& rsv)->bool {
    return lsv.GetCount() > rsv.GetCount();
    };

int main() {
    ::setlocale(LC_ALL, "rus");
    std::vector<Record> records;

    std::ifstream inF("russian_names.csv");
    if (inF.is_open()) {
        {
            std::string tmp;
            std::getline(inF, tmp, '\n');
        }
        while (!inF.eof()) {
            std::string line;
            std::getline(inF, line, '\n');
            if (line.size()) {
                std::stringstream line_stream(line);
                std::string raw;
                Record tmp;

                std::getline(line_stream, raw, ';');//пропуск первого блока
                std::getline(line_stream, raw, ';');//считываем имя
                tmp.SetName(raw);//записываем имя в временный объект
                std::getline(line_stream, raw, ';');//считали пол
                tmp.SetSex(raw[0]);//записали в объект с конвертацией из строки в символ
                std::getline(line_stream, raw, ';');//считали цисло носителей
                tmp.SetCount(std::stoi(raw));//конвертация данных в число и запись в объект
                records.push_back(tmp);//добавили запись в вектор
            }
            if (records.size() == 20) { break; }
        }
    }
    for (auto& record : records)
    {
        std::cout << record << '\n';
    }
    auto res = std::max_element(records.begin(), records.end(), OurMeasuring);
    
    std::cout<<'\n' << *res;

    auto res2 = std::min_element(
                                    records.begin(), 
                                    records.end(),
                                    [](const Record& lsv, const Record& rsv)->bool {
                                        return lsv.GetCount() > rsv.GetCount();
                                    }
                                );
    /*
    std::min_element(){
    ...
    Pred(val1,val2);
    }    
    */
    std::cout << '\n' << *res2;

    auto reult = [](const Record& lsv, const Record& rsv)->bool {
        return lsv.GetCount() > rsv.GetCount();
        }(records[0],records[1]);

    std::cout << typeid(func).name() << '\n';

    return 0;
}