An operator with only one operand is called unary operator. Examples are ```-``` for numeric operand and ```!``` for boolean operand etc.


```antlrv4
op=(NEG|NOT) expr=expression    #unaryOperationExpression

NEG: '-';
NOT: '!';
```
