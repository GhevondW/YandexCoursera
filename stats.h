#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
using namespace std;

class Stats {
public:
    Stats();

public:
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int>& GetMethodStats() const;
    const map<string_view, int>& GetUriStats() const;
    
private:
    std::map<string_view, int> _methods;
    std::map<string_view, int> _uris;
};

HttpRequest ParseRequest(string_view line);
