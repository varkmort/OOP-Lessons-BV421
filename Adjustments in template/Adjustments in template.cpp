//  Расширенные материалы про шаблоны 
//      переменные - аргументы шаблона
//      выводимые аргументы шаблона(значения аргументов по умолчанию)
//      вариативные шаблоны(variadic template)
//

//int Summ(int a, int b, ...) {
//    return 0;
//}

#include <iostream>

#include <array>
#include <vector>
#include <tuple>

template<typename Type, size_t n>
class StArray{
private:
    Type dat_[n];
};

template<typename Type, typename Alloc = std::allocator<Type>>
class DinArray {
private:
    Alloc arrlocator_;
    size_t size_;
    size_t capacity_;
    Type *date_;
};

template<typename Type>
Type Summ(Type firstArg) {
    return firstArg;
}

template<typename Type, typename ...Args>
Type Summ(Type firstArg, Args ...restArgs) {
    return firstArg + Summ(restArgs...);
}



int main()
{
    //Summ(1, 2,5,7,8,9,6,2,4,8,0);
    // переменные как аргументы шаблона
    std::array<int, 5> StArr;

    auto demo = new std::array<int, 5>{};
    delete demo;
    for (int &i : StArr)
    {
        i = 1;
    }
    for (const auto &i : StArr)
    {
       std::cout <<  i << ' ';
    }
    std::cout << '\n';
// выводимые аргументы шаблона(значения аргументов по умолчанию)
    std::vector<int, std::allocator<int>> DinArr(5);
    for (int &i : DinArr)
    {
        i = 1;
    }
    for (const auto &i : DinArr)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
// variadic
    std::tuple<int, double, int> Cortege{ 1, 4.5, 1 };
    auto collect = std::make_tuple(1, 4.5,"string", 1);
    
    std::cout <<  Summ(1, 2, 3, 4, 5, 6, 7, 8, 9);
}