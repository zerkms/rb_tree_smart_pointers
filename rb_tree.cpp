#include "tree.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace zerkms;

void print(const Tree&);
void read(const std::string &input, std::vector<std::string> &output);

int main(int argc, char** argv)
{
    Tree tree;

    std::vector<std::string> data;

    read("dict.in", data);

    std::vector<std::string>::const_iterator it = data.begin(),
        ite = data.end();

    for (; it != ite; ++it) {
        tree.Insert(*it);
    }

    print(tree);

	return 0;
}

void read(const std::string &input, std::vector<std::string> &output)
{
    std::ifstream finput(input);
    if (!finput.is_open()) {
        throw "the input file is bad";
    }

    std::string tmp_string;

    while (std::getline(finput, tmp_string)) {
        output.push_back(tmp_string);
    }

    finput.close();
}

void printNode(const sNode node, size_t level = 0, char side = '^')
{
    std::string indentation(level * 2, ' ');

    std::cout << indentation << '(' << side << ") " << node->key;

    std::cout << '(' << (node->color == Node::RED ? "Red" : "Black") << ')' << std::endl;

    if (node->isNil) {
        return;
    }
    
    if (!node->left->isNil) {
        printNode(node->left, level + 1, 'L');
    }

    if (!node->right->isNil) {
        printNode(node->right, level + 1, 'R');
    }
}

void print(const Tree &tree)
{
    printNode(tree.GetRoot());
}