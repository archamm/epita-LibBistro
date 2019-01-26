#pragma once

#include <cstdint>
#include <initializer_list>
#include <vector>
#include <map>

namespace bistro
{
    /**
    ** Base class.
    **
    ** This class represents a numerical base, along with the means to convert
    ** single digits to and from textual representation.
    **
    ** A valid representation type (for \a Char) has the following properties:
    **   - it can be copied.
    **   - it can be output (with \c operator<< )
    **   - it can be compared to itself (with \c operator== )
    **   - it can be compared to a \c char (with \c operator== )
    **   - it provides a \c hash functor.
    **/
    template <typename Value = uint8_t, typename Char = char>
    class Base
    {
    public:
        /// A digit in textual representation.
        using char_t = Char;

        /// A digit in "value" representation.
        using value_t = Value;

        /// Default constructor.
        Base();

        /// Construct a base from an initializer list.
        Base(std::initializer_list<char_t> list)
        {
            repr_.assign(list.begin(), list.end());
            base_ = repr_.size();
        }
       
        
        /// Get the numerical base represented.
        size_t get_base_num() const
        {
            return base_;
        }
        /**
        ** Add a the representation of a digit.
        **
        ** This will match the representation \a repr of the digit with the
        ** smallest unmatched value, thus increasing the size of the base by 1.
        **
        ** Throws invalid_argument if the representation is reserved (for an
        ** operator) or already matched).
        **/
        void add_digit(char_t repr)
        {
            if (!is_digit(repr))
                repr_.insert(repr, repr_.size());
            throw std::invalid_argument("Already in the list");
        }

        /// Check wether there is a match for the character representation \a c.
        bool is_digit(char_t c) const
        {
            return std::find(repr_.begin(), repr_.end(), c) != repr_.end();
            
        }

        /**
        ** Check wether the character representation \a c is reserved for an
        ** operator.
        **/
        static bool is_operator(char_t c)
        {
            return c == '+' || c == '*' || c == '-' || c == '%' || c == '/';
        }

        /**
        ** Get the representation for the value \a i.
        **
        ** \throw std::out_of_range if the value is not in the base.
        **/
        char_t get_digit_representation(value_t i) const
        {
            return repr_.at(i);
            
        }

        /**
        ** Get the value for the representation \a i.
        **
        ** \throw std::out_of_range if the representation is not in the base.
        **/
        value_t get_char_value(char_t r) const
        {
            //auto it = std::find(repr_.begin(), repr_.end(), r);
            for (size_t i = 0; i < repr_.size(); i++)
            {
                if (repr_.at(i) == r)
                    return i;
            }
            //if (it == repr_.end())
                throw std::out_of_range("oor in get_char_value");
        }
    
        
    private:
        std::vector<char_t> repr_;
        value_t base_;
    };

}
