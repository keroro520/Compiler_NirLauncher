# -*- coding: utf-8 -*
# 输入文件grammer.txt包含LL(1)文法
# 输出first(X)，follow(X)X是非终结符
# 约定：大写字母表示非终结符，其他表示终结符，空用@表示
#       输入的都是合法的LL(1)文法，一个产生式一行，即如果有 | 的话要分成几个产生式
#       样例就看grammer.txt吧...
from genarate_follow_table import *

for X in nonterminal :
    follow[X].discard('@')
    print 'first(' + X + ') = ', first[X], '\t\t', 'follow(' + X + ') = ', follow[X]
