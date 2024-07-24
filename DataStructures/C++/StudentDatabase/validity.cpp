#include <iostream>
#include <string>
#include <cstdlib>
#include "Tree.h"
#include "TreeNode.h"
using namespace std;

int Tree::Valid() {

    int r;

    if (!root) {
        r = 1;
    }
    else {
        if (!root->getColor() || root->getparent()) {
            r = 0;
        }
        else {
            r = root->ValidNode() != -1;
        }
    }
    return r;
}

int TreeNode::ValidNode() {

    int lc, rc, r;

    if (!color && parent && !parent->getColor()) {
        r = -1;
    }
    else {
        if (left && left->getparent() != this) {
            r = -1;
        }
        else {
            if (left && left->getk() >= k) {
                r = -1;
            }
            else {
                if (right && right->getparent() != this) {
                    r = -1;
                }
                else {
                    if (right && right->getk() <= k) {
                        r = -1;
                    }
                    else {
                        if (left) {
                            lc = left->ValidNode();
                        }
                        else {
                            lc = 0;
                        }
                        if (lc == -1) {
                            r = -1;
                        }
                        else {
                            if (right) {
                                rc = right->ValidNode();
                            }
                            else {
                                rc = 0;
                            }
                            if (rc == -1) {
                                r = -1;
                            }
                            else {
                                if (lc != rc) {
                                    r = -1;
                                }
                                else {
                                    if (color) {
                                        r = lc + 1;
                                    }
                                    else {
                                        r = lc;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return r;
}