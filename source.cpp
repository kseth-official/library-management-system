
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

//stdlib for atoi function
//math for absolute value function
int n;

//INPUT OF SERIAL NUMBER AS CHARACTERS MESSES UP PROGRAM

//FUNCTION PROTOTYPES
int daysSinceJanuary1st(char [],char [], char []);
int isValidDate(char [],char [], char []);

void moveInBounds(int *position, int direction) //Function To Prevent Cursor From Moving Off Screen																																																 			    
{			      
	int initialPosition=*position;

	if(direction==0)
		--*position;
	else
		++*position;

	if(*position==0 || *position==6)
		*position=initialPosition;
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

class books //CONTAINS ALL BOOK RELATED OPERATIONS
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
} book ;

int books::getSerialNumber()
{
	return serialNumberAsInt;
}

char books::getIsReturned()
{
	return isReturned;
}

void books::displayIssueInformationFormatted()
{
	cout.write(issueDay,2);
	cout<<"/";
	cout.write(issueMonth,2);
	cout<<"/";
	cout.write(issueYear,4);
}

void books::displayReturnInformationFormatted()
{
	cout.write(returnDay,2);
	cout<<"/";
	cout.write(returnMonth,2);
	cout<<"/";
	cout.write(returnYear,4);
}
void books::inputData(int isNewData)
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

void books::displayData()
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

void books::getReturnInformation()
{
	int shouldExit;
	do
	{
		shouldExit = 0;

		cout<<"\n\t\t\tEnter Return Date";
		cout<<"\n\t\t\tEnter day (dd): ";
		cin.get(returnDay, sizeof(returnDay));

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
			shouldExit = 1;
			continue;
		}
		if( returnYearAsInt<issueYearAsInt || (returnYearAsInt==issueYearAsInt && returnMonthAsInt<issueMonthAsInt) || (returnYearAsInt==issueYearAsInt && returnMonthAsInt==issueMonthAsInt && returnDayAsInt<issueDayAsInt) )
		{
			cout<<"\t\t\tReturn Date Cannot Be Before Issue Date\n";
			shouldExit = 1;
		}
	} while(shouldExit == 1) ;

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

class library //CONTAINS ALL MASTER LIBRARY OPERATIONS
{
	private:

	public: 
		void beginBorrowSequence();
		void beginSearchSequence();
		void showMainMenu();
		void saveAllData();
		void beginReturnSequence();
		void beginRecordModificationSequence();

} library ;

void library::beginSearchSequence()
{
	system("cls");
	char serialNumberAsCString[5];
	int serialNumber;

	ifstream mast("mfile.dat",ios::binary | ios::in);

	cout<<"\n\n\n\n\n\n\n\n";
	cout<<"\t\t\tEnter serial number: ";
	fgets(serialNumberAsCString, sizeof(serialNumberAsCString), stdin);
	serialNumber = atoi(serialNumberAsCString);

	mast.seekg(0);

	while(!mast.eof())
	{
		mast.read((char*)&book,sizeof(book));
		if(book.getSerialNumber()==serialNumber)
		{
			book.displayData();
			getch();
			break;
		}
	}

	mast.close();

	return;
}

void library::beginBorrowSequence()
{
	system("cls");
	char numberOfBorrowersAsCString[5];

	fstream mastFileStream("mfile.dat",ios::binary|ios::app|ios::in);

	cout<<"\n\n\n\n\n\n\n\n\t\t\tEnter number of borrowers: ";
	fgets(numberOfBorrowersAsCString, sizeof(numberOfBorrowersAsCString), stdin); 
	n=atoi(numberOfBorrowersAsCString);

	for(int i=0;i<n;i++)
	{
		system("cls");
		//cout<<"\n\n\n\n\n\n\t\t\tNOTE:\n\t\t\tIF SERIAL NUMBER ALREADY EXISTS";
		//cout<<"\n\t\t\tINPUTTING SERIAL NUMBER\n\t\t\tWILL NOT OVERWRITE IT";
		cout<<"\n\n\n\n\n\n\t\t\tNOTE: TO MODIFY EXISTING SERIAL NUMBER\n\t\t\tUSE MODIFY OPTION IN MENU\n";
		cout<<"\n\t\t\tEnter Borrower "<<i+1<<"\n";
		book.inputData(0);
		mastFileStream.write((char*)&book,sizeof(book));
	}

	mastFileStream.close();
	return;
}

void library::saveAllData()
{
	fstream mastFileStream("mfile.dat",ios::in|ios::binary);
	fstream saveFileStream("save.dat",ios::app|ios::binary);
	while(mastFileStream)
	{
		mastFileStream.read((char*)&book,sizeof(book));
		saveFileStream.write((char*)&book,sizeof(book));
	}
}

