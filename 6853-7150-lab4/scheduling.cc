// Lara HossamElDin Mostafa	6853
// Nour Hesham Shaheen 		7150

#include <iostream>
#include <string>
#include "scheduling.h"
#include <cstring>
#include <vector>
#include <sstream>
#include <regex>
#include <queue>
#include  <bits/stdc++.h>
using namespace std;


// utils

Triple::Triple()
{
}


struct myComp {
    constexpr bool operator()(
        pair<int, int> const& x,
        pair<int, int> const& y)
        const noexcept
    {
		if(x.first == y.first)
			return x.second > y.second;
		
        return x.first < y.first;
    }
};

struct myComp2 {
    constexpr bool operator()(
        pair<float, int> const& x,
        pair<float, int> const& y)
        const noexcept
    {
		if(x.first == y.first)
			return x.second > y.second;
		
        return x.first < y.first;
    }
};

struct myComp3{
	constexpr bool operator()(
        Triple const& x,
        Triple const& y)
        const noexcept
    {
		if(x.a == y.a){
			if(x.b == y.b)
				return x.c > y.c;
			return x.b < y.b;
		}		
        return x.a < y.a;
    }

};

void utility(priority_queue<Triple, vector<Triple>, myComp3> q)
{
	priority_queue<Triple, vector<Triple>, myComp3> pq = q;
	size_t size = pq.size();
	for(int i = 0; i < size; ++i) {
    cout << pq.top().a << " " << pq.top().b << " " << pq.top().c << "; ";
    pq.pop();
	}
	cout << endl;
}

