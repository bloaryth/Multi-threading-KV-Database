//
// Created by 良觌 on 2018/6/25.
//

#ifndef DATABASE_REORDERBUFFER_H
#define DATABASE_REORDERBUFFER_H
#include <map>
#include <deque>
#include <stack>
#include "FrontEnd/Instruction.hpp"

namespace sample {
class ReorderBuffer {
private:
    class ROBPiece;
    std::deque<ROBPiece> buffer;
    std::map<int, std::stack<std::string>> bufferData;
    static int PIECE_NUMBER;
public:
    ReorderBuffer();
    std::pair<bool, std::string> find(int key);
    bool insert(Instruction inst);
    bool write();


private:
    class ROBPiece {
    private:
        int pieceID;
        Instruction instruction;
    public:
        ROBPiece(int id, Instruction inst) : pieceID(id), instruction(inst){}
        int getPieceID() const;
        const Instruction &getInstruction() const;
    };

};


}


#endif //DATABASE_REORDERBUFFER_H
