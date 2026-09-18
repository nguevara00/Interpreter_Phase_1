Interpreter Project: Phase 1
Introduction
In this project, you will extend a small interpreter for a Python-inspired programming language. This is the first stage of a larger project: over time, the interpreter will grow to recognize and execute a respectable subset of Python.

An interpreter processes a program in several stages. The tokenizer reads the source text and groups its characters into tokens such as identifiers, integers, operators, keywords, and line endings. The parser checks whether those tokens follow the language grammar and builds an abstract syntax tree (AST). Finally, the interpreter evaluates that tree, using a symbol table to keep track of variables and their values.

This project uses a recursive-descent parser. Each major production in the grammar is represented by a corresponding parser function. Those functions call one another in the same way that the grammar's productions refer to one another. This close correspondence makes the parser easier to understand, extend, and test.

Although the language is inspired by Python, this phase deliberately uses braces and a C-style for header. This lets us study parsing and interpretation without first having to implement indentation-sensitive blocks.

Download the starter projectDownload Download the starter project

Download the grammar rulesDownload Download the grammar rules

 

Learning Objectives
By completing this project, you will gain experience with:

Tokens and lexical analysis
Recursive-descent parsing
Operator precedence
Abstract syntax trees
Symbol tables
Interpreting statements and expressions
Incremental software development and testing
Teams
You will work in  teams of two. Both partners are responsible for understanding the complete submission, including portions primarily written by the other partner. More on this during the lecture. 

Both partners must upload the same completed ZIP archive to Canvas.

AI Assistance: Explanations Only
You may use generative AI only as a tutor for explanations of general concepts. For example, you may ask for an explanation of recursive-descent parsing, inheritance, virtual functions, or the general meaning of a compiler diagnostic.

You may not use AI to:

Generate project code or project-specific pseudocode
Complete any parser function, AST class, tokenizer logic, or evaluation logic
Review, modify, refactor, or debug your project code
Analyze code, tests, the grammar, or other project materials that you provide to it
Generate test cases, expected output, or project documentation
Produce any portion of the submitted solution
In short, AI may explain a concept, but it may not work on this project for you. If you are unsure whether a proposed use is permitted, ask the instructor before using it.

Every submission must contain an AI Use section in README.md. If neither partner used AI, write None. Otherwise, identify the tool, the concepts you asked it to explain, and how extensively it was used. Do not claim that AI was unused if either partner used it.

Materials Provided
You are given:

The complete context-free grammar for this phase
A working tokenizer for the tokens used by the starter interpreter
A recursive-descent parser for assignments and arithmetic expressions
AST classes for assignment statements and arithmetic expressions
A symbol table and evaluator
A Makefile and a small sample input file
The starter parser already contains functions corresponding to all three relational-expression levels. In the starter version, these functions simply pass an arithmetic expression upward. You will extend them to recognize the relational operators in the grammar.

The tokenizer already recognizes for and print as keywords, but the starter parser deliberately reports that these statements have not yet been implemented.

Language Definition
The supplied grammar is the authoritative definition of the language for this project. Your interpreter must accept programs described by that grammar and must reject input that does not conform to it.

Important lexical and syntactic details include:

Spaces and tabs are insignificant.
Blank lines are ignored.
A nonblank source line produces a NEWLINE token.
The final statement must be followed by NEWLINE before EOF.
Top-level statements are not terminated by semicolons.
Semicolons occur only within a for-loop header.
A for-loop body must contain at least one statement.
The opening brace of a for loop must be followed by NEWLINE.
Repeated unary signs such as --x are not part of the language.
Required Work
1. Recognize relational operators and braces
Extend Token and Tokenizer to recognize:

==  !=  >  >=  <  <=  {  }
The starter implementation stores a symbol as a single char. You will need to extend this representation so that a token can also represent two-character operators. Make sure the tokenizer distinguishes = from == and recognizes the longest valid operator. A lone ! is not a valid token in this language.

Add appropriate token-query functions and update Token::print() so all new tokens can be displayed correctly.

Compile and run the unchanged sample program after completing this step. The existing assignment and arithmetic behavior should continue to work.

2. Parse and evaluate relational expressions
Complete the following parser functions according to the supplied grammar:

