#include <iostream>

#include "../../SourceFiles/part2/Observer.h"
#include "../../SourceFiles/part2/Subject.h"

class TemperatureSensor : public Subject<int> {
};

class AirConditioner : public Observer<int> {

    static int nextId;
    int id;

    void onTemperatureChange(int temperature) {
        std::cout << "Air Conditioner #" << id << " got a report from TemperatureSensor, reading " << temperature
                  << std::endl;
    }

public:
    AirConditioner() : Observer() {
        id = (++nextId);
    }

    void handleEvent(const int &param) override {
        onTemperatureChange(param);
    }
};

int AirConditioner::nextId = 0;

int main() {
    TemperatureSensor s;
    AirConditioner a, b, c;

    (((s += a) += b) += c);

    // Should print:
    // Air Conditioner #1 got a report from TemperatureSensor, reading 42
    // Air Conditioner #2 got a report from TemperatureSensor, reading 42
    // Air Conditioner #3 got a report from TemperatureSensor, reading 42
    s(42);

    s -= b;
    // Should print:
    // Air Conditioner #1 got a report from TemperatureSensor, reading 420
    // Air Conditioner #3 got a report from TemperatureSensor, reading 420
    s(420);

    try {
        (s += a);
    } catch (ObserverAlreadyKnownToSubject &e) {
        std::cout << "Should be printed - 1" << std::endl;
    }

    try {
        AirConditioner d;
        s -= d;
    } catch (ObserverUnknownToSubject &e) {
        std::cout << "Should be printed - 2" << std::endl;
    }

    return 0;
}