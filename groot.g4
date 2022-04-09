grammar groot;
prog: (assignment EOL NEWLINE?| returnstmt EOL NEWLINE?)* EOF  #program;


returnstmt: 'return' expr=expression                                                        #returnStatement;
assignment: var=IDENTIFIER '=' expr=expression                                              #assignmentStatement;

expression:	left=expression op=('*'|'/') right=expression                                   #mulDivExpression
    | left=expression op=('+'|'-') right=expression                                         #addSubExpression
    | left=expression op=(GT|GE|LT|LE) right=expression                                     #numericComparisonExpression
    | left=expression op=(EQ|NE) right=expression                                           #equalityCheckExpression
    | '(' expr=expression ')'                                                               #prenEnclosedExpression
    | atom=(INTEGER | BOOLEAN | STRING | IDENTIFIER)                                        #atomicValueExpression
    ;

NEWLINE: [\r\n]+ ;
INTEGER: [0-9]+ ;
BOOLEAN: 'true' | 'false';
STRING: ["] ( ~["\r\n\\] | '\\' ~[\r\n] )* ["];

IDENTIFIER: [a-zA-Z_] [a-zA-Z_0-9]*;

GT: '>';
GE: '>=';
LT: '<';
LE: '<=';

EQ: '==';
NE: '!=';

EOL: ';';


WHITESPACE: [ \t\r\n\u000c] -> skip;