
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
int dayofyear(char [],char [], char []);
int datecheck(char [],char [], char []);

void move(int *pos, int temp) //Function To Prevent Cursor From Moving Off
{			      //Screen																																																 			      //cursor from leaving screen
	int x=*pos;
	if(temp==0)
	--*pos;
	else
	++*pos;
	if(*pos==0 || *pos==6)
	*pos=x;
}

int datecheck(char day[],char month[],char year[]) //to check for valid date
{
	int d=atoi(day);
	int m=atoi(month);
	int y=atoi(year);
	if(d<1 || m>12 || m<1 || y<2000 || y>2025) //check within constraints
	return 0;
	switch(m)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:if(d>31)
			return 0;
			break;
		case 2: if(y%4==0) //check leap year
			{
				if(d>29)
				return 0;
			}
			else if(d>28)
			return 0;
			break;
		case 4:
		case 6:
		case 9:
		case 11:if(d>30)
			return 0;
	}
	return 1;
}

class books //CONTAINS ALL BOOK RELATED OPERATIONS
{
	private: char slno[5], name[30], bname[30];
		 char iday[5], imonth[5], iyear[7];
		 char rday[5], rmonth[5], ryear[7];
		 char returned;
		 int late_fee, issue_days, return_days, serial;
		 int issue_year, return_year;

	public: int sl()
		{
			return serial;
		}

		void input(int);
		void output();
		void modify();
		void fissue();
		void freturn();
		char freturned();
		int fserial();
} b ;

int books::fserial()
{
	return serial;
}

char books::freturned()
{
	return returned;
}

void books::fissue()
{
	cout.write(iday,2);
	cout<<"/";
	cout.write(imonth,2);
	cout<<"/";
	cout.write(iyear,4);
}

void books::freturn()
{
	cout.write(rday,2);
	cout<<"/";
	cout.write(rmonth,2);
	cout<<"/";
	cout.write(ryear,4);
}
void books::input(int n)
{
	int x, temp;
	if(n==0)
	{
		cout<<"\t\t\tEnter serial number: ";
		fgets(slno, sizeof(slno), stdin); 
		serial=atoi(slno);
	}
	cout<<"\t\t\tEnter name: ";
	fgets(name, sizeof(name), stdin); 
	cout<<"\t\t\tEnter book name: ";
	fgets(bname, sizeof(bname), stdin); 
	do
	{
		x=0;
		cout<<"\t\t\tENTER ISSUE DATE: ";
		cout<<"\n\t\t\tEnter date of month (dd): ";
		fgets(iday, sizeof(iday), stdin); 
		cout<<"\t\t\tEnter month number(mm): ";
		fgets(imonth, sizeof(imonth), stdin); 
		cout<<"\t\t\tEnter year number (yyyy): ";
		fgets(iyear, sizeof(iyear), stdin);
		if(datecheck(iday,imonth,iyear)==0)
		{
			cout<<"\n\t\t\tInvalid Date.\n\t\t\tPlease enter as the following:\n\t\t\tdd should be from 1 to 31 only\n\t\t\tmm should be from 1 to 12\n\t\t\tyyyy should be four digits\n\n";
			x=1;
		}
		cout<<"\n";
	} while(x==1) ;
	issue_days = dayofyear(iday,imonth,iyear);
	issue_year = atoi(iyear);
	if(n==0)
	returned='n';
}

void books::output()
{
	cout<<"\t\t\tSerial Number: "<<slno;
	cout<<"\n\t\t\tName: ";
	puts(name);
	cout<<"\t\t\tBook Name: ";
	puts(bname);

	cout<<"\t\t\tIssue Date: ";
	fissue();

	cout<<"\n\t\t\tReturn Status: ";
	if(returned=='n')
	cout<<"Not Returned";
	else if(returned=='y') cout<<"Returned";
	//cout<<"\nIssue Days: "<<issue_days;
}

