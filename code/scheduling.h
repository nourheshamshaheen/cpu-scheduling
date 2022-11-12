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
    Process();
    std::vector<char> listVisualization;
};


struct SimpleScheduler{
    int policy_id;
    int quantum;
    SimpleScheduler();
    void execute(); // Make a copy of listProcesses
    void print();
};


struct Scheduler{
    int numberSimpleSchedulers;
    std::vector<SimpleScheduler> listSimpleSchedulers;
    bool flag;
    int timespan;
    Scheduler();
    void insertSimpleScheduler(SimpleScheduler simpleScheduler);
    static Scheduler currentScheduler;
    std::vector<Process> listProcesses;
    void insertProcess(Process process);
};





#endif