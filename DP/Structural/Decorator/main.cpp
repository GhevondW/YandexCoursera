#include <iostream>
#include <string>
#include <memory>
#include "StringDecorator.h"
using namespace std;

int main()
{

	std::cout << "---Hello Decorator---" << std::endl;

	std::unique_ptr<IStringReader> stringReader{new StringReader("C://Files//Files")};
	
	// std::unique_ptr<ReadingDecorator> decorator{new ReadingDecorator
    // (
    //     std::unique_ptr<ReadingDecorator>{new EncryptionDecorator
    //     {
    //         std::unique_ptr<ReadingDecorator>{new EncryptionDecorator
    //         {
    //             std::unique_ptr<ReadingDecorator>{new OtherDecorator
    //             {
    //                 std::unique_ptr<ReadingDecorator>{new EncryptionDecorator
    //                 {
    //                     std::unique_ptr<ReadingDecorator>{new OtherDecorator
    //                     {
    //                         std::unique_ptr<ReadingDecorator>{new OtherDecorator
    //                         {
    //                             std::move(stringReader)
    //                         }}
    //                     }}
    //                 }}
    //             }}
    //         }}
    //     }}
    // )};

    ReadingDecorator decorator;

    decorator 
    << EncDecorator 
    << OthDecorator 
    << EncDecorator 
    << OthDecorator 
    << EncDecorator 
    << OthDecorator 
    << EncDecorator 
    << OthDecorator 
    << EncDecorator 
    << std::move(stringReader);

    cout<<decorator.Read()<<endl;

	return 0;
}