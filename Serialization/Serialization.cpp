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

struct CarOwner {
    std::string name;
    int age;
    int count_of_cars;
};

std::ostream& operator<<(std::ostream& out, const CarOwner& obj) {
    return out << "name: " << obj.name << ", age: " << obj.age <<
        ", cars in ownership: " << obj.count_of_cars;
}

int main()
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
}