relExpr()
relTerm()
relPrimary()
Preserve the two precedence levels specified by the grammar: ordering operators bind more tightly than equality operators. Because each relational operator is optional rather than repeatable, expressions such as a < b < c must be rejected.

Extend BinaryExprNode::evaluate() to evaluate all six relational operators. A true comparison must evaluate to integer 1, and a false comparison must evaluate to integer 0.

3. Implement print statements
Define a PrintStatement class derived from Statement. Add a printStatement() parser function and update statement() to dispatch to it when the next token is the print keyword.

Executing:

print expression
must evaluate the expression and print its integer value followed by a newline.

4. Implement for statements
Define a ForStatement class derived from Statement and add a forStatement() parser function. Implement the exact syntax specified in the grammar. In particular, the two assignments in the loop header are not followed by NEWLINE: forStatement() must consume the two header semicolons and the closing parenthesis in their proper locations.

When evaluated, a for statement must:

Evaluate the initialization assignment once.
Evaluate the relational condition before every iteration.
Continue while the condition evaluates to a nonzero value.
Evaluate every statement in the loop body.
Evaluate the update assignment after each iteration.
The grammar permits nested for loops, so your implementation must support them. Follow the existing raw-pointer ownership model and provide destructors for any new classes that own AST nodes or statements.

For example:

limit = 4
for (i = 0; i < limit; i = i + 1) {
    print i
}
should print:

0
1
2
3
Testing Requirements
Create a directory named tests inside your project directory and place all of your test input files there. Use descriptive filenames so the purpose of each test is apparent.

Your tests should cover at least:

All six relational operators
Equality and ordering precedence
True and false comparisons
Arithmetic and unary-expression regression cases
Print statements
Loops that execute zero, one, and several times
Nested loops
Blank lines and ordinary whitespace
Malformed input that should be rejected
Test after completing each stage rather than waiting until the entire project is finished. The grader will also run hidden input files that are not included with the starter project.

README.md
Your project directory must contain a README.md with the following sections:

Team Members
List both partners' names.

Contributions
Briefly describe each partner's contributions. You may also identify work that was pair-programmed or completed jointly. Both partners remain responsible for the complete solution.

AI Use
Write None if neither partner used AI. If AI was used for permitted conceptual explanations, list the tool, the topics discussed, and the extent of its use.

Building and Running
Your project must build from the command line with:

make
This command must produce an executable named interpreter.x. The interpreter must accept exactly one command-line argument: the name of the input file.

For example:

./interpreter.x tests/basic-loop.txt
Your implementation must use C++20 and compile with the supplied warning flags. Update the Makefile if you add source files.

Required Testing on Blue
Your final solution must compile and run on blue.cs.sonoma.edu. Testing on Blue is an essential part of this project. A solution that works only on your own computer or in an IDE does not satisfy this requirement.

Before submitting, transfer the exact project directory that you intend to submit to Blue and test it from the command line. At a minimum, run:

make clean
make
./interpreter.x tests/name-of-an-input-file
Run several representative files from your tests directory, including files that exercise relational expressions, loops, and nested loops.

Submission
Before creating the archive, remove generated files and directories, including:

Executables
Object files
CMake or IDE build directories
IDE-specific project metadata
The submitted directory should have a structure similar to:

your-project-directory/
├── Makefile
├── README.md
├── *.cpp
├── *.hpp
└── tests/
    └── your test input files
Zip the entire project directory. Both partners must upload the same ZIP file to Canvas.

Before uploading, copy the ZIP file to Blue, extract it into a clean directory, and verify that the extracted submission builds and runs there. This final Blue test is essential because it checks the same archive that you will submit—not a different working copy.

We will test submissions on Blue using commands equivalent to:

unzip your-project.zip
cd your-project-directory
make
./interpreter.x tests/name-of-an-input-file
Make sure your archive expands into a single project directory and does not depend on files elsewhere on your computer.

Suggested Development Order
Study the grammar and trace the starter parser on the sample input.
Extend the token representation and tokenizer.
Test tokenization before changing the expression parser.
Implement and test relational parsing and evaluation.
Implement and test print statements.
Implement and test for statements.
Add nested-loop and malformed-input tests.
Clean the project directory and verify a fresh command-line build before creating the ZIP archive.
Copy the ZIP file to Blue, extract it into a clean directory, and verify that it builds and runs successfully there.
