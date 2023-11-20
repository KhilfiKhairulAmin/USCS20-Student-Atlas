#include<iostream>
using namespace std;
void mainUI(int);

int main()
{
	mainUI(1);
	return 0;
}

void mainUI(int x)
{
	int select;
	if(x == 1)
	{
		cout<< "========================="
			<< "\n Welcome to main menu "
			<<"\n========================="
			<<endl
			<<"1.Browse"
			<<"\n2.Edit"
			<<"\n3.Delete"
			<<"\n4.Exit";
			do {
			cout<<"\nPlease make your selection: ";
			cin>>select;
			} while (x > 4 || x < 1);
			
		switch(select)
		{
			case 1:
				
				break;
			case 2:
				
				break;
			case 3:
				
				break;
			case 4:
				break;
			
		}
	}
	else
	{
		
	}
	
	return;
	
}
