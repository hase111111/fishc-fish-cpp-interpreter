
#ifndef FISHC_INTERPRETER_H_
#define FISHC_INTERPRETER_H_


namespace fishc {

class Interpreter final {
  public:
    Interpreter() = delete;
    Interpreter(const std::string& code);
    ~Interpreter() = default;

    void Run();

  private:
    std::string code_;
};

}  // namespace fishc

#endif  // FISHC_INTERPRETER_H_
