#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <iostream>
#include <string>

class Database
{
private:
    std::string _connection{false};
    bool _isConnected{false};
public:

    ~Database() = default;

    bool Connect(const std::string& connection)
    {
        _isConnected = true;
        _connection = connection;
        std::cout << "connected" << std::endl;
        return _isConnected;
    }

    bool Query(const std::string& sql) const
    {
        std::cout << sql << std::endl;
        return true;
    }

    void PrintConnectionString() const
    {
        if(_isConnected){
            std::cout<<"Connection String : "<<_connection<<std::endl;
        }
        else{
            std::cout<<"No connection"<<std::endl;
        }
    }

    static Database& Get()
    {
        /***
         * 
         * Version #1
         * 
         ***/
        //always initing db object
        // return database;

        /***
         * 
         * Version #2
         * 
         ***/
        //Lazy initialization
        static Database database;
        return database;
    }

private:
    Database()
    {
        std::cout<<"Database Ctor"<<std::endl;
    }

        /***
         * 
         * Version #1
         * 
         ***/

    //always initing db object
    // static Database database;
};
//always initing db object
// Database Database::database = Database{};

#endif