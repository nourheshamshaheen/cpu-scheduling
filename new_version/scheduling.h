#ifndef scheduling_h
#define scheduling_h
#include <vector>


struct Triple{
    int a;
    int b;
    int c;
    Triple();
};
struct Process{
    char name;
    int arrival;
    int service;
    int tempService;
    float rspR;
    bool preempted;
    int finish;
    float norm;
    int turn;
    int priority;
    int tempPriority;
    Process();
    std::vector<char> listVisualization;
};


struct SimpleScheduler{
    // std::vector<Process*> listProcesses;
    int policy_id;
    int quantum;
    SimpleScheduler();
    void execute(bool status, int timespan, std::vector<Process*> Processes,int numberOfProcesses); // Make a copy of listProcesses First
    void print();
};


struct Scheduler{
    int numberSimpleSchedulers;
    std::vector<SimpleScheduler*> listSimpleSchedulers;
    bool status;
    int timespan;
    Scheduler();
    void insertSimpleScheduler(SimpleScheduler* simpleScheduler);
    //static Scheduler currentScheduler;
    int numberOfProcesses;
    std::vector<Process*> listProcesses;
    void insertProcess(Process* process);
    void print();
};





#endif