#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

template <typename myType>

class List {
public:
	List() { //Constructor.
		count = 0;
		data = new myType[128];
	}
	List(const List& other) { //Copy constructor.
		count = other.count;
		data = new myType[other.count];
	}
	List(List&& other) noexcept { //Move constructor.
		count = other.count;
		data = new myType[other.count];
		other.data = nullptr;
	}
	~List() noexcept { //Destructor.
		Release();
	}
	void Push(myType info) { //Adds a thing to the list.
		data[count] = info;
		count++;
	}
	void Pop() { //Removes the most recently added thing from the list.
		data[count - 1] = NULL;
		count--;
	}
	void Print() { //Prints the contents of the list to the console.
		for (int i = 0; i < count; i++) {
			cout << data[i] << endl;
		}
	}
	int GetSize() { //Returns how many things are in the list.
		return count;
	}
	bool IsEmpty() { //Returns whether or not there are things in the list.
		if (count == 0) {
			cout << "List is empty." << endl;
			return true;
		}
		else {
			cout << "List is not empty." << endl;
			return false;
		}
	}
	void Release() {
		delete[] data;
	}
private:
	int count; //Amount of things in my list.
	myType* data = nullptr; //My list.
};