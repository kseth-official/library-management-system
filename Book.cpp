#include "Book.h"

using namespace std;

int daysSinceJanuary1st(char dayAsCString[],char monthAsCString[],char yearAsCString[]) //FUNCTION TO CALCULATE
{                                                  //DAYS FROM START OF YEAR
	int sum = 0;
	int day = atoi(dayAsCString) ;
	int month = atoi(monthAsCString) ;
	int year = atoi(yearAsCString) ;
	
	sum += day; //Add days of month number m to sum

	int i = 1;
	while(i != month)
	{
		switch(i)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12: 
				sum += 31;
				break;
			case 2: 
				if(year % 4 == 0)
					sum += 29;
				else
					sum += 28;
				
				break;

			case 4:
			case 6:
			case 9:
			case 11: sum += 30;
		}

		++i;
	}
	
	return sum;
}

int isValidDate(char dayAsCString[],char monthAsCString[],char yearAsCString[]) //to check for valid date
{
	int day=atoi(dayAsCString);
	int month=atoi(monthAsCString);
	int year=atoi(yearAsCString);
	
	if(day<1 || month>12 || month<1 || year<2000 || year>2025) //check within constraints
		return 0;
	
	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(day>31)
				return 0;
			break;
		case 2: 
			if(year%4==0) //check leap year
			{
				if(day>29)
					return 0;
			} else if(day>28)
				return 0;
			
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if(day>30)
				return 0;
	}
	return 1;
}

int Book::getSerialNumber()
{
	return serialNumberAsInt;
}

char Book::getIsReturned()
{
	return isReturned;
}

void Book::displayIssueInformationFormatted()
{
	cout.write(issueDay,2);
	cout<<"/";
	cout.write(issueMonth,2);
	cout<<"/";
	cout.write(issueYear,4);
}

void Book::displayReturnInformationFormatted()
{
	cout.write(returnDay,2);
	cout<<"/";
	cout.write(returnMonth,2);
	cout<<"/";
	cout.write(returnYear,4);
}
void Book::inputData(int isNewData)
{
	int shouldExit;
	if(isNewData==0)
	{
		cout<<"\t\t\tEnter serial number: ";
		fgets(serialNumber, sizeof(serialNumber), stdin); 
		serialNumberAsInt=atoi(serialNumber);
	}

	cout<<"\t\t\tEnter name: ";
	fgets(borrowerName, sizeof(borrowerName), stdin); 

	cout<<"\t\t\tEnter book name: ";
	fgets(bookName, sizeof(bookName), stdin); 

	do
	{
		shouldExit=0;

		cout<<"\t\t\tENTER ISSUE DATE: ";
		cout<<"\n\t\t\tEnter date of month (dd): ";
		fgets(issueDay, sizeof(issueDay), stdin); 

		cout<<"\t\t\tEnter month number(mm): ";
		fgets(issueMonth, sizeof(issueMonth), stdin); 

		cout<<"\t\t\tEnter year number (yyyy): ";
		fgets(issueYear, sizeof(issueYear), stdin);

		if(isValidDate(issueDay,issueMonth,issueYear)==0)
		{
			cout<<"\n\t\t\tInvalid Date.\n\t\t\tPlease enter as the following:\n\t\t\tdd should be from 1 to 31 only\n\t\t\tmm should be from 1 to 12\n\t\t\tyyyy should be four digits\n\n";
			shouldExit=1;
		}

		cout<<"\n";
	} while(shouldExit==1) ;
	
	issueDateAsDaysSinceJan1st = daysSinceJanuary1st(issueDay,issueMonth,issueYear);
	
	yearOfIssue = atoi(issueYear);
	
	if(isNewData==0)
		isReturned='n';
}

void Book::displayData()
{
	cout<<"\t\t\tSerial Number: "<<serialNumber;
	cout<<"\n\t\t\tName: ";
	puts(borrowerName);
	cout<<"\t\t\tBook Name: ";
	puts(bookName);

	cout<<"\t\t\tIssue Date: ";
	displayIssueInformationFormatted();

	cout<<"\n\t\t\tReturn Status: ";

	if(isReturned=='n')
		cout<<"Not Returned";
	else if(isReturned=='y') 
		cout<<"Returned";
	//cout<<"\nIssue Days: "<<issue_days;
}

void Book::getReturnInformation()
{
	while (true) {
		cout<<"\n\t\t\tEnter Return Date";
		cout<<"\n\t\t\tEnter day (dd): ";
		fgets(returnDay, sizeof(returnDay), stdin);

		cout<<"\t\t\tEnter month (mm): ";
		fgets(returnMonth, sizeof(returnMonth), stdin); 

		cout<<"\t\t\tEnter year (yyyy): ";
		fgets(returnYear, sizeof(returnYear), stdin); 
		
		int issueDayAsInt = atoi(issueDay);
		int issueMonthAsInt = atoi(issueMonth);
		int issueYearAsInt = atoi(issueYear);
		int returnDayAsInt = atoi(returnDay);
		int returnMonthAsInt = atoi(returnMonth);
		int returnYearAsInt = atoi(returnYear);

		if(isValidDate(returnDay,returnMonth,returnYear)==0)
		{
			cout<<"\t\t\tInvalid Date.\n\t\t\tPlease enter as the following:\n\t\t\tdd should be from 1 to 31 only\n\t\t\tmm should be from 1 to 12\n\t\t\tyyyy should be four digits\n";
			continue;
		}
		if( returnYearAsInt<issueYearAsInt || (returnYearAsInt==issueYearAsInt && returnMonthAsInt<issueMonthAsInt) || (returnYearAsInt==issueYearAsInt && returnMonthAsInt==issueMonthAsInt && returnDayAsInt<issueDayAsInt) )
		{
			cout<<"\t\t\tReturn Date Cannot Be Before Issue Date\n";
			continue;
		}

		break;
	}

	returnDateAsDaysSinceJan1st = daysSinceJanuary1st(returnDay,returnMonth,returnYear);
	yearOfReturn = atoi(returnYear);

	cout<<"\n\t\t\tDATE OF ISSUE: ";
	displayIssueInformationFormatted();

	cout<<"\n\t\t\tDATE OF RETURN: ";
	displayReturnInformationFormatted();

	// Calculate Late Fee
	int yearDifference = abs(yearOfIssue-yearOfReturn);
	if(yearDifference == 0)
	{
		cout<<"\n\t\t\tNUMBER OF DAYS: "<<returnDateAsDaysSinceJan1st-issueDateAsDaysSinceJan1st;
		lateFee = returnDateAsDaysSinceJan1st-issueDateAsDaysSinceJan1st;
	}
	else if(abs(yearDifference) > 0)
	{
		cout<<"\n\t\t\tNUMBER OF DAYS: ";
		if(yearOfIssue % 4 == 0)
			lateFee = (366 - issueDateAsDaysSinceJan1st + returnDateAsDaysSinceJan1st);
		else
			lateFee = (365 - issueDateAsDaysSinceJan1st + returnDateAsDaysSinceJan1st);

		for(int i = yearOfIssue + 1;i < yearOfReturn;i++)
		{
			if(i % 4 == 0)
				lateFee += 366;
			else 
				lateFee += 365;
		}
		
		// cout<<"Late Fee Is: "<<lateFee;
	}

	double tlate_fee = lateFee ;
	tlate_fee = (tlate_fee / 14) * 100;
	cout << "\n\t\t\tLate Fee: " << tlate_fee;

	isReturned = 'y';

	getch();
}