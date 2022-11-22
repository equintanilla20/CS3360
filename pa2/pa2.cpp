#include <iostream>
#include <math.h>

#define ARR 1
#define DEP 0

struct Event {
    int type;
    double time;
    Event* next = 0;
};
class Simulation {
private:
    bool serverIdle;
    double timer;
    int readyQueueCount;
    Event* eq_head = 0;
    int lambda;
    double avgServiceTime;
    int finishedProc;
    int arrivalCount = 0;
    int departureCount = 0;
    static const int procLimit = 10000;
    double timeElapsedTotal;
    int waitingProcesses;

public:
    Simulation(int userLambda, double userServTime) {
        lambda = userLambda;
        avgServiceTime = userServTime;
    }

    void initialize() {
        timer = 0;
        serverIdle = true;
        readyQueueCount = 0;
        eq_head = 0;
        finishedProc = 0;
        waitingProcesses = 0;
        timeElapsedTotal = 0;

        double initialArrival = -log(static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) / lambda;
        scheduleEvent(ARR, timer + initialArrival);

    }

    void scheduleEvent(int eventType, double time) {
        Event* e = new Event;
        e->type = eventType;
        e->time = time;

        if (eventType) {
            arrivalCount++;
        } else {
            departureCount++;
        }

        // Sorted insertion
        Event* currPtr = eq_head;
        Event* prevPtr;

        if (!eq_head) {
            // First Case - Empty list, insert new node as only node.
            eq_head = e;
        } else if (currPtr->time >= e->time) {
            // Second Case - New node added to front of sorted list
            e->next = currPtr;
            eq_head = e;
        } else {
            // Third Case - Find proper location for new node in sorted list
            while ((currPtr != nullptr) && (e->time >= currPtr->time)) {
                prevPtr = currPtr;
                currPtr = currPtr->next;
            }
        
            prevPtr->next = e;
            e->next = currPtr;
        }
    }

    void run() {
        double oldTime = 0;
        double timeElapsed = 0;
        
        while (finishedProc < procLimit) {
            
            Event* e = eq_head;
            oldTime = timer;
            timer = e->time;
            timeElapsed = timer - oldTime;
            if (serverIdle) {
                timeElapsedTotal += timeElapsed;
            }
            waitingProcesses += readyQueueCount;
            switch(e->type) {
                case ARR:
                    arrHandler();
                    break;
                case DEP:
                    depHandler();
                    finishedProc++;
                    break;
            }
            
            if (eq_head != 0) {
                Event* removedEvent = eq_head;
                eq_head = eq_head->next;
                delete removedEvent;
            }
        }
    }

    void arrHandler() {
        double arrTime = -log(static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) / lambda;
        double servTime = -log(static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * avgServiceTime;

        if (serverIdle == true) {
            serverIdle = false;
            scheduleEvent(DEP, timer + servTime);
        } else {

            readyQueueCount++;
        }
        scheduleEvent(ARR, timer + arrTime);
    }

    void depHandler() {
        double servTime = -log(static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * avgServiceTime;

        if (readyQueueCount == 0) {
            serverIdle = true;
        } else {
            readyQueueCount--;
            scheduleEvent(DEP, timer + servTime);
        }
    }

    void report() {
        double avgWaitingProcs = (double)waitingProcesses / (double)procLimit;
        double avgTurnaroundTime = (avgWaitingProcs / (double)lambda) * avgServiceTime;
        double idleTime = timeElapsedTotal / timer;

        std::cout << "Average Turnaround Time: " << avgTurnaroundTime << " seconds" << std::endl;
        std::cout << "Total Throughput: " << (timer / procLimit) << " processes" << std::endl;
        std::cout << "Average CPU Utilization: " << (1 - idleTime)*100 << "%" << std::endl;
        std::cout << "Average Number of Processes in Ready Queue: " << avgWaitingProcs << std::endl;
        std::cout << std::endl;
    }
};
void greetUser();

int main(int argc, char* argv[]) {
    srand(time(NULL));
    if (argc != 3) return -1;
    int lambda = atof(argv[1]);
    double avgServiceTime = atof(argv[2]);
    greetUser();

    std::cout << "Initial Lambda: " << lambda << std::endl;
    std::cout << "Avg Service Time: " << avgServiceTime << std::endl << std::endl;
    
    for (int i = lambda; i < 31; i++) {
        Simulation testSim(i, avgServiceTime);
        std::cout << "==============" << std::endl;
        std::cout << "Simulation #" << (i-lambda+1) << std::endl;
        testSim.initialize();
        testSim.run();
        testSim.report();
    }
    
    return 0;
}

void greetUser() {
    std::cout << std::endl << "=====================================" << std::endl;
    std::cout << "==  DISCRETE TIME EVENT SIMULATOR  ==" << std::endl;
    std::cout << "=====================================" << std::endl << std::endl;
}