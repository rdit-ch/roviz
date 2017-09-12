#ifndef STRONG_TYPEDEF_H
#define STRONG_TYPEDEF_H

/**
 * @brief A strong typedef that doesn't allow much casting around
 *
 * From http://www.ilikebigbits.com/blog/2014/5/6/type-safe-identifiers-in-c
 */
template<class Tag, class Impl, Impl default_value>
class StrongTypedef
{
public:
    static StrongTypedef invalid() { return StrongTypedef(); }

    // Defaults to StrongTypedef::invalid()
    StrongTypedef() : m_val(default_value) { }

    // Explicit constructor:
    explicit StrongTypedef(Impl val) : m_val(val) { }

    // Explicit conversion to get back the impl:
    explicit operator Impl() const { return m_val; }

    friend bool operator==(StrongTypedef a, StrongTypedef b) { return a.m_val == b.m_val; }
    friend bool operator!=(StrongTypedef a, StrongTypedef b) { return a.m_val != b.m_val; }
    friend bool operator<(StrongTypedef a, StrongTypedef b) { return a.m_val < b.m_val; }

private:
    Impl m_val;
};

#endif // STRONG_TYPEDEF_H
