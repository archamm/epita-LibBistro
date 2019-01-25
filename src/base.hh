#pragma once

#include <cstdint>
#include <initializer_list>

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
            /* FIXME */
            throw "Not implemented";
        }

        /// Get the numerical base represented.
        size_t get_base_num() const
        {
            /* FIXME */
            throw "Not implemented";
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
            /* FIXME */
            throw "Not implemented";
        }

        /// Check wether there is a match for the character representation \a c.
        bool is_digit(char_t c) const
        {
            /* FIXME */
            throw "Not implemented";
        }

        /**
        ** Check wether the character representation \a c is reserved for an
        ** operator.
        **/
        static bool is_operator(char_t c)
        {
            /* FIXME */
            throw "Not implemented";
        }

        /**
        ** Get the representation for the value \a i.
        **
        ** \throw std::out_of_range if the value is not in the base.
        **/
        char_t get_digit_representation(value_t i) const
        {
            /* FIXME */
            throw "Not implemented";
        }

        /**
        ** Get the value for the representation \a i.
        **
        ** \throw std::out_of_range if the representation is not in the base.
        **/
        value_t get_char_value(char_t r) const
        {
            /* FIXME */
            throw "Not implemented";
        }

    private:
    };

}
