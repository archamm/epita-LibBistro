#pragma once

#include <fstream>
#include <iostream>
#include <memory> // shared_ptr
#include <stdexcept> // domain_error
#include <utility> // pair


#include "ast-node.hh"
#include "ast-node-UnOp.hh"
#include "ast-node-Num.hh"
#include "ast-node-BinOp.hh"

namespace bistro
{

    /**
    ** AST factory node.
    **
    ** This is an implementation of the factory pattern.
    ** A node may be constructed with one or two operand (nodes) and an operator
    ** (OpType, defined in ast-node header), or with a BigNum.
    **/
    template <typename BigNum, typename Base>
    class ASTFactory 
    {
    public:
        /// BigNum.
        using num_t = BigNum;
        /// Base.
        using base_t = Base;
        /// Pointer to AST node.
        using node_t =  std::shared_ptr<ASTNode<BigNum, Base>>;
        
        ASTFactory() = default;

        node_t operator()(const node_t& lhs, OpType op) const
        {
            return std::make_shared<UnOpNode<BigNum, Base>>(lhs, op);
        }

        node_t operator()(const node_t& lhs, const node_t& rhs, OpType op) const
        {
            return std::make_shared<BinOpNode<BigNum, Base>>(lhs, rhs, op);
        }

        node_t operator()(const std::shared_ptr<num_t>& num) const
        {
            return std::make_shared<NumberNode<BigNum, Base>>(num);
        }
private:
        
    };
}
