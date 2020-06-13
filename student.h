//
//  student.h
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 5/15/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//

#ifndef student_h
#define student_h

#include <map>
#include <string>

using namespace std;

struct Student {
  string first_name;
  string last_name;
  map<string, double> marks;
  double rating;

  bool operator < (const Student& other) const {
    return GetName() < other.GetName();
  }

  bool Less(const Student& other) const {
    return rating > other.rating;
  }

  string GetName() const {
    return first_name + " " + last_name;
  }
};

#endif /* student_h */
