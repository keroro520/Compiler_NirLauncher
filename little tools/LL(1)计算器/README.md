#### 运算器

* 只能是数字的四则运算, 没有实现变量, 一次只能算一个表达式.

* [语法](file:///root/data/Froe/froe/tmp/grammar.g) :

	E : T E'

	E': + T E' | - T E' | ε

	T : F T'

	T': * F T' | / F T' | ε

	F : ( E )  | id | number

* [预测分析表](file:///root/data/Froe/froe/tmp/预测分析表.jpg)

  ![](file:///root/data/Froe/froe/tmp/预测分析表.jpg)