void
FCFS(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{
	/* Logic: 
	- Check if Ready_Queue is not empty and CPU is free
	- If Yes: Pop process from Queue, mark the CPU as busy, update the remaining service time of this process
	 - When processe's remaing service time is 0, mark CPU as free
	*/ 
	
	// Initialize Queue
	// Initialize array for each process
	char result[numberOfProcesses][timespan];
	queue<int> readyQueue;
	bool cpu_free = true;
	int currIdx = -1;

	for(int a = 0; a < numberOfProcesses; a++)
			{
				for(int b = 0; b < timespan; b++)
				{
				result[a][b]=' ';
				}
			}
	for (int i = 0; i < timespan; i++)
	{
		// Check if new process arrives
		for (int j=0; j < numberOfProcesses; j++)
		{
			if(Processes[j]->arrival == i)
			{
				// Push process index in ready Queue
				readyQueue.push(j);
			}
			if(Processes[j]->arrival <= i && Processes[j]->service == Processes[j]->tempService )
			{
				result[j][i] = '.';
			}
		}
		if (!readyQueue.empty() && cpu_free)
		{
			currIdx=readyQueue.front();
			readyQueue.pop();
			cpu_free = false;
		}
		if(!cpu_free && currIdx != -1)
		{
			Processes[currIdx]->tempService--;
			result[currIdx][i] = '*';
		}
		if (Processes[currIdx]->tempService == 0)
		{
			cpu_free = true;
			Processes[currIdx]->finish = i;
			Processes[currIdx]->turn = Processes[currIdx]->finish - Processes[currIdx]->arrival + 1;
			Processes[currIdx]->norm = (Processes[currIdx]->turn*1.0 / Processes[currIdx]->service*1.0);
			Processes[currIdx]->finish++;
			// currIdx = -1;
		}

	}
	// TRACE
	if(status == 0)
	{
		cout << "FCFS  ";
		for(int a = 0; a <= timespan; a++)
		{
			if(a>9)
			{
				cout << a%10 << " ";
			}
			else
			{
				cout << a << " ";
			}
		}
		cout << '\n';
		cout << "------------------------------------------------" << endl;
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << Processes[a]->name << "     |";

			for(int b = 0; b < timespan; b++)
			{
			cout << result[a][b] << "|";
			}
			cout <<" " << endl;
		} 
		cout << "------------------------------------------------" << endl << endl;
	}
		// STATS
	else if(status ==1)
	{
		cout << "FCFS" << endl;
		cout << "Process    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << "  " << Processes[a]->name << "  |";
		} 
		cout << endl;
		cout << "Arrival    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->arrival>9)
			{
			cout << " " << Processes[a]->arrival << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->arrival << "  |";
			}
		} 
		cout << endl;

		cout << "Service    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->service>9)
			{
			cout << " " << Processes[a]->service << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->service << "  |";
			}		} 
			cout << " Mean|" << endl;
		cout << "Finish     |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->finish>9)
			{
			cout << " " << Processes[a]->finish << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->finish << "  |";
			}		
			}
			cout << "-----|" << endl;
 
		float meanTurn = 0;
		cout << "Turnaround |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->turn>9)
			{
			cout << " " << Processes[a]->turn << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->turn << "  |";
			}
			meanTurn += Processes[a]->turn;	
		} 
		meanTurn = meanTurn/numberOfProcesses;
		if(meanTurn<10) printf(" %.2f|\n", meanTurn);
		else printf("%.2f|\n", meanTurn);
		float normTurn = 0;
		cout << "NormTurn   |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			printf(" %.2f|", Processes[a]->norm);
			normTurn += Processes[a]->norm;
		} 
		normTurn = normTurn/numberOfProcesses;
		if(normTurn<10) printf(" %.2f|\n", normTurn);
		else printf("%.2f|\n", normTurn);
		cout << endl;		

	}

}
void
RR(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses, int quantum)
{
/*
	First process that arrives is seleced and sent for execution for the specified time quantum. 
	Process is stopped at a timer (quantum) and gets sent to the end of the queue. 
	Scheduler selects the next ready process for the same quantum and iterates again until completion.
*/
	
	char result[numberOfProcesses][timespan];
	int quantumList[numberOfProcesses] = {0};
	int doneList[numberOfProcesses]={0};
	for(int a = 0; a < numberOfProcesses; a++)
			{
				for(int b = 0; b < timespan; b++)
				{
				result[a][b]=' ';
				}
			}
	queue<int> readyQueue;
	bool cpu_free = true;
	int currIdx = -1;
	int pushed = 0;
	for (int i = 0; i < timespan; i++)
	{
		// Check if new process arrives
		for (int j=0; j < numberOfProcesses; j++)
		{
			if(Processes[j]->arrival == i && pushed == false)
			{
				// Push process index in ready Queue
				readyQueue.push(j);
			}
			if(Processes[j]->arrival <= i && doneList[j] != 1 )
			{
				result[j][i] = '.';
			}
		}
		pushed = false;
		if (!readyQueue.empty() && cpu_free)
		{
			currIdx=readyQueue.front();
			readyQueue.pop();
			cpu_free = false;
		}
		if(!cpu_free && currIdx != -1)
		{
			Processes[currIdx]->tempService--;
			result[currIdx][i] = '*';
			quantumList[currIdx]++;
			if (quantumList[currIdx] == quantum)
			{
				if(Processes[currIdx]->tempService != 0)
				{

					for (int j=0; j < numberOfProcesses; j++)
					{
						if(Processes[j]->arrival == i+1)
						{
							// Push process index in ready Queue
							// cout << "Pushing " << j << " into Queue." << endl;
							readyQueue.push(j);
							pushed = 1;
						}
						if(Processes[j]->arrival <= i+1 && doneList[j] != 1 )
						{
							result[j][i+1] = '.';
						}
					}
					readyQueue.push(currIdx);
					quantumList[currIdx] = 0;
					cpu_free = true;
				}	
			}
		}		
		if (Processes[currIdx]->tempService == 0)
		{
			doneList[currIdx] = 1;
			cpu_free = true;
			Processes[currIdx]->finish = i;
			Processes[currIdx]->turn = Processes[currIdx]->finish - Processes[currIdx]->arrival + 1;
			Processes[currIdx]->norm = (Processes[currIdx]->turn*1.0 / Processes[currIdx]->service*1.0);
			Processes[currIdx]->finish++;
			// currIdx = -1;
		}
	}
	// TRACE
	if(status == 0)
	{
		cout << "RR-";
		cout << quantum <<"  ";
		for(int a = 0; a <= timespan; a++)
		{
			if(a>9)
			{
				cout << a%10 << " ";
			}
			else
			{
				cout << a << " ";
			}
		}
		cout << '\n';
		cout << "------------------------------------------------" << endl;
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << Processes[a]->name << "     |";

			for(int b = 0; b < timespan; b++)
			{
			cout << result[a][b] << "|";
			}
			cout << " " << endl;
		} 
		cout << "------------------------------------------------" << endl << endl;
	}
		// STATS
	else if(status ==1)
	{
		cout << "RR-";
		cout << quantum <<endl;
				cout << "Process    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << "  " << Processes[a]->name << "  |";
		} 
		cout << endl;
		cout << "Arrival    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->arrival>9)
			{
			cout << " " << Processes[a]->arrival << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->arrival << "  |";
			}
		} 
		cout << endl;

		cout << "Service    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->service>9)
			{
			cout << " " << Processes[a]->service << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->service << "  |";
			}		} 
			cout << " Mean|" << endl;
		cout << "Finish     |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->finish>9)
			{
			cout << " " << Processes[a]->finish << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->finish << "  |";
			}		
			}
			cout << "-----|" << endl;
 
		float meanTurn = 0;
		cout << "Turnaround |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->turn>9)
			{
			cout << " " << Processes[a]->turn << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->turn << "  |";
			}
			meanTurn += Processes[a]->turn;	
		} 
		meanTurn = meanTurn/numberOfProcesses;
		if(meanTurn<10) printf(" %.2f|\n", meanTurn);
		else printf("%.2f|\n", meanTurn);
		float normTurn = 0;
		cout << "NormTurn   |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			printf(" %.2f|", Processes[a]->norm);
			normTurn += Processes[a]->norm;
		} 
		normTurn = normTurn/numberOfProcesses;
		if(normTurn<10) printf(" %.2f|\n", normTurn);
