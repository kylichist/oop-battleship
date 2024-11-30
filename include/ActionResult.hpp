#ifndef ACTIONRESULT_HPP  // ACTIONRESULT_HPP
#define ACTIONRESULT_HPP

#include <stdexcept>
#include <string>

class ActionResult {
public:
    virtual std::string getResult() = 0;

    virtual ~ActionResult() {}
};

class ActionResultSuccess : public ActionResult {
private:
    std::string result;

public:
    ActionResultSuccess(std::string result) : result(result) {}

    std::string getResult() override;
};

class ActionResultFailure : public ActionResult {
private:
    std::string result;

public:
    ActionResultFailure(std::runtime_error error) : result(error.what()) {}

    ActionResultFailure(std::exception exception) : result(exception.what()) {}

    std::string getResult() override;
};

#endif  // ACTIONRESULT_HPP
