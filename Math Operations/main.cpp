#include "Common.h"
#include "test_runner.h"
#include <sstream>

using namespace std;

string Print(const Expression* e) {
  if (!e) {
    return "Null expression provided";
  }
  stringstream output;
  output << e->ToString() << " = " << e->Evaluate();
  return output.str();
}

namespace Expressions {
class Value : public Expression {
 public:

  explicit Value(int value) : _value(value) {}
  int Evaluate() const override {
    return _value;
  }

  string ToString() const override {
    return to_string(_value);
  }
 private:
  int _value;
};

class BinaryExpression : public Expression{
public:
    BinaryExpression(ExpressionPtr left, ExpressionPtr right)
    :_left(move(left)),
    _right(move(right)){}
    
    virtual ~BinaryExpression(){}
protected:
    ExpressionPtr _left;
    ExpressionPtr _right;
};

class Sum : public BinaryExpression {
 public:
  Sum(ExpressionPtr left, ExpressionPtr right)
    :BinaryExpression(move(left), move(right))
    {}
    
  int Evaluate() const override {
    return _left->Evaluate() + _right->Evaluate();
  }

  string ToString() const override {
    return "(" + _left->ToString() + ")+(" + _right->ToString() + ")";
  }
};

class Product : public BinaryExpression {
 public:
  Product(ExpressionPtr left, ExpressionPtr right)
    :BinaryExpression(move(left), move(right)){}
    
  int Evaluate() const override {
    return _left->Evaluate() * _right->Evaluate();
  }

  string ToString() const override {
    return "(" + _left->ToString() + ")*(" + _right->ToString() + ")";
  }
    
};
}

ExpressionPtr Value(int value) {
  return make_unique<Expressions::Value>(Expressions::Value(value));
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return unique_ptr<Expressions::Sum>{new Expressions::Sum(move(left), move(right))};
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return unique_ptr<Expressions::Product>{new Expressions::Product(move(left), move(right))};
}

void Test() {
  ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
  ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

  ExpressionPtr e2 = Sum(move(e1), Value(5));
  ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

  ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test);
  return 0;
}