else printf("%.2f|\n", normTurn);
		cout << endl;
	
	}

	
	

}
void
SPN(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{
	// Initialize Priority Queue
	// Initialize array for each process
	char result[numberOfProcesses][timespan];
	for(int a = 0; a < numberOfProcesses; a++)
			{
				for(int b = 0; b < timespan; b++)
				{
				result[a][b]=' ';
				}
			}
	// map<int, int> service_indicator;
	priority_queue<pair<int, int>> readyQueue;
	bool cpu_free = true;
	int currIdx = -1;
	for (int i = 0; i < timespan; i++)
	{
		// Check if new process arrives
		for (int j=0; j < numberOfProcesses; j++)
		{
			if(Processes[j]->arrival == i)
			{
				// Push process service time in ready Queue
				readyQueue.push(make_pair(Processes[j]->service * -1, j));
			}
			if(Processes[j]->arrival <= i && Processes[j]->service == Processes[j]->tempService )
			{
				result[j][i] = '.';
			}
		}
		if (!readyQueue.empty() && cpu_free)
		{
			pair<int, int> top = readyQueue.top();
			currIdx = top.second;
			readyQueue.pop();
			cpu_free = false;
		}
		if(!cpu_free && currIdx != -1)
		{
			Processes[currIdx]->tempService--;
			result[currIdx][i] = '*';
		}
		if (Processes[currIdx]->tempService == 0)
		{
			cpu_free = true;
			Processes[currIdx]->finish = i;
			Processes[currIdx]->turn = Processes[currIdx]->finish - Processes[currIdx]->arrival + 1;
			Processes[currIdx]->norm = (Processes[currIdx]->turn*1.0 / Processes[currIdx]->service)*1.0;
			Processes[currIdx]->finish++;
			// currIdx = -1;
		}

	}
	// TRACE
	if(status == 0)
	{
		cout << "SPN   ";
		for(int a = 0; a <= timespan; a++)
		{
			if(a>9)
			{
				cout << a%10 << " ";
			}
			else
			{
				cout << a << " ";
			}
		}
		cout << '\n';
		cout << "------------------------------------------------" << endl;
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << Processes[a]->name << "     |";

			for(int b = 0; b < timespan; b++)
			{
			cout << result[a][b] << "|";
			}
			cout << " "<< endl;
		} 
		cout << "------------------------------------------------" << endl << endl;
	}
		// STATS
	else if(status ==1)
	{
		cout << "SPN"<<endl;
		cout << "Process    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << "  " << Processes[a]->name << "  |";
		} 
		cout << endl;
		cout << "Arrival    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->arrival>9)
			{
			cout << " " << Processes[a]->arrival << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->arrival << "  |";
			}
		} 
		cout << endl;

		cout << "Service    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->service>9)
			{
			cout << " " << Processes[a]->service << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->service << "  |";
			}		} 
			cout << " Mean|" << endl;
		cout << "Finish     |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->finish>9)
			{
			cout << " " << Processes[a]->finish << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->finish << "  |";
			}		
			}
			cout << "-----|" << endl;
 
		float meanTurn = 0;
		cout << "Turnaround |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->turn>9)
			{
			cout << " " << Processes[a]->turn << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->turn << "  |";
			}
			meanTurn += Processes[a]->turn;	
		} 
		meanTurn = meanTurn/numberOfProcesses;
		if(meanTurn<10) printf(" %.2f|\n", meanTurn);
		else printf("%.2f|\n", meanTurn);
		float normTurn = 0;
		cout << "NormTurn   |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			printf(" %.2f|", Processes[a]->norm);
			normTurn += Processes[a]->norm;
		} 
		normTurn = normTurn/numberOfProcesses;
		if(normTurn<10) printf(" %.2f|\n", normTurn);
		else printf("%.2f|\n", normTurn);
		cout << endl;		

	}
	
}

