//
// Created by 良觌 on 2018/6/26.
//

#ifndef DATABASE_INSTRUCTION_HPP
#define DATABASE_INSTRUCTION_HPP

#include "../DataBase.h"


namespace sample {
class Instruction {
private:
    sample::Command operation;
    int key;
    std::string value;

    int transitionID;
public:
    Instruction(Command o, int k, std::string s) : operation(o), key(k), value(s){}
    Instruction(std::tuple<Command, int, std::string> t) :
            operation(std::get<0>(t)), key(std::get<1>(t)), value(std::move(std::get<2>(t))) {}

    Command getOperation() const {
        return operation;
    }

    int getKey() const {
        return key;
    }

    const std::string &getValue() const {
        return value;
    }

    int getTransitionID() const {
        return transitionID;
    }

    void setTransitionID(int transitionID) {
        Instruction::transitionID = transitionID;
    }

};




}

#endif //DATABASE_INSTRUCTION_HPP
