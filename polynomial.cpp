#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;
int *coeff1, *coeff2;

int FindDegree(const char *a, size_t length) {
	int degree = 0;
	int number = 0, power = 0, powl = 0;
	for (int i = length; i >= 0; i--) {
		if (a[i] >= '0' && a[i] <= '9') {
			number += (a[i] - '0')*pow(10, powl);
			powl++;
			if (i == 0) {
				if (power >= degree)
					degree = power;
			}
		}
		else if (a[i] == 'x' || a[i] == 'X') {
			if (number != 0)
				power = number;
			else
				power = 1;
			if (i == 0) {
				if (power >= degree)
					degree = power;
			}
			number = 0;
			powl = 0;
		}
		else if (a[i] == '+' || a[i] == '-') {
			if (power >= degree)
				degree = power;
			number = 0;
			powl = 0;
			power = 0;
		}
		else if (i == 0) {
			if (power >= degree)
				degree = power;
			number = 0;
			powl = 0;
			power = 0;
		}
	}
	return degree;
}

void setData(const char *a,size_t lenght,int *c) {
	int number = 0, power = 0, powl = 0;
	for (int i = lenght; i >= 0; i--) {
		//if the charecter was number
		if (a[i] >= '0' && a[i] <= '9') {
			//count digits every loop to create a number
			number += (a[i] - '0')*pow(10, powl);
			//count the order value of each number
			powl++;
			//if last charecter was number charecter
			if (i == 0) {
				//set coeffition arrey to number we collect
				c[power] += number;
				//start over every value
				number = 0;
				power = 0;
				powl = 0;
			}
		}
		//when we reach this condition 1)we collected power of numial 2)x is the least charecter
		else if (a[i] == 'x' || a[i] == 'X') {
			//if we did collect number and reach x the power is the number
			if (number != 0)
				power = number;
			else //if we did not collect any number and reach x the power is the 1
				power = 1;
			//if x is the last charecter we set coeffition arrey 1
			if (i == 0) {
				c[power] += 1;
			}
			//start over number and powl
			number = 0;
			powl = 0;
		}
		//if we reach this conition the sentense is over
		else if (a[i] == '+') {
			//if we collected power but coeffition is 0
			if (power != 0 && number == 0) {
				c[power] = 1;
				number = 0;
				power = 0;
				powl = 0;
			}
			//we set values that we collected
			else {
				c[power] += number;
				number = 0;
				power = 0;
				powl = 0;
			}
		}
		//if we reach this condition the sentense is over
		else if (a[i] == '-') {
			//if we collected power but coeffition is 0
			if (power != 0 && number == 0) {
				c[power] = -1;
				number = 0;
				power = 0;
				powl = 0;
			}
			//we set values that we collected
			else {
				c[power] += number*(-1);
				number = 0;
				power = 0;
				powl = 0;
			}
		}
		//if we reach this condition the last digit is nonsense like space
		else if (i == 0) {
			if (power != 0 && number == 0) {
				c[power] = 1;
				number = 0;
				power = 0;
				powl = 0;
			}
			else {
				c[power] += number;
				number = 0;
				power = 0;
				powl = 0;
			}
		}
	}
}

int main()
{
	string func1 = "-x^6+40 x^5 -x^3 -3x^2 + 12x+20";
	//{-1,40,0,-1,-3,12,20}
	string func2 = "-1x^3+ 36x^2 + 10x + 0";
	//{1,36,10,0}
	//Define sizes for arrey that hold coeffitions
	int size1 = FindDegree(func1.c_str(), func1.length()) + 1;
	int size2 = FindDegree(func2.c_str(), func2.length()) + 1;
	//set sizes for pointers
	coeff1 = new int[size1];
	coeff2 = new int[size2];
	//set first value for all parts of coeff arrey
	for (int i = 0; i < size1; i++) {coeff1[i] = 0;}
	for (int i = 0; i < size2 + 1; i++) {coeff2[i] = 0;}
	//setting data using setData() function
	setData(func1.c_str(), func1.length(),coeff1);
	setData(func2.c_str(), func2.length(),coeff2);
	/*<DEBUG>*/
	for (int i = 0; i < size1; i++) {
		cout<<coeff1[i]<<" ";
	}
	cout << endl;
	for (int i = 0; i < size2; i++) {
		cout << coeff2[i] << " ";
	}
	/*<DEBUG>*/
	cin.get();
	cin.get();
	return 0;
}
