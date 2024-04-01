/**
 * @file Subject.h
 * @brief this .h file is used for the subject which extends the observable
 * that is used for both map observalbe and character observable
 * @ref Observable.h
 */
#ifndef INC_345ASSIGNMENT1_SRC_SUBJECT_H_
#define INC_345ASSIGNMENT1_SRC_SUBJECT_H_
#include "Observer.h"
#include <list>
using namespace std;
/**
 * @class Subject
 * @brief this is the class for creating the subject which is used for overriding
 * the attach and detach and also the notify methods, which allows the needed classes
 * to be observed.
 * @extends Observable
 */
class Subject {
 public:
  Subject();
  ~Subject();

  void attach(Observer *);
  void detach(Observer *);
  void notify();
 private:
  list<Observer *> *_observers;
};
#endif //INC_345ASSIGNMENT1_SRC_SUBJECT_H_
