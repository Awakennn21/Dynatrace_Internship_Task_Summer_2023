#include "Task.h"
#include <iostream>
#include <fstream>
#include <boost/date_time/gregorian/gregorian.hpp>

Task::Task(const std::string& filePath, int elementsCount)
    :m_Data(ParseFile(filePath)), m_OutputVectorSize(elementsCount) {}

nlohmann::json Task::ParseFile(const std::string& filePath)
{
    //Parse JSON file
    std::ifstream FileParser(filePath);
    nlohmann::json JsonData = nlohmann::json::parse(FileParser);
    // Erase form Json data every object that is not an operating system
    JsonData.erase(std::remove_if(JsonData.begin(), JsonData.end(), [](const nlohmann::json& obj) { return obj["os"] == false; }), JsonData.end()); 
    return JsonData;
}

uint32_t Task::CalculateDaysBetweenDates(const std::string& date1, const std::string& date2)
{
    auto Date1 = boost::gregorian::from_string(date1);
    auto Date2 = boost::gregorian::from_string(date2);
    return (Date2 - Date1).days();
}

void Task::PushIfBetterFound( std::vector<Task::OutputFormat>& vector, Task::OutputFormat&& value)
{
    if(vector.size() < m_OutputVectorSize)
    {
        vector.push_back(value);
        return;
    }

    for(int i = 0; i < vector.size(); i++)
    {
        if(vector[i].SupportedDays < value.SupportedDays)
        {
            //Insert value before the first os found with shorter period od support 
            vector.insert(vector.begin() + i, value);
            vector.pop_back();
            return;
        }
    }
}

std::vector<Task::OutputFormat> Task::GetEachOsSuportedDays()
{
    std::vector<OutputFormat> Result;
    for(const auto& obj : m_Data) 
    {        
        for(const nlohmann::json& version : obj["versions"])
        {
            //Check whether fileds, required as an output, exist in a json object
            if (version.contains("releaseDate") && version.contains("eol") && version.contains("cycle") && obj.contains("name")) 
            {
                PushIfBetterFound(Result, {obj["name"], version["cycle"], CalculateDaysBetweenDates(version["releaseDate"], version["eol"]) });
            }
        }
    }
    return Result;
}

void Task::PrintData(int count)
{
    std::vector<OutputFormat> OsData = GetEachOsSuportedDays();
    for(int i = 0; i < count; i++) 
    {
        std::cout<<OsData[i].Name<<" "<<OsData[i].Version<<" "<<OsData[i].SupportedDays<<std::endl;
    }
}