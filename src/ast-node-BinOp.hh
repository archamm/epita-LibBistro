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

        /// Type of a node in the AST.
        /// Keep in mind you should be able to add/delete those.
        virtual ~ASTNode();
        
        /// Print the tree in infix notation, e.g. "(2+3)".
        virtual std::ostream&
        print_infix(std::ostream& out, const base_t& b) const = 0;
        
        /// Print the tree in polish notation, e.g. "+ 2 3".
        virtual std::ostream&
        print_pol(std::ostream&, const base_t&) const
        {
            throw "Not implemented";
        }
        
        /// Print the tree in reverse polish notation, e.g. "2 3 +".
        virtual std::ostream&
        print_rpol(std::ostream&, const base_t&) const
        {
            throw "Not implemented";
        }
        
        /// Evaluate the tree and return a shared_pointer to the result.
        virtual num_t eval() const = 0;
    private:
        
        node_t node_;
        num_t right_num_;
        num_t left_num_;
        OpType op_;
    };
    
};

