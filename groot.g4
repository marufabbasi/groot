grammar groot;
prog: expr=expression EOL  #program;

expression:	left=expression op=('*'|'/') right=expression    #mulDivExpression
    | 	left=expression op=('+'|'-') right=expression        #addSubExpression
    | '(' expr=expression ')'                                #prenEnclosedExpression
    | INTEGER                                                #atomicValueExpression
    ;

NEWLINE : [\r\n]+ ;
INTEGER     : [0-9]+ ;
EOL: ';';
WHITESPACE: [ \t\r\nu000c] -> skip;