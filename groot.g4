grammar groot;
prog: expr=expression EOL  #program;

expression:	left=expression op=('*'|'/') right=expression    #mulDivExpression
    | 	left=expression op=('+'|'-') right=expression        #addSubExpression
    | '(' expr=expression ')'                                #prenEnclosedExpression
    | atom=(INTEGER | BOOLEAN)                               #atomicValueExpression
    ;

NEWLINE: [\r\n]+ ;
INTEGER: [0-9]+ ;
BOOLEAN: 'true' | 'false';
EOL: ';';
WHITESPACE: [ \t\r\n\u000c] -> skip;