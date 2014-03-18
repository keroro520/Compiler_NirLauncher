# simple scheme lexer
from test import *

INTEGER  = 1
FLOAT    = 2
STRING   = 3
VARIABLE = 3
KEYWORD  = 10
OPERATOR = 20
keywords_list  = ['define', 'if', 'cond', ')', '(']
operators_list = [ '+', '-', '*', '/', '=', '>', '>=', '<', '<=']

class Token () :
	def __init__(self, _t, _n) :
		self.t = _t
		self.n = _n
	def toString (self) :
		return "Fs"
def get_type(token) :
	if token in keywords_list :
		return Token(KEYWORD, token)
	elif token in operators_list :
		return Token(OPERATOR, token)
	else :
		try :
			num = (int)(token)
			return Token(INTEGER, num)
		except :
			try : 
				num = (float)(token)
				return Token(FLOAT, num)
			except :
				if token[0] == "\"" and token[-1] == "\"" :	
					return Token(STRING,   token)
				else : 
					return Token(VARIABLE, token) 

tokens = map(get_type, raw_input().replace(')', ' ) ').replace('(', ' ( ').split())
# for i in tokens : print(i.t, i.n)
l = lex(tokens)
print(l)
