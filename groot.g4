grammar groot;
prog: (statement)* EOF  #program;

statement: assignment EOL
           | returnstmt EOL
           | ifstatement
           | whileloop
           | funcdefstmt
           | importStatement EOL
           | expression EOL
           ;

importStatement: 'import' name=IMPORT_PATH ('as' alias=IDENTIFIER)?;

funcdefstmt: ftype=('native'|'function') name=IDENTIFIER '(' (IDENTIFIER (',' IDENTIFIER)*)? ')' (EOL| blk=block)  #functionDefStatement;

whileloop: 'while' '(' cond=expression ')' blk=block;

ifstatement: ifblk=ifblock elseblk=elseblock?                                               #ifStatement;

ifblock: 'if' '(' cond=expression ')' blk=block;
elseblock: 'else' (b=block|ib=ifblock);

block: '{' (statement)* '}';

returnstmt: 'return' expr=expression                                                        #returnStatement;
assignment: var_name=IDENTIFIER '=' expr=expression                                              #assignmentStatement;

expression: op=(NEG|NOT) expr=expression                                                    #unaryOperationExpression
    | <assoc=right> base=expression '^' pow=expression                                      #powerExpression
    | left=expression op=('*'|'/') right=expression                                         #mulDivExpression
    | left=expression op=('+'|'-') right=expression                                         #addSubExpression
    | left=expression op=(GT|GE|LT|LE) right=expression                                     #numericComparisonExpression
    | left=expression op=(EQ|NE) right=expression                                           #equalityCheckExpression
    | '(' expr=expression ')'                                                               #prenEnclosedExpression
    | '[' (expression ( ',' expression )*)? ']'                                             #listValueExpression
    | var_name=expression ('[' idx=expression ']')                                               #itemAtIndexExpression
    | name=IDENTIFIER '(' (expression (',' expression)*)? ')'                               #functionCallExpression
    | atom=(INTEGER | BOOLEAN | CHARACTER | STRING | IDENTIFIER)                            #atomicValueExpression
    ;

INTEGER: [0-9]+ ;
BOOLEAN: 'true' | 'false';
STRING: ["] ( ~["\r\n\\] | '\\' ~[\r\n] )* ["];
CHARACTER: ['](~['\\] | '\\'['] )['];
IDENTIFIER: [a-zA-Z_] [a-zA-Z_0-9]*;
IMPORT_PATH: [a-zA-Z_] [a-zA-Z_0-9.]*;

GT: '>';
GE: '>=';
LT: '<';
LE: '<=';

EQ: '==';
NE: '!=';
NEG: '-';
NOT: '!';

EOL: ';';

WHITESPACE: [ \f\t\r\n] -> skip;
