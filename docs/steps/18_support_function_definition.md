


```antlrv4
funcdefstmt: 'function' name=IDENTIFIER '(' (IDENTIFIER (',' IDENTIFIER)*)? ')' (EOL| blk=block)  #functionDefStatement;
```
