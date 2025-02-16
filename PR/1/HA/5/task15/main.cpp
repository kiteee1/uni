#include <iostream>

int stack_overflow(int i) {
	return stack_overflow(i+1);
}

int main() {
	stack_overflow(1);
	
	return 0;
}
