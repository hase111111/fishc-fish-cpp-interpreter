
#include "type.h"

#include <cmath>
#include <ostream>
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

Number operator%(const Number& a, const Number& b) {
    if (a.index() == 0 && b.index() == 0) {
        ImplInt ia = std::get<ImplInt>(a);
        ImplInt ib = std::get<ImplInt>(b);
        if (ib == 0) {
            throw std::runtime_error("Division by zero");
        }
        return static_cast<ImplInt>(ia % ib);
    } else if (a.index() == 1 && b.index() == 1) {
        ImplFloat fa = std::get<ImplFloat>(a);
        ImplFloat fb = std::get<ImplFloat>(b);
        if (fb == 0) {
            throw std::runtime_error("Division by zero");
        }
        return static_cast<ImplFloat>(std::fmod(fa, fb));
    } else if (a.index() == 0 && b.index() == 1) {
        ImplInt ia = std::get<ImplInt>(a);
        ImplFloat fb = std::get<ImplFloat>(b);
        if (fb == 0) {
            throw std::runtime_error("Division by zero");
        }
        return static_cast<ImplFloat>(std::fmod(ia, fb));
    } else if (a.index() == 1 && b.index() == 0) {
        ImplFloat fa = std::get<ImplFloat>(a);
        ImplInt ib = std::get<ImplInt>(b);
        if (ib == 0) {
            throw std::runtime_error("Division by zero");
        }
        return static_cast<ImplFloat>(std::fmod(fa, ib));
    }

    return Number();
}

bool operator==(const Number& a, const Number& b) noexcept {
    if (a.index() == 0 && b.index() == 0) {
        return std::get<ImplInt>(a) == std::get<ImplInt>(b);
    } else if (a.index() == 1 && b.index() == 1) {
        return std::get<ImplFloat>(a) == std::get<ImplFloat>(b);
    } else if (a.index() == 0 && b.index() == 1) {
        return static_cast<ImplFloat>(std::get<ImplInt>(a)) == std::get<ImplFloat>(b);
    } else if (a.index() == 1 && b.index() == 0) {
        return std::get<ImplFloat>(a) == static_cast<ImplFloat>(std::get<ImplInt>(b));
    }

    return false;
}

bool operator<(const Number& a, const Number& b) noexcept {
    if (a.index() == 0 && b.index() == 0) {
        return std::get<ImplInt>(a) < std::get<ImplInt>(b);
    } else if (a.index() == 1 && b.index() == 1) {
        return std::get<ImplFloat>(a) < std::get<ImplFloat>(b);
    } else if (a.index() == 0 && b.index() == 1) {
        return static_cast<ImplFloat>(std::get<ImplInt>(a)) < std::get<ImplFloat>(b);
    } else if (a.index() == 1 && b.index() == 0) {
        return std::get<ImplFloat>(a) < static_cast<ImplFloat>(std::get<ImplInt>(b));
    }

    return false;
}

std::ostream& operator<<(std::ostream& os, const Number& n) {
    if (n.index() == 0) {
        os << std::get<ImplInt>(n);
    } else if (n.index() == 1) {
        os << std::get<ImplFloat>(n);
    }

    return os;
}

}  // namespace fishc