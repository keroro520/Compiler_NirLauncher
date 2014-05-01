
froe, Scheme interpreter
因为之前看过了天弋娘的代码, 又很喜欢他那优美的码风, 不知不觉就按他的框架来写了.




有了大致的雏形

TODO : 
	[*] 实现里面list并不是pair衍生出来的常物, 所以很多处理代码都要分list和pair两种情况,
		可list和pair的本质联系我已经不太清楚了, 等这两天拿回SICP再复习一下, 清楚了之后
		把list和pair统一一下
	[*] lambda虽然实现了, 但还不能使用, 先暂且用define吧.
		(话说如此, define不是lambda的语法糖么=_=  有define没lambda会不会被Church诅咒)
	[*] 现在基本类型还只有int, 之后要引入复数, string
