grammar groot;
prog: (expression EOL | returnstmt EOL)* EOF  #program;

returnstmt: 'return' expr=expression                                                        #returnStatement;

expression:	left=expression op=('*'|'/') right=expression                                   #mulDivExpression
    | left=expression op=('+'|'-') right=expression                                         #addSubExpression
    | left=expression op=(GT|GE|LT|LE) right=expression                                     #numericComparisonExpression
    | left=expression op=(EQ|NE) right=expression                                           #equalityCheckExpression
    | '(' expr=expression ')'                                                               #prenEnclosedExpression
    | atom=(INTEGER | BOOLEAN | STRING)                                                     #atomicValueExpression
    ;

NEWLINE: [\r\n]+ ;
INTEGER: [0-9]+ ;
BOOLEAN: 'true' | 'false';
STRING: ["] ( ~["\r\n\\] | '\\' ~[\r\n] )* ["];

GT: '>';
GE: '>=';
LT: '<';
LE: '<=';

EQ: '==';
NE: '!=';

EOL: ';';


WHITESPACE: [ \t\r\n\u000c] -> skip;