#if 0
//
//  string_view_test.cpp
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 5/29/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <array>

int main(){
    
    std::array<char, 10> str;
    str.fill('d');
    
    std::string_view sv(&str[0], str.size());
    
    std::cout<<sv<<std::endl;
    
    size_t a = sv.npos;
    
    std::cout<<(a)<<std::endl;
    
    auto space  = a;
    
    auto res = sv.substr(1, space - 1);

    std::cout<<res<<std::endl;
    
    return 0;
}
#endif
