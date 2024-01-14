#ifndef BEHAVIOUR_TREE_SUCCEED_HPP
#define BEHAVIOUR_TREE_SUCCEED_HPP

#pragma once

#include "Leaf.hpp"

namespace behaviour_tree::node::leaf
{
    class Succeed : public Leaf
    {
    public:
        Succeed(const std::string& name) : Leaf(name) {}

        const LeafType type() const override { return LeafType::Succeed; }

        const Status run() override
        {
            return Status::SUCCESS;
        }
    };
}

#endif