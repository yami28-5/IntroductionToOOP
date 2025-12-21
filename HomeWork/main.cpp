#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class MyString {
	char* data;
public:
	// Constructor
	MyString(const char* str = "") {
		data = new char[strlen(str) + 1];
		strcpy(data, str);
	}
	MyString& operator=(MyString&& other) {
		std::cout << "Move assignment called\n";

		if (this != &other) {

			delete[] data;

			data = other.data;
			other.data = nullptr;
		}

		return *this;
	}
	~MyString() {
		delete[] data;
	}
	void print() const {
		if (data)
			std::cout << data << "\n";
		else
			std::cout << "[empty]\n";
	}
};
int main() {
	MyString a("Hello");
	MyString b("World");

	b = std::move(a);

	b.print();
	a.print();
}