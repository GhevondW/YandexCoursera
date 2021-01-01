#ifndef _STRING_DECORATOR_H_
#define _STRING_DECORATOR_H_

#include <string>
#include <iostream>
#include <memory>
#include <utility>

#define EncDecorator std::unique_ptr<ReadingDecorator>(new EncryptionDecorator{})
#define OthDecorator std::unique_ptr<ReadingDecorator>(new OtherDecorator{})

class IStringReader
{
public:
    virtual ~IStringReader() = default;
	virtual std::string Read() = 0;
    virtual IStringReader& operator<<(std::unique_ptr<IStringReader>&& next){ return *this; }
};

class IStringWriter
{
public:
    virtual ~IStringWriter() = default;   
	virtual void Write(const std::string& data) = 0;
};

class StringReader: public IStringReader
{
public:
	StringReader(const std::string& path):_path(path)  {}
	~StringReader() 
    {
        std::cout<<"~StringReader"<<std::endl;
    }

	std::string Read() override {
		return "[" + _path + "]";
	}

private:
	std::string _path;
};

class ReadingDecorator: public IStringReader
{
public:
	ReadingDecorator() = default;
	ReadingDecorator(std::unique_ptr<IStringReader>&& next)
		:_pNext(std::move(next))
	{}
	virtual ~ReadingDecorator() {
        std::cout<<"~ReadingDecorator"<<std::endl;
	}

	std::string Read() override {
		if (_pNext != nullptr)
		{
			return _pNext->Read();
		}
		throw "invalid operation";
	}

    IStringReader& operator<<(std::unique_ptr<IStringReader>&& next) override
    {
        _pNext = std::move(next);
        return *_pNext;
    }

private:
	std::unique_ptr<IStringReader> _pNext{nullptr};
};

class EncryptionDecorator: public ReadingDecorator
{
public:
	EncryptionDecorator() = default;
	EncryptionDecorator(std::unique_ptr<IStringReader>&& next)
		:ReadingDecorator(std::move(next))
	{}
	~EncryptionDecorator() 
    {
        std::cout<<"~EncryptionDecorator"<<std::endl;
    }

	std::string Read() override {
		std::string data = ReadingDecorator::Read();
		std::string res = "(" + data + ")";
		return res;
	}

private:

};

class OtherDecorator : public ReadingDecorator
{
public:
    OtherDecorator() = default;
	OtherDecorator(std::unique_ptr<IStringReader>&& next)
		:ReadingDecorator(std::move(next))
	{}
	~OtherDecorator() {
        std::cout<<"~OtherDecorator"<<std::endl;
    }

	std::string Read() override {
		std::string data = ReadingDecorator::Read();
		std::string res = "{" + data + "}";
		return res;
	}

private:

};

#endif