#include "stats.h"

using namespace std;


Stats::Stats()
:_methods(
{
    {"GET", 0},
    {"POST", 0},
    {"PUT", 0},
    {"DELETE", 0},
    {"UNKNOWN", 0}
}),
_uris(
{
    {"/", 0},
    {"/order", 0},
    {"/product", 0},
    {"/basket", 0},
    {"/help", 0},
    {"unknown", 0}
})
{}

void Stats::AddMethod(string_view method)
{
    if(_methods.count(method)){
        ++_methods[method];
    }
    else{
        ++_methods["UNKNOWN"];
    }
}

void Stats::AddUri(string_view uri)
{
    if(_uris.count(uri)){
        ++_uris[uri];
    }
    else{
        ++_uris["unknown"];
    }
}

const map<string_view, int>& Stats::GetMethodStats() const
{
    return _methods;
}

const map<string_view, int>& Stats::GetUriStats() const
{
    return _uris;
}
    
HttpRequest ParseRequest(string_view line)
{
    HttpRequest request;

    size_t pos = 0;
    while (line[pos] == ' ' && pos != line.npos) {
      ++pos;
    }
    
    line.remove_prefix(pos);

    size_t f = line.find(' ');
    request.method = line.substr(0, f);

    line.remove_prefix(++f);
    f = line.find(' ');
    request.uri = line.substr(0, f);

    line.remove_prefix(++f);
    request.protocol = line;

    return request;
}
