#include <iostream>
#include <cassert>
#include "barchartanimate.h"
using namespace std;

bool testBarDefaultConstructor() {
	Bar b;
    if (b.getName() != "") {
    	cout << "testBarDefaultConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 0) {
    	cout << "testBarDefaultConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "") {
    	cout << "testBarDefaultConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {
	Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
    	cout << "testBarParamConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 9234324) {
    	cout << "testBarParamConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << "testBarParamConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarParamConstructor: all passed!" << endl;
    return true;
}


bool testBarChartGraph() {
   BarChart bc(10);

   bc.addBar("Chicago", 1020, "US");
   bc.addBar("NYC", 1300, "US");
   bc.addBar("Paris", 1200, "France");
   bc.setFrame("1950");

   string red("\033[1;36m");
   string blue("\033[1;33m");
   map<string, string> colorMap;
   colorMap["US"] = red;
   colorMap["France"] = blue;

   stringstream result("");
   bc.graph(result, colorMap, 3);

   //
   // build correct answer:
   //
   stringstream correct("");

   correct << red;
   for (int i = 0; i < 60; i++) {
      correct << BOX;
   }
   correct << " NYC 1300" << endl;

   correct << blue;
   for (int i = 0; i < (1200*60/1300); i++) {
      correct << BOX;
   }
   correct << " Paris 1200" << endl;

   correct << red;
   for (int i = 0; i < (1020 * 60 / 1300); i++) {
      correct << BOX;
   }
   correct << " Chicago 1020" << endl;

   //
   // Compare to result graph() returned:
   //
   //cout << result.str() << endl;
   //cout << correct.str() << endl;

   string R, C;
   R = result.str();
   C = correct.str();

   if (R.size() != C.size()) {
      cout << "strings diff in size (R="
         << R.size() << ",C="
         << C.size() << ")" << endl;
   }

   for (size_t i = 0; i < R.size() && i < C.size(); i++) {
      if (result.str()[i] != correct.str()[i]) {
         cout << "strings diff at index " << i
            << " (R=" << result.str()[i] << ",C="
            << correct.str()[i] << ")" << endl;
      }
   }

   assert(R.size() == C.size());
   assert(R == C);

   cout << "testBarChart: all passed!" << endl;
   return true;
}

int main() {
	testBarDefaultConstructor();
	testBarParamConstructor();
  testBarChartGraph();
	
  return 0;
}