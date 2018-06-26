//
// Created by 良觌 on 2018/6/25.
//

#include "ReorderBuffer.h"
#include <deque>
#include <stack>

namespace sample
{
    int sample::ReorderBuffer::ROBPiece::getPieceID() const {
        return pieceID;
    }

    const sample::Instruction &sample::ReorderBuffer::ROBPiece::getInstruction() const {
        return instruction;
    }

    ReorderBuffer::ReorderBuffer() : PIECE_NUMBER(0) {}
    std::pair<bool, std::string> ReorderBuffer::find(int key)
    {
        if(bufferData[key].size() == 0)
            return std::make_pair(false, "no value");
        return std::make_pair(true, bufferData[key].top());
    };
    bool ReorderBuffer::insert(Instruction inst)
    {
        buffer.push_front(ROBPiece(PIECE_NUMBER++, inst));
        bufferData.[inst.getKey()].push(inst);
        return true;
    }
    bool ReorderBuffer::write()
    {
        Instruction inst = buffer.back().getInstruction();
        buffer.pop_back();
        bufferData.[inst.getKey()].pop();
        return true;
    }




}

