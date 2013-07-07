#include "node.h"
#include <string>

#include <iostream>

using namespace zerkms;

Node::Node()
    :
    color(BLACK), left(0), right(0), isNil(false)
{
    std::cout << "Construct no name" << std::endl;
}

Node::Node(const std::string &data)
    :
    color(BLACK), key(data), left(0), right(0), isNil(false)
{
    std::cout << "Construct " << data << std::endl;
}

Node::~Node()
{
    if (!key.length()) {
        std::cout << "Destruct no name" << std::endl;
    } else {
        std::cout << "Destruct " << key << '.' << std::endl;
    }
}