
froe, Scheme interpreter
因为之前看过了天弋娘的代码, 又很喜欢他那优美的码风, 不知不觉就按他的框架来写了.




有了大致的雏形

TODO : 
	[*] 引入empty '()			//话说'()到底是何物我已经忘记了
	[*] 现在基本类型还只有int, 之后要引入复数, string






Situation : 
	[*] 实现里面list并不是pair衍生出来的常物, 所以很多处理代码都要分list和pair两种情况,
		可list和pair的本质联系我已经不太清楚了, 等这两天拿回SICP再复习一下, 清楚了之后
		把list和pair统一一下

		//"表面上"实现了统一, 不过内部实现里面list和pair还是两种结构.
		//可以通过(cons x (list 1 2 3))-->(list x 1 2 3)
	
