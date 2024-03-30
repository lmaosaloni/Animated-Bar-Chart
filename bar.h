// bar.h
// 
// Creates a class called Bar. 
// A Bar aggregates related information (name, value, and category) for use in a bar chart.


#include <iostream>
#include <string>
#include "myrandom.h" // used in autograder, do not remove
using namespace std;

//
// Bar
//
class Bar {
  private:
    // Private member variables for a Bar object
    // TO DO:  Define private member variables for this class
    // NOTE: You should not be allocating memory on the heap for this class.

  string Name;
  int Value;
  string Category;

  public:
    // default constructor:
    Bar() {

      Name = "";
      Value = 0;
      Category = "";
    }

  //
  // a second constructor:
  //
  // Parameter passed in constructor Bar object.
  //
  Bar(string name, int value, string category) {

    this -> Name = name;
    this -> Value = value;
    this -> Category = category;
  }

  // destructor:
  virtual~Bar() {
    // TO DO:  Write this destructor or leave empty if not needed.
  }

  // getName:
  string getName() {

    return this -> Name;
  }

  // getValue:
  int getValue() {

    return this -> Value;
  }

  // getCategory:
  string getCategory() {

    return this -> Category;
  }

  // operators:
  // TO DO:  Write these operators.  This allows you to compare two Bar
  // objects.  Comparison should be based on the Bar's value.  For example:
  bool operator < (const Bar & other) const {
    if (this -> Value < other.Value) {
      return true;
    } else {
      return false;
    }
  }

  bool operator <= (const Bar & other) const {
    if (this -> Value <= other.Value) {
      return true;
    } else {
      return false;
    }
  }

  bool operator > (const Bar & other) const {
    if (this -> Value > other.Value) {
      return true;
    } else {
      return false;
    }
  }

  bool operator >= (const Bar & other) const {
    if (this -> Value >= other.Value) {
      return true;
    } else {
      return false;
    }
  }
};  // all code stylized by c++ beautifier to pass style points.