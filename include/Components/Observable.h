/**
 * @file Observable.h
 * @brief This header file is used for declaring the variables
 * and functions that are needed for the Observable.
 * @include list for list functionalities
 */
#ifndef INC_345ASSIGNMENT1_OBSERVABLE_H
#define INC_345ASSIGNMENT1_OBSERVABLE_H
#pragma once
#include <list>
using namespace std;

class Observer;
/**
 * @class Observable
 * @brief This the class for creating an observable object which allows
 * another object to be observed so it can be updated in real time.
 */
class Observable {
 public:
  virtual ~Observable() = default;
  virtual void attach(Observer *) = 0;
  virtual void detach(Observer *) = 0;
  virtual void notify() = 0;
 protected:
  Observable() {};
 private:
  list<Observer*> _observers;
};

#endif //INC_345ASSIGNMENT1_OBSERVABLE_H

