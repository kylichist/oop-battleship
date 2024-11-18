#ifndef ABILITYRESULT_HPP  // ABILITYRESULT_HPP
#define ABILITYRESULT_HPP

#include <string>

class AbilityResult {
public:
    virtual std::string getResult() = 0;

    virtual ~AbilityResult() {}
};

class BombardSuccessResult : public AbilityResult {
public:
    std::string getResult() override {
        return "A ship was damaged during bombard";
    }
};

class BombardFailureResult : public AbilityResult {
public:
    std::string getResult() override {
        return "No ship was damaged during bombard";
    }
};

class BombardShipDestroyedResult : public AbilityResult {
public:
    std::string getResult() override {
        return "A ship was destroyed during bombard";
    }
};

class DoubleDamageSuccessResult : public AbilityResult {
public:
    std::string getResult() override { return "Next attack damage is doubled"; }
};

class ScannerFailureResult : public AbilityResult {
public:
    std::string getResult() override {
        return "No ship was found in selected area";
    }
};

class ScannerSuccessResult : public AbilityResult {
public:
    std::string getResult() override {
        return "A ship was found in selected area";
    }
};

#endif  // ABILITYRESULT_HPP