void library::beginRecordModificationSequence()
{
	system("cls");
	char serialNumberAsCString[5];
	char passwordAsCString[10];

	int recordPosition;
	int serialNumber;

	cout<<"\n\n\n\n\n\n\n\n\t\tEnter Administrator Password To Modify: ";
	fgets(passwordAsCString, sizeof(passwordAsCString), stdin); 

	if(strcmp("amaatra",passwordAsCString)!=0)
	{
		cout<<"\n\t\t\tWRONG PASSWORD! PRESS ANY KEY!";
		getch();
		return;
	}

	system("cls");
	
	cout<<"\n\n\n\n\n\n\t\t\tEnter serial number to modify: ";
	fgets(serialNumberAsCString, sizeof(serialNumberAsCString), stdin); 
	serialNumber=atoi(serialNumberAsCString);

	fstream mastFileStream("mfile.dat",ios::binary|ios::in|ios::out);

	mastFileStream.seekp(0);
	while(!mastFileStream.eof())
	{
		recordPosition = mastFileStream.tellg();

		mastFileStream.read((char*)&book,sizeof(book));
		if(book.getSerialNumber()==serialNumber)
		{
			cout<<"\t\t\tRECORD FOUND!\n";
			book.inputData(1);
			mastFileStream.seekp(recordPosition);
			mastFileStream.write((char*)&book,sizeof(book));

			cout<<"\t\t\tRECORD MODIFIED! PRESS ANY KEY!";
			getch();

			return;
		}
	}
}

void library::beginReturnSequence()
{
	system("cls");

	char option;
	char serialNumberAsCString[5];

	int positionOfRecord;
	int serial;

	cout<<"\n\n\n\n\n\n\t\t\tEnter serial number to return book: ";
	fgets(serialNumberAsCString, sizeof(serialNumberAsCString), stdin);
	serial=atoi(serialNumberAsCString);

	fstream mastFileStream("mfile.dat",ios::binary|ios::in|ios::out);

	mastFileStream.seekp(0);
	while(!mastFileStream.eof())
	{
		positionOfRecord = mastFileStream.tellg();
		mastFileStream.read((char*)&book,sizeof(book));

		if(book.getSerialNumber()==serial)
		{
			if(book.getIsReturned()=='y')
			{
				cout<<"\t\t\tBOOK ALREADY RETURNED! PRESS ANY KEY!";
				getch();
				return;
			}

			cout<<"\t\t\tRecord Found!";
			start:
			cout<<"\n\t\t\tDate of issue: ";
			book.displayIssueInformationFormatted();
			cout<<"\n\t\t\tDo you wish to return book? (y/n): ";
			cin>>option;
			option=tolower(option);

			if(option=='n') 
				return;
			else if(option=='y') 
				goto cont;
			else
			{
				cout<<"\t\t\tTry Again!";
				goto start;
			}
			cont:

			book.getReturnInformation();
			mastFileStream.seekp(positionOfRecord);
			mastFileStream.write((char*)&book,sizeof(book));

			break;
		}
	}

	mastFileStream.close();

	return;
}

void library::showMainMenu()
{
	int count=0;
	int mainMenuPosition = 1;
	char choice;
	do
	{
		// textcolor(2);
		system("cls");
		char artCharacter;

		fstream artFileStream("artwork.txt",ios::in);

		while(artFileStream)
		{
			artFileStream.get(artCharacter);
			cout<<artCharacter;
		}

		if(count==0)
		{
			loop:
			cout<<"\n\n 		    DO YOU WISH TO DELETE ALL RECORDS? (y/n): ";
			cin>>choice;

			if(tolower(choice)=='y')
			{
				fstream saveFileStream("save.dat",ios::out|ios::trunc);
				saveFileStream.close();
				count=1;
				cout<<"\n		           DATA DELETED! PRESS ANY KEY!";
			}
			else if(tolower(choice)=='n')
			{
				count=1;
				cout<<"\n		         DATA NOT DELETED! PRESS ANY KEY!";
			}
			else
			{
				cout<<"		         Try Again!";
				goto loop;
			}

			fstream mastFileStream("mfile.dat",ios::out|ios::trunc|ios::binary);
			fstream saveFileStream("save.dat",ios::in|ios::binary);

			while(saveFileStream)
			{
				saveFileStream.read((char*)&book,sizeof(book));
				mastFileStream.write((char*)&book,sizeof(book));
			}

			mastFileStream.close();
			saveFileStream.close();

			getch();

			continue;
		}

		cout<<"\n\n		       USE W and S TO NAVIGATE: ";
		cout<<"\n		       1 ) I n p u t  D a t a ";
		if(mainMenuPosition==1)
			cout<<"      <-";
		
		cout<<"\n		       2 ) S e a r c h  D a t a ";
		
		if(mainMenuPosition==2)
			cout<<"    <-";
		
		cout<<"\n		       3 ) R e t u r n  B o o k ";
		if(mainMenuPosition==3)
			cout<<"    <-";
		
		cout<<"\n		       4 ) M o d i f y  R e c o r d ";
		if(mainMenuPosition==4)
			cout<<"<-";
		
		cout<<"\n		       5 ) E x i t  P r o g r a m ";
		if(mainMenuPosition==5)
			cout<<"  <-";
		
		char ch=getch();
		if(ch=='w')
			moveInBounds(&mainMenuPosition,0);
		else if(ch=='s')
			moveInBounds(&mainMenuPosition,1);
		else if(ch=='\r')
		{
			switch(mainMenuPosition)
			{
				case 1:beginBorrowSequence() ;
					break ;
				case 2:beginSearchSequence() ;
					break ;
				case 3:beginReturnSequence() ;
					break ;
				case 4:beginRecordModificationSequence() ;
					break;
				case 5:saveAllData() ;
				       exit(0) ;
			}
		}
	} while(1) ;
}

int main()
{
	system("cls");
	library.showMainMenu();
}