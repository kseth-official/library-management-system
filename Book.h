#pragma once

#include<iostream>
#include<conio.h>
#include<fstream>
#include<cstdio>
#include<ctype.h>
#include<process.h>
#include<stdlib.h>
#include<cmath>
#include<cstring>

using namespace std;

//CONTAINS ALL BOOK RELATED OPERATIONS
class Book 
{
	private: 
		char serialNumber[5], borrowerName[30], bookName[30];
		char issueDay[5], issueMonth[5], issueYear[7];
		char returnDay[5], returnMonth[5], returnYear[7];
		char isReturned;
		int lateFee, issueDateAsDaysSinceJan1st, returnDateAsDaysSinceJan1st, serialNumberAsInt;
		int yearOfIssue, yearOfReturn;

	public: 
		void inputData(int);
		void displayData();
		void getReturnInformation();
		void displayIssueInformationFormatted();
		void displayReturnInformationFormatted();
		char getIsReturned();
		int getSerialNumber();
};

extern Book book;
