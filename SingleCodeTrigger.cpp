#include "SingleCodeTrigger.h"

SingleCodeTrigger::SingleCodeTrigger(const char* code):
    code(std::string(code))
{ }

bool SingleCodeTrigger::receive(const std::string& code) {
    return (code == this->code);
}