void
SRT(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{
	// Shortest Remaining time
	// Initialize array for each process
	char result[numberOfProcesses][timespan];
	for(int a = 0; a < numberOfProcesses; a++)
	{
				for(int b = 0; b < timespan; b++)
				{
				result[a][b]=' ';
				}
	}
	priority_queue<pair<int,int>, vector<pair<int,int>>, myComp> readyQueue;
	bool cpu_free = true;
	int currIdx = -1;
	for (int i = 0; i < timespan; i++)
	{
		// Check if new process arrives
		for (int j=0; j < numberOfProcesses; j++)
		{
			if(Processes[j]->arrival == i)
			{
				// Check if we should preempt or not
				if(!cpu_free && currIdx != -1 && Processes[j]->service < Processes[currIdx]->tempService){
						Processes[currIdx]->preempted = true;
						result[currIdx][i] = '.';
						readyQueue.push(make_pair(Processes[currIdx]->tempService * -1, currIdx));
						currIdx = j;
				}
				else{
					readyQueue.push(make_pair(Processes[j]->service * -1, j));
				}
			}
			if(Processes[j]->arrival <= i && Processes[j]->service == Processes[j]->tempService || Processes[j]->preempted)
			{
				result[j][i] = '.';
			}
		}
		if (!readyQueue.empty() && cpu_free)
		{
			pair<int, int> top = readyQueue.top();
			currIdx = top.second;
			readyQueue.pop();
			Processes[currIdx]->preempted = false;
			//printf("%d\n", readyQueue.top());
			cpu_free = false;
		}
		if(!cpu_free && currIdx != -1)
		{
			Processes[currIdx]->tempService--;
			result[currIdx][i] = '*';
		}
		if (Processes[currIdx]->tempService == 0)
		{
			cpu_free = true;
			Processes[currIdx]->finish = i;
			Processes[currIdx]->turn = Processes[currIdx]->finish - Processes[currIdx]->arrival + 1;
			Processes[currIdx]->norm = (Processes[currIdx]->turn*1.0 / Processes[currIdx]->service)*1.0;
			Processes[currIdx]->finish++;
			// currIdx = -1;
		}

	}
	// TRACE
	if(status == 0)
	{
		cout << "SRT   ";
		for(int a = 0; a <= timespan; a++)
		{
			if(a>9)
			{
				cout << a%10 << " ";
			}
			else
			{
				cout << a << " ";
			}
		}
		cout << '\n';
		cout << "------------------------------------------------" << endl;
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << Processes[a]->name << "     |";

			for(int b = 0; b < timespan; b++)
			{
			cout << result[a][b] << "|";
			}
			cout << " " << endl;
		} 
		cout << "------------------------------------------------" << endl;
		cout << endl;
	}
		// STATS
	else if(status ==1)
	{
		cout << "SRT"<<endl;
		cout << "Process    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << "  " << Processes[a]->name << "  |";
		} 
		cout << endl;
		cout << "Arrival    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->arrival>9)
			{
			cout << " " << Processes[a]->arrival << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->arrival << "  |";
			}
		} 
		cout << endl;

		cout << "Service    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->service>9)
			{
			cout << " " << Processes[a]->service << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->service << "  |";
			}		} 
			cout << " Mean|" << endl;
		cout << "Finish     |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->finish>9)
			{
			cout << " " << Processes[a]->finish << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->finish << "  |";
			}		
			}
			cout << "-----|" << endl;
 
		float meanTurn = 0;
		cout << "Turnaround |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->turn>9)
			{
			cout << " " << Processes[a]->turn << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->turn << "  |";
			}
			meanTurn += Processes[a]->turn;	
		} 
		meanTurn = meanTurn/numberOfProcesses;
		if(meanTurn<10) printf(" %.2f|\n", meanTurn);
		else printf("%.2f|\n", meanTurn);
		float normTurn = 0;
		cout << "NormTurn   |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			printf(" %.2f|", Processes[a]->norm);
			normTurn += Processes[a]->norm;
		} 
		normTurn = normTurn/numberOfProcesses;
		if(normTurn<10) printf(" %.2f|\n", normTurn);
		else printf("%.2f|\n", normTurn);
		cout << endl;		
	}
}

void
HRRN(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{

	// Initialize array for each process
	char result[numberOfProcesses][timespan];
	for(int a = 0; a < numberOfProcesses; a++){
				for(int b = 0; b < timespan; b++)
				{
				result[a][b]=' ';
				}
	}
	priority_queue<pair<float,int>, vector<pair<float,int>>, myComp2> readyQueue;	
	priority_queue<pair<float,int>, vector<pair<float,int>>, myComp2> readyQueue_new;
	priority_queue<pair<float,int>, vector<pair<float,int>>, myComp2> emptyQueue;
	int waitingTimes[numberOfProcesses] = {0};
	bool cpu_free = true;
	int currIdx = -1;
	for (int i = 0; i < timespan; i++)
	{
		// Check if new process arrives
		for (int j=0; j < numberOfProcesses; j++)
		{
			if(Processes[j]->arrival == i)
			{
				// Push process service time in ready Queue
				float rspR = (waitingTimes[j]+Processes[j]->service)*1.0/Processes[j]->service;
				readyQueue.push(make_pair(rspR, j));
			}
			if(Processes[j]->arrival <= i && Processes[j]->service == Processes[j]->tempService )
			{
				result[j][i] = '.';
				waitingTimes[j]++;
				float new_rspR = (waitingTimes[j]+Processes[j]->service)*1.0/Processes[j]->service;
				while(!readyQueue.empty())
				{
					pair<float, int> top = readyQueue.top();
					readyQueue.pop();
					float rspR = top.first;
					int l = top.second;
					if(l == j)
						rspR = new_rspR;
					readyQueue_new.push(make_pair(rspR, l));		
				}
				readyQueue = readyQueue_new;
				readyQueue_new = emptyQueue;
			}
		}
		if (!readyQueue.empty() && cpu_free)
		{
			pair<float, int> top = readyQueue.top();
			currIdx = top.second;
			readyQueue.pop();
			cpu_free = false;
		}
		if(!cpu_free && currIdx != -1)
		{
			Processes[currIdx]->tempService--;
			result[currIdx][i] = '*';
		}
		// cout << Processes[currIdx] -> tempService << endl;
		if (Processes[currIdx]->tempService <= 0)
		{
			cpu_free = true;
			Processes[currIdx]->finish = i;
			Processes[currIdx]->turn = Processes[currIdx]->finish - Processes[currIdx]->arrival + 1;
			Processes[currIdx]->norm = (Processes[currIdx]->turn*1.0 / Processes[currIdx]->service)*1.0;
			Processes[currIdx]->finish++;
			// currIdx = -1;
		}

	}
			// TRACE
	if(status == 0)
	{
		cout << "HRRN  ";
		for(int a = 0; a <= timespan; a++)
		{
			if(a>9)
			{
				cout << a%10 << " ";
			}
			else
			{
				cout << a << " ";
			}
		}
		cout << '\n';
		cout << "------------------------------------------------" << endl;
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << Processes[a]->name << "     |";

			for(int b = 0; b < timespan; b++)
			{
			cout << result[a][b] << "|";
			}
			cout << " " << endl;
		} 
		cout << "------------------------------------------------" << endl;
		cout << endl;
	}
		// STATS
	else if(status ==1)
	{
		cout << "HRRN"<<endl;
		cout << "Process    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << "  " << Processes[a]->name << "  |";
		} 
		cout << endl;
		cout << "Arrival    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->arrival>9)
			{
			cout << " " << Processes[a]->arrival << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->arrival << "  |";
			}
		} 
		cout << endl;

		cout << "Service    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->service>9)
			{
			cout << " " << Processes[a]->service << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->service << "  |";
			}		} 
			cout << " Mean|" << endl;
		cout << "Finish     |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->finish>9)
			{
			cout << " " << Processes[a]->finish << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->finish << "  |";
			}		
			}
			cout << "-----|" << endl;
 
		float meanTurn = 0;
		cout << "Turnaround |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->turn>9)
			{
			cout << " " << Processes[a]->turn << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->turn << "  |";
			}
			meanTurn += Processes[a]->turn;	
		} 
		meanTurn = meanTurn/numberOfProcesses;
		if(meanTurn<10) printf(" %.2f|\n", meanTurn);
		else printf("%.2f|\n", meanTurn);
		float normTurn = 0;
		cout << "NormTurn   |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			printf(" %.2f|", Processes[a]->norm);
			normTurn += Processes[a]->norm;
		} 
		normTurn = normTurn/numberOfProcesses;
		if(normTurn<10) printf(" %.2f|\n", normTurn);
		else printf("%.2f|\n", normTurn);
		cout << endl;
	}
}

void
FB1(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{
	int quantum = 1;
	char result[numberOfProcesses][timespan];
	int quantumList[numberOfProcesses] = {0};
	int doneList[numberOfProcesses]={0};
	int queueTracker[numberOfProcesses]={0};
	bool cpu_free = true;
	int currIdx = -1;
	queue<int> RQ0;
	queue<int> RQ1;
	queue<int> RQ2;
	queue<int> RQ3;
	queue<int> RQ4;
	queue<int> RQ5;
	int queueStatus[6]={0};


	for(int a = 0; a < numberOfProcesses; a++)
			{
				for(int b = 0; b < timespan; b++)
				{
				result[a][b]=' ';
				}
			}

	for (int i = 0; i < timespan; i++)
	{
		// Check if new process arrives
		for (int j=0; j < numberOfProcesses; j++)
		{
			if(Processes[j]->arrival == i)
			{
				// Push process index in RQ that is suitable to its 
				// prioriry, RQ0 because it has just arrived.
				RQ0.push(j);
				queueStatus[0]++;
			}
			if(Processes[j]->arrival <= i && doneList[j] != 1 )
			{
				result[j][i] = '.';
			}
		}

		if (!RQ0.empty())
		{
			if(cpu_free)
			{
				currIdx=RQ0.front();
				RQ0.pop();
				queueStatus[0]--;
				cpu_free = false;
			}
		}
		else if (!RQ1.empty() && RQ0.empty())
		{
			if(cpu_free)
			{
				currIdx=RQ1.front();
				RQ1.pop();
				queueStatus[1]--;
				cpu_free = false;
			}
		}
		else if (!RQ2.empty() && RQ0.empty() && RQ1.empty())
		{
			if(cpu_free)
			{
				currIdx=RQ2.front();
				RQ2.pop();
				queueStatus[2]--;
				cpu_free = false;
			}
		}
		else if (!RQ3.empty() && RQ0.empty() && RQ1.empty() && RQ2.empty())
		{
			if(cpu_free)
			{
				currIdx=RQ3.front();
				RQ3.pop();
				queueStatus[3]--;
				cpu_free = false;
			}
		}
		else if (!RQ4.empty() && RQ0.empty() && RQ1.empty() && RQ2.empty() && RQ3.empty() )
		{
			if(cpu_free)
			{
				currIdx=RQ4.front();
				RQ4.pop();
				queueStatus[4]--;
				cpu_free = false;
			}
		}
		else if (!RQ5.empty() && RQ0.empty() && RQ1.empty() && RQ2.empty() && RQ3.empty() && RQ4.empty() )
		{
			if(cpu_free)
			{
				currIdx=RQ5.front();
				RQ5.pop();
				queueStatus[5]--;
				cpu_free = false;
			}
		}
		

		if(!cpu_free && currIdx != -1)
		{
			Processes[currIdx]->tempService--;
			result[currIdx][i] = '*';
			quantumList[currIdx]++;
			int count = 0;
			for (int j=0; j < numberOfProcesses; j++)
			{
				if(Processes[j]->arrival == i+1)
				{
					count++;
				}
			}
			if (quantumList[currIdx] == quantum)
			{
				// IF ALL OTHER QUEUES ARE EMPTY, STAY IN THE SAME QUEUE
				int sum  = 0;
				for (int i=0;i<6;i++)
				{
					sum+=queueStatus[i];
				}
				if (Processes[currIdx]->tempService != 0 && queueStatus[queueTracker[currIdx]]-sum == 0 && count==0)
				{
					queueTracker[currIdx]--;
				}
				queueTracker[currIdx]++;
				if(Processes[currIdx]->tempService != 0)
				{
					// cout << "Pushing " << currIdx << " into Queue " << queueTracker[currIdx] << endl;
					switch(queueTracker[currIdx])
					{
						case 0:
							RQ0.push(currIdx);
							break;
						case 1:
							RQ1.push(currIdx);
							break;
						case 2:
							RQ2.push(currIdx);
							break;
						case 3:
							RQ3.push(currIdx);
							break;
						case 4:
							RQ4.push(currIdx);
							break;
						case 5:
							RQ5.push(currIdx);
							break;
					}
					queueStatus[queueTracker[currIdx]]++;
				}
				quantumList[currIdx] = 0;
				cpu_free = true;
		
			}	
		}
		if (Processes[currIdx]->tempService == 0)
		{
			doneList[currIdx] = 1;
			cpu_free = true;
			Processes[currIdx]->finish = i;
			Processes[currIdx]->turn = Processes[currIdx]->finish - Processes[currIdx]->arrival + 1;
			Processes[currIdx]->norm = (Processes[currIdx]->turn*1.0 / Processes[currIdx]->service)*1.0;
			Processes[currIdx]->finish++;
			// currIdx = -1;

		}

		}		
	// TRACE
	if(status == 0)
	{
		cout << "FB-1  ";
		for(int a = 0; a <= timespan; a++)
		{
			if(a>9)
			{
				cout << a%10 << " ";
			}
			else
			{
				cout << a << " ";
			}
		}
		cout << '\n';
		cout << "------------------------------------------------" << endl;
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << Processes[a]->name << "     |";

			for(int b = 0; b < timespan; b++)
			{
			cout << result[a][b] << "|";
			}
			cout << " " << endl;
		} 
		cout << "------------------------------------------------" << endl;
		cout << endl;
	}
	// STATS
	else if(status ==1)
	{
		cout << "FB-1" << endl;
		cout << "Process    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << "  " << Processes[a]->name << "  |";
		} 
		cout << endl;
		cout << "Arrival    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->arrival>9)
			{
			cout << " " << Processes[a]->arrival << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->arrival << "  |";
			}
		} 
		cout << endl;

		cout << "Service    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->service>9)
			{
			cout << " " << Processes[a]->service << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->service << "  |";
			}		} 
			cout << " Mean|" << endl;
		cout << "Finish     |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->finish>9)
			{
			cout << " " << Processes[a]->finish << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->finish << "  |";
			}		
			}
			cout << "-----|" << endl;
 
		float meanTurn = 0;
		cout << "Turnaround |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->turn>9)
			{
			cout << " " << Processes[a]->turn << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->turn << "  |";
			}
			meanTurn += Processes[a]->turn;	
		} 
		meanTurn = meanTurn/numberOfProcesses;
		printf("%.2f|\n", meanTurn);
		float normTurn = 0;
		cout << "NormTurn   |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			printf(" %.2f|", Processes[a]->norm);
			normTurn += Processes[a]->norm;
		} 
		printf(" %.2f|\n", normTurn/numberOfProcesses);
		cout << endl;


	}

}
void
FB2(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{
	int quantum;
	char result[numberOfProcesses][timespan];
	int quantumList[numberOfProcesses] = {0};
	int doneList[numberOfProcesses]={0};
	int queueTracker[numberOfProcesses]={0};
	bool cpu_free = true;
	bool pushed = false;
	int currIdx = -1;
	queue<int> RQ0;
	queue<int> RQ1;
	queue<int> RQ2;
	queue<int> RQ3;
	queue<int> RQ4;
	queue<int> RQ5;
	int queueStatus[6]={0};


	for(int a = 0; a < numberOfProcesses; a++)
			{
				for(int b = 0; b < timespan; b++)
				{
				result[a][b]=' ';
				}
			}

	for (int i = 0; i < timespan; i++)
	{
		// Check if new process arrives
		for (int j=0; j < numberOfProcesses; j++)
		{
			if(Processes[j]->arrival == i && pushed == false)
			{
				// Push process index in RQ that is suitable to its 
				// prioriry, RQ0 because it has just arrived.
				RQ0.push(j);
				queueStatus[0]++;
			}
			if(Processes[j]->arrival <= i && doneList[j] != 1 )
			{
				result[j][i] = '.';
			}
		}
		pushed = false;
		if (!RQ0.empty())
		{
			if(cpu_free)
			{
				currIdx=RQ0.front();
				RQ0.pop();
				queueStatus[0]--;
				cpu_free = false;
				quantum = 1;
			}
		}
		else if (!RQ1.empty() && RQ0.empty())
		{
			if(cpu_free)
			{
				currIdx=RQ1.front();
				RQ1.pop();
				queueStatus[1]--;
				cpu_free = false;
				quantum = 2;
			}
		}
		else if (!RQ2.empty() && RQ0.empty() && RQ1.empty())
		{
			if(cpu_free)
			{
				currIdx=RQ2.front();
				RQ2.pop();
				queueStatus[2]--;
				cpu_free = false;
				quantum = 4;

			}
		}
		else if (!RQ3.empty() && RQ0.empty() && RQ1.empty() && RQ2.empty())
		{
			if(cpu_free)
			{
				currIdx=RQ3.front();
				RQ3.pop();
				queueStatus[3]--;
				cpu_free = false;
				quantum = 8;

			}
		}
		else if (!RQ4.empty() && RQ0.empty() && RQ1.empty() && RQ2.empty() && RQ3.empty() )
		{
			if(cpu_free)
			{
				currIdx=RQ4.front();
				RQ4.pop();
				queueStatus[4]--;
				cpu_free = false;
				quantum = 16;

			}
		}
		else if (!RQ5.empty() && RQ0.empty() && RQ1.empty() && RQ2.empty() && RQ3.empty() && RQ4.empty() )
		{
			if(cpu_free)
			{
				currIdx=RQ5.front();
				RQ5.pop();
				queueStatus[5]--;
				cpu_free = false;
				quantum = 32;

			}
		}
		

		if(!cpu_free && currIdx != -1)
		{

			if (quantumList[currIdx] != quantum) {
				Processes[currIdx]->tempService--;
				result[currIdx][i] = '*';
				quantumList[currIdx]++;
			}
			int waiting = 0;
			int count = 0;
			for (int j=0; j < numberOfProcesses; j++)
			{
				if(Processes[j]->arrival == i+1)
				{
					count++;
				}
			}	
			if (quantumList[currIdx] == quantum)
			{
				int sum  = 0;
				for (int i=0;i<6;i++)
				{
					sum+=queueStatus[i];
				}
				if (Processes[currIdx]->tempService != 0 && queueStatus[queueTracker[currIdx]]-sum == 0 && count==0)
				{
					queueTracker[currIdx]--;
				}
				
				// Preemption and Sending to another Queue
				queueTracker[currIdx]++;
				if(Processes[currIdx]->tempService != 0)
				{
					switch(queueTracker[currIdx])
					{
						case 0:
							RQ0.push(currIdx);
							break;
						case 1:
							RQ1.push(currIdx);
							break;
						case 2:
							RQ2.push(currIdx);
							break;
						case 3:
							RQ3.push(currIdx);
							break;
						case 4:
							RQ4.push(currIdx);
							break;
						case 5:
							RQ5.push(currIdx);
							break;
					}
				
				queueStatus[queueTracker[currIdx]]++;
				quantumList[currIdx] = 0;
				cpu_free = true;
			}	
			}
		}
		if (Processes[currIdx]->tempService == 0)
		{
			doneList[currIdx] = 1;
			cpu_free = true;
			Processes[currIdx]->finish = i;
			Processes[currIdx]->turn = Processes[currIdx]->finish - Processes[currIdx]->arrival + 1;
			Processes[currIdx]->norm = (Processes[currIdx]->turn*1.00 / Processes[currIdx]->service*1.00);
			Processes[currIdx]->finish++;
			// currIdx = -1;
		}

		}		
		
	
	
	// TRACE
	if(status == 0)
	{
		cout << "FB-2i ";
		for(int a = 0; a <= timespan; a++)
		{
			if(a>9)
			{
				cout << a%10 << " ";
			}
			else
			{
				cout << a << " ";
			}
		}
		cout << '\n';
		cout << "------------------------------------------------" << endl;
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << Processes[a]->name << "     |";

			for(int b = 0; b < timespan; b++)
			{
			cout << result[a][b] << "|";
			}
			cout <<" "<< endl;
		} 
		cout << "------------------------------------------------" << endl << endl;
	}
	// STATS
	else if(status ==1)
	{
		cout << "FB-2i" << endl;
		cout << "Process    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << "  " << Processes[a]->name << "  |";
		} 
		cout << endl;
		cout << "Arrival    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->arrival>9)
			{
			cout << " " << Processes[a]->arrival << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->arrival << "  |";
			}
		} 
		cout << endl;

		cout << "Service    |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->service>9)
			{
			cout << " " << Processes[a]->service << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->service << "  |";
			}		} 
			cout << " Mean|" << endl;
		cout << "Finish     |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->finish>9)
			{
			cout << " " << Processes[a]->finish << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->finish << "  |";
			}		
			}
			cout << "-----|" << endl;
 
		float meanTurn = 0;
		cout << "Turnaround |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			if (Processes[a]->turn>9)
			{
			cout << " " << Processes[a]->turn << "  |";
			}
			else
			{			
			cout << "  " << Processes[a]->turn << "  |";
			}
			meanTurn += Processes[a]->turn;	
		} 
		meanTurn = meanTurn/numberOfProcesses;
		printf("%.2f|\n", meanTurn);
		float normTurn = 0;
		cout << "NormTurn   |";
		for(int a = 0; a < numberOfProcesses; a++)
		{
			printf(" %.2f|", Processes[a]->norm);
			normTurn += Processes[a]->norm;
		} 
		printf(" %.2f|\n", normTurn/numberOfProcesses);
		cout << endl;
	}
	
}
void
AGING(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses, int quantum)
{
	// Initialize array for each process
	char result[numberOfProcesses][timespan];
	int current_quantum = quantum;
	for(int a = 0; a < numberOfProcesses; a++){
				for(int b = 0; b < timespan; b++)
				{
				result[a][b]=' ';
				}
	}
	priority_queue<Triple, vector<Triple>, myComp3> readyQueue;
	priority_queue<Triple, vector<Triple>, myComp3> readyQueue_new;
	priority_queue<Triple, vector<Triple>, myComp3> emptyQueue;	
	// priority_queue<pair<int, int>> readyQueue;
	bool cpu_free = true;
	int currIdx = -1;
	for (int i = 0; i < timespan; i++)
	{
		// cout << "I = " << i << endl;
		// Check if new process arrives
		for (int j=0; j < numberOfProcesses; j++)
		{
			if(Processes[j]->arrival == i)
			{
				// Push process service time in ready Queue
				Triple t;
				t.a = Processes[j]->priority;
				t.b = 0;
				t.c = j;
				readyQueue.push(t);
			}
			if(Processes[j]->arrival <= i)
			{
				result[j][i] = '.';

			}
		}
		if(current_quantum <= 0)
		{
			while(!readyQueue.empty())
			{
				Triple top = readyQueue.top();
				top.a = top.a + 1;
				int l = top.c;
				top.b = top.b + 1;
				readyQueue.pop();
				readyQueue_new.push(top);
			}
			readyQueue = readyQueue_new;
			readyQueue_new = emptyQueue;
			cpu_free = true;
			Triple t;
			t.a = Processes[currIdx]->priority;
			t.b = 0;
			t.c = currIdx;
			readyQueue.push(t);

		}
		if (!readyQueue.empty() && cpu_free)
		{
			Triple top = readyQueue.top();
			currIdx = top.c;
			readyQueue.pop();
			cpu_free = false;
			current_quantum = quantum;
		}
		if(!cpu_free && currIdx != -1)
		{
			result[currIdx][i] = '*';
			current_quantum--;
		}
		// if(currIdx != -1) cout << Processes[currIdx]->priority << " 0 " << currIdx << " "<< endl;
		// utility(readyQueue);
	}
			// TRACE
	if(status == 0)
	{
		cout << "Aging ";
		for(int a = 0; a <= timespan; a++)
		{
			if(a>9)
			{
				cout << a%10 << " ";
			}
			else
			{
				cout << a << " ";
			}
		}
		cout << '\n';
		cout << "------------------------------------------------" << endl;
		for(int a = 0; a < numberOfProcesses; a++)
		{
			cout << Processes[a]->name << "     |";

			for(int b = 0; b < timespan; b++)
			{
			cout << result[a][b] << "|";
			}
			cout << " " << endl;
		} 
		cout << "------------------------------------------------" << endl;
		cout << endl;
	}
	
}


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

SimpleScheduler::SimpleScheduler()
{

}

void
SimpleScheduler::execute(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses)
{
	switch(policy_id)
	{
		case 1:
			FCFS(status,timespan,Processes,numberOfProcesses);
			break;
		case 2:
			RR(status, timespan, Processes, numberOfProcesses, quantum);
			break;
		case 3:
			SPN(status, timespan, Processes, numberOfProcesses);
			break;
		case 4:
			SRT(status, timespan, Processes, numberOfProcesses);
			break;
		case 5:
			HRRN(status, timespan, Processes, numberOfProcesses);
			break;
		case 6:
			FB1(status, timespan, Processes, numberOfProcesses);
			break;
		case 7:
			FB2(status, timespan, Processes, numberOfProcesses);
			break;
		case 8:
			AGING(status, timespan, Processes, numberOfProcesses, quantum);
			break;
	}
}

Process::Process()
{
	priority = 0;
}


Scheduler* S = new Scheduler;

vector<string> parseInput()
{

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
		Process *P = new Process;
		P->preempted=false;
		P->name=parsed[0].c_str()[0] ;
		P->arrival=stoi(parsed[1]);
		P->service=stoi(parsed[2]);
		P->tempService=stoi(parsed[2]);
		P->priority=stoi(parsed[2]);
		P->tempPriority=stoi(parsed[2]);
		if (parsed.size() == 4)
		{
			P->priority = stoi(parsed[3]);
		}
		S->insertProcess(P);
	}
return processes;
}


int 
main()
{
	vector <string> processes = parseInput();

	for(int i = 0; i < S->numberSimpleSchedulers; i++)
	{
		S->listSimpleSchedulers[i]->execute(S->status, S->timespan, S->listProcesses, S->numberOfProcesses);	
		S->listProcesses.clear();
		for (int i = 0; i < S->numberOfProcesses; i++ )
	{
		string policy = processes[i];
		regex reg("[, ]+");
    	sregex_token_iterator iter(policy.begin(), policy.end(), reg, -1);
    	sregex_token_iterator end;
    	vector<string> parsed(iter, end);
		Process *P = new Process;
		P->preempted=false;
		P->name=parsed[0].c_str()[0] ;
		P->arrival=stoi(parsed[1]);
		P->service=stoi(parsed[2]);
		P->tempService=stoi(parsed[2]);
		if (parsed.size() == 4)
		{
			P->priority = stoi(parsed[3]);
		}
		S->insertProcess(P);
	}

	}
		
	return 0;
}

