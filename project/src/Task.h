#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Task
{
public:
    Task(const std::string& filePath, int elementsCount);

    void PrintData(int count);

private:
    struct OutputFormat
    {
        std::string Name;
        std::string Version;
        uint32_t SupportedDays;
    };

    nlohmann::json m_Data;
    int m_OutputVectorSize;
private:
    nlohmann::json ParseFile(const std::string& filePath);

    uint32_t CalculateDaysBetweenDates(const std::string& date1, const std::string& date2);

    void PushIfBetterFound(std::vector<OutputFormat>& vector, OutputFormat&& value);

    std::vector<OutputFormat> GetEachOsSuportedDays();
};