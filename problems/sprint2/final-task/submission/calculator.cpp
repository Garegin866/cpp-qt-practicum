#include "calculator.h"

#include <cmath>

void Calculator::Set(Number n) {
    n_ = n;
}

Number Calculator::GetNumber() const {
    return n_;
}

void Calculator::Add(Number n) {
    n_ += n;
}

void Calculator::Sub(Number n) {
    n_ -= n;
}

void Calculator::Div(Number n) {
    n_ /= n;
}

void Calculator::Mul(Number n) {
    n_ *= n;
}

void Calculator::Pow(Number n){
    n_ = std::pow(n_, n);
}

void Calculator::Save() {
    buffer_ = n_;
}

void Calculator::Load() {
    n_ = buffer_.value();
}

bool Calculator::HasMem() const {
    return buffer_.has_value();
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(n_);
}
