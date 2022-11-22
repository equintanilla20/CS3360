#include <iostream>
#include <math.h>
#include <time.h>

void problemTwoB()
{
    
    std::cout << "====================================" << std::endl;
    std::cout << "Problem Two, Part B" << std::endl;
    std::cout << "====================================" << std::endl << std::endl;
    
    srand(time(NULL));
    
    int MTBF = 500;                  // Mean Time Between Failures (Hours)
    int MTTR = 10;                   // Mean Time To Repair (Hours)

    bool totalSystemFailure = false;
    float totalSystemFailTime = 0, systemFailureTime;
    float failureTime1 = 0, failureTime2 = 0;
    int totalFailureCount = 0;

    // Simulation
    for (int i = 0; i < 1000; i++)
    {
        // Ensure variables reset every run of the sim
        systemFailureTime = 0;
        totalSystemFailure = false;

        // Find server 1 initial failure time
        failureTime1 = -log(static_cast<float>(rand()) / static_cast<float>(RAND_MAX))*MTBF;
        // Find server 2 initial failure time
        failureTime2 = -log(static_cast<float>(rand()) / static_cast<float>(RAND_MAX))*MTBF;

        while(!totalSystemFailure)
        {
            // Check if either server failed while the other was already down
            if ((failureTime2 <= failureTime1 && failureTime1 < failureTime2 + MTTR) || 
                (failureTime1 <= failureTime2 && failureTime2 < failureTime1 + MTTR)) 
            {
                totalSystemFailure = true;
                totalFailureCount++;
                // Which server did this specifically, save that time
                if (failureTime2 <= failureTime1 && failureTime1 < failureTime2+MTTR)
                    // Server 1 failed while Server 2 was down
                    systemFailureTime = failureTime1;
                else
                    // Server 2 failed while Server 1 was down
                    systemFailureTime = failureTime2;
            }
            else 
            {
                // Else see which server is behind in time, add another failure to that one + MTTR
                if (failureTime1 < failureTime2)
                {
                    failureTime1 += -log(static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * MTBF + MTTR;
                    failureTime2 += MTTR;
                }
                else
                {
                    failureTime1 += MTTR;
                    failureTime2 += -log(static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * MTBF + MTTR;
                }
            }
        }
        totalSystemFailTime += systemFailureTime;
    }

    std::cout << "------" << std::endl;
    std::cout << "Total Failure Count: " << totalFailureCount << std::endl;
    std::cout << "Total System Failure Time: " <<  totalSystemFailTime << " hours" << std::endl;
    std::cout << "Average failure time: " << totalSystemFailTime / totalFailureCount << " hours" << std::endl;
    std::cout << std::endl << "End Problem 2b Simulation" << std::endl;
}

int main()
{
    std::cout << std::endl << "3/10/2022" << std::endl;
    std::cout << "Programming Assignment 1" << std::endl;
    std::cout << "Ezekiel Quintanilla" << std::endl << std::endl;

    problemTwoB();
    
    return 0;
}