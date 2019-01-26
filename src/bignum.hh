#pragma once

#include <cstdint>  // uint8_t
#include <fstream>  // ifstream
#include <iostream> // ostream
#include <memory>   // shared_ptr
#include "base.hh"
#include <vector>
#include <ctype.h>
#include <stdexcept>


namespace bistro
{

    /**
    ** BigNum class.
    **
    ** This class represents an arbitrarily large integer number, expressed in a
    ** specific base, and comes with the basic arithmetic operations.
    **
    ** The parameter \a T can be any unsigned integer type (\c uint8_t,
    ** \c uint16_t, ...).
    */
    template <typename T = uint8_t>
    class BigNum
    {
    public:
        /// Type of a single digit.
        using digit_t = T;

        /// This class.
        using self_t = BigNum;

        /// Shared pointer to this class.
        using self_ptr_t = std::shared_ptr<BigNum>;

        /// Shared pointer to const self.
        using const_self_ptr_t = const std::shared_ptr<BigNum>;

        /// Type of the digit container.
        using digits_t = std::vector<T>;

        /// Type used as index.
        using index_t = size_t;

        /**
        ** Basic constructor, for empty number.
        **
        ** \a base is the numeric value of the base in which the number will be
        ** represented.
        **/
        BigNum(std::size_t base) : base_(base),
        is_positive_(1)
        {
        }

        /**
        ** Construct the number from a file stream.
        **
        ** Read the number from \a in, with base \a b, stopping before the first
        ** non-digit character.
        **
        ** \throw std::length_error if the stream doesn't start with a number.
        **/
        template <typename Base>
        BigNum(std::istream& in, const Base& b)
        {
            base_ = b.get_base_num();
            std::string line;
            getline(in, line);
            if (line.length() == 0 || !isdigit(line[0]))
                throw std::length_error("le in construsctor");
            do
            {
                for(size_t i = 0; i < line.length() && b.is_digit(line[0]); ++i)
                {
                    number_.push_back(b.get_char_value(i));
                }
            }
            while (getline(in, line));
        }
        

        /// Disable copy constructor.
        BigNum(const BigNum&) = delete;

        /// Disable copy by assignment.
        BigNum& operator=(const BigNum&) = delete;

        /// Enable move constructor.
        BigNum(BigNum&&) = default;

        /// Enable move assignment.
        BigNum& operator=(BigNum&&) = default;

        /// Clone the bignum into a new instance.
        self_t clone() const
        {
            BigNum clone;
            clone.is_positive_ = is_positive_;
            clone.number_ = number_;
            clone.base_ = base_;
            return clone;
        }

        /// Get the number of digits in the base representation of the number.
        index_t get_num_digits() const
        {
            return number_.size();
        }

        /**
        ** Get the \a i th digit in the base representation of the number, 0
        ** being the least significant digit.
        **
        ** \throw std::out_of_range exception if the digit asked is over the
        ** number of digits in the BigNum.
        **/
        digit_t get_digit(index_t i) const
        {
            return number_.at(i);
        }

        /**
        ** Set the \a i th digit to the value \a d, 0 being the least
        ** significant digit.
        **
        ** If \a i is bigger than the number of digits, increase the number of
        ** digits by adding 0s.
        ** If this causes the number to have leading 0s, strip them.
        **
        ** 0 is represented by no digits.
        **
        ** \throw std::invalid_argument if \a d is bigger than the base.
        **/
        void set_digit(index_t i, digit_t d)
        {
            if (d > base_)
                throw std::invalid_argument("ia in set_digit");
            if (i < number_.size())
            {
                number_.at(i) = d;
                return;
            }
            for (size_t y = number_.size(); y < i; ++y)
                number_.push_back(0);
            number_.push_back(d);
        }

        /**
        ** Return the sign of the BigNum.
        **
        ** For the case of 0, the result of this function is undefined.
        ** However, when printing, there must not be a minus sign before the 0.
        **/
        bool is_positive() const
        {
            return is_positive_;
        }

        /// Set the sign of the BigNum.
        void set_positive(bool p)
        {
            is_positive_ = p;
        }

        /**
        ** Output the number in the stream \a out, in the representation of \a b.
        **
        ** The output is not followed by a newline.
        **
        ** \throw std::invalid_argument if the size of \a b is not the base of \a this.
        **/
        template <typename Base>
        std::ostream& print(std::ostream& out, const Base& b) const
        {
            if (!is_positive())
                out << '-';
            for (size_t i = 0; i < number_.size(); i++)
            {
                out << b.get_char_value(number_.at(i));
            }
            return out;
        }

        /// Output the number in polish notation (i.e. -2 becomes "- 0 2").
        template <typename Base>
        std::ostream& print_pol(std::ostream& out, const Base& b) const
        {
            if (!is_positive())
                out << "- 0 ";
            
            for (size_t i = 0; i < number_.size(); i++)
            {
                out << b.get_char_value(number_.at(i));
            }
            return out;
            
        }

        /// Output the number in reverse polish notation (i.e. -2 becomes "0 2 -").
        template <typename Base>
        std::ostream& print_rpol(std::ostream& out, const Base& b) const
        {
            if (!is_positive())
                out << '0';
            for (size_t i = 0; i < number_.size(); i++)
            {
                out << b.get_char_value(number_.at(i));
            }
            if (!is_positive())
                out << '-';
            return out;
        }

        ///@{
        /**
        ** \throw std::invalid_argument if \a this and \a other are not
        ** expressed in the same base.
        **/

        self_t operator+(const self_t& other) const;

        self_t operator-(const self_t& other) const;

        self_t operator*(const self_t& other) const;

        /// \throw std::overflow_error for a division by 0.
        self_t operator/(const self_t& other) const;

        /**
        ** Modulus, with the C/C++ convention.
        **
        ** \throw std::overflow_error for a modulo 0.
        **/
        self_t operator%(const self_t& other) const;

        self_t pow(const self_t& exponent) const;

        self_t sqrt() const;

        self_t log(const self_t& base) const;

        self_t& operator+=(const self_t& other);

        self_t& operator-=(const self_t& other);

        self_t& operator*=(const self_t& other);

        self_t& operator/=(const self_t& other);

        self_t& operator%=(const self_t& other);

        self_t& pow_inplace(const self_t& exponent);

        self_t& sqrt_inplace();

        self_t& log_inplace(const self_t& base);

        bool operator>(const self_t& other) const;

        bool operator==(const self_t& other) const;
        ///@}

        /// Returns true if the number is not 0, false otherwise
        explicit operator bool() const;

    private:
        
        std::vector<digit_t> number_;
        std::size_t base_;
        bool is_positive_;
        
    };

}