void books::modify()
{
	int x;
	do
	{
		x=0;
		cout<<"\n\t\t\tEnter Return Date";
		cout<<"\n\t\t\tEnter day (dd): ";
		cin.get(rday, sizeof(rday));
		cout<<"\t\t\tEnter month (mm): ";
		fgets(rmonth, sizeof(rmonth), stdin); 
		cout<<"\t\t\tEnter year (yyyy): ";
		fgets(ryear, sizeof(ryear), stdin); 
		int id = atoi(iday), im = atoi(imonth),  iy = atoi(iyear);
		int rd = atoi(rday), rm = atoi(rmonth) , ry = atoi(ryear);

		if(datecheck(rday,rmonth,ryear)==0)
		{
			cout<<"\t\t\tInvalid Date.\n\t\t\tPlease enter as the following:\n\t\t\tdd should be from 1 to 31 only\n\t\t\tmm should be from 1 to 12\n\t\t\tyyyy should be four digits\n";
			x=1;
			continue;
		}
		if( ry<iy || (ry==iy && rm<im) || (ry==iy && rm==im && rd<id) )
		{
			cout<<"\t\t\tReturn Date Cannot Be Before Issue Date\n";
			x=1;
		}
	} while(x==1) ;

	return_days = dayofyear(rday,rmonth,ryear);
	return_year = atoi(ryear);
	cout<<"\n\t\t\tDATE OF ISSUE: ";

	fissue();

	cout<<"\n\t\t\tDATE OF RETURN: ";

	freturn();

	int D = abs(issue_year-return_year);
	if(D==0)
	{
		cout<<"\n\t\t\tNUMBER OF DAYS: "<<return_days-issue_days;
		late_fee = return_days-issue_days;
	}
	else if(abs(D)>0)
	{
		cout<<"\n\t\t\tNUMBER OF DAYS: ";
		if(issue_year%4==0)
		late_fee = (366-issue_days + return_days);
		else
		late_fee = (365-issue_days + return_days);
		for(int i=issue_year+1;i<return_year;i++)
		{
			if(i%4==0)
			late_fee+=366;
			else late_fee+=365;
		}
		cout<<late_fee;
	}
	double tlate_fee = late_fee ;
	tlate_fee = (tlate_fee/14)*100;
	cout<<"\n\t\t\tLate Fee: "<<tlate_fee;
	returned='y';
	getch();
}
int dayofyear(char day[],char month[],char year[]) //FUNCTION TO CALCULATE
{                                                  //DAYS FROM START OF YEAR
	int sum=0;
	int d=atoi(day) ;
	int m=atoi(month) ;
	int y=atoi(year) ;
	int temp=1;

	sum+=d; //Add days of month number m to sum

	while(temp!=m)
	{
		switch(temp)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12: sum+=31;
				break;

			case 2: if(y%4==0)
				sum+=29;
				else
				sum+=28;
				break;

			case 4:
			case 6:
			case 9:
			case 11: sum+=30;
		}
		++temp;
	}
	return sum;
}

class library //CONTAINS ALL MASTER LIBRARY OPERATIONS
{
	private: char ch; int pos;
	public: library()
		{
			pos=1;
		}
		void input();
		void search();
		void menu();
		void save();
		void retbk();
		void modify();
} lib ;

void library::search()
{
	system("cls");
	char s[5];
	int serial;
	ifstream mast("mfile.dat",ios::binary|ios::in);
	cout<<"\n\n\n\n\n\n\n\n";
	cout<<"\t\t\tEnter serial number: ";
	fgets(s, sizeof(s), stdin); 
	serial = atoi(s);
	mast.seekg(0);
	while(!mast.eof())
	{
		mast.read((char*)&b,sizeof(b));
		if(b.sl()==serial)
		{
			b.output();
			getch();
			break;
		}
	}
	mast.close();
	return;
}

void library::input()
{
	system("cls");
	char temp[5], serial, opt;
	fstream mast("mfile.dat",ios::binary|ios::app|ios::in);
	cout<<"\n\n\n\n\n\n\n\n\t\t\tEnter number of borrowers: ";
	fgets(temp, sizeof(temp), stdin); 
	n=atoi(temp);
	for(int i=0;i<n;i++)
	{
		system("cls");
		//cout<<"\n\n\n\n\n\n\t\t\tNOTE:\n\t\t\tIF SERIAL NUMBER ALREADY EXISTS";
		//cout<<"\n\t\t\tINPUTTING SERIAL NUMBER\n\t\t\tWILL NOT OVERWRITE IT";
		cout<<"\n\n\n\n\n\n\t\t\tNOTE: TO MODIFY EXISTING SERIAL NUMBER\n\t\t\tUSE MODIFY OPTION IN MENU\n";
		cout<<"\n\t\t\tEnter Borrower "<<i+1<<"\n";
		b.input(0);
		mast.write((char*)&b,sizeof(b));
	}

	mast.close();
	return;
}

void library::save()
{
	fstream mast("mfile.dat",ios::in|ios::binary);
	fstream data("save.dat",ios::app|ios::binary);
	while(mast)
	{
		mast.read((char*)&b,sizeof(b));
		data.write((char*)&b,sizeof(b));
	}
}

