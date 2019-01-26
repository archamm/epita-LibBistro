//
//  ast-node-Num.hh
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
    class NumberNode: public ASTNode <BigNum, Base>
    {
    public:
        
        /// The BigNum class used to represent the numbers.
        using bignum_t = BigNum;
        
        /// The Base class.
        using base_t = Base;
        
        /// Shared_ptr to a BigNum.
        using num_t = std::shared_ptr<BigNum>;
        
        using self_t = NumberNode;

        /// Type of a node in the AST.
        /// Keep in mind you should be able to add/delete those.
        using node_t = std::shared_ptr<ASTNode<BigNum, Base>>;

        NumberNode(const num_t num)
            : num_(num) 
        {
        }
        /// Print the tree in infix notation, e.g. "(2+3)".
        std::ostream&
        print_infix(std::ostream& out, const base_t& b) const override
        {
            num_->print(out, b);
            return out;
        }
        
        /// Print the tree in polish notation, e.g. "+ 2 3".
        std::ostream&
        print_pol(std::ostream& out, const base_t& b) const override
        {
            num_->print(out, b);
            return out;
    
        }
        
        /// Print the tree in reverse polish notation, e.g. "2 3 +".
        std::ostream&
        print_rpol(std::ostream& out, const base_t& b) const override
        {
            num_->print(out, b);
            return out;
        }
        
        /// Evaluate the tree and return a shared_pointer to the result.
        num_t eval() const override
        {
            return num_;
        }
    private:
        num_t num_;
    };
    
}
