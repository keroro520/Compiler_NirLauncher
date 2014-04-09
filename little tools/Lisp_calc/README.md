define, 
+,-,*,\
<,<=,>,>=,
and,or
if
print

$ antlr4 -no-listener -visitor Expr.g && javac Expr*.java EvalVisitor.java Calc.java  && java Calc < input
