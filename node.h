#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <memory>

namespace zerkms {

class Node
{
public:
    Node();
    Node(const std::string &);
    ~Node();

    bool isNil;

    std::shared_ptr<Node> left, right;
    std::weak_ptr<Node> parent;

    enum Color
    {
        RED,
        BLACK
    };

    Color color;

    std::string key;

};

}

#endif