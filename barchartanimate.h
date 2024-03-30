// barchartanimate.h


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <unistd.h>
#include "myrandom.h" 
#include "barchart.h"
using namespace std;
//
// BarChartAnimate
//
class BarChartAnimate {
  private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart * barcharts; // pointer to a C-style array
  int size;
  int capacity;
  int index;
  map < string, string > colorMap;
  vector < string > type;
  string title;
  string xlabel;
  string source;
  public:
    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {

      capacity = 4;
      size = 0;
      barcharts = new BarChart[capacity];
      index = 0;
      this -> source = source;
      this -> title = title;
      this -> xlabel = xlabel;
    }
  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated
  // by BarChartAnimate.
  //
  virtual~BarChartAnimate() {

    if (barcharts != nullptr) {
      delete[] barcharts;
      barcharts = nullptr;
    }
  }
  // makeBig:
  // when size and capacity are equal
  // capacity get exponentially doubled
  // then barcharts gets updated
  // helps reduce code
  void makeBig(int & size, int & capacity) {
    if (size == capacity) {
      int c = pow(capacity, 2);
      BarChart * temp = new BarChart[c];
      for (int i = 0; i < size; i++) {
        temp[i] = barcharts[i];
      }
      delete[] barcharts;
      capacity = c;
      barcharts = temp;
      temp = nullptr;
    }
  }
  // addFrame:
  // adds a new BarChart to the BarChartAnimate object from the file stream.
  // if the barcharts has run out of space, double the capacity (see
  // ourvector.h for how to double the capacity).
  // See application.cpp and handout for pre and post conditions.
  void addFrame(ifstream & file) {
    //if size is cap have old contents in new array and delete
    //name value and category so i can get value do not neefd the year

    int sum;
    string year, city, country, value, category;
    getline(file, year);
    file >> sum;
    if (!file.good()) {
      return;
    }
    BarChart chart(sum);
    for (int i = 0; i < sum; i++) { // getting data for each frame
      getline(file, year, ',');
      getline(file, city, ',');
      getline(file, country, ',');
      getline(file, value, ',');
      getline(file, category);
      if (colorMap.count(category) == 0) { // adding data at index
        colorMap[category] = COLORS[index];
        index++;
      }
      if (index == COLORS.size()) { // else set at 0
        index = 0;
      }
      chart.addBar(city, stoi(value), category);
      chart.setFrame(year);
    }
    makeBig(size, capacity);
    barcharts[size] = chart;
    size++;
  }
  // animate:
  // this function plays each frame stored in barcharts.  In order to see the
  // animation in the terminal, you must pause between each frame.  To do so,
  // type:  usleep(3 * microsecond);
  // Additionally, in order for each frame to print in the same spot in the
  // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
  // in between each frame.
  void animate(ostream & output, int top, int endIter) {
    unsigned int microsecond = 50000;

    if (endIter == -1) { // indexing properly to animate
      endIter = size;
    }
    for (int i = 0; i < endIter; ++i) { // forloop to display each bar per frame
      usleep(3 * microsecond);
      output << CLEARCONSOLE;
      output << BLACK << title << endl;
      output << BLACK << source << endl;
      barcharts[i].graph(output, colorMap, top);
      output << BLACK << xlabel << endl;
      output << "Frame: " << barcharts[i].getFrame() << endl;
    }
  }

  // multiplier (creative component):
  // this function multiplies each frame stored in barcharts.  In order to see the
  // animation in the terminal, you must pause between each frame.  To do so,
  // type:  usleep(3 * speed);
  // Additionally, in order for each frame to print in the same spot in the
  // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
  // in between each frame.
  void multiplier(ostream & output, int top, int endIter, int speed) {
    unsigned int microsecond = 50000;

    if (endIter == -1) {
      endIter = size;
    }
    for (int i = 0; i < endIter; ++i) {
      usleep(speed * microsecond);
      output << CLEARCONSOLE;
      output << BLACK << title << endl;
      output << BLACK << source << endl;
      barcharts[i].graph(output, colorMap, top);
      output << BLACK << xlabel << endl;
      output << "Frame: " << barcharts[i].getFrame() << endl;
    }
  }

  //
  // Public member function.
  // Returns the size of the BarChartAnimate object.
  //
  int getSize() {
    return size;
  }
  //
  // Public member function.
  // Returns BarChart element in BarChartAnimate.
  // This gives public access to BarChart stored in the BarChartAnimate.
  // If i is out of bounds, throw an out_of_range error message:
  // "BarChartAnimate: i out of bounds"
  //
  BarChart & operator[](int i) {
    BarChart bc;
    if (i > size || i < 0) {
      throw out_of_range("BarChartAnimate: i out of bounds");
    }
    return barcharts[i];
  }
}; 