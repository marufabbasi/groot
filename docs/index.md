# groot
Groot programming language

![groot](images/groot.png)


Groot is a "Turing Complete" programming language written in C++ aimed to be used as a learning tool for students of 
Compiler Construction in Computer Science curriculum.

## Example Program

```js
function sub(p,q)
{
    return p-q;
}

function add(a,b)
{
    return a+b;
}

s="hello";
c='A';
d=s[1];
l = [1,2,3,[4, 5, 6], 7];
l2 = l[3];
l3 = l2[1];
x = l3 * 4 - 13;

y=1;

while(y<7)
{
    y=y+1;
}

p=add(x,y);
q=2 + x * 2;
r = sub(p,q);

if (r<0)
{
    return -r;
}
else
{
    return r;
}
```