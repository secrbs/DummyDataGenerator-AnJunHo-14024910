#include <iostream>
#include <string>
#include "generator/DummyDataGenerator.h"

int main(int argc, char* argv[]) {
    std::string dataDir = "data";
    bool reset = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--reset") reset = true;
        else dataDir = arg;
    }

    std::cout << "=== DummyDataGenerator ===\n";
    std::cout << "경로  : " << dataDir << "\n";
    std::cout << "모드  : " << (reset ? "--reset (기존 데이터 초기화)" : "append (기존 데이터에 추가)") << "\n\n";

    DummyDataGenerator generator(dataDir);
    generator.generate(reset);

    std::cout << "\n완료.\n";
    return 0;
}
