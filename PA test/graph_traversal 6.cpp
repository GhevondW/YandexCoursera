#include <cstdint>
#include <cstdio>
#include <vector>

struct Node {
    std::vector<Node> children_;
    int id_;
    Node(int id, const std::vector<Node> &children) : children_(children), id_(id) {}
    
};


int main(int argc, const char * argv[]){
    /*
     Write a recursive method that will find any path in graph from source to destination with specific ID.
     
     std::vector<Node*> findPathWithId(const Node &root, int id);
     */
    
    
    auto root = Node(0, {
        Node(1, {
            Node(3, {
                Node(100, {
                    Node(300, {})
                }),
                Node(200, {
                    Node(400, {})
                })
            })
        }),
        Node(2, {
            Node(4, {}),
            Node(5, {}),
            Node(6, {}),
            Node(7, {}),
            Node(8, {}),
            Node(9, {}),
            Node(4456, {
                Node(1000, {
                    Node(3000, {
                        Node(100000, {
                            Node(300000, {})
                        }),
                        Node(20000, {
                            Node(400000, {})
                        })
                    })
                })
            }
                 
        ),
        })
    }
    );
    
    return 0;
}
