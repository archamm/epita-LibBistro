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
    class BinOpNode : public ASTNode <BigNum, Base>
    {
    public:
        
        /// The BigNum class used to represent the numbers.
        using bignum_t = BigNum;
        
        /// The Base class.
        using base_t = Base;
        
        /// Shared_ptr to a BigNum.
        using num_t = std::shared_ptr<BigNum>;
        
        using self_t = BinOpNode;
        
        using node_t = std::shared_ptr<ASTNode<BigNum, Base>>;

        BinOpNode(const node_t left, const node_t right, OpType op)
            :left_node_(left)
            ,right_node_(right)
            ,op_(op)
        {
        }
        /// Print the tree in infix notation, e.g. "(2+3)".
        std::ostream&
        print_infix(std::ostream& out, const base_t& b) const
        {
            std::cout << '(';
            right_node_->print_infix(out, b);
            if (op_ == OpType::MINUS)
                out << '-';
            if (op_ == OpType::PLUS)
                out << '+';
            if (op_ == OpType::DIVIDE)
                out << '/';
            if (op_ == OpType::TIMES)
                out << '*';
            right_node_->print_infix(out, b);
            std::cout << ')';

            return out;
            
        }
        
        /// Print the tree in polish notation, e.g. "+ 2 3".
        std::ostream&
        print_pol(std::ostream& out, const base_t& b) const
        {
            if (op_ == OpType::MINUS)
                out << '-';
            if (op_ == OpType::PLUS)
                out << '+';
            if (op_ == OpType::DIVIDE)
                out << '/';
            if (op_ == OpType::TIMES)
                out << '*';
            right_node_->print_pol(out, b);
            right_node_->print_pol(out, b);
            return out;
            
        }
        
        /// Print the tree in reverse polish notation, e.g. "2 3 +".
        std::ostream&
        print_rpol(std::ostream& out, const base_t& b) const
        {
            if (op_ == OpType::MINUS)
                out << '-';
            if (op_ == OpType::PLUS)
                out << '+';
            right_node_->print_pol(out, b);
            right_node_->print_pol(out, b);
            if (op_ == OpType::MINUS)
                out << '-';
            if (op_ == OpType::PLUS)
                out << '+';
            if (op_ == OpType::DIVIDE)
                out << '/';
            if (op_ == OpType::TIMES)
                out << '*';
            
            return out;
            
        }
        
        /// Evaluate the tree and return a shared_pointer to the result.
        num_t eval() const
        {
            auto right_eval = right_node_->eval();
            auto left_eval = left_node_->eval();
            return std::make_shared<BigNum>(*(left_eval.get()) + *(right_eval.get()));
        }
    private:
        
        node_t left_node_;
        node_t right_node_;
        OpType op_;
    };
    
};

