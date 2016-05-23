#include<iostream>
#include<cstdlib>
#include<unistd.h>
using namespace std;
int main()
{
	int milli=0,sec=0,hour=0,min=0;
	for(;;)
	{
		if(milli==10)
		{
			++sec;
			milli=0;
		}	
		if(sec==60)
		{
			++min;
			sec=0;
		}
		if(min==60)
		{
			++hour;
			min=0;	
		}
		system("clear");
		cout<<"\t\t\t\t\033[1;36mTIMER :  "<<hour<<":"<<min<<":"<<sec<<"\033[0m"<<endl;
		++milli;
		usleep(100000);
	}
	return 0;
}
