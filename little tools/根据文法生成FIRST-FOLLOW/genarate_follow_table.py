# -*- coding: utf-8 -*
# 输入格式在genarate_first.table.py有说明
# 这个文件是生出follow的
from genarate_first_table import *

def couldBeNull(production) :
    for ch in production : 
        if not ('@' in first[ch]) : return False
    return True

def update_follow(X) :
    if visit[ord(X)] or color[ord(X)] : return 
    
    color[ord(X)] = True
    for ch in edge[X] :
        update_follow(ch)
        follow[X].update(follow[ch])

edge, follow = {}, {}
for i in range(0, 256) :
    ch = chr(i)
    if not isTerminalSymbol(ch) : edge[ch], follow[ch] = set(), set()
follow[S] = set('$')

for production in grammers :
    A = production[0]
    for i in range(3, len(production)) :
        B = production[i]
        if not isTerminalSymbol(B) :
            if i != len(production) - 1 :
                y = production[i+1]
                follow[B].update(first[y])

            if i == len(production) - 1 or \
                (production[i+1].isupper() and couldBeNull(production[i+1:])) :
                    edge[B].add(A)

visit = [False] * 256
for X in nonterminal :
    global color
    color = [False] * 256
    update_follow(X)
    visit[ord(X)] = True

#for X in nonterminal : print 'follow(' + X + ') = ', follow[X]
