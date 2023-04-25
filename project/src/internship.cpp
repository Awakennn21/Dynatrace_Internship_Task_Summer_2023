#include <chrono>
#include <fstream>
#include <iostream>

#include <date/date.h>
#include <nlohmann/json.hpp>
#include "Task.h"
#include "internship.h"

using json = nlohmann::json;
using namespace date;

namespace internship {
    // do not remove this function
    void solution(const std::string& jsonFileName, int elementsCount) 
    {   
        Task Solution(jsonFileName, elementsCount);
        Solution.PrintData(elementsCount);
    }
}