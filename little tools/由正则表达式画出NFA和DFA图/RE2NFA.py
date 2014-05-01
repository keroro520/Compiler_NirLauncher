# -*- coding: utf-8 -*
# 输入正则表达式
# 输出dot.dot，还有NFA图test.png
# 需求：需要安装Graphviz


import os

global null
global point_num
global edge

null = '@'
point_num = 0
edge = set()

def new_point() :
    global point_num
    point_num = point_num + 1
    return point_num

def add_edge(u, v, z) :
    edge.add( (u,v,z) )

def Cat(start, end, p, q, ch) :
    ''' Operation : cat '''
    add_edge(end, p, ch)
    return (start, q)

def Union(super_start, super_end, start, end, ch) :
    ''' Operation : OR '''
    add_edge(super_start, start, ch)
    add_edge(end, super_end, ch)

def merge_point(a, b) : 
    ''' merge point a and point b as one point '''
    for (x, y, z) in edge :
        if x == b :
            add_edge(a, y, z)
            edge.discard((x, y, z))
    return a

def findBraket(s) :
    ''' find the corresponding rbracket , and return the index'''
    sum, i = -1, 0
    while sum != 0 :
        if s[i] == '(' : sum = sum - 1
        elif s[i] == ')' : sum = sum + 1
        i = i + 1
    return i

def findORorEND(s) :
    ''' divide the regular expression s into ORs'''
    sum, i = 0, 0
    while i < len(s) :
        if   s[i] == '(' : sum = sum - 1
        elif s[i] == ')' : sum = sum + 1
        elif s[i] == '|' and sum == 0 : return i
        i = i + 1
    return len(s)

def take_over(freshman, oldman) :
    for (x, y, z) in edge :
        if y == oldman :
            add_edge(x, freshman, z)
            edge.discard((x,y,z))

def Star(p1, p2, pre, now) :
    #所有指向pre的都由p1接管
    take_over(p1, pre)
    add_edge(p1, pre, null)
    add_edge(now, p2, null)
    add_edge(p1,  p2, null)
    add_edge(now, pre, null)
    return (p1, p2)

def func(s) :
    super_start, super_end = -1, -1
    now = new_point()
    start, pre = now, now
    i, l = 0, len(s)
    while i < l :
        ch = s[i]
        if ch == '(' :
            r = i + findBraket(s[i+1:])
            boy = func(s[i+1:r])
            #else : _, now = Cat(now, now, boy[0], boy[1], null)
            pre = now
            now = merge_point(now, boy[0])
            if i == 0 : start = now
            now = boy[1]
            i = r + 1
        elif ch == '|' : 
            super_start, super_end = new_point(), new_point()

            Union(super_start, super_end, start, now, null)

            i = i + 1
            while i < l :
                r = i + findORorEND(s[i:])
                girl = func(s[i:r])
                Union(super_start, super_end, girl[0], girl[1], null)
                i = r + 1
        elif ch == '*' :
            p1, p2 = new_point(), new_point()
            if pre == start : 
                pre, now = Star(p1, p2, pre, now)
                start = pre
            else :
                pre, now = Star(p1, p2, pre, now)
                
            i = i + 1
        else :
            p = new_point()
            pre = now
            _, now = Cat(now, now, p, p, ch)
            i = i + 1

    if super_start != -1 : return (super_start, super_end)
    else : return (start, now)

def output() :
    f = file('nfa.dot', 'w')
    print >> f, 'digraph {'
    print >> f, 'rankdir = LR'

    global edge
    edge = list(edge)
    edge.sort()
    for (s,t,c) in edge : 
        if c == '@' : c = ' '
        print >> f , str(s) + "->" + str(t) + '[label="' + str(c) + '"]'
    print >> f, '}'
    f.close()
    os.system('dot -T png  -o nfa.png nfa.dot')

def main() : 
    s = raw_input().replace(' ', '').replace('\t', '')
    func(s)
    output()

#if '__main__' == __name__ : 
#    main()
main()
