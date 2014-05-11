### DAG IR
* 学习目的 : DAG作为IR
 
* 语法存在grammar.txt里面.  输入串在为stdin

* 格式为 :
	
	* expr ; expr

	* 而赋值语句要多加一个分号在后面, 如: a = 1 + 2 ; 末尾不要多加分号

		实例 : 

			a = 1 + 2 ;;
			1 + 3;
			b = a + 4 ;

* SSA静态单赋值形式, 即一个变量名最多只能赋值一次

<br>
<br>
<br>
加入一条语法要做的工作:

	1. 在grammar的**末尾**按格式写上语法
	
	2. 如果有文法符号没有在之前出现过的话, 在structure.hpp 的Type里加入

	3. 在如果有文法符号没有在之前出现过的话, lexer加入相应的此法分析

	4. 在parser.hpp加入相应的**后缀sdt**声明, 再在parser.cpp里实现

	5. 记得在reduce的switch语句里面加上上述sdt分支
