#ifndef _STREAM_H_
#define _STREAM_H_

#include <string>
#include <iostream>

struct Stream
{
	virtual void Pass(std::string& value) = 0;
};

class StreamDecorator : public Stream
{
public:
	StreamDecorator(Stream* next) :_next(next) {}
	~StreamDecorator() = default;

	virtual void Pass(std::string& value) override
	{
		if (_next) {
			_next->Pass(value);
		}
	}

private:
	Stream* _next{nullptr};
};

class Encode : public StreamDecorator
{
public:
	Encode(Stream* next) :StreamDecorator(next) {}
	~Encode() = default;

	virtual void Pass(std::string& value) override
	{
		value += "E";
		StreamDecorator::Pass(value);
	}
};

class Decode : public StreamDecorator
{
public:
	Decode(Stream* next) :StreamDecorator(next) {}
	~Decode() = default;

	virtual void Pass(std::string& value) override
	{
		value += "D";
		StreamDecorator::Pass(value);
	}
};

class FinalizeStream : public Stream
{
public:
	FinalizeStream() = default;
	~FinalizeStream() = default;

	virtual void Pass(std::string& value) override
	{
		value += "F";
	}
private:
};

#endif // !_STREAM_H_

