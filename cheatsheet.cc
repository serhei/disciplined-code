/* Serhei's ACM cheatsheet for C++; partly inspired from
   - http://psc.cpsc.ucalgary.ca/acpc/2013/files/io-containers.pdf */

//////////////////
// Basic Template

/* Problem A -- This Is A Fake Problem */

#include <iostream>
using namespace std;

int main() {
  // ...
}

/////////////
// Basic I/O

#include <iostream>
#include <string>

int i; string s; double d;
cin >> i >> s >> d;

// Check for end-of-file
if (cin >> var) ...; // read OK
else ...; // EOF

// Read one word vs. entire line
string word; cin >> word;
string line; getline (cin, line); // -- careful of pseudo-empty line after token

// Print exact string "$1234 hello world 27.35\n"
int dollars = 1234;
double foo = 27.35;
string word = "hello";

cout << fixed << setprecision(2); // -- two sig. digits after decimal point
cout << "$" << dollars << " " << word << " world " << foo << endl;

//////////////////////////////////////
// Containers: Vectors, Lists, Deques

#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>

// Resizable array:
vector<int> numbers; numbers.push_back(5); numbers.push_back(7);

int i = 1;
vector<int>::iterator it = numbers.begin() + i; // -- constant time
numbers.insert(it, 6); // -- linear time; insert before i

assert(numbers.size() == 3);
assert(numbers[0] == 5); assert(numbers[1] == 6); assert(numbers[2] == 7);

numbers.clear(); assert(numbers.empty());

// Linked list:
list<int> numbers; numbers.push_back(7); numbers.push_front(5)

int i = 1;
list<int>::iterator it = numbers.begin() + i; // -- linear time
numbers.insert(it, 6); // -- contant time; insert before i

assert(numbers.size() == 3);

list<int>::iterator it = numbers.begin();
assert(*(it + 0) == 5); assert(*(it + 1) == 6); assert(*(it + 2) == 7);

// Deque:
deque<int> numbers;
numbers.push_back(7); numbers.push_back(8);
numbers.push_front(6); numbers.push_front(5);
assert(numbers.size() == 4);
for (int i = 5; i <= 8; i++) {
  assert(numbers.front() == i); numbers.pop_front();
  // -- likewise back(), pop_back()
}

// Queues and stacks:
queue<int> numbers; // -- supports push(), size(), front(), pop(), empty()
stack<int> numbers; // -- supports push(), size(), top(), pop(), empty()

/////////////////////////////
// Containers: Maps and Sets

#include <map>

map<string,int> days;
set<string> daynames;

// Add elements (maps and sets):
days["Monday"]    = 1; daynames.insert("Monday");
days["Tuesday"]   = 2; daynames.insert("Tuesday");
days["Wednesday"] = 3; daynames.insert("Wednesday");
days["Thursday"]  = 4; // ... and so forth for daynames
days["Friday"]    = 5;
days["Saturday"]  = 6;
days["Sunday"]    = 7;

// Test presence (maps and sets):
assert(days.count("Monday") == 1); // -- likewise for daynames
assert(days.find("Monday") != days.end());
assert(days.count("Nonday") == 0);

// Get values (maps only):
assert(days["Monday"] == 1);
assert(days["Tuesday"] == 2);

// CAREFUL -- accessing nonexistent key creates it with default-constructed value
assert(days["Nonday"] == 0);

// Iterate keys in order of < (maps and sets):
map<string, int>::iterator i, iend;
for (i = days.begin(), iend = days.end(); i != iend; i++) {
  string key = i->first, value = i->second;
}

set<string>::iterator i, iend;
for (i = daynames.begin(), iend = daynames.end(); i != iend; i++) {
  string val = *i;
}

// Delete values (maps and sets):
days.erase("Tuesday");

///////////////////////////////
// Containers: custom ordering

struct pt {
  int x, y;
};

// Natural (lexicographic) ordering for pt, used as default.
bool operator < (const pt &a, const pt &b) {
  return a.x != b.x ? a.x < b.x : a.y < b.y;
};

// Custom ordering -- sort by y-coordinate, say:
bool ycoorder (const pt &a, const pt &b) {
  return a.y < b.y;
};

// Custom order containers:
set<pt, typeof(&ycoorder)> s; // -- uses < by default
map<pt, string, typeof(&ycoorder)> s(&ycoorder);

// Sorting:
vector<pt> v;
std::sort(v.begin(), v.end());
std::sort(v.begin(), v.end(), &ycoorder);

pt ary[27];
std::sort(ary, ary + 27);
std::sort(ary, ary + 27, &ycoorder);

std::stable_sort(v.begin(), v.end()); // -- preserves order of equal elements

// TODOXXX common order transformations (???)

// TODOXXX
// TODOXXX basic geometry & trig
// TODOXXX implementing a hash table
// TODOXXX multimaps, multisets
// TODOXXX heaps, priority queues

/////////////
// std::pair

#include <utility>

pair<int,int> p = make_pair(1,2);
p.second = 3;
assert (p.first == 1 && p.second == 3);

////////////////////
// Next Permutation

#include <vector>
#include <algorithm>

int arr[] = { 0,1,2,3 };
vector<int> vec; vec.insert(vec.begin(), arr, arr+4);

do {
  stuff(vec[0], vec[1], vec[2], vec[3]);
} while (std::next_permutation(vec.begin(), vec.end());
// -- also possible to use next_permutation(begin,end,&comp)
// -- also possible to use prev_permutation(begin,end)
