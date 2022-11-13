#include <iostream>
#include <string>
#include "scheduling.h"
#include <cstring>
#include <vector>
using namespace std;



Scheduler::Scheduler()
{

}

int 
main()
{
	// Taking input from user

    string flag;
	string policiesList;
    string timespan;
    string numberOfProcesses;
    vector <string> processes;

    getline(cin, flag);
    cout << flag << endl;
    getline(cin, policiesList);
    cout << policiesList << endl;
	getline(cin, timespan);
    cout << timespan << endl;
	getline(cin, numberOfProcesses);
    cout << numberOfProcesses << endl;
	for(int i=0; i< stoi(numberOfProcesses);i++)
	{
		string temp;
		getline(cin,temp);
		processes.push_back(temp);
	}
	for(int i=0; i< stoi(numberOfProcesses);i++)
	{
		cout << processes[i] << endl;
	}

	// Initializing structs
	Scheduler* S = new Scheduler;
	//currentScheduler->numberSimpleSchedulers = stoi();
	S->numberOfProcesses = stoi(numberOfProcesses);
	if(flag == "stats") S->flag = 0;
	else if(flag == "trace") S->flag = 1;
	S->timespan = stoi(timespan);



	return 0;
}

