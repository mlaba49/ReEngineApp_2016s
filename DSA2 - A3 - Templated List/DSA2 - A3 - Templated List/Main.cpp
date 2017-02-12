#include "List.h"

int main() {
	//List of integers
	List<int> myInts;
	myInts.IsEmpty();
	myInts.GetSize();
	myInts.Print();
	myInts.Push(5);
	myInts.Push(12);
	myInts.Push(42);
	myInts.IsEmpty();
	myInts.GetSize();
	myInts.Print();

	//List of characters
	List<char> myChars;
	myChars.Push('f');
	myChars.Push('r');
	myChars.Push('i');
	myChars.Push('s');
	myChars.Push('k');
	myChars.Print();

	//List of doubles
	List<double> myDoubles;
	myDoubles.Push(2.3);
	myDoubles.Push(5.6);
	myDoubles.Push(9.1);
	myDoubles.Print();

	getchar();
	return 0;
}