void library::modify()
{
	system("cls");
	char opt,temp[5], pass[10];
	int pos_of_record, x, serial;
	cout<<"\n\n\n\n\n\n\n\n\t\tEnter Administrator Password To Modify: ";
	fgets(pass, sizeof(pass), stdin); 
	if(strcmp("amaatra",pass)!=0)
	{
		cout<<"\n\t\t\tWRONG PASSWORD! PRESS ANY KEY!";
		getch();
		return;
	}
	system("cls");
	cout<<"\n\n\n\n\n\n\t\t\tEnter serial number to modify: ";
	fgets(temp, sizeof(temp), stdin); 
	serial=atoi(temp);
	fstream mast("mfile.dat",ios::binary|ios::in|ios::out);
	mast.seekp(0);
	while(!mast.eof())
	{
		pos_of_record = mast.tellg();
		mast.read((char*)&b,sizeof(b));
		if(b.sl()==serial)
		{
			cout<<"\t\t\tRECORD FOUND!\n";
			b.input(1);
			mast.seekp(pos_of_record);
			mast.write((char*)&b,sizeof(b));
			cout<<"\t\t\tRECORD MODIFIED! PRESS ANY KEY!";
			getch();
			return;
		}
	}
}

void library::retbk()
{
	system("cls");
	char opt,temp[5];
	int pos_of_record, x, serial;
	cout<<"\n\n\n\n\n\n\t\t\tEnter serial number to return book: ";
	fgets(temp, sizeof(temp), stdin); 
	serial=atoi(temp);
	fstream mast("mfile.dat",ios::binary|ios::in|ios::out);
	mast.seekp(0);
	while(!mast.eof())
	{
		pos_of_record = mast.tellg();
		mast.read((char*)&b,sizeof(b));
		if(b.sl()==serial)
		{
			if(b.freturned()=='y')
			{
				cout<<"\t\t\tBOOK ALREADY RETURNED! PRESS ANY KEY!";
				getch();
				return;
			}
			cout<<"\t\t\tRecord Found!";
			start:
			cout<<"\n\t\t\tDate of issue: ";
			b.fissue();
			cout<<"\n\t\t\tDo you wish to return book? (y/n): ";
			cin>>opt;
			opt=tolower(opt);
			if(opt=='n') return;
			else if(opt=='y') goto cont;
			else
			{
				cout<<"\t\t\tTry Again!";
				goto start;
			}
			cont:
			b.modify();
			mast.seekp(pos_of_record);
			mast.write((char*)&b,sizeof(b));
			break;
		}
	}
	mast.close();
	return;
}

void library::menu()
{
	int count=0;
	char choice;
	do
	{
		// textcolor(2);
		system("cls");
		char a;
		fstream art("artwork.txt",ios::in);
		while(art)
		{
			art.get(a);
			cout<<a;
		}
		if(count==0)
		{
			loop:
			cout<<"\n\n 		    DO YOU WISH TO DELETE ALL RECORDS? (y/n): ";
			cin>>choice;
			if(tolower(choice)=='y')
			{
				fstream data("save.dat",ios::out|ios::trunc);
				data.close();
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
			fstream mast("mfile.dat",ios::out|ios::trunc|ios::binary);
			fstream data("save.dat",ios::in|ios::binary);
			while(data)
			{
				data.read((char*)&b,sizeof(b));
				mast.write((char*)&b,sizeof(b));
			}
			mast.close();
			data.close();
			getch();
			continue;
		}
		cout<<"\n\n		       USE W and S TO NAVIGATE: ";
		cout<<"\n		       1 ) I n p u t  D a t a ";
		if(pos==1)
		cout<<"      <-";
		cout<<"\n		       2 ) S e a r c h  D a t a ";
		if(pos==2)
		cout<<"    <-";
		cout<<"\n		       3 ) R e t u r n  B o o k ";
		if(pos==3)
		cout<<"    <-";
		cout<<"\n		       4 ) M o d i f y  R e c o r d ";
		if(pos==4)
		cout<<"<-";
		cout<<"\n		       5 ) E x i t  P r o g r a m ";
		if(pos==5)
		cout<<"  <-";
		ch=getch();
		if(ch=='w')
		move(&pos,0);
		else if(ch=='s')
		move(&pos,1);
		else if(ch=='\r')
		{
			switch(pos)
			{
				case 1:input() ;
					break ;
				case 2:search() ;
					break ;
				case 3:retbk() ;
					break ;
				case 4:modify() ;
					break;
				case 5:save() ;
				       exit(0) ;
			}
		}
	} while(1) ;
}
int main()
{
	system("cls");
	lib.menu();
}
