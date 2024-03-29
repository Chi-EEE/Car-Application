#ifndef BEHAVIOUR_TREE_LEAFTYPE_HPP
#define BEHAVIOUR_TREE_LEAFTYPE_HPP

#pragma once

namespace behaviour_tree::node::leaf
{
    enum class LeafType
    {
        Succeed,
        Fail,
        UseRoot,
    };
}

#endif