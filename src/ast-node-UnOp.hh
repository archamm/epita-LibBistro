//
//  ast-node-UnOp.h
//  epita-LibBistro
//
//  Created by Matthieu Archambault on 26/01/2019.
//  Copyright © 2019 Matthieu Archambault. All rights reserved.
//

#pragma once

#include "ast-node.hh"
#include "ast-factory.hh"

namespace bistro
{
    template <typename BigNum, typename Base>
    class UnOpNode: public ASTNode <BigNum, Base>
    {
    public:

        /// The BigNum class used to represent the numbers.
        using bignum_t = BigNum;

        /// The Base class.
        using base_t = Base;

        /// Shared_ptr to a BigNum.
        using num_t = std::shared_ptr<BigNum>;

        using self_t = UnOpNode;

        /// Type of a node in the AST.
        /// Keep in mind you should be able to add/delete those.
        using node_t = std::shared_ptr<ASTNode<BigNum, Base>>;

        UnOpNode(const node_t node, OpType op)
            :node_(node)
            ,op_(op)
        {
        }
        /// Print the tree in infix notation, e.g. "(2+3)".

        std::ostream&
        print_infix(std::ostream& out, const base_t& b) const override
        {
            if (op_ == OpType::MINUS)
                out << '-';
            node_->print_infix(out, b);
            return out;
        }

        /// Print the tree in polish notation, e.g. "+ 2 3".
        std::ostream&
        print_pol(std::ostream& out, const base_t& b) const override
        {
            if (op_ == OpType::MINUS)
                out << '-';
            node_->print_pol(out, b);
            return out;

        }

        /// Print the tree in reverse polish notation, e.g. "2 3 +".
        std::ostream&
        print_rpol(std::ostream& out, const base_t& b) const override
        {
            node_->print_rpol(out, b);
            if (op_ == OpType::MINUS)
                out << '-';
            return out;

        }

        /// Evaluate the tree and return a shared_pointer to the result.
        virtual num_t eval() const override
        {
            return node_->eval();
        }
    private:
        node_t node_;
        OpType op_;
    };

}

