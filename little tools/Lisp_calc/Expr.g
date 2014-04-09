grammar Expr ;

prog : (expr|print)+ ;
expr : arithmetic 
	 | comparison
	 | logical
	 | assign 
	 | iif
	 | id	
	 | iint
	 ;
args : iint
	 | id
	 | expr	
	 ;

arithmetic : '(' ARITHMETIC_OPERATOR args args ')' ;
comparison : '(' COMPARISON_OPERATOR args args ')' ;
logical    : '(' iand                 args args ')' #and
		   | '(' ior 				 args args ')'	#or
		   ;
assign     : '(' define ID expr ')' ;
iif        : '(' 'if' expr expr expr ')' 			#if
		   ;
print	   : '(' 'print' args* ')'
		   ;

define : 'define' ;	
id : ID ;
iint : INT 		#int
	 ;
iand : 'and' ; 
ior  : 'or'  ;

ID  : [a-zA-Z]+ ;
INT : [0-9]+;			
WS  : [ \t\r\n]+	-> 	skip ;
ARITHMETIC_OPERATOR : ADD
		 		    | SUB
		 		    | MUL
		 		    | DIV
		 			;
COMPARISON_OPERATOR : EQ
					| GT
					| GE
					| LT
					| LE
					;
ADD : '+' ;
SUB : '-' ;
MUL : '*' ;
DIV : '\\'; 
EQ  : '==';
GT  : '>' ;
GE  : '>=';
LT  : '<' ;
LE  : '<=';
