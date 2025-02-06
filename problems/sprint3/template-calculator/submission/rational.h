#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <numeric>
#include <compare>

class Rational {
public:
    Rational()
        : numerator_(0)
        , denominator_(1) {}

    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }

        Reduction();
    }

    Rational(int numerator) : numerator_(numerator) {}

    Rational& operator= (int numerator) {
        numerator_ = numerator;
        return *this;
    }

    int GetNumerator() const;
    int GetDenominator() const;

    Rational Inv() const {
        return {denominator_, numerator_};
    }

    Rational operator+() const;
    Rational operator-() const;

    Rational& operator+=(const Rational& oth);
    Rational& operator-=(const Rational& oth);
    Rational& operator*=(const Rational& oth);
    Rational& operator/=(const Rational& oth);

    friend Rational operator+(const Rational& l, const Rational& r);
    friend Rational operator-(const Rational& l, const Rational& r);
    friend Rational operator*(const Rational& l, const Rational& r);
    friend Rational operator/(const Rational& l, const Rational& r);

    friend std::istream& operator>>(std::istream& is, Rational& r);
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);

private:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};

inline int Rational::GetNumerator() const {
    return numerator_;
}

inline int Rational::GetDenominator() const {
    return denominator_;
}

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    using namespace std::literals;

    os << r.numerator_;
    if (r.denominator_ != 1) {
        os << " / "s << r.denominator_;
    }

    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int n, d;
    char div;

    if (!(is >> n)) {
        return is;
    }

    if (!(is >> std::ws >> div)) {
        r = Rational(n, 1);
        is.clear();
        return is;
    }

    if (div != '/') {
        r = Rational(n, 1);
        is.unget();
        return is;
    }

    if (!(is >> d) || (d == 0)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    r = Rational(n, d);

    return is;
}

inline Rational Rational::operator+() const {
    return *this;
}

inline Rational Rational::operator-() const {
    return {-numerator_, denominator_};
}

inline Rational operator+(const Rational& l, const Rational& r) {
    Rational result;

    const int lcm = std::lcm(l.GetDenominator(), r.GetDenominator());
    result.numerator_ = (lcm / l.GetDenominator() * l.GetNumerator()) +
                        (lcm / r.GetDenominator() * r.GetNumerator());
    result.denominator_ = lcm;

    result.Reduction();
    return result;
}

inline Rational operator-(const Rational& l, const Rational& r) {
    Rational result;

    const int lcm = std::lcm(l.GetDenominator(), r.GetDenominator());
    result.numerator_ = (lcm / l.GetDenominator() * l.GetNumerator()) -
                        (lcm / r.GetDenominator() * r.GetNumerator());
    result.denominator_ = lcm;

    result.Reduction();
    return result;
}

inline Rational operator*(const Rational& l, const Rational& r) {
    Rational result;

    result.numerator_ = l.GetNumerator() * r.GetNumerator();
    result.denominator_ = l.GetDenominator() * r.GetDenominator();
    result.Reduction();

    return result;
}

inline Rational operator/(const Rational& l, const Rational& r) {
    Rational result;

    result.numerator_ = l.GetNumerator() * r.GetDenominator();
    result.denominator_ = l.GetDenominator() * r.GetNumerator();
    result.Reduction();

    return result;
}

inline Rational& Rational::operator+=(const Rational& oth) {
    const int lcm = std::lcm(this->denominator_, oth.denominator_);

    numerator_ = (lcm / this->denominator_ * this->numerator_) +
                 (lcm / oth.denominator_ * oth.numerator_);
    denominator_ = lcm;

    Reduction();

    return *this;
}

inline Rational& Rational::operator-=(const Rational& oth) {
    const int lcm = std::lcm(this->denominator_, oth.denominator_);

    numerator_ = (lcm / this->denominator_ * this->numerator_) -
                 (lcm / oth.denominator_ * oth.numerator_);
    denominator_ = lcm;

    Reduction();

    return *this;
}

inline Rational& Rational::operator*=(const Rational& oth) {
    numerator_ *= oth.numerator_;
    denominator_ *= oth.denominator_;

    Reduction();

    return *this;
}

inline Rational& Rational::operator/=(const Rational& oth) {
    numerator_ *= oth.denominator_;
    denominator_ *= oth.numerator_;

    Reduction();

    return *this;
}

inline auto operator<=>(const Rational& l, const Rational& r) {
    std::int64_t n1 = static_cast<std::int64_t>(l.GetNumerator()) *
                      r.GetDenominator();
    std::int64_t n2 = static_cast<std::int64_t>(l.GetDenominator()) *
                      r.GetNumerator();

    return n1 <=> n2;
}

inline bool operator==(const Rational& l, const Rational& r) {
    std::int64_t n1 = static_cast<std::int64_t>(l.GetNumerator()) *
                      r.GetDenominator();
    std::int64_t n2 = static_cast<std::int64_t>(l.GetDenominator()) *
                      r.GetNumerator();

    return n1 == n2;
}
