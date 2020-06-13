#if 0
//
//  players.cpp
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 5/26/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//


#include <iostream>
#include <list>
#include <map>

//template<typename T>
//auto MyFind(const std::list<T>& c, const T& val)
//{
//    auto b = c.begin();
//    auto e = c.end();
//    while (b != e) {
//        if(*b == val){
//            return b;
//        }
//        ++b;
//    }
//    return e;
//}

int main(){
    
    int n{};
    std::cin>>n;
    std::list<int> players;
    std::map<int, std::list<int>::iterator> m;
    for (int i = 0; i < n; ++i) {
        int a{};
        int b{};
        std::cin>>a>>b;
        
        auto iter = m.find(b);
        
        if(iter != m.end()){
            m[a] = players.insert(iter->second, a);
        }
        else{
            m[a] = players.insert(end(players), a);
        }
    }
    
    for (auto a: players) {
        std::cout<<a<<std::endl;
    }
    
    return 0;
}
#endif
