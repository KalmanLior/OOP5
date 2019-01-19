#include "Observer.h"
#include "OOP5EventException.h"
#include <list>

using std::list;

#ifndef OOP5_PART2_SUBJECT_H
#define OOP5_PART2_SUBJECT_H

#define FOREACH(object, container)         for(auto (object) = (container).begin(); \
                                                (object) != (container).end();       \
                                                (object)++)

template <typename T>
class Subject{
private:
    list<Observer<T>*> observers;
public:
    Subject<T>(){
        observers =  list<Observer<T>*>();
    }
    void notify(const T& event){
        for(auto observer : observers){
            observer->handleEvent(event);
        }
    }
    void addObserver(Observer<T>& observer){
        for(auto o : observers){
            if(o == &observer)
                throw ObserverAlreadyKnownToSubject();
        }
        observers.push_back(&observer);
    }
    void removeObserver(Observer<T>& observer){
        FOREACH(o, observers){
            if((*o) == &observer) {
                observers.erase(o);
                return;
            }
        }
        throw ObserverUnknownToSubject();
    }
    Subject<T>& operator+=(Observer<T>& observer){
        this->addObserver(observer);
        return *this;
    }
    Subject<T>& operator-=(Observer<T>& observer){
        this->removeObserver(observer);
        return *this;
    }
    Subject<T>& operator()(const T& event){
        this->notify(event);
        return *this;
    }
};

#endif //OOP5_PART2_SUBJECT_H
