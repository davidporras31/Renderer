#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

class CSVLoader
{
public:
    CSVLoader(const std::string &filePath);
    void load();
    const std::vector<std::vector<std::string>> &getData() const
    {
        return data;
    }

private:
    std::string filePath;
    std::vector<std::vector<std::string>> data;
    std::vector<std::string> parseLine(const std::string &line);
};

CSVLoader::CSVLoader(const std::string &filePath) : filePath(filePath) {load();}

void CSVLoader::load()
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::string line;
    std::getline(file, line); // skip the first line (header)
    while (std::getline(file, line))
    {
        data.push_back(parseLine(line));
    }

    file.close();
}

std::vector<std::string> CSVLoader::parseLine(const std::string &line)
{
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    return tokens;
}

class CSVFile
{
private:
    std::string filePath;
    std::filesystem::file_time_type lastModifiedTime;
    CSVLoader *loader;

public:
    CSVFile(const std::string &path) : filePath(path), lastModifiedTime(std::filesystem::last_write_time(path)), loader(new CSVLoader(path)) {}
    ~CSVFile() { delete loader; }

    const std::vector<std::vector<std::string>> &getData() const
    {
        return loader->getData();
    }

    void update();
};

void CSVFile::update()
{
    auto currentModifiedTime = std::filesystem::last_write_time(filePath);
    if (currentModifiedTime <= lastModifiedTime)
    {
        return; // No update needed
    }
    delete loader;
    loader = new CSVLoader(filePath);
}

#endif // CSVLOADER_H