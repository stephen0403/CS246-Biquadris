#include "subject.h"
#include "observer.h"

void Subject::attach(Observer *o) {
    observers.emplace_back(o);
}

void Subject::detach(Observer *o) {
    for (auto it = observers.begin(); it != observers.end();) {
        if (*it == o) it = observers.erase(it);
        else ++it;
    }
}

void Subject::notifyObservers() {
    for (auto o:observers) {
        o->notify();
    }
}
