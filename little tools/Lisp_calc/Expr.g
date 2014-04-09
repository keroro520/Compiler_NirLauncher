grammar Expr ;

prog : expr+ ;
expr : arithmetic 
	 | assign 
	 | id	
	 | iint
	 ;
args : iint
	 | id
	 | expr	
	 ;

arithmetic : '(' OPERATOR args args ')' ;
assign : '(' define ID expr ')' ;
define : 'define' ;	
id : ID ;
iint : INT 		#int
	 ;

ID  : [a-zA-Z]+ ;
INT : [0-9]+;			
WS  : [ \t\r\n]+	-> 	skip ;
OPERATOR : ADD
		 | SUB
		 | MUL
		 | DIV
		 ;
ADD : '+' ;
SUB : '-' ;
MUL : '*' ;
DIV : '\\'; 
