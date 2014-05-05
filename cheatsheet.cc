/* Serhei's ACM cheatsheet for C++; partly inspired from
   - http://psc.cpsc.ucalgary.ca/acpc/2013/files/io-containers.pdf */

/* Important skills:
   - using the right data structures (this document)
   - working with assertions (<cassert> and choosing invariants) */

//////////////////
// Basic Template

/* Problem A -- This Is A Fake Problem */

#include <iostream>
using namespace std;

int main() {
  // ...
}

////////////////////
// Basic Assertions

#include <cassert>
assert(2+2==4);

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
// I/O for a custom class:
struct pt { int x, y; };
ostream &operator<< (ostream &out, const pt &p) { ... }
istream &operator>> (istream &in, pt &p) { ... }
// ... declare as 'friend operator' *inside* the class to access private data.

// Print exact string "$1234 hello world 27.35\n"
int dollars = 1234;
double foo = 27.35;
string word = "hello";

cout << fixed << setprecision(2); // -- two sig. digits after decimal point
cout << "$" << dollars << " " << word << " world " << foo << endl;

#include <cstdio>
printf("$%d hello %s %.2f\n", dollars, word, foo);

// TODOXXX I/O to and from files -- file object
// TODOXXX I/O to and from files -- open a stream
// TODOXXX I/O to and from files -- freopen or similar-for-streams

std::istringstream iss ("2 4 6 8");
int a, b, c, d; iss >> a >> b >> c >> d;

std::ostringstream o1;
std::ostringstream o2 ("initial prefix: ");
o1 << 42; o2 << 42;
cout << o1.str() << endl; // 42
cout << o2.str() << endl; // initial prefix: 42
o1.str("replaced content");
cout << o1.str() << endl; // replaced content


//////////////////////////////////////
// Containers: Vectors, Lists, Deques

#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>

// Resizable array:
vector<int> numbers; numbers.push_back(5); numbers.push_back(7);
vector<int> fill(10); // allocate initial size of vector, with default value
vector<int> fill(10, -1); // fill with initial value of -1

// Bitset (represented very compactly for small n):
vector<bool> mask(n, false);

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

// TODOXXX ways to fill a map or other container with val ???

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

#include <functional>
map<int, int, std::greater<int> > m;
// likewise greater_equal, less, less_equal

// Sorting:
vector<pt> v;
std::sort(v.begin(), v.end());
std::sort(v.begin(), v.end(), &ycoorder);

pt ary[27];
std::sort(ary, ary + 27);
std::sort(ary, ary + 27, &ycoorder);

std::stable_sort(v.begin(), v.end()); // -- preserves order of equal elements

// Tricks to sort a bunch of variables:
void sort(int &a, int &b) { if (a > b) { int t = a; a = b; b = t; } }
sort(a,b); sort(b,c); sort(a,b); // -- guarantees a <= b <= c

// Binary Search (for an iterator, or just testing presence):
vector<pt> A;
vector<pt>::iterator it = std::lower_bound(A.begin(), A.end(), val, ycoorder);
int index = it - A.begin(); // -- recover index from iterator
bool found = std::binary_search(A.begin(), A.end(), val, ycoorder);

// Reversing the order of a functional:
// TODOXXX xcoorder
// TODOXXX creating a custom functional like greater<>

// TODOXXX
// TODOXXX basic geometry & trig
// TODOXXX implementing a hash table -- especially necessary in C++
// TODOXXX multimaps, multisets
// TODOXXX heaps, priority queues
// TODOXXX custom shared linked list / prefix list
// TODOXXX 'recursive' computation with a stack
// TODOXXX more stuff from UofT's codebook, credit it
// TODOXXX more stuff from http://cppreference.com, credit it

///////////////////////////////////////////
// Convenience Stuff: std::pair, std::swap

#include <utility>

pair<int,int> p = make_pair(1,2);
p.second = 3;
assert (p.first == 1 && p.second == 3);

// Useful shorthands like:
#define o std::make_pair

typedef pair<int,int> pt;
typedef pair<pt,pt> seg;
seg foo = o(o(0,0),o(1,1));

#include <algorithm>

vector<int> v1(n_a), v2(n_b);
vector<int> *a = v1, *b = v2; int n_a, n_b;
swap(a,b); swap(n_a, n_b); // -- *a alternates between v1 and v2

///////////////////////////
// Basic Trig and Geometry

#include <cmath>

double PI = 4*atan(1.0);
double degree(double rad) { return rad*(180.0/PI); }
double radian(double deg) { return deg*(PI/180.0); }

struct pt { int x; int y; };

double dist(pt a, pt b) {
  double dx = b.x-a.x, dy = b.y-a.y;
  return sqrt(dx*dx+dy*dy);
}

struct line { pt a; pt b; };

pt intersect(line p, line q) {
  // TODOXXX
}

////////////////////
// Next Permutation

#include <vector>
#include <algorithm>

int arr[] = { 0,1,2,3 };
vector<int> vec; vec.insert(vec.begin(), arr, arr+4);

do {
  stuff(vec[0], vec[1], vec[2], vec[3]);
} while (std::next_permutation(vec.begin(), vec.end()));
// -- also possible to use next_permutation(begin,end,&comp)
// -- also possible to use prev_permutation(begin,end)

///////////////////////////////
// Tarjan's Algorithm and 2SAT

// Possible typedefs for the below:
typedef int node;
typedef map<node, set<node> > graph;
struct stack_and_set {
private:
  stack<node> st; set<node> st_i;
public:
  void push(node i) { st.push(i); st_i.insert(i); }
  node pop() { node i = st.top(); st.pop(); st_i.erase(i); return i; }
  int count(node i) { return st_i.count(i); }
};

// Tarjan's SCC Algorithm (pseudocode)
struct tarjan {
  int ticket;
  graph G; // -- directed graph

  map<node, int> index;
  map<node, int> lowlink;
  stack_and_set S;

  deque<set<int> > sccs;

  void nextSCCs(node v);
  void findSCCs();
};

void tarjan::nextSCCs(node v) {
  index[v] = lowlink[v] = ticket; ticket++;
  S.push(v);

  // successors of v
  foreach (edge v -> w in G) {
    if (index.count(w) == 0) {
      nextSCCs(w);
      lowlink[w] = min(lowlink[v],lowlink[w]);
    } else if (S.count(w) > 0) {
      lowlink[v] = min(lowlink[v],index[w]);
    }
  }

  // if v is a root node, output an SCC
  if (lowlink[v] == index[v]) {
    set<node> scc;
    do { node w = S.pop(); scc.insert(w) } while (w != v);
    sccs.push_back(scc); // -- or report it in some other way...
  }
}

void tarjan::findSCCs() {
  ticket = 0, index = 0, S = empty_stack;
  foreach (node v in G) {
    if (index.count(v) == 0) nextSCCs(v);
  }
}

// applying Tarjan to 2SAT
// ---
// to produce an implication graph for a 2SAT problem:
// - foreach item a|b, create implication !b -> a
// - foreach item a|b, create implication !a -> b
// - then use Tarjan to check if any SCCs contain a contradiction a <--> !a

// TODOXXX Kosaraju's Algorithm

///////////////////////////////////////
// Dijkstra's Algorithm and Variations

// TODOXXX Dijkstra's Algorithm
// TODOXXX Suurballe Algorithm

/////////////////////////
// Network Flow Problems

// TODOXXX network flow problems
