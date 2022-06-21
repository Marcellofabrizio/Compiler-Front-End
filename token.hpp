#include <string>

typedef enum
{
    LexicalError = -1,
    EndOfFile = 0,
    Keyword,
    Identifier,
    Constant,
    Plus,             // +
    Minus,            // -
    Product,          // *
    Division,         // /
    Power,            // ˆ
    Increment,        // ++
    IncOp,            // ++
    Decrement,        // --
    DecOp,            // --
    Module,           // %
    LeftOp,           // <<
    RightOp,          // >>
    EQOp,             // ==
    NEOp,             // !=
    Less,             // <
    Greater,          // >
    LessOrEqual,      // <=
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
    Pointer,          // pointer
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

Token keywords[] = {
    {"NULL", Null},
    {"printf", Identifier},
    {"scanf", Identifier},
    {"ident", Identifier},
    {"if", If},
    {"else if", ElseIf},
    {"else", Else},
    {"while", While},
    {"for", For},
    {"break", Break},
    {"continue", Continue},
    {"return", Return},
    {"try", Try},
    {"except", Except},
    {"int", Int},
    {"float", Float},
    {"short", Short},
    {"long", Long},
    {"signed", Signed},
    {"unsigned", Unsigned},
    {"void", Void},
    {"char", Char},
    {"const", Const},
    {"Struct", Struct},
    {"Double", Double},
    {"switch", Switch},
    {"case", Case},
    {"default", Default}};