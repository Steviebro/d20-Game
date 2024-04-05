/**
 * @file Subject.cpp
 * @brief This cpp file writes the functionalities for the subject that is used for
 * attaching an object to be a subject that can be observed which allows the
 * object to be updated in real time when there are modifications that affect it.
 * @ref Subject.h
 * @ref Observer.h
 */
#include "../include/Components/Subject.h"
#include "../include/Components/Observer.h"
/**
 * @brief method which creates a new observers list
 */
Subject::Subject() {
  _observers = new list<Observer*>;
}
/**
 * @brief method which deletes the observers list
 */
Subject::~Subject() {
  //delete _observers;
}
/**
 * @brief method that adds the observer to the list of observers
 * @param o observer that needs to be attached
 */
void Subject::attach(Observer* o) {
  _observers->push_back(o);
};
/**
 * @brief method that removes the observer from the list of observables.
 * @param o observer that needs to be removed
 */
void Subject::detach(Observer* o) {
  _observers->remove(o);
};
/**
 * @brief method that will parse through each observer in the list of observers
 * and will update each and every one of them when the notify method is called.
 */
void Subject::notify() {
  auto i = _observers->begin();
  for (; i != _observers->end(); ++i)
    (*i)->update();
};
