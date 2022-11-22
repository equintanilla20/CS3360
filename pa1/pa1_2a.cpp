#include <iostream>
#include <math.h>
#include <time.h>

void problemTwoA()
{
    std::cout << "====================================" << std::endl;
    std::cout << "Problem Two, Part A" << std::endl;
    std::cout << "====================================" << std::endl << std::endl;
    srand(time(NULL));
    float totalRunTime = 175200;     // # Of Hours in 20 Years
    int MTBF = 500;                  // Mean Time Between Failures (Hours)
    int MTTR = 10;                   // Mean Time To Repair (Hours)

    // Variables for Servers 1 & 2
    float failure_time1 = 0, failure_time2 = 0;
    int numOfFailures1 = 0, numOfFailures2 = 0;
    float time1 = 0, time2 = 0;
    
    while (time1 <= totalRunTime || time2 <= totalRunTime)
    {
        // Server 1 Simulation
        if (time1 <= totalRunTime)
        {
            // Generate Failure Time, save for later
            failure_time1 = -log(static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * MTBF;
            std::cout << "Server 1 failure at hour " << time1 + failure_time1 << std::endl;
            std::cout << "Server 1 restored at hour " << time1 + failure_time1 + MTTR << std::endl << std::endl;
            numOfFailures1++;
            time1 += failure_time1 + MTTR;
        }

        // Server 2 Simulation
        if (time2 <= totalRunTime)
        {
            // Generate Failure Time, save for later
            failure_time2 = -log(static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * MTBF;
            std::cout << "Server 2 failure at hour " << time2 + failure_time2 << std::endl;
            std::cout << "Server 2 restored at hour " << time2 + failure_time2 + MTTR << std::endl << std::endl;
            numOfFailures2++;
            time2 += failure_time2 + MTTR;
        }
    }
    
    std::cout << "-----" << std::endl;
    std::cout << "Number of Server 1 failures: " << numOfFailures1 << std::endl;
    std::cout << "Number of Server 2 failures: " << numOfFailures2 << std::endl;
    std::cout << std::endl << "End Problem 2a Simulation" << std::endl;
}

int main()
{
    std::cout << std::endl << "3/10/2022" << std::endl;
    std::cout << "Programming Assignment 1" << std::endl;
    std::cout << "Ezekiel Quintanilla" << std::endl << std::endl;

    problemTwoA();
    
    return 0;
}