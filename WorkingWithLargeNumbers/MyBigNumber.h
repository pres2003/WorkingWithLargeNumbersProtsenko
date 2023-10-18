#ifndef MYBIGNUMBER_H
#define MYBIGNUMBER_H

#include <string>
#include <vector>

class MyBigNumber {
public:
    MyBigNumber();
    void setNumber(const std::string& hexString);
    std::string getNumber() const;
    const std::vector<unsigned long long>& getData() const;
    std::vector<unsigned long long>& getData();
    
    void XOR(const MyBigNumber& other);
    void INV();
    void OR(const MyBigNumber& other);
    void AND(const MyBigNumber& other);
    void shiftR(int n);
    void shiftL(int n);
    void ADD(const MyBigNumber& other);
    void SUB(const MyBigNumber& other);
    void MOD(const MyBigNumber& mod);
    void divideAndRemainder(const MyBigNumber& divisor, MyBigNumber& quotient, MyBigNumber& remainder);
    int compare(const MyBigNumber& other) const;

private:
    std::vector<unsigned long long> data;
};

#endif
