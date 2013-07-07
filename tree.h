#ifndef TREE_H_
#define TREE_H_

#include <memory>
#include "node.h"

namespace zerkms {

typedef std::shared_ptr<Node> sNode;

class Tree
{
private:
    sNode nil_, root_;

public:
    Tree();
    ~Tree();

public:
    sNode GetRoot() const;
    sNode Insert(const std::string &);
    sNode Find(const std::string &) const;

private:
    void InsertFixup(sNode);
    void LeftRotate(sNode);
    void RightRotate(sNode);

    sNode Find(sNode const, const std::string &) const;

};

}

#endif