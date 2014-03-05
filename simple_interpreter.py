class Env(dict) :
	def __init__(self, parms = (), args = (), outer = None) :
		self.update( zip(parms, args) )
		self.outer = outer
	def find(self, var) :
		return self if var in self else self.outer.find(var)

def add_globals_env(env) :
	import math, operator as op
	env.update( vars(math) )
	env.update(
		{'+' : op.add, '-' : op.sub, '*':op.mul, '/':op.div, 'not':op.not_,
		 '>':op.gt, '<':op.lt, '>=':op.ge, '<=':op.le, '=':op.eq, 
		 'equal?':op.eq, 'eq?':op.is_, 'length':len, 'cons':lambda x,y:[x]+y,
		 'car':lambda x:x[0],'cdr':lambda x:x[1:], 'append':op.add,  
		 'list':lambda *x:list(x), 'list?': lambda x:isa(x,list), 
		 'null?':lambda x:x==[], 'symbol?':lambda x: isa(x, Symbol),
		 'exit' : exit}) 
	return env

global_env = add_globals_env(Env())

def eval(x, env = global_env) :
	if isinstance(x, Symbol) :
		return env.find(x)[x]
	elif not isinstance(x, list) :
		return x
	elif x[0] == 'quote' :
		(_, exp) = x
		return exp
	elif x[0] == 'if' :
		(_, test, conseq, alt) = x
		return eval( (conseq if eval(test, env) else alt) , env)
	elif x[0] == 'set!' :
		(_, var, val) = x
		env.find(var)[var] = eval(val, env)
	elif x[0] == 'define' : 
		(_, var, val) = x
		env[var] = eval(val, env)
	elif x[0] == 'lambda' :
		(_, vars, exp) = x
		return lambda *args : eval(exp, Env(vars, args, env))		## cool ! but I don't really understand
	elif x[0] == 'begin' :
		for exp in x[1:] :
			val = eval(exp, env)
		return val
	else :	# function call
		exps = [eval(exp, env) for exp in x]
		proc = exps.pop(0)
		return proc(*exps)

def atom(token) :
	try :
		return (int) (token)
	except ValueError :
		try :
			return (float) (token)
		except ValueError :
			return Symbol(token)
	
def tokenize(s) :
	return s.replace('(', ' ( ').replace(')', ' ) ').split()

def read_from(tokens) :
	if len(tokens) == 0 :
		raise SyntaxError('unexpected EOF while reading')
	token = tokens.pop(0)
	if token == '(' :
		L = []
		while tokens[0] != ')' :
			L.append( read_from(tokens) )
		tokens.pop(0)
		return L
	elif token == ')' :
		raise SyntaxError('unexpected ")"')
	else :
		return atom(token)

def read(s) :
	return read_from( tokenize(s) )

parse = read
Symbol = str

def to_string(exp) :
	return '(' + ' '.join(map(to_string, exp)) + ')' if isinstance(exp, list) else str(exp)
def repl(prompt = '>>>') :
	while True :
		print prompt, 
		val = eval(parse(raw_input()), global_env)
		if val is not None : print( to_string(val) )

repl()
