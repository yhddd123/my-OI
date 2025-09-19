#pragma once
#include <cstdint>
#include <type_traits>

// 24-bit signed integer backed by 3 bytes
struct i24 {
    std::uint8_t bytes[3];

    i24() : bytes{0, 0, 0} {}
    i24(int v) { *this = v; }

    i24& operator=(int v) {
        std::uint32_t x = static_cast<std::uint32_t>(v);
        bytes[0] = static_cast<std::uint8_t>(x);
        bytes[1] = static_cast<std::uint8_t>(x >> 8);
        bytes[2] = static_cast<std::uint8_t>(x >> 16);
        return *this;
    }

    operator int() const {
        std::uint32_t x = static_cast<std::uint32_t>(bytes[0]) |
                           (static_cast<std::uint32_t>(bytes[1]) << 8) |
                           (static_cast<std::uint32_t>(bytes[2]) << 16);
        if (x & 0x00800000u) x |= 0xFF000000u; // sign-extend from bit 23
        return static_cast<int>(static_cast<std::int32_t>(x));
    }

    // compound assignments
    i24& operator+=(int v) { return *this = static_cast<int>(*this) + v; }
    i24& operator-=(int v) { return *this = static_cast<int>(*this) - v; }
    i24& operator*=(int v) { return *this = static_cast<int>(*this) * v; }
    i24& operator/=(int v) { return *this = static_cast<int>(*this) / v; }
    i24& operator%=(int v) { return *this = static_cast<int>(*this) % v; }

    // increment / decrement
    i24& operator++() { return *this += 1; }
    i24 operator++(int) { i24 t = *this; *this += 1; return t; }
    i24& operator--() { return *this -= 1; }
    i24 operator--(int) { i24 t = *this; *this -= 1; return t; }
};

// 24-bit unsigned integer backed by 3 bytes
struct u24 {
    std::uint8_t bytes[3];

    u24() : bytes{0, 0, 0} {}
    u24(unsigned v) { *this = v; }

    u24& operator=(unsigned v) {
        std::uint32_t x = static_cast<std::uint32_t>(v);
        bytes[0] = static_cast<std::uint8_t>(x);
        bytes[1] = static_cast<std::uint8_t>(x >> 8);
        bytes[2] = static_cast<std::uint8_t>(x >> 16);
        return *this;
    }

    operator unsigned() const {
        std::uint32_t x = static_cast<std::uint32_t>(bytes[0]) |
                           (static_cast<std::uint32_t>(bytes[1]) << 8) |
                           (static_cast<std::uint32_t>(bytes[2]) << 16);
        return static_cast<unsigned>(x);
    }

    // compound assignments
    u24& operator+=(unsigned v) { return *this = static_cast<unsigned>(*this) + v; }
    u24& operator-=(unsigned v) { return *this = static_cast<unsigned>(*this) - v; }
    u24& operator*=(unsigned v) { return *this = static_cast<unsigned>(*this) * v; }
    u24& operator/=(unsigned v) { return *this = static_cast<unsigned>(*this) / v; }
    u24& operator%=(unsigned v) { return *this = static_cast<unsigned>(*this) % v; }

    // increment / decrement
    u24& operator++() { return *this += 1u; }
    u24 operator++(int) { u24 t = *this; *this += 1u; return t; }
    u24& operator--() { return *this -= 1u; }
    u24 operator--(int) { u24 t = *this; *this -= 1u; return t; }
};

// relational operators (work via implicit conversion)
inline bool operator==(i24 a, i24 b) { return static_cast<int>(a) == static_cast<int>(b); }
inline bool operator!=(i24 a, i24 b) { return !(a == b); }
inline bool operator<(i24 a, i24 b) { return static_cast<int>(a) < static_cast<int>(b); }
inline bool operator>(i24 a, i24 b) { return b < a; }
inline bool operator<=(i24 a, i24 b) { return !(b < a); }
inline bool operator>=(i24 a, i24 b) { return !(a < b); }

inline bool operator==(u24 a, u24 b) { return static_cast<unsigned>(a) == static_cast<unsigned>(b); }
inline bool operator!=(u24 a, u24 b) { return !(a == b); }
inline bool operator<(u24 a, u24 b) { return static_cast<unsigned>(a) < static_cast<unsigned>(b); }
inline bool operator>(u24 a, u24 b) { return b < a; }
inline bool operator<=(u24 a, u24 b) { return !(b < a); }
inline bool operator>=(u24 a, u24 b) { return !(a < b); }

// arithmetic operators returning i24/u24 results
inline i24 operator+(i24 a, int b) { a += b; return a; }
inline i24 operator-(i24 a, int b) { a -= b; return a; }
inline i24 operator*(i24 a, int b) { a *= b; return a; }
inline i24 operator/(i24 a, int b) { a /= b; return a; }
inline i24 operator%(i24 a, int b) { a %= b; return a; }
inline int operator+(i24 a, i24 b) { return static_cast<int>(a) + static_cast<int>(b); }
inline int operator-(i24 a, i24 b) { return static_cast<int>(a) - static_cast<int>(b); }

inline u24 operator+(u24 a, unsigned b) { a += b; return a; }
inline u24 operator-(u24 a, unsigned b) { a -= b; return a; }
inline u24 operator*(u24 a, unsigned b) { a *= b; return a; }
inline u24 operator/(u24 a, unsigned b) { a /= b; return a; }
inline u24 operator%(u24 a, unsigned b) { a %= b; return a; }
inline unsigned operator+(u24 a, u24 b) { return static_cast<unsigned>(a) + static_cast<unsigned>(b); }
inline unsigned operator-(u24 a, u24 b) { return static_cast<unsigned>(a) - static_cast<unsigned>(b); }

static_assert(sizeof(i24) == 3, "i24 must be 3 bytes");
static_assert(sizeof(u24) == 3, "u24 must be 3 bytes"); 