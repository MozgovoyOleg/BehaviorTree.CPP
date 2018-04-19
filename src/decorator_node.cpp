/* Copyright (C) 2015-2017 Michele Colledanchise - All Rights Reserved
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
*   to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
*   and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include "behavior_tree_core/decorator_node.h"
#include <string>
#include <vector>

BT::DecoratorNode::DecoratorNode(std::string name) :
    TreeNode::TreeNode(name),
    child_node_(nullptr),
    child_state_(BT::IDLE)
{
    // TODO(...) In case it is desired to set to idle remove the ReturnStatus
    // type in order to set the member variable
    // ReturnStatus child_i_status_ = BT::IDLE;  // commented out as unused
}

void BT::DecoratorNode::AddChild(TreeNode* child)
{
    if (child_node_ )
    {
        throw BehaviorTreeException("Decorator '" + Name() + "' has already a child assigned");
    }

    child_node_  = child;
    child_state_ = BT::IDLE;
}


void BT::DecoratorNode::Halt()
{
    DEBUG_STDOUT("HALTING: "<< Name());
    HaltChild();
    SetStatus(BT::HALTED);
}

const BT::TreeNode* BT::DecoratorNode::Child() const
{
    return child_node_;
}

void BT::DecoratorNode::HaltChild()
{
    if (child_node_->Status() == BT::RUNNING)
    {
        DEBUG_STDOUT("SENDING HALT TO CHILD " << child_node_->Name());
        child_node_->Halt();
    }
    else{
        DEBUG_STDOUT("NO NEED TO HALT " << child_node_->Name()
                     << "STATUS" << child_node_->Status());
    }
}

