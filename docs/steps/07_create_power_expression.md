


```antlrv4
<assoc=right> base=expression '^' pow=expression    #powerExpression
```

With right association if we have ```3^4^2``` will be evaluated from right to left precedence like ```3^(4^2)``` instead of ```(3^4)^2```.
