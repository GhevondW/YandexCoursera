//
//  profile.h
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 5/15/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//

#ifndef profile_h
#define profile_h

#include <chrono>
#include <iostream>
#include <string>



class LogDuration {
public:
  explicit LogDuration(const string& msg = "")
    : message(msg + ": ")
    , start(std::chrono::steady_clock::now())
  {
  }

  ~LogDuration() {
      auto finish = std::chrono::steady_clock::now();
    auto dur = finish - start;
    cerr << message
      << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
       << " ms" << endl;
  }
private:
  string message;
    std::chrono::steady_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
  LogDuration UNIQ_ID(__LINE__){message};

#endif /* profile_h */
