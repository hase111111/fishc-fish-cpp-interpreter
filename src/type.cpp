
#include "type.h"

#include <stdexcept>

namespace fishc {

Number operator+(const Number& a, const Number& b) noexcept {
    if (a.index() == 0 && b.index() == 0) {
        const ImplInt ia = std::get<ImplInt>(a);
        const ImplInt ib = std::get<ImplInt>(b);
        return static_cast<ImplInt>(ia + ib);
    } else if (a.index() == 1 && b.index() == 1) {
        const ImplFloat fa = std::get<ImplFloat>(a);
        const ImplFloat fb = std::get<ImplFloat>(b);
        return static_cast<ImplFloat>(fa + fb);
    } else if (a.index() == 0 && b.index() == 1) {
        const ImplInt ia = std::get<ImplInt>(a);
        const ImplFloat fb = std::get<ImplFloat>(b);
        return static_cast<ImplFloat>(ia + fb);
    } else if (a.index() == 1 && b.index() == 0) {
        ImplFloat fa = std::get<ImplFloat>(a);
        ImplInt ib = std::get<ImplInt>(b);
        return static_cast<ImplFloat>(fa + ib);
    }

    return Number();
}

Number operator-(const Number& a, const Number& b) noexcept {
    if (a.index() == 0 && b.index() == 0) {
        ImplInt ia = std::get<ImplInt>(a);
        ImplInt ib = std::get<ImplInt>(b);
        return static_cast<ImplInt>(ia - ib);
    } else if (a.index() == 1 && b.index() == 1) {
        ImplFloat fa = std::get<ImplFloat>(a);
        ImplFloat fb = std::get<ImplFloat>(b);
        return static_cast<ImplFloat>(fa - fb);
    } else if (a.index() == 0 && b.index() == 1) {
        ImplInt ia = std::get<ImplInt>(a);
        ImplFloat fb = std::get<ImplFloat>(b);
        return static_cast<ImplFloat>(ia - fb);
    } else if (a.index() == 1 && b.index() == 0) {
        ImplFloat fa = std::get<ImplFloat>(a);
        ImplInt ib = std::get<ImplInt>(b);
        return static_cast<ImplFloat>(fa - ib);
    }

    return Number();
}

Number operator*(const Number& a, const Number& b) noexcept {
    if (a.index() == 0 && b.index() == 0) {
        ImplInt ia = std::get<ImplInt>(a);
        ImplInt ib = std::get<ImplInt>(b);
        return static_cast<ImplInt>(ia * ib);
    } else if (a.index() == 1 && b.index() == 1) {
        ImplFloat fa = std::get<ImplFloat>(a);
        ImplFloat fb = std::get<ImplFloat>(b);
        return static_cast<ImplFloat>(fa * fb);
    } else if (a.index() == 0 && b.index() == 1) {
        ImplInt ia = std::get<ImplInt>(a);
        ImplFloat fb = std::get<ImplFloat>(b);
        return static_cast<ImplFloat>(ia * fb);
    } else if (a.index() == 1 && b.index() == 0) {
        ImplFloat fa = std::get<ImplFloat>(a);
        ImplInt ib = std::get<ImplInt>(b);
        return static_cast<ImplFloat>(fa * ib);
    }

    return Number();
}

Number operator/(const Number& a, const Number& b) {
    if (a.index() == 0 && b.index() == 0) {
        ImplInt ia = std::get<ImplInt>(a);
        ImplInt ib = std::get<ImplInt>(b);
        if (ib == 0) {
            throw std::runtime_error("Division by zero");
        }
        return static_cast<ImplInt>(ia / ib);
    } else if (a.index() == 1 && b.index() == 1) {
        ImplFloat fa = std::get<ImplFloat>(a);
        ImplFloat fb = std::get<ImplFloat>(b);
        if (fb == 0) {
            throw std::runtime_error("Division by zero");
        }
        return static_cast<ImplFloat>(fa / fb);
    } else if (a.index() == 0 && b.index() == 1) {
        ImplInt ia = std::get<ImplInt>(a);
        ImplFloat fb = std::get<ImplFloat>(b);
        if (fb == 0) {
            throw std::runtime_error("Division by zero");
        }
        return static_cast<ImplFloat>(ia / fb);
    } else if (a.index() == 1 && b.index() == 0) {
        ImplFloat fa = std::get<ImplFloat>(a);
        ImplInt ib = std::get<ImplInt>(b);
        if (ib == 0) {
            throw std::runtime_error("Division by zero");
        }
        return static_cast<ImplFloat>(fa / ib);
    }

    return Number();
}

}  // namespace fishc