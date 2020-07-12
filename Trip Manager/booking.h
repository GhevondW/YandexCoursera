//
//  booking.h
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 7/12/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//

#ifndef booking_h
#define booking_h

namespace RAII {

template<class Provider>
class Booking
{
public:
    Booking(Provider* provider, int count)
    :_provider(provider),
    _id(count)
    {}
    
    Booking(const Booking&) = delete;
    Booking& operator=(const Booking&) = delete;
    Booking(Booking&& other)
    :_provider(other._provider),
    _id(other._id)
    {
        other._provider = nullptr;
    }
    
    Booking& operator=(Booking&& other)
    {
        this->_provider = other._provider;
        this->_id = other._id;
        other._provider = nullptr;
    }
    
    ~Booking(){
        if(_provider != nullptr){
            _provider->CancelOrComplete(*this);
        }
    }
    
    
private:
    Provider* _provider{nullptr};
    int _id{};
};

};

#endif /* booking_h */

