%{
	/* definition of manifest constant */	
	int _LINE_ = 0;
	enum {
		LT = 10,
		LE = 11,
		EQ = 12,
		NE = 13,
		GT = 14,
		GE = 15,

		
		ID = 40,
		NUMBER = 41,
		RELOP  = 42,

		IF = 2,
		THEN = 3,
		ELSE = 4,
		WHILE = 5
	};
%}

/* regular expression */
delim 		[ \t\n]
ws			{delim}+
letter		[a-zA-Z]
digit		[0-9]
id			({letter}|_)?(_|{letter}|{digit})*
number		{digit}+(\.{digit}+)?(E[+-]?{digit}+)?
string 		\"\"
%%
	
{delim}		{ }
{ws}		{ }
if			{ return (IF);   }
then		{ return (THEN); }
else 		{ return (ELSE); }
while		{ return (WHILE);}
{id}		{ /*yy1val = (int) installID(); */ return (ID);     }
{number}	{ /*yy1val = (int) installNum();*/ return (NUMBER); }
"<"			{ /*yy1val = LT; */return (RELOP); }
"<="		{ /*yy1val = LE; */return (RELOP); }
">"			{ /*yy1val = GT; */return (RELOP); }
">="		{ /*yy1val = GE; */return (RELOP); }
"="			{ /*yy1val = EQ; */return (RELOP); }
"!="		{ /*yy1val = NE; */return (RELOP); }
%%

int installID() {
	printf("!\n");
	return 0;
}

int installNum() {
	return 0;
}

int yywrap() {
    return 1;
}
int main()
{
	int i = 0;
    while(i++ < 20) {
		printf("%d  %d\t", yylex(), yylineno), printf("!%s \n", yytext);
	}	
    printf("hello world !\n");

    return 0;
}
