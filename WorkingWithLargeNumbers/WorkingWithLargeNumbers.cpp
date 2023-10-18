#include "MyBigNumber.h"
#include <iostream>

int main() {
    MyBigNumber numberA;
    MyBigNumber numberB;

    numberA.setNumber("51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    numberB.setNumber("403db8ad88a3932a0b7e8189aed9eeffb8121dfac05c3512fdb396dd73f6331c");

    // XOR; expect 1182d8299c0ec40ca8bf3f49362e95e4ecedaf82bfd167988972412095b13db8
    numberA.XOR(numberB);
    std::cout << "XOR result in hexadecimal: " << numberA.getNumber() << std::endl;

    // INV; expect ae409f7beb52a8d95c3e413f670884e4ab004d878072ad758b3e280219b8f15b
    numberA.setNumber("51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    numberA.INV();
    std::cout << "INV result in hexadecimal: " << numberA.getNumber() << std::endl;

    // OR; expect 51bff8ad9cafd72eabffbfc9befffffffcffbffaffdd779afdf3d7fdf7f73fbc
    numberA.setNumber("51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    numberA.OR(numberB);
    std::cout << "OR result in hexadecimal: " << numberA.getNumber() << std::endl;

    // AND; expect 403d208400a113220340808088d16a1b10121078400c1002748196dd62460204
    numberA.setNumber("51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    numberA.AND(numberB);
    std::cout << "AND result in hexadecimal: " << numberA.getNumber() << std::endl;

    // SHIFTL; expect 46fd821052b55c990000000000000028
    numberA.setNumber("51bf608414ad5726a");
    numberA.shiftL(2);
    std::cout << "SHIFT LEFT result in hexadecimal: " << numberA.getNumber() << std::endl;

    // SHIFTR; expect 946fd821052b55c98000000000000002
    numberA.setNumber("51bf608414ad5726a");
    numberA.shiftR(2);
    std::cout << "SHIFT RIGHT result in hexadecimal: " << numberA.getNumber() << std::endl;

    // ADD; expect a78865c13b14ae4d25e90771b54963ed2d68c0a64d4a8ba8c6f45ee0e9daa65c
    numberA.setNumber("36f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    numberB.setNumber("70983d692f648185febe6d6fa607630ae68649f7e6fc45b94680096c06e4fadb");
    numberA.ADD(numberB);
    std::cout << "ADD result in hexadecimal: " << numberA.getNumber() << std::endl;

    // SUB; expect 10e570324e6ffdbd6b9c813dec968d9bad134bc0dbb061520934f4e59c2700b9
    numberA.setNumber("33ced2c76b26cae94e162c4c0d2c0ff7c13094b0185a3c122e732d5ba77efebc");
    numberB.setNumber("22e962951cb6cd2ce279ab0e2095825c141d48ef3ca9dabf253e38760b57fe03");
    numberA.SUB(numberB);
    std::cout << "SUB result in hexadecimal: " << numberA.getNumber() << std::endl;

    // MOD; expect 33ced2c76b26cae9
    numberA.setNumber("33ced2c76b26cae94e162c4c0d2c0ff7c13094b0185a3c122e732d5ba77efebc");
    numberB.setNumber("22e962951cb6cd2ce279ab0e2095825c141d48ef3ca9dabf253e38760b57fe03");
    numberA.MOD(numberB);
    std::cout << "MOD result in hexadecimal: " << numberA.getNumber() << std::endl;

    return 0;
}
