
```antlrv4
funcdefstmt: ftype=('native'|'function') name=IDENTIFIER '(' (IDENTIFIER (',' IDENTIFIER)*)? ')' (EOL|blk=block)  #functionDefStatement;
```

