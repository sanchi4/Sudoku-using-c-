#include<bits/stdc++.h>

using namespace std;

int main()
{
	system("tmux attach");
	system("tmux send -t 1 clear ENTER");
	system("tmux send -t 0 clear ENTER");
	system("g++ SUDO.cpp -o xyz");
	system("g++ timer.cpp -o abc");
	system("tmux send -t 1 ./xyz ENTER");
	system("tmux send -t 0 ./abc ENTER");
	//system("tmux send -t 0 ^C ");
	//system(" ^C  >& /dev/pts/1");
	//system("./abc & ./xyz");
	return 0;
}
