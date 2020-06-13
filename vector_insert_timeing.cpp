//
//  vector_insert_timeing.cpp
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 5/14/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//
#if 0
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "profile.h"

std::vector<std::string> GenerateBigVector()
{
    std::vector<std::string> result;
    result.clear();
    result.reserve(20000);
    for (int i = 19999; i >= 0; --i) {
        result.emplace_back(std::to_string(i));
    }
    return result;
}

int main(){
    
    auto begin = std::chrono::high_resolution_clock::now();
    
    std::cout<<GenerateBigVector().size()<<std::endl;
    
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout<<"Result:"<<std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()<<std::endl;
    
    return 0;
}
#endif
