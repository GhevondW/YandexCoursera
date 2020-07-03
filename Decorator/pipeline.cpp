#if 0
#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

using namespace std;


struct Email {
    string from;
    string to;
    string body;
};


class Worker {
public:
    virtual ~Worker() = default;
    virtual void Process(unique_ptr<Email> email) = 0;
    virtual void Run() {
      // только первому worker-у в пайплайне нужно это имплементировать
      throw logic_error("Unimplemented");
    }

protected:
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const
    {
        if(_pNext.get() != nullptr){
            _pNext->Process(move(email));
        }
    }

public:
    void SetNext(unique_ptr<Worker> next)
    {
        if(_pNext.get() == nullptr){
            _pNext = move(next);
        }
        else{
            _pNext->SetNext(move(next));
        }
    }

protected:
    unique_ptr<Worker> _pNext{nullptr};
};


class Reader : public Worker {
public:
    Reader(istream& in):_in(in){}
    ~Reader(){}

    virtual void Process(unique_ptr<Email> email) override
    {
        
    }

    virtual void Run() override
    {
        while (true) {
            Email email;
            if(!std::getline(_in, email.from)) return;
            if(!std::getline(_in, email.to)) return;
            if(!std::getline(_in, email.body)) return;
            Worker::PassOn(make_unique<Email>(email));
        }
    }

private:
    istream& _in;
};


class Filter : public Worker {
public:
    using Function = function<bool(const Email&)>;
    Filter(Function pred)
    :_fPredicate(pred)
    {}
public:
    
    virtual void Process(unique_ptr<Email> email) override
    {
        if(_fPredicate(*email)){
            Worker::PassOn(std::move(email));
        }
    }
    
private:
    Function _fPredicate;
};


class Copier : public Worker {
public:
  
    Copier(std::string to)
    :_to(to)
    {}
    
    virtual void Process(unique_ptr<Email> email) override
    {
        Email tmp = *email;
        Worker::PassOn(move(email));
        if(tmp.to != _to){
            tmp.to = _to;
            Worker::PassOn(make_unique<Email>(tmp));
        }
    }
    
private:
    std::string _to;
};


class Sender : public Worker {
public:
    Sender(ostream& out)
    :_out(out)
    {}
    
    virtual void Process(unique_ptr<Email> email) override
    {
        _out<<email->from<<endl;
        _out<<email->to<<endl;
        _out<<email->body<<endl;
        Worker::PassOn(move(email));
    }
    
private:
    ostream& _out;
};


// реализуйте класс
class PipelineBuilder {
public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream& in)
    {
        _worker = std::make_unique<Reader>(in);
    }
    
    ~PipelineBuilder() = default;

    // добавляет новый обработчик Filter
    PipelineBuilder& FilterBy(Filter::Function filter)
    {
        _worker->SetNext(std::make_unique<Filter>(filter));
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder& CopyTo(string recipient)
    {
        _worker->SetNext(std::make_unique<Copier>(recipient));
        return *this;
    }

    // добавляет новый обработчик Sender
    PipelineBuilder& Send(ostream& out)
    {
        _worker->SetNext(std::make_unique<Sender>(out));
        return *this;
    }

    // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build()
    {
        return move(_worker);
    }
    
private:
    //Worker* _worker = nullptr;
    std::unique_ptr<Worker> _worker;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );
    
  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
    
  return 0;
}
#endif
