// barchart.h
// 
// In this abstraction, we are going 
// to allocate space on the heap. 
// We will store one entire frame of 
// the animation inside 
// a C-array of Bar objects.
// We will allocate space based on 
// the n value passed in as a parameter in the parameterized 
// constructor. Additionally, we will 
// keep track of how many Bars are added using size.
//


#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h" 
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

// Color codes for Mimir (light mode)
const string RED("\033[1;36m");
const string PURPLE("\033[1;32m");
const string BLUE("\033[1;33m");
const string CYAN("\033[1;31m");
const string GREEN("\033[1;35m");
const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
const string RESET("\033[0m");
const vector < string > COLORS = {
  RED,
  PURPLE,
  BLUE,
  CYAN,
  GREEN,
  GOLD,
  BLACK
};

// Color codes for Codio (light/dark mode)
// const string CYAN("\033[1;36m");
// const string GREEN("\033[1;32m");
// const string GOLD("\033[1;33m");
// const string RED("\033[1;31m");
// const string PURPLE("\033[1;35m");
// const string BLUE("\033[1;34m");
// const string WHITE("\033[1;37m");
// const string RESET("\033[0m");
// const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};

//
// BarChart
//
class BarChart {
  private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar * bars; // pointer to a C-style array
  int capacity;
  int size;
  string frame;

  public:

    // default constructor:
    BarChart() {
      bars = nullptr;
      this -> capacity = 0;
      this -> size = 0;
      this -> frame = "";
    }

  // parameterized constructor:
  // Parameter passed in determines memory allocated for bars.
  BarChart(int n) {
    this -> bars = new Bar[n]; // new bar array size of n
    this -> capacity = n;
    this -> size = 0;
    this -> frame = "";

  }
  //
  // copy constructor:
  //
  // Called automatically by C++ to create an BarChart that contains
  // a copy of an existing BarChart.  Example: this occurs when passing
  // BarChart as a parameter by value.
  //
  BarChart(const BarChart & other) {
    capacity = other.capacity;
    bars = new Bar[capacity];
    size = other.size;
    frame = other.frame;

    for (int i = 0; i < other.size; ++i) { // iterating through every bar in barchart array to duplicate into
      bars[i] = other.bars[i];
    }
  }
  //
  // copy operator=
  //
  // Called when you assign one BarChart into another, i.e. this = other;
  //
  BarChart & operator = (const BarChart & other) {
    // BarChart bc;

    if (this == & other) {

      return *this;
    }
    delete[] bars; // clear bars array 

    this -> bars = new Bar[other.capacity];
    this -> size = other.size;
    this -> capacity = other.capacity;
    this -> frame = other.frame;

    for (int i = 0; i < other.size; ++i) { // iterating through current bars arrayy to copy into
      this -> bars[i] = other.bars[i];
    }
    return *this;
  }
  // clear
  // frees memory and resets all private member variables to default values.
  void clear() {

    delete[] bars;

    bars = nullptr;
    size = 0;
    capacity = 0;
    frame = "";
  }

  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated by the
  // BarChart.
  //
  virtual~BarChart() {
    delete[] bars;
  }

  // setFrame
  void setFrame(string frame) {
    this -> frame = frame;
  }

  // getFrame()
  // Returns the frame of the BarChart oboject.
  string getFrame() {
    return this -> frame;
  }

  // addBar
  // adds a Bar to the BarChart.
  // returns true if successful
  // returns false if there is not room
  bool addBar(string name, int value, string category) {
    if (size == capacity) {
      return false;
    }
    Bar temp(name, value, category);
    bars[size] = temp;
    size++;
    return true;
  }

  // getSize()
  // Returns the size (number of bars) of the BarChart object.
  int getSize() {
    return size;
  }

  // operator[]
  // Returns Bar element in BarChart.
  // This gives public access to Bars stored in the Barchart.
  // If i is out of bounds, throw an out_of_range error message:
  // "BarChart: i out of bounds"
  Bar & operator[](int i) {
    if (i < 0 || i > size) {
      throw out_of_range("BarChart: i out of bounds");
    }

    return bars[i];
  }

  // dump
  // Used for printing the BarChart object.
  // Recommended for debugging purposes.  output is any stream (cout,
  // file stream, or string stream).
  // Format:
  // "frame: 1
  // aname 5 category1
  // bname 4 category2
  // cname 3 category3" <-newline here
  void dump(ostream & output) {

    sort(bars, bars + size, greater < Bar > ());
    output << "frame: " << frame << endl;
    for (int i = 0; i < size; i++) { // printing each component of the bars array through the for loop
      output << bars[i].getName() << " " << bars[i].getValue() << " " << bars[i].getCategory() << endl;
    }
  }

  // graph
  // Used for printing out the bar.
  // output is any stream (cout, file stream, string stream)
  // colorMap maps category -> color
  // top is number of bars you'd like plotted on each frame (top 10? top 12?)
  void graph(ostream & output, map < string, string > & colorMap, int top) {

    int lenMax = 60; // this is number of BOXs that should be printed
    // for the top bar (max value)
    // e.g. Here I am plotting 60 red BOXs to output
    // use built in sort fucntion loop through and find the length and output those.
    // loop through top and calculate the offset relative ;length of each bar
    // string color = "\033[1;36m";  // you should get this from colorMap

    string color = "";
    string barStr = "";
    double value = 0.0;

    sort(bars, bars + size, greater < Bar > ());

    if (top > size) { // to set the number of bars to size
      top = size;
    }

    int sum = bars[0].getValue(); // get sum from file cause first instance
    for (int i = 0; i < top; ++i) {
      value = (bars[i].getValue() / double(sum)) * lenMax; // lenMax calculation as described in the handout
      if (!colorMap.count(bars[i].getCategory())) {
        color = BLACK;
      } else {
        color = colorMap[bars[i].getCategory()];
      }

      for (int j = 0; j < floor(value); ++j) { // actual bar for graph
        barStr += BOX;
      }

      output << color << barStr << " " << bars[i].getName() << " " << bars[i].getValue() << endl; // outputting actual graph data
      barStr = "";
    }
  }
};
// all code stylized by c++ beautifier to pass style points.