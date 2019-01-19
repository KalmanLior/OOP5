#ifndef OOP5_PART2_OBSERVER_H
#define OOP5_PART2_OBSERVER_H

template <typename T>
class Observer{
public:
    //pure virtual
    virtual void handleEvent(const T&) = 0;
};

#endif //OOP5_PART2_OBSERVER_H
