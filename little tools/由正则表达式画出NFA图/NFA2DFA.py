from RE2NFA import *

global edge
global e
global start_point
global end_point

ops = 'qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM`1234567890-=~!#$%^&*()_+[]\\;,\./{}|:"<>?'


def dfa_output(stats, edge) :
	f = file('dfa.dot', 'w')
	print >> f, 'digraph {'
	print >> f, 'rankdir = LR'

	edge = list(edge)
	edge.sort()

	global end_point
	for (_,t,_) in edge :
		if end_point in stats[t] : print >> f, t , '[shape = doublecircle]'

	for (s,t,c) in edge : 
		if c == '@' : c = ' '
		print >> f , str(s) + "->" + str(t) + '[label="' + str(c) + '"]'
	print >> f, '}'
	f.close()
	os.system('dot -T png  -o dfa.png dfa.dot')

	
def dfs(p, c, ans) :
	if not (p in e) : return ans

	for (_,t,ch) in e[p] :
		if t in ans : continue
		if ch == c : 
			ans.add(t)
			ans.update( dfs(t,null,ans) )
		if ch == null :
			ans.update( dfs(t,c,ans) )

	return ans


e = dict()
def find_start_stat() :
	d = dict()
	for (s, t, c) in edge : 
		if t in d : d[t] = d[t] + 1
		else : d[t] = 1
		if not (s in e) : e[s] = [(s,t,c)]
		else : e[s].append((s,t,c))

	global start_point
	global end_point
	for (s, t, _) in edge :
		if not (s in d) : 
			start_point = s
		if not (t in e) :
			end_point = t

	return	dfs(start_point, null, set()) 


def main() :
	stats = [find_start_stat()]
	edge = set()
	for stat in stats :
		for c in ops : 
			new_stat = set()
			for s in stat :
				new_stat.update( dfs(s,c,set()) )
			if new_stat == set() : continue
			if not (new_stat in stats) : stats.append(new_stat)
			i1, i2 = stats.index(stat), stats.index(new_stat)
			edge.add( (i1,i2,c) )

	dfa_output(stats, edge)


if '__main__' == __name__ :
	main()
