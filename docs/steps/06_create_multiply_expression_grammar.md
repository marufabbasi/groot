

```antlrv4
left=expression op=('*'|'/') right=expression                                         #mulDivExpression
```

This rule must be before the add rule so that multiplication gets precedence to addition.