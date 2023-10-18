#include "MyBigNumber.h"
#include <iostream>
#include <sstream>
#include <iomanip>

MyBigNumber::MyBigNumber() {
    data.push_back(0);
}

void MyBigNumber::setNumber(const std::string& hexString) {
    data.clear();
    for (size_t i = 0; i < hexString.length(); i += 16) {
        std::string hexChunk = hexString.substr(i, 16);
        std::istringstream stream(hexChunk);
        unsigned long long chunkValue = 0;
        stream >> std::hex >> chunkValue;
        data.push_back(chunkValue);
    }
}

std::string MyBigNumber::getNumber() const {
    std::ostringstream hexStream;
    for (const unsigned long long& chunkValue : data) {
        hexStream << std::hex << std::setw(16) << std::setfill('0') << chunkValue;
    }
    return hexStream.str();
}

const std::vector<unsigned long long>& MyBigNumber::getData() const {
    return data;
}

std::vector<unsigned long long>& MyBigNumber::getData() {
    return data;
}

void MyBigNumber::XOR(const MyBigNumber& other) {
    const std::vector<unsigned long long>& otherData = other.getData();
    size_t maxSize = std::max(data.size(), otherData.size());

    while (data.size() < maxSize) {
        data.push_back(0);
    }

    for (size_t i = 0; i < maxSize; i++) {
        unsigned long long valueA = (i < data.size()) ? data[i] : 0;
        unsigned long long valueB = (i < otherData.size()) ? otherData[i] : 0;
        data[i] = valueA ^ valueB;
    }
}

void MyBigNumber::INV() {
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = ~data[i];
    }
}

void MyBigNumber::OR(const MyBigNumber& other) {
    const std::vector<unsigned long long>& otherData = other.getData();
    size_t minSize = std::min(data.size(), otherData.size());

    for (size_t i = 0; i < minSize; i++) {
        data[i] |= otherData[i];
    }

    if (data.size() < otherData.size()) {
        data.insert(data.end(), otherData.begin() + minSize, otherData.end());
    }
}

void MyBigNumber::AND(const MyBigNumber& other) {
    const std::vector<unsigned long long>& otherData = other.getData();
    size_t minSize = std::min(data.size(), otherData.size());

    for (size_t i = 0; i < minSize; i++) {
        data[i] &= otherData[i];
    }
}

void MyBigNumber::shiftR(int n) {
    if (n < 0) {
        shiftL(-n);
    }
    else {
        int numChunks = n / 64;
        int numBits = n % 64;

        for (size_t i = 0; i < data.size(); i++) {
            unsigned long long current = data[i];
            if (i + numChunks < data.size()) {
                unsigned long long next = data[i + numChunks];
                data[i] = (current >> numBits) | (next << (64 - numBits));
            }
            else {
                data[i] = current >> numBits;
            }
        }
    }
}

void MyBigNumber::shiftL(int n) {
    if (n < 0) {
        shiftR(-n);
    }
    else {
        int numChunks = n / 64;
        int numBits = n % 64;

        for (size_t i = data.size(); i > 0; i--) {
            if (i - numChunks > 0) {
                unsigned long long current = data[i - 1];
                unsigned long long prev = data[i - 1 - numChunks];
                data[i - 1] = (current << numBits) | (prev >> (64 - numBits));
            }
            else {
                data[i - 1] = 0;
            }
        }
    }
}

void MyBigNumber::ADD(const MyBigNumber& other) {
    const std::vector<unsigned long long>& otherData = other.getData();
    size_t sizeA = data.size();
    size_t sizeB = otherData.size();
    size_t maxSize = std::max(sizeA, sizeB);
    unsigned long long carry = 0;

    data.resize(maxSize, 0);

    for (size_t i = 0; i < maxSize; i++) {
        unsigned long long valueA = (i < sizeA) ? data[i] : 0;
        unsigned long long valueB = (i < sizeB) ? otherData[i] : 0;

        unsigned long long sum = valueA + valueB + carry;
        carry = (sum < valueA) ? 1 : 0;
        data[i] = sum;
    }

    if (carry > 0) {
        data.push_back(carry);
    }
}

void MyBigNumber::SUB(const MyBigNumber& other) {
    const std::vector<unsigned long long>& otherData = other.getData();
    size_t sizeA = data.size();
    size_t sizeB = otherData.size();
    size_t maxSize = std::max(sizeA, sizeB);
    unsigned long long borrow = 0;

    data.resize(maxSize, 0);

    for (size_t i = 0; i < maxSize; i++) {
        unsigned long long valueA = (i < sizeA) ? data[i] : 0;
        unsigned long long valueB = (i < sizeB) ? otherData[i] : 0;

        if (valueA >= valueB + borrow) {
            data[i] = valueA - valueB - borrow;
            borrow = 0;
        }
        else {
            data[i] = (1ULL << 64) + valueA - valueB - borrow;
            borrow = 1;
        }
    }

    while (data.size() > 1 && data.back() == 0) {
        data.pop_back();
    }
}

void MyBigNumber::MOD(const MyBigNumber& mod) {
    MyBigNumber quotient, remainder;
    divideAndRemainder(mod, quotient, remainder);
    *this = remainder;
}

void MyBigNumber::divideAndRemainder(const MyBigNumber& divisor, MyBigNumber& quotient, MyBigNumber& remainder) {
    MyBigNumber divisorCopy = divisor;

    quotient.setNumber("0");
    remainder.setNumber("0");

    for (int i = data.size() - 1; i >= 0; i--) {
        remainder.shiftL(1);
        remainder.data[0] = data[i];
        int compare = remainder.compare(divisorCopy);

        if (compare >= 0) {
            while (compare >= 0) {
                MyBigNumber temp;
                temp.setNumber("1");
                temp.shiftL(i * 64);
                quotient.ADD(temp);
                remainder.SUB(divisorCopy);
                compare = remainder.compare(divisorCopy);
            }
        }
    }
}

int MyBigNumber::compare(const MyBigNumber& other) const {
    const std::vector<unsigned long long>& otherData = other.getData();
    size_t sizeA = data.size();
    size_t sizeB = otherData.size();

    if (sizeA < sizeB) return -1;
    if (sizeA > sizeB) return 1;

    for (int i = sizeA - 1; i >= 0; i--) {
        if (data[i] < otherData[i]) return -1;
        if (data[i] > otherData[i]) return 1;
    }

    return 0;
}