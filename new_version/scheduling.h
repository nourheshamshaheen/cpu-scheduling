#ifndef scheduling_h
#define scheduling_h
#include <vector>

struct Process{
    char name;
    int arrival;
    int service;
    int finish;
    int norm;
    int turn;
    int priority;
    Process();
    std::vector<char> listVisualization;
};


struct SimpleScheduler{
    int policy_id;
    int quantum;
    SimpleScheduler();
    void execute(); // Make a copy of listProcesses First
    void print();
};


struct Scheduler{
    int numberSimpleSchedulers;
    std::vector<SimpleScheduler> listSimpleSchedulers;
    int status;
    int timespan;
    Scheduler();
    void insertSimpleScheduler(SimpleScheduler * simpleScheduler);
    static Scheduler currentScheduler;
    int numberOfProcesses;
    std::vector<Process> listProcesses;
    void insertProcess(Process process);
    void print();
};





#endif