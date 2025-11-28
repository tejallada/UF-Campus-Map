#pragma once

#include <string>
#include <unordered_set>

struct Student {
    std::string name;
    std::string id;
    int residence_location_id;
    std::unordered_set<std::string> class_codes;
};
