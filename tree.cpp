#include "tree.h"
#include "node.h"
#include <iostream>

using namespace zerkms;

Tree::Tree()
    :
    nil_(new Node("nil")), root_(nil_)
{
    std::cout << "Construct tree" << std::endl;

    nil_->isNil = true;
}

Tree::~Tree()
{
    std::cout << "Destruct tree" << std::endl;
}

sNode Tree::GetRoot() const
{
    return root_;
}

sNode Tree::Insert(const std::string &key)
{
    auto z = std::make_shared<Node>(key);

    auto y = nil_;
    auto x = root_;

    while (x != nil_) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == nil_) {
        root_ = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = nil_;
    z->right = nil_;
    z->color = Node::Color::RED;

    this->InsertFixup(z);

    return z;
}

sNode Tree::Find(const std::string &needle) const
{
    return Find(root_, needle);
}

sNode Tree::Find(sNode const node, const std::string &needle) const
{
    if (node->isNil || node->key == needle) {
        return node;
    }

    if (needle < node->key) {
        return Find(node->left, needle);
    }

    return Find(node->right, needle);
}

void Tree::InsertFixup(sNode z)
{
    std::shared_ptr<Node> y;

    while (true) {
        auto zp = z->parent.lock();

        if (zp->color != Node::Color::RED) {
            break;
        }

        auto zpp = zp->parent.lock();

        if (zp == zpp->left) {
            y = zpp->right;
            if (y->color == Node::Color::RED) {
                zp->color = Node::Color::BLACK;
                y->color = Node::Color::BLACK;
                zpp->color = Node::Color::RED;
                z = zpp;
            } else {
                if (z == zp->right) {
                    z = zp;
                    this->LeftRotate(z);
                }

                zp->color = Node::Color::BLACK;
                zpp->color = Node::Color::RED;
                this->RightRotate(zpp);
            
            }
        } else {
            y = zpp->left;
            if (y->color == Node::Color::RED) {
                zp->color = Node::Color::BLACK;
                y->color = Node::Color::BLACK;
                zpp->color = Node::Color::RED;
                z = zpp;
            } else {
                if (z == zp->left) {
                    z = zp;
                    this->RightRotate(z);
                } 

                zp->color = Node::Color::BLACK;
                zpp->color = Node::Color::RED;
                this->LeftRotate(zpp);
            }
        }
    }

    root_->color = Node::Color::BLACK;
}

void Tree::LeftRotate(sNode x)
{
    auto y = x->right;
    x->right = y->left;

    if (y->left != nil_) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    auto xp = x->parent.lock();

    if (xp == nil_) {
        root_ = y;
    } else if (x == xp->left) {
        xp->left = y;
    } else {
        xp->right = y;
    }

    y->left = x;
    x->parent = y;
}

void Tree::RightRotate(sNode x)
{
    auto y = x->left;
    x->left = y->right;

    if (y->right != nil_) {
        y->right->parent = x;
    }

    y->parent = x->parent;

    auto xp = x->parent.lock();

    if (xp == nil_) {
        root_ = y;
    } else if (x == xp->left) {
        xp->left = y;
    } else {
        xp->right = y;
    }

    y->right = x;
    x->parent = y;
}