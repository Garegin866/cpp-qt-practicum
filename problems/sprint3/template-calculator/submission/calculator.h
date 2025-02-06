#pragma once

#include <QtCore/qdebug.h>
#include <QtCore/qlogging.h>
#include <string>
#include <optional>
#include <cmath>

#include "rational.h"
#include "pow.h"

using Error = std::string;

namespace errors {
inline const Error kDivisionByZero = "Division by zero";
inline const Error kZeroPowerToZero = "Zero power to zero";
inline const Error kFractionalPower = "Fractional power is not supported";
inline const Error kIntegerNegativePower = "Integer negative power";
}

template<typename Number>
class Calculator {
public:
    void Set(Number n) {
        n_ = n;
    }

    Number GetNumber() const {
        return n_;
    }

    std::optional<Error> Add(Number n) {
        n_ += n;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number n) {
        n_ -= n;
        return std::nullopt;
    }

    std::optional<Error> Div(Number n) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if (n == 0) {
                return errors::kDivisionByZero;
            }
        }
        n_ /= n;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number n) {
        n_ *= n;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number n) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if (n_ == 0 && n == 0) {
                return errors::kZeroPowerToZero;
            }
            if constexpr (std::is_integral_v<Number>) {
                if (n < 0) {
                    return errors::kIntegerNegativePower;
                }
                n_ = IntegerPow(n_, n);
            } else {
                if (n.GetDenominator() != 1) {
                    return errors::kFractionalPower;
                }

                n_ = ::Pow(n_, n);
            }
        } else {
            if (std::floor(n) != n) {
                return errors::kFractionalPower;
            }
            n_ = std::pow(n_, n);
        }

        return std::nullopt;
    }

    void Save() {
        buffer_ = n_;
    }

    void Load() {
        if (buffer_) {
            n_ = *buffer_;
        }
    }

    bool GetHasMem() const {
        return buffer_.has_value();
    }

    std::string GetNumberRepr() const {
        return std::to_string(n_);
    }

private:
    Number n_ = 0;
    std::optional<Number> buffer_;
};
