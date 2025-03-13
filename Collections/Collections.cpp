#include <iostream>

#include <vector>
#include <set>
#include <unordered_set>

#include <random>
#include <algorithm>
#include <type_traits>

bool Contain(const std::vector<int>& arr, int value) {
    bool result{false};
    for (const auto& element : arr){
        if (element == value) {
            result = true;
            return result;
        }
    }
    return result;
}

std::vector<int> Unique(const std::vector<int>& arr) {
    std::vector<int> result;
    for (const auto& i : arr){
        if (!Contain(result, i)) {
            result.push_back(i);
        }
    }
    return result;
}

struct MyStruct
{
    int a; 
    int b;
    MyStruct(int a,int b):a(a),b(b){}
    friend bool operator ==(const MyStruct& lsv, const MyStruct& rsv) {
        return lsv.a == rsv.a && lsv.b == rsv.b; 
    }
    friend bool operator <(const MyStruct& lsv, const MyStruct& rsv) {
        //вы безумны если думаете что так можно
        // оператор меньше требуется для типа данных чтобы можно было работать 
        // с обычным set и map вариантами деревьев.
        return lsv.a == rsv.a && lsv.b == rsv.b;
    }
};

namespace std {

    template<>
    struct hash<MyStruct>{
        std::size_t operator()(const MyStruct& obj) const
        {
            return std::hash<int>()(obj.a) ^ (std::hash<int>()(obj.b) << 1);
        }
    };
}


int main()
{
    int size{ 1'000'000 };
    std::vector<int> r_numbers;
    r_numbers.reserve(size);
    ///=========================
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> prov(0, size * 10);
    for (size_t i = 0; i < r_numbers.capacity(); i++)
    {
        r_numbers.push_back(prov(gen));
        //r_numbers.emplace(r_numbers.begin(), prov(gen));
    }
    //================================================
    std::cout << "Vector contain: " << r_numbers.size() <<
        " numbers/\n";

    //auto uniq = Unique(r_numbers);
    std::set<int> uniq(r_numbers.begin(), r_numbers.end());

    std::cout << "Unique numbers: " << uniq.size() << ".\n";
    //=================================================
    auto answer = uniq.find(14);
    if (answer != uniq.end()) {
        std::cout << "We found " << 14 << " in set!\n";
    }
    else {
        std::cout << "We can't found " << 14 << " in set!\n";
    }
    //////////
    std::vector<MyStruct> custom;
    custom.reserve(size);
    for (size_t i = 0; i < custom.capacity(); i++)
    {
        custom.emplace_back(prov(gen), prov(gen));
        //r_numbers.emplace(r_numbers.begin(), prov(gen));
    }
    //--------------
    std::set<MyStruct> customS;
    for (size_t i = 0; i < size; i++)
    {
        customS.insert(prov(gen), prov(gen));
        //r_numbers.emplace(r_numbers.begin(), prov(gen));
    }
    //std::unordered_set< MyStruct >;
}