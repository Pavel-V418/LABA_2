#ifndef LABA2_BIT_H
#define LABA2_BIT_H

#include <stdexcept>

class Bit {

public:
    Bit() : value_(false) {} // бит со значением 0
    explicit Bit(bool value) : value_(value) {} // для строгой типизации
    Bit(int value) : value_( value != 0 ) { // для удобства (Bit a = 1)
        if ( value != 0 && value != 1 ) {
            throw std::invalid_argument( "Bit: value must be 0 or 1" );
        }
    } // чтобы можно было записать бит = 1 или 0

    bool GetValue() const {return value_;};

    // bool operations
    Bit operator&(const Bit& other) const {return Bit(value_ && other.value_);};
    Bit operator|(const Bit& other) const {return Bit( value_ || other.value_);};
    Bit operator^(const Bit& other) const {return Bit( value_ != other.value_);};
    Bit operator~() const {return Bit( !value_ );}; // NOT

    bool operator==( const Bit& other ) const { return value_ == other.value_; }
    bool operator!=( const Bit& other ) const { return value_ != other.value_; }

private:
    bool value_;
};

#endif //LABA2_BIT_H