
#ifndef FISHC_INSTRUCTION_HANDLER_H_
#define FISHC_INSTRUCTION_HANDLER_H_

#include <memory>
#include <random>

#include "fish_resource.h"

namespace fishc {

class InstructionHandler final {
    public:
        InstructionHandler() = delete;
        explicit InstructionHandler(const std::shared_ptr<FishResource> &fish_resource_ptr) noexcept;
        ~InstructionHandler() = default;
    
        bool Handle(char ch);

    private:
        const std::shared_ptr<FishResource> fish_resource_ptr_;
        std::mt19937 mt_;

        void Mirror(char ch);
        void ConditionalTrampoline();
        void Jump();
        void ArithmeticOperators(char op);
        void ComparisonOperator(char op);
};

}  // namespace fishc

#endif  // FISHC_INSTRUCTION_HANDLER_H_
