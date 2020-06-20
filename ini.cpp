#include "ini.h"
#include <iostream>

using namespace std;
using namespace Ini;

namespace Ini {

    Section& Document::AddSection(std::string name) {
          return sections[name];
    }
    const Section& Document::GetSection(const std::string& name) const {
          return sections.at(name);
    }
    std::size_t Ini::Document::SectionCount() const {
          return sections.size();
    }
    Document Load(std::istream& input) {
                Document doc;
                std::string line, name_section;
                while (std::getline(input, line)) {
                      if (line.empty()) {
                            continue;
                      }
                      if (line.front()=='[') {
                            name_section = line.substr(1, line.size() - 2);
                            doc.AddSection(name_section);
                      }
                      else {
                            std::size_t index = line.find('=');
                            doc.AddSection(name_section).insert( {line.substr(0, index), line.substr(index+1, std::string::npos)} );
                      }
                }
                return doc;
    }

}


