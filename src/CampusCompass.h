#pragma once
#include <string>
#include "Graph.h"
#include "Student.h"
#include "ClassInfo.h"

using namespace std;

class CampusCompass {
private:
    Graph graph_;
    std::unordered_map<std::string, Student> students_;
    std::unordered_map<std::string, ClassInfo> classes_;


    // Think about what member variables you need to initialize
    // perhaps some graph representation?
public:
    // Think about what helper functions you will need in the algorithm
    CampusCompass(); // constructor
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool ParseCommand(const string &command);
};
