#include <iostream>
#include <string>
using namespace std;



class IStringReader
{
public:
    virtual ~IStringReader() = default;
	virtual std::string Read() = 0;
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
        cout<<"~StringReader"<<endl;
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
	ReadingDecorator(IStringReader* pnext = nullptr)
		:_pNext(pnext)
	{}
	virtual ~ReadingDecorator() {
        cout<<"~ReadingDecorator"<<endl;
		if (_pNext != nullptr) {
			delete _pNext;
			_pNext = nullptr;
		}
	}

	std::string Read() override {
		if (_pNext != nullptr)
		{
			return _pNext->Read();
		}
		throw "invalid operation";
	}

private:
	IStringReader* _pNext{nullptr};
};

class EncryptionDecorator: public ReadingDecorator
{
public:
	EncryptionDecorator(IStringReader* pnext = nullptr)
		:ReadingDecorator(pnext)
	{}
	~EncryptionDecorator() 
    {
        cout<<"~EncryptionDecorator"<<endl;
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
	OtherDecorator(IStringReader* pnext = nullptr)
		:ReadingDecorator(pnext)
	{}
	~OtherDecorator() {
        cout<<"~OtherDecorator"<<endl;
    }

	std::string Read() override {
		std::string data = ReadingDecorator::Read();
		std::string res = "{" + data + "}";
		return res;
	}

private:

};
int main()
{

	std::cout << "---Hello Decorator---" << std::endl;

	StringReader* stringReader = new StringReader("C://Files//Files");
	
	ReadingDecorator* decorate = new ReadingDecorator
	{
		new EncryptionDecorator
		{
			new EncryptionDecorator
			{
				new OtherDecorator
				{
					new EncryptionDecorator
					{
						new OtherDecorator
						{
							stringReader
						}
					}
				}
			}
		}
	};

    cout<<decorate->Read()<<endl;

	delete decorate;
	return 0;
}