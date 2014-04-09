grammar Expr ;

prog : (expr|condition|print)+ ;
condition : cond | iif;
expr : arithmetic 
	 | comparison
	 | logical
	 | assign 
	 | id	
	 | iint
	 ;
args : expr	
	 | condition
	 ;

arithmetic : '(' ARITHMETIC_OPERATOR args args+ ')' ;
comparison : '(' COMPARISON_OPERATOR args args+ ')' ;
logical    : '(' iand                args args+ ')' #and
		   | '(' ior 				 args args+ ')'	#or
		   ;
assign     : '(' define ID args ')' ;
iif        : '(' iiif expr expr expr? ')' 			#if
		   ;
cond 	   : '(' icond ('(' expr expr ')')+ ( '(' 'else' expr ')' )? ')'
		   ;
print	   : '(' 'print' args* ')'
		   ;

define : 'define' ;	
iiif : 'if' ;
icond: 'cond' ;
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
