#ifndef EXPRINTER_FORSTATEMENT_H
#define EXPRINTER_FORSTATEMENT_H
#include "Statements.hpp"

// class Statement {
// public:
//     virtual ~Statement() = default;
//
//     virtual void print() const = 0;
//     virtual void evaluate(SymbolTable &symbolTable) const = 0;
// };

class ForStatement : public Statement {
    void print() const override;
    void evaluate(SymbolTable &symbolTable) const override;
};


#endif
