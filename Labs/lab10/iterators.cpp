#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
  map<string,string> mymap;
  set<int> myset;

  mymap["KEY1"] = "VALUE9";
  mymap["KEY2"] = "VALUE8";
  mymap["KEY3"] = "VALUE7";
  mymap["KEY4"] = "VALUE6";
  mymap["KEY5"] = "VALUE5";
  mymap["KEY6"] = "VALUE4";
  mymap["KEY7"] = "VALUE3";
  mymap["KEY8"] = "VALUE2";
  mymap["KEY9"] = "VALUE1";

  myset.insert(1);
  myset.insert(22);
  myset.insert(333);
  myset.insert(4444);
  myset.insert(55555);
  myset.insert(666666);
  myset.insert(7777777);
  myset.insert(88888888);
  myset.insert(999999999);

  // Print alternating KEYs and VALUEs in the map, starting with the key. 
  // Result should look like:
  //    KEY
  //    VALUE
  //    KEY
  //    VALUE
  //    etc.
  



  // Print all the values in the set!
  



  return 0;
}