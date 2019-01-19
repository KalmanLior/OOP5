#include "Observer.h"
#include "OOP5EventException.h"
#include <list>

using std::list;

#ifndef OOP5_PART2_SUBJECT_H
#define OOP5_PART2_SUBJECT_H

template <typename T>
class Subject{
private:
    list<Observer<T>*>* observers;
public:
    Subject<T>(){
        observers =  new list<Observer<T>*>();
    }
    ~Subject(){
        delete(observers);
    }
    void notify(const T& event){
        for(auto observer = observers->begin(); \
            observer != observers->end();       \
            observer++){
            (*observer)->handleEvent(event);
        }
    }
    void addObserver(Observer<T>& observer){
        for(auto o = observers->begin(); \
            o != observers->end();       \
            o++){
            if((*o) == &observer) //TODO: comparing by addresses.. is that ok?
                throw ObserverAlreadyKnownToSubject();
        }
        observers->push_back(&observer);
    }
    void removeObserver(Observer<T>& observer){
        for(auto o = observers->begin(); \
            o != observers->end();       \
            o++){
            if((*o) == &observer) {//TODO: comparing by addresses.. is that ok?
                observers->erase(o);
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
