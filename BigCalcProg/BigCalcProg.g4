grammar BigCalcProg;

program
    : statement + EOF
    ;

statement
    : assigmentStatement
    | expressionStatement
    ;

assigmentStatement
    : variable '=' expression ';'
    ;

expressionStatement
        : expression ';'
        ;

expression
        : expression op=('*' | '/') expression  # mulDiv
        | expression op=('+' | '-') expression  # addSub
        | '(' expression ')'                    # parenExpr
        | Number                                # num
        | variable                              # var
        | expression '?' expression ':' expression # ternary
        ;

variable
    :   VARIABLE
    ;


// Lexer riles
VARIABLE
    :[a-zA-Z] [a-zA-Z0-9]*
    ;

// From BigCalc
Number
        : Digit* '.' Digit+ (ExponentPart)?
        | Digit+ (ExponentPart)?
        ;

ExponentPart
    : [eE] [+\-]? Digit+
    ;

Digit
        : [0-9]
        ;

WS      : [ \t\r\n\u000C]+ -> skip
        ;

COMMENT
        :   '/*' .*? '*/' -> skip
        ;

LINE_COMMENT
        : '//' ~[\r\n]* -> skip
        ;