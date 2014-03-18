# -*- coding: utf-8 -*
# 输入文件grammer.txt包含LL(1)文法
# 输出first(X)，X是非终结符
# 约定：大写字母表示非终结符，其他表示终结符，空用@表示
#       输入的都是合法的LL(1)文法，一个产生式一行

# 算法：其实要追求低复杂度的话可以先缩点成树再扫一遍就可以了，这里没有这么实现，而是
#       暴力搜。对于每个X都搜一遍，得出该X的完整first。visit[y]=True的话说明之前已经
#       得出了X的完整X了，不用再继续下去了

def isTerminalSymbol(ch) :
    return not ('A' <= ch and ch <= 'Z')

def update_null(X) :
    if visit[ord(X)] : return first[X]
    
    visit[ord(X)] = True
    for l in edge[X] :
        for i in range(len(l)) :
            ch = l[i]
            if not visit[ord(ch)] : first[ch].update(update_null(ch))
            if not ('@' in first[ch]) : 
                break
            elif i == len(l) - 1 : 
                return set('@')
            
    return set()

def update_first(X) :
    if visit[ord(X)] or color[ord(X)]: return 
    
    color[ord(X)] = True
    for ch in edge[X] :
        update_first(ch)
        first[X].update(first[ch])

grammers, first, visit, edge, nonterminal = [], {}, [False]*256, {}, set()
S = ''
for i in range(0, 256) :
    ch = chr(i)
    if isTerminalSymbol(ch) : first[ch] = set(ch)
    else : first[ch], edge[ch] = set(), set()

for production in open('grammer.txt') :
    production = production.replace(' ', '')[:-1]
    if not production : continue

    X = production[0]
    nonterminal.add(X)
    if S == '' : S = X

    if production[1:] == '->@' : visit[ord(X)], first[X] = True, set('@')
    else : grammers.append( production )

    if production[3:].isalpha() and production[3:].isupper() : edge[X].add(production[3:])      #该串都是非终结符

for production in grammers :        #预处理好first包含@的部分
    X = production[0]
    if not visit[ord(X)] :
        first[X].update(update_null(X))

# 如果first(X) ∈ first(Y)，则把连边X->Y。更新first的过程就是BFS遍历过程

edge, edge_inv = {}, {}
for i in range(ord('A'), ord('Z')+1) :
    ch = chr(i)
    edge[ch], edge_inv[ch] = set(), set()

for production in grammers :
    X = production[0]
    for ch in production[3:] :
        if isTerminalSymbol(ch) : first[X].add(ch)
        else : edge[X].add(ch)
        if not ('@' in first[ch]) : break

visit = [False] * 256
for X in nonterminal : 
    global color
    color = [False] * 256
    update_first(X)
    visit[ord(X)] = True


#for X in nonterminal : print 'first('+X+') = ' , first[X]
