#include <iostream>
#include <string>
#include "scheduling.h"
#include <cstring>
#include <vector>
#include <sstream>
#include <regex>
using namespace std;

enum PolicyName {
	// REVERSE ENUM
	FCFS = 1,
	RR = 2,
	SPN = 3,
	SRT = 4,
	HRRN = 5,
	FB1 = 6,
	FB2i = 7,
	Aging = 8
};

Scheduler::Scheduler()
{
	numberSimpleSchedulers = 0;
}

SimpleScheduler::SimpleScheduler()
{

}
Process::Process()
{
	priority = 0;
}
void
Scheduler::insertSimpleScheduler(SimpleScheduler * simpleScheduler)
{
	// SimpleScheduler simpleSchedulerCurrent = simpleScheduler;
	// listSimpleSchedulers.push_back(simpleSchedulerCurrent);
}
void
Scheduler::print()
{
	cout << "WELCOME TO OUR SIMPLE SCHEDULER" << endl;
	cout << "1- Mode of visualization: " << to_string(status) << endl;
	cout << "2- Scheduling policies: " << to_string(numberSimpleSchedulers) << endl;
	cout << "3- Timespan: " << to_string(timespan) << endl;
	cout << "4- Number of processes: " << to_string(numberOfProcesses) << endl;
	cout << "5- Processes: " << "Not yet supported." << endl;
}

void
SimpleScheduler::print()
{
	// PolicyName pn;
	// pn = policy_id;
}
int 
main()
{
	// Taking input from user in the following format:

	/*
	LINE 1: STATS/ TRACE
	LINE 2: SCHEDULING POLICIES LIST
	LINE 3: TIMESPAN
	LINE 4: NUMBER OF PROCESSES
	LINE 5 - END: PROCESS DESCRIPTION
	*/

    string flag;
	string policiesList;
    string timespan;
    string numberOfProcesses;
    vector <string> processes;

    getline(cin, flag);
    // cout << flag << endl;
    getline(cin, policiesList);
    // cout << policiesList << endl;
	getline(cin, timespan);
    // cout << timespan << endl;
	getline(cin, numberOfProcesses);
    // cout << numberOfProcesses << endl;

	// Loop over processes and store them in an array proccesses

	for(int i=0; i< stoi(numberOfProcesses);i++)
	{
		string temp;
		getline(cin,temp);
		processes.push_back(temp);
	}

	// Initializing structs

	Scheduler* S = new Scheduler;

	// Assigning numeric variables to Scheduler S
	S->numberOfProcesses = stoi(numberOfProcesses);
	int res = flag.compare("stats");
	S->status = res;
	S->timespan = stoi(timespan);

	// Creating new simple schedulers according to different policies
	// Parse comma-separated string 

	vector <string> policiesParsedList;
	regex reg("[, ]+");
    sregex_token_iterator iter(policiesList.begin(), policiesList.end(), reg, -1);
    sregex_token_iterator end;
     vector<string> policies(iter, end);
 
    for (auto &s: policies) {
        policiesParsedList.push_back(s);
	}

	S->numberSimpleSchedulers = policiesParsedList.size();

	for (int i = 0; i < policiesParsedList.size(); i++)
	{
	string policy = policiesParsedList[i];
	regex reg("[- ]+");
    sregex_token_iterator iter(policy.begin(), policy.end(), reg, -1);
    sregex_token_iterator end;
    vector<string> parsed(iter, end);
 
	if (parsed.size() == 2)
	{
		cout << "ID: " << parsed[0] << endl;
		cout << "Quantum: " << parsed[1] << endl;
		SimpleScheduler *SS	= new SimpleScheduler;
		SS->policy_id = stoi(parsed[0]);
		SS->quantum = stoi(parsed[1]);
		// S->insertSimpleScheduler(SS);
	}

	if (parsed.size() == 1)
	{
		cout << "ID: " << parsed[0] << endl;
		SimpleScheduler *SS	= new SimpleScheduler;
		SS->policy_id = stoi(parsed[0]);
		// S->insertSimpleScheduler(SS);
	}

	}

	// Creating new Processes according to input
	for (int i = 0; i < processes.size(); i++ )
	{
		string policy = processes[i];
		regex reg("[, ]+");
    	sregex_token_iterator iter(policy.begin(), policy.end(), reg, -1);
    	sregex_token_iterator end;
    	vector<string> parsed(iter, end);
		cout << "Process name: " << parsed[0] << endl;
		cout << "Arrival time: " << parsed[1] << endl;
		cout << "Service time: " << parsed[2] << endl;
		Process *P = new Process;
		// P->name=parsed[0].c_str() ;
		P->arrival=stoi(parsed[1]);
		P->service=stoi(parsed[2]);
		if (parsed.size() == 4)
		{
			P->priority = stoi(parsed[3]);
		}
	}

	S->print();
	SimpleScheduler * SS = new SimpleScheduler;
	SS->print();


	return 0;
}

