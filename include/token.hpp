#ifndef TOKEN
#define TOKEN

#include <string>

typedef enum
{
    LexicalError = -1,
    EndOfFile = 0,
    Identifier,
    Constant,
    CharConstant,
    Plus,             // +
    Minus,            // -
    Product,          // *
    Division,         // /
    Power,            // ˆ
    IncOp,            // ++
    DecOp,            // --
    Module,           // %
    LeftOp,           // <<
    RightOp,          // >>
    EQOp,             // ==
    NEOp,             // !=
    Less,             // <
    Greater,          // >
    LEOp,             // <=
    GEOp,             // >=
    Negate,           // ~
    LogicalAnd,       // &&
    LogicalOr,        // ||
    LogicalNot,       // !
    AndOp,            // &
    OrOp,             // |
    Assign,           // =
    AddAssign,        // +=
    LessAssign,       // -=
    MulAssign,        // *=
    DivAssign,        // /=
    ModAssign,        // %=
    LeftAssign,       // >>=
    RightAssign,      // <<=
    For,              // for
    Do,               // do
    While,            // while
    If,               // if
    Else,             // else
    ElseIf,           // else if
    Continue,         // continue
    Break,            // break
    Return,           // return
    Try,              // try
    Except,           // except
    Switch,           // switch
    Case,             // case
    Default,          // default
    Int,              // int
    Signed,           // signed
    Unsigned,         // unsigned
    Char,             // char
    Double,           // double
    Short,            // short
    Long,             // long
    Float,            // float
    Struct,           // struct
    Void,             // void
    Null,             // null
    Const,            // const
    Accessor,         // -> / .
    Underscore,       // _
    Dot,              // .
    Comma,            // ,
    SemiCollon,       // ;
    Collon,           // :
    ParenthesisOpen,  // (
    ParenthesisClose, // )
    BracketOpen,      // [
    BracketClose,     // ]
    BraceOpen,        // {
    BraceClose,       // }
    QuestionMark,     // ?
    Colon,            // :
    Ellipsis,         // ...

} TokenType;

typedef struct
{
    std::string value;
    TokenType types;
} Token;

#endif