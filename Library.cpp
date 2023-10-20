#include<iostream>
#include<conio.h>
#include<fstream>
#include<cstdio>
#include<ctype.h>
#include<process.h>
#include<stdlib.h>
#include<cmath>
#include<cstring>

#include "Library.h"
#include "Book.h"

using namespace std;

//FUNCTION PROTOTYPES
int daysSinceJanuary1st(char [],char [], char []);
int isValidDate(char [],char [], char []);

int moveInBounds(int position, int direction) //Function To Prevent Cursor From Moving Off Screen																																																 			    
{			      
	int initialPosition=position;

	if(direction==0)
		--position;
	else
		++position;

	if(position==0 || position==6)
		position=initialPosition;

	return position;
}


void Library::beginSearchSequence()
{
	system("cls");
	char serialNumberAsCString[5];
	int serialNumber;

	ifstream mast("mfile.dat",ios::binary | ios::in);

	cout<<"\n\n\n\n\n\n\n\n";
	cout<<"\t\t\tEnter serial number: ";
	fgets(serialNumberAsCString, sizeof(serialNumberAsCString), stdin);
	serialNumber = atoi(serialNumberAsCString);

	if (serialNumber <= 0) {
		cout << "\t\t\tInvalid Serial Number";
		mast.close();
		getch();
		return;	
	}

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

void Library::beginBorrowSequence()
{
	system("cls");
	char numberOfBorrowersAsCString[5];

	fstream mastFileStream("mfile.dat",ios::binary|ios::app|ios::in);

	cout<<"\n\n\n\n\n\n\n\n\t\t\tEnter number of borrowers: ";
	fgets(numberOfBorrowersAsCString, sizeof(numberOfBorrowersAsCString), stdin); 
	numberOfBorrowers=atoi(numberOfBorrowersAsCString);

	for(int i=0;i<numberOfBorrowers;i++)
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

void Library::saveAllData()
{
	fstream mastFileStream("mfile.dat",ios::in|ios::binary);
	fstream saveFileStream("save.dat",ios::app|ios::binary);
	while(mastFileStream)
	{
		mastFileStream.read((char*)&book,sizeof(book));
		saveFileStream.write((char*)&book,sizeof(book));
	}
}

void Library::beginRecordModificationSequence()
{
	system("cls");
	char serialNumberAsCString[5];
	string password;

	int recordPosition;
	int serialNumber;

	cout<<"\n\n\n\n\n\n\n\n\t\tEnter Administrator Password To Modify: ";
	cin>>password;

	if("amaatra" != password)
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

void Library::beginReturnSequence()
{
	system("cls");

	char option;
	char serialNumberAsCString[5];

	int positionOfRecord;
	int serialNumber;

	cout<<"\n\n\n\n\n\n\t\t\tEnter serial number to return book: ";
	fgets(serialNumberAsCString, sizeof(serialNumberAsCString), stdin);
	serialNumber=atoi(serialNumberAsCString);

	fstream mastFileStream("mfile.dat",ios::binary|ios::in|ios::out);

	mastFileStream.seekg(0);
	while(!mastFileStream.eof())
	{
		positionOfRecord = mastFileStream.tellg();
		mastFileStream.read((char*)&book,sizeof(book));

		if(book.getSerialNumber()==serialNumber)
		{
			if(book.getIsReturned()=='y')
			{
				cout<<"\t\t\tBOOK ALREADY RETURNED! PRESS ANY KEY!";
				mastFileStream.close();
				getch();
				return;
			}

			while (true) {
				cout<<"\t\t\tRecord Found!";
				cout<<"\n\t\t\tDate of issue: ";
				book.displayIssueInformationFormatted();
				cout<<"\n\t\t\tDo you wish to return book? (y/n): ";
				cin>>option;
				option=tolower(option);

				if(option=='n') {
					mastFileStream.close();
					return;
				}
				else if(option=='y') 
				{
					book.getReturnInformation();
					mastFileStream.seekp(positionOfRecord);
					mastFileStream.write((char*)&book,sizeof(book));
					
					break;
				} 
				else 
				{
					cout<<"\t\t\tTry Again!";
				}
			}

			break;
		}
	}

	mastFileStream.close();

	return;
}

void Library::showMainMenu()
{
	int showDeleteFilesSequence=0;
	int mainMenuPosition = 1;
	char choice;
	while (true)
	{
		// textcolor(2);
		system("cls");
		char artCharacter;

		fstream artFileStream("artwork.txt",ios::in);

		while(!artFileStream.eof())
		{
			artFileStream.get(artCharacter);
			cout<<artCharacter;
		}

		if(showDeleteFilesSequence==0)
		{
			while(true) {
				cout<<"\n\n 		    DO YOU WISH TO DELETE ALL RECORDS? (y/n): ";
				cin>>choice;

				if(tolower(choice)=='y')
				{
					fstream saveFileStream("save.dat",ios::out|ios::trunc);
					saveFileStream.close();
					showDeleteFilesSequence=1;
					cout<<"\n		           DATA DELETED! PRESS ANY KEY!";
					break;
				}
				else if(tolower(choice)=='n')
				{
					showDeleteFilesSequence=1;
					cout<<"\n		         DATA NOT DELETED! PRESS ANY KEY!";
					break;
				}
				else
				{
					cout<<"		         Try Again!";
				}
			}
			
			fstream mastFileStream("mfile.dat",ios::out|ios::trunc|ios::binary);
			fstream saveFileStream("save.dat",ios::in|ios::binary);

			while(!saveFileStream.eof())
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
			mainMenuPosition = moveInBounds(mainMenuPosition,0);
		else if(ch=='s')
			mainMenuPosition = moveInBounds(mainMenuPosition,1);
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
	}
}