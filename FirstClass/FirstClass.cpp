#include <iostream>


class Integer {
public:
    Integer():Integer(false, 0u) {}

    Integer(bool sign, unsigned units):sign_(sign),units_(units) {}
    
    Integer(int num) {                                     
        if (0 >= num) {                                                       
            sign_ = true;
            units_ = -1 * num;
        }
        else
        {
            sign_ = false;
            units_ = (unsigned) num;
        }
    }

    void Print()const {
        std::cout << (sign_ ? '-' : ' ') << units_ << '\n';
    }

    Integer Summ(Integer other)const{
        Integer result;
        //магия сложения
        return result;
    }

    void SetUnits(unsigned newUnits) {
        this->units_ = newUnits;
    }

private:
    bool sign_;
    unsigned units_;
};


int main()
{
    Integer a(true, 90u);
    a.Print();
    Integer b {-5};
    b.Print();
    b.SetUnits(76);
    b.Print();
}