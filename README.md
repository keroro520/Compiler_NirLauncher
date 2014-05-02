
froe, Scheme interpreter
因为之前看过了天弋娘的代码, 又很喜欢他那优美的码风, 不知不觉就按他的框架来写了.




有了大致的雏形

TODO : 






Situation : 
	[*] 实现里面list并不是pair衍生出来的常物, 所以很多处理代码都要分list和pair两种情况,
		可list和pair的本质联系我已经不太清楚了, 等这两天拿回SICP再复习一下, 清楚了之后
		把list和pair统一一下

		//"表面上"实现了统一, 不过内部实现里面list和pair还是两种结构.
		//可以通过(cons x (list 1 2 3))-->(list x 1 2 3)
	
	[*] 引入nil '()
		应该是引入了~ '()是空list, 用一个全局变量nil表示

	[*] 因为真正的define无法实现, 所以实际上set!跟define一样了...就不实现set!了
