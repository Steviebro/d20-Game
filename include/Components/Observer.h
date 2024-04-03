/**
 *@file Observer.h
 * @brief this .h file is used for declaring the observer, variables
 * and functions that are needed for implementing an observer
 */
#ifndef INC_345ASSIGNMENT1_SRC_OBSERVER_H_
#define INC_345ASSIGNMENT1_SRC_OBSERVER_H_
/**
 * @class Observer
 * @brief the observer class is used for creating an observer and calling the update
 * method which allows us to update the observed object when any change causes a modification to
 * that specific object.
 */
class Observer {
 public:
  ~Observer();
  virtual void update() = 0;
 protected:
  Observer();
};

#endif //INC_345ASSIGNMENT1_SRC_OBSERVER_H_