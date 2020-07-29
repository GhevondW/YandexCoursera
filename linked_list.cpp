#if 1
#include "test_runner.h"

#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node {
        T value;
        Node* next = nullptr;
    };

    LinkedList() = default;
    ~LinkedList()
    {
        Node* curr = head;
        while (curr != nullptr) {
            Node* then = curr->next;
            delete curr;
            curr = then;
        }
    }
    
    void PushFront(const T& value)
    {
        if(head == nullptr){
            head = new Node;
            head->value = value;
            return;
        }
        Node* tmp = new Node;
        tmp->value = value;
        tmp->next = head;
        head = tmp;
    }
    
    void InsertAfter(Node* node, const T& value)
    {
        if(node == nullptr)
        {
            PushFront(value);
        }
        else
        {
            Node* tmp = node->next;
            Node* new_node = new Node;
            new_node->value = value;
            new_node->next = tmp;
            node->next = new_node;
        }
    }
    
    void RemoveAfter(Node* node)
    {
        if(node == nullptr)
        {
            PopFront();
        }
        else
        {
            if(node->next != nullptr){
                Node* tmp = node->next->next;
                delete node->next;
                node->next = tmp;
            }
        }
    }
    
    void PopFront()
    {
        if(head != nullptr){
            Node* tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    Node* GetHead() { return head; }
    const Node* GetHead() const { return head; }

private:
    Node* head = nullptr;
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
  vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

void TestPushFront() {
  LinkedList<int> list;

  list.PushFront(1);
  ASSERT_EQUAL(list.GetHead()->value, 1);
  list.PushFront(2);
  ASSERT_EQUAL(list.GetHead()->value, 2);
  list.PushFront(3);
  ASSERT_EQUAL(list.GetHead()->value, 3);

  const vector<int> expected = {3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
  LinkedList<string> list;

  list.PushFront("a");
  auto head = list.GetHead();
  ASSERT(head);
  ASSERT_EQUAL(head->value, "a");

  list.InsertAfter(head, "b");
  const vector<string> expected1 = {"a", "b"};
  ASSERT_EQUAL(ToVector(list), expected1);

  list.InsertAfter(head, "c");
  const vector<string> expected2 = {"a", "c", "b"};
  ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
  LinkedList<int> list;
  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }

  const vector<int> expected = {5, 4, 3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);

  auto next_to_head = list.GetHead()->next;
  list.RemoveAfter(next_to_head); // ÑƒÐ´Ð°Ð»ÑÐµÐ¼ 3
  list.RemoveAfter(next_to_head); // ÑƒÐ´Ð°Ð»ÑÐµÐ¼ 2

  const vector<int> expected1 = {5, 4, 1};
  ASSERT_EQUAL(ToVector(list), expected1);

  while (list.GetHead()->next) {
    list.RemoveAfter(list.GetHead());
  }
  ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
  LinkedList<int> list;

  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }
  for (int i = 1; i <= 5; ++i) {
    list.PopFront();
  }
  ASSERT(list.GetHead() == nullptr);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPushFront);
  RUN_TEST(tr, TestInsertAfter);
  RUN_TEST(tr, TestRemoveAfter);
  RUN_TEST(tr, TestPopFront);
  return 0;
}
#endif
