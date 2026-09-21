#include <iostream>
#include <string>
#include <utility>

#include "Statements.hpp"

Statements::~Statements() {
    for (auto *statement : statements)
        delete statement;
}

void Statements::addStatement(Statement *statement) {
    statements.push_back(statement);
}

void Statements::print() const {
    for (const auto *statement : statements)
        statement->print();
}

void Statements::evaluate(SymbolTable &symbolTable) const {
    for (const auto *statement : statements)
        statement->evaluate(symbolTable);
}

AssignmentStatement::AssignmentStatement(
    std::string variableName,
    ExprNode *expression)
    : variableName{std::move(variableName)}, expression{expression} {}

AssignmentStatement::~AssignmentStatement() {
    delete expression;
}

void AssignmentStatement::evaluate(SymbolTable &symbolTable) const {
    symbolTable.setValueFor(variableName, expression->evaluate(symbolTable));
}

void AssignmentStatement::print() const {
    std::cout << variableName << " = ";
    expression->print();
    std::cout << '\n';
}

PrintStatement::PrintStatement(ExprNode *expression) : relExpr{expression} {}

PrintStatement::~PrintStatement() {
    delete relExpr;
};

void PrintStatement::evaluate(SymbolTable &symbolTable) const {
    std::cout << relExpr->evaluate(symbolTable) << std::endl;
}

void PrintStatement::print() const {
    // relExpr->print();
    // std::cout << '\n';
}

// initializer, forStatementCompare, forStatementIncr, forloopStatements
ForStatement::ForStatement(AssignmentStatement *initializer, ExprNode *forStatementCompare, AssignmentStatement *forStatementIncr, Statements *forLoopStatements) :
    initializer{initializer}, forStatementCompare{forStatementCompare}, forStatementIncr{forStatementIncr}, forLoopStatements{forLoopStatements}
{}

ForStatement::~ForStatement() {
    delete initializer;
    delete forStatementCompare;
    delete forStatementIncr;
    delete forLoopStatements;
};

// When evaluated, a for statement must:
//
// Evaluate the initialization assignment once.
// Evaluate the relational condition before every iteration.
// Continue while the condition evaluates to a nonzero value.
// Evaluate every statement in the loop body.
// Evaluate the update assignment after each iteration.

void ForStatement::evaluate(SymbolTable &symbolTable) const {
    initializer->evaluate(symbolTable);

    while (forStatementCompare->evaluate(symbolTable)) {
        forLoopStatements->evaluate(symbolTable);
        forStatementIncr->evaluate(symbolTable);
    }
}

void ForStatement::print() const {
    // relExpr->print();
    // std::cout << '\n';
}