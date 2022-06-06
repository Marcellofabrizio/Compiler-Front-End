#include <string>

typedef enum
{
    LexicalError = -1,
    EndOfFile = 0,
    ReservedWord,
    Identifier,
    IntegerConstant,
    FloatingPointConstant,

    Plus,      // +
    Minus,     // -
    Product,   // *
    Division,  // /
    Power,     // ˆ
    Increment, // ++
    Decrement, // --
    Module,    // %

    Equals,         // ==
    NotEquals,      // !=
    Less,           // <
    Greater,        // >
    LessOrEqual,    // <=
    GreaterOrEqual, // >=
    LogicalAnd,     // &&
    LogicalOr,      // ||
    LogicalNot,     // !

    ShiftLeft,  // <<
    ShiftRight, // >>
    And,        // &
    Or,         // |

    Assign,         // =
    PlusAssign,     // +=
    MinusAssign,    // -=
    ProductAssign,  // *=
    DivisionAssign, // /=
    ModuleAssign,   // %=

    For,      // for
    DoWhile,  // do {} while
    While,    // while
    If,       // if
    ElseIf,   // else if
    Else,     // else
    Continue, // continue
    Break,    // break
    Return,   // return
    Try,      // try
    Except,   // except

    Switch,  // switch
    Case,    // case
    Default, // default

    Int,    // int
    Char,   // char
    Double, // double
    Float,  // float
    Struct, // struct
    Void,   // void
    Null,   // null
    Const,  // const

    Pointer,  // pointer
    Accessor, // ->

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
    BraceClose
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
    {"void", Void},
    {"char", Char},
    {"const", Const}
};