### Language grammar

For our programming language we need to define its syntax by designing a grammar which is the formal language description. 
Tools are usually used to create a set of components called lexer or tokenizer, parser etc. We are going to use a tool named ```antlr``` 
specifically its version 4 that is named ```antlr4```. This tool will generate code that will allow us to load  a source file and 
generate a parse tree from that source code. Antlr4 will also generate a ```visitor``` that we can use to traverse through the 
parse tree and interpret the program along the way of going through the tree nodes.

In antlr4 grammar is defined in grammar file usually with an extension```g4`` and the filename follows the name of the grammar.

Example grammar from https://www.antlr.org/: 

```antlrv4
grammar Expr;		
prog:	(expr NEWLINE)* ;
expr:	expr ('*'|'/') expr
    |	expr ('+'|'-') expr
    |	INT
    |	'(' expr ')'
    ;
NEWLINE : [\r\n]+ ;
INT     : [0-9]+ ;
```

If we use input like ```(300+500)\n``` we get following parse tree:

![Parse tree](images/expr.png)


### Create aliases
For easily accessing the antlr tool lets prepare our system.

First copy ```antlr-4.9.3-complete.jar``` file to ```/usr/local/lib/``` directory and then  append following to your bash 
configuration file ( ~/.bashrc file)

```shell
export CLASSPATH=".:/usr/local/lib/antlr-4.9.3-complete.jar:$CLASSPATH"
alias antlr4='java -jar /usr/local/lib/antlr-4.9.3-complete.jar'
alias grun='java org.antlr.v4.gui.TestRig'
```

Now you will be able to use ```antlr4``` and ```grun``` command from bash shell.

### Generating parser

Antlr takes the grammar file and generates lexer/parser and a set of helper classes like listeners or visitors. We will be directly executing each source line / block.
For that visitor is suitable and we do not need listeners. The options ```-visitor``` and ```-no-listener``` will instruct antlr to create visitor but 
no listener.

We will be using C++ which is not the default language. So we need to use option ```-Dlanguage=Cpp```. And finally ```-o <directory_name>``` instructs antlr 
where to generate the lexer/parser/visitor and other files. So, we need to use following command for generating our required classes:

```shell
antlr4 -Dlanguage=Cpp -o parser -no-listener -visitor groot.g4
```

This will generate the lexer, parser and visitor for the grammar defined. These are the file names those are generated in the ```parser``` directory:

```shell
grootBaseVisitor.cpp  
grootBaseVisitor.h  
groot.interp  
grootLexer.cpp  
grootLexer.h  
grootLexer.interp  
grootLexer.tokens  
grootParser.cpp  
grootParser.h  
groot.tokens  
grootVisitor.cpp  
grootVisitor.h 
```

