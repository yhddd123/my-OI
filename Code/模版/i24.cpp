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

inline bool operator==(i24 a, i24 b) { return static_cast<int>(a) == static_cast<int>(b); }
inline bool operator!=(i24 a, i24 b) { return !(a == b); }
inline bool operator<(i24 a, i24 b) { return static_cast<int>(a) < static_cast<int>(b); }
inline bool operator>(i24 a, i24 b) { return b < a; }
inline bool operator<=(i24 a, i24 b) { return !(b < a); }
inline bool operator>=(i24 a, i24 b) { return !(a < b); }

inline i24 operator+(i24 a, int b) { a += b; return a; }
inline i24 operator-(i24 a, int b) { a -= b; return a; }
inline i24 operator*(i24 a, int b) { a *= b; return a; }
inline i24 operator/(i24 a, int b) { a /= b; return a; }
inline i24 operator%(i24 a, int b) { a %= b; return a; }
inline int operator+(i24 a, i24 b) { return static_cast<int>(a) + static_cast<int>(b); }
inline int operator-(i24 a, i24 b) { return static_cast<int>(a) - static_cast<int>(b); }
