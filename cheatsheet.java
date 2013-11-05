/* Serhei's ACM cheatsheet for Java; partly inspired from
- http://psc.cpsc.ucalgary.ca/acpc/2013/files/io-containers.pdf */

//////////////////
// Basic Template

// TODOXXX

/////////////
// Basic I/O

import java.util.*;

Scanner sc = new Scanner(System.in);
int i = sc.nextInt();
String s = sc.next();
double d = sc.nextDouble();

// Check for end-of-file
if (sc.hasNext()) ...; // can read
else ...; // EOF

// Read one word vs. entire line
String word = sc.next();
String line = sc.nextLine(); // -- careful of pseudo-empty line after token

// Print exact string "$1234 hello world 27.35\n"
int dollars = 1234;
double foo = 27.35;
String word = "hello";
System.out.printf("$%d hello %s %.2f\n", dollars, word, foo);

// I/O to and from files:
File f = new File("in.txt");
Scanner sc = new Scanner(f);

File f = new File("out.txt");
PrintStream p = new PrintStream(f); // -- works similarly to System.out

////////////////////////////////////////////
// Containers: ArrayList, LinkedList, Deque

import java.util.*;

// Resizable array:
List<Integer> numbers = new ArrayList<Integer>();
numbers.add(5); numbers.add(7);
// TODOXXX specify initial size, fill with custom default value

numbers.add(1,6); // -- linear time; insert at position 1

assert(numbers.size() == 3);
assert(numbers.get(0) == 5);
assert(numbers.get(1) == 6);
assert(numbers.get(2) == 7);

numbers.clear(); // -- empty
assert(numbers.isEmpty());

// Linked list:
List<Integer> numbers = new LinkedList<Integer>();
numbers.add(7);
numbers.add(0,5); // -- at the beginning

ListIterator<Integer> iter = numbers.listIterator(1); // -- linear time
assert(iter.next() == 7); // -- CAREFUL: next() moves iterator forwards
iter.previous(); // -- moves iterator backwards

iter.add(6); // -- insert before iterator

assert(numbers.size() == 3);
assert(numbers.get(0) == 5); // -- linear time to access LinkedList position
assert(numbers.get(1) == 6);
assert(numbers.get(2) == 7);

// Deque:
deque<int> numbers;
numbers.addLast(7); numbers.addLast(8);
numbers.addFirst(6); numbers.addFirst(5);
assert(numbers.size() == 4);
for (int i = 5; i <= 8; i++) {
  assert(numbers.peekFirst() == i); numbers.removeFirst();
  // -- likewise peekLast(), removeLast()
}

// Queues and stacks:
Queue<Integer> numbers; // -- add(), peek(), remove(), isEmpty()
Stack<Integer> numbers; // -- push(), peek(), pop(), isEmpty(), search()
// -- note that remove()-type operations return the value in question

assert(numbers.search(2) == -1); // -- using search to check for obj presence

/////////////////////////////
// Containers: Maps and Sets

import java.util.*;

// TODOXXX hashtables vs treemaps

Map<String, Integer> days = new TreeMap<String, Integer>();
Set<String> daynames = new Set<String>();

// Add elements (maps and sets):
days.put("Monday",    1); daynames.add("Monday");
days.put("Tuesday",   2); daynames.add("Tuesday");
days.put("Wednesday", 3); daynames.add("Wednesday");
days.put("Thursday",  4); // ... and so forth for daynames
days.put("Friday",    5);
days.put("Saturday",  6);
days.put("Sunday",    7);

// Test presence (maps and sets):
assert(days.containsKey("Monday")); assert(daynames.contains("Monday"));
assert(!days.containsKey("Nonday")); assert(!daynames.contains("Nonday"));

// Get values (maps only):
assert(days.get("Monday") == 1);
assert(days.get("Tuesday") == 1);

// Iterate keys in order of Comparable (maps and sets):
for (Map.Entry<String, Integer> i : days.entrySet()) {
    String key = i.getKey(), value = i.getValue();
}
for (String value : daynames) {
    // ... do stuff with value ...
}

// Delete values (maps and sets):
days.remove("Tuesday"); daynames.remove("Tuesday");

///////////////////////////////
// Containers: custom ordering

// Natural (lexicographic) ordering for pt, used as default.
class Pt implements Comparable {
    public int x, y;

    public int compareTo (Pt other) {
        return x != other.x ? x - other.x : y - other.y;
    }
}

// Custom ordering -- sort by y-coordinate, say:
class CustomOrder implements Comparator<Pt> {
    public int compare (Pt a, Pt b) {
        return a.y - b.y;
    }
}

// Custom order containers:
new TreeSet<Pt>; // -- uses Pt.compareTo() by default
new TreeSet<Pt>(new CustomOrder());
new TreeMap<Pt,String>(new CustomOrder());

// Sorting:
List<Pt> vec;
Collections.sort(vec);
Collections.sort(vec, new CustomOrder());

Pt[] ary;
Arrays.sort(ary);
Arrays.sort(ary, new CustomOrder());
