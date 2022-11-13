#include <iostream>
#include <string>
#include "scheduling.h"
#include <cstring>
#include <vector>
#include <sstream>
#include <regex>
#include  <bits/stdc++.h>
  
using namespace std;


// FUNCTIONS OF SCHEDULER

Scheduler::Scheduler()
{
	numberSimpleSchedulers = 0;
}
void 
Scheduler::insertSimpleScheduler(SimpleScheduler* simpleScheduler)
{
	listSimpleSchedulers.push_back(simpleScheduler);
}
void 
Scheduler::insertProcess(Process* P)
{
	listProcesses.push_back(P);
}
void
Scheduler::print()
{
	cout << "WELCOME TO OUR SIMPLE SCHEDULER" << endl;
	cout << "1- Mode of visualization: " << status << endl;
	cout << "2- Scheduling policies: " << numberSimpleSchedulers << endl;
	cout << "3- Timespan: " << timespan << endl;
	cout << "4- Number of processes: " << numberOfProcesses << endl;
	cout << "5- Processes: " << listProcesses[1]->name << endl;
}

// FUNCTIONS OF SIMPLE SCHEDULER

SimpleScheduler::SimpleScheduler()
{

}
void
SimpleScheduler::print()
{
	
}
void
SimpleScheduler::execute(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{
	switch(policy_id)
	{
		case 1:
			FCFS(status,timespan,Processes,numberOfProcesses);
		case 2:
			RR(status,timespan,Processes,numberOfProcesses,quantum);
		case 3:
			SPN(status,timespan,Processes,numberOfProcesses);
		case 4:
			SRT(status,timespan,Processes,numberOfProcesses);
		case 5:
			HRRN(status,timespan,Processes,numberOfProcesses);
		case 6:
			FB1(status,timespan,Processes,numberOfProcesses);
		case 7:
			FB2(status,timespan,Processes,numberOfProcesses);
		case 8:
			AGING(status,timespan,Processes,numberOfProcesses);
	}
}

void
FCFS(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{

}
void
RR(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses, int quantum)
{
	
}
void
SPN(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{

}
void
SRT(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{

}
void
HRRN(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{

}
void
FB1(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{

}
void
FB2(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{

}
void
Aging(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{

}




// FUNCTIONS OF PROCESS

Process::Process()
{
	priority = 0;
}


Scheduler* S = new Scheduler;


// UTILS

void parseInput()
{
	// Taking input from user in the following format:

	/*
	LINE 1: STATS/ TRACE
	LINE 2: SCHEDULING POLICIES LIST
	LINE 3: TIMESPAN
	LINE 4: NUMBER OF PROCESSES
	LINE 5 - END: PROCESS DESCRIPTION
	*/

    char flag [8];
	string policiesList;
    string timespan;
    string numberOfProcesses;
    vector <string> processes;

    cin.getline(flag, 8);
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

	// Assigning numeric variables to Scheduler S
	S->numberOfProcesses = stoi(numberOfProcesses);
	char* res = strstr(flag, "trace");
	if(res) S->status = 0;
	else S->status = 1;
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
		// cout << "ID: " << parsed[0] << endl;
		// cout << "Quantum: " << parsed[1] << endl;
		SimpleScheduler *SS	= new SimpleScheduler;
		SS->policy_id = stoi(parsed[0]);
		SS->quantum = stoi(parsed[1]);
		S->insertSimpleScheduler(SS);
	}

	if (parsed.size() == 1)
	{
		// cout << "ID: " << parsed[0] << endl;
		SimpleScheduler *SS	= new SimpleScheduler;
		SS->policy_id = stoi(parsed[0]);
		S->insertSimpleScheduler(SS);
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
		// cout << "Process name: " << parsed[0] << endl;
		// cout << "Arrival time: " << parsed[1] << endl;
		// cout << "Service time: " << parsed[2] << endl;
		Process *P = new Process;
		P->name=parsed[0].c_str()[0] ;
		P->arrival=stoi(parsed[1]);
		P->service=stoi(parsed[2]);
		if (parsed.size() == 4)
		{
			P->priority = stoi(parsed[3]);
		}
		S->insertProcess(P);
	}

}



int 
main()
{
	parseInput();
	for(int i = 0; i < S->numberSimpleSchedulers; i++)
	{
		S->listSimpleSchedulers[i]->execute(S->status, S->timespan, S->listProcesses, S->numberOfProcesses);	
	}
		
	return 0;
}

