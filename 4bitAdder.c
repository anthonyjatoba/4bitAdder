/* 	Program: 4 bit adder
	Author: Anthony Jatobá (anthonyjatoba@gmail.com)
	Date: 2015-06-05
*/
	
#include<stdio.h>
#include<string.h>

//The result of the operations are stored on a global char array
char result[5] = "00000";
//This counter sets the position for the result array. It starts at 4 because the sum process is made backwards
int i = 4;

//Those methods below simulate the logic ports
char andGate(char a, char b) {
	return a & b;
}
char orGate(char a, char b) {
	return a | b;
}

char xorGate(char a, char b) {
	//The bitwise operator ^, unlike & and |, returns an int containing 0 (false) or 1 (true).
	//As ASCII code for '0' is 48 and '1' is 49, i can simply add 48 to get the result as a char
	return (a ^ b) + 48;
}

//The function below uses the logic ports declared above for simulate the half adder circuit.
//The carry bit is returned by the function, while the sum is stored on the result array
char halfAdder(char a, char b) {
	result[i] = xorGate(a, b);
	i--;
	
	char carry = andGate(a, b);
	return carry;
}

//It works like the half adder function, but receives the carryIn parameter
char fullAdder(char a, char b, char carryIn) {
	result[i] = xorGate(carryIn, xorGate(a, b));
	i--;

	char carryOut = orGate(andGate(a, b), andGate(xorGate(a, b), carryIn));
	return carryOut;
}

int main(int argc,char *argv[]) {
	char num1[5];
	char num2[5];

	//Passing the parameters received of the program execution to those new variables, for convenience and legibility
	strcpy(num1, argv[1]);
	strcpy(num2, argv[2]);

	//Variable used to store the carry returned by the adder functions
	char carry;

	//Below, the program simulates a 4 bit adder
	carry = halfAdder(num1[3], num2[3]);
	carry = fullAdder(num1[2], num2[2], carry);
	carry = fullAdder(num1[1], num2[1], carry);
	carry = fullAdder(num1[0], num2[0], carry);
	result[0] = carry;

	printf("%s\n", result);

	return 0;
}
