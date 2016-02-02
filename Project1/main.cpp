#include <iostream>

class poop {

	int poopoo;
public:
	poop(int poo) : poopoo(poo) {}
	int getPoopoo() { return poopoo; }

};

void doPoo(poop poop1, poop poop2) {
	int i = poop1.getPoopoo();
	std::cout << i << std::endl;
}

int main() {

	std::cout << "main" << std::endl;
	doPoo(64, 32);

	while (true) {}

	return 0;
}