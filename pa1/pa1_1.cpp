#include <iostream>
#include <math.h>
#include <time.h>
#include <tuple>
#include <vector>

void problemOne()
{
    srand(time(NULL));
    int k = 1000;               // Number of processes
    float lambda = 2;
    float t = 1;
    float arrvTime = 0, servTime = 0;
    float totalServTime = 0, totalArrvTime = 0;

    // List of process tuples
    std::vector<std::tuple<int, float, float>> procList;
    
    for (int i = 0; i < k; i++)
    {
        // Calculate z values, arrival, and service times

        // Based on Poisson Distribution
        arrvTime = -log(static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) / lambda;
        // Based on Exponential Distribution
        servTime = -log(static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * t;

        totalArrvTime += arrvTime;
        totalServTime += servTime;
        
        // Push processes to process list
        std::tuple<int, float, float> service = std::make_tuple ((i + 1), totalArrvTime, servTime);
        procList.push_back(service);
    }

    std::cout << std::endl << "====================================" << std::endl;
    std::cout << "Problem One" << std::endl;
    std::cout << "====================================" << std::endl << std::endl;
    std::cout << "<Service ID, Arrival Time, Service Time>" << std::endl;

    // Print list of processes
    for (size_t i = 0; i < procList.size(); i++)
    {
        std::cout << "< " << std::get<0>(procList[i]) << 
                     ", " << std::get<1>(procList[i]) << 
                     ", " << std::get<2>(procList[i]) << 
                     " >" << std::endl;
    }

    std::cout << std::endl << "-----" << std::endl;
    std::cout << "Expected Avg Arrival Time: " << 1 / lambda << std::endl;
    std::cout << "Actual Avg Arrival Time (s): " << totalArrvTime / k << std::endl;
    std::cout << "Expected Arrivals per Second: 2.00" << std::endl;
    std::cout << "Actual Avg Arrivals Per Second: " << 1 / (totalArrvTime / k) << std::endl;
    std::cout << "Expected Service Time (s): 1.00" << std::endl;
    std::cout << "Actual Avg Service Time (s): " << totalServTime / k << std::endl;
    std::cout << std::endl << "End Problem 1 Simulation" << std::endl;
    
}

int main()
{
    std::cout << std::endl << "3/10/2022" << std::endl;
    std::cout << "Programming Assignment 1" << std::endl;
    std::cout << "Ezekiel Quintanilla" << std::endl << std::endl;

    problemOne();
    
    return 0;
}