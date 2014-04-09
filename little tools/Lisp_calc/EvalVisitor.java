import java.util.HashMap ;
import java.util.Map ;
import java.util.ArrayList ;

public class EvalVisitor extends ExprBaseVisitor <Integer> {
	Map<String, Integer> memory = new HashMap<String, Integer> () ;

    Integer arithmetic(String op, Integer a, Integer b) {
        if     (op.equals("+"))  return a + b;
        else if(op.equals("-"))  return a - b;
        else if(op.equals("*"))  return a * b;
        else if(op.equals("\\")) return a / b;
        else return -1;
    }


	boolean comparison(String op, Integer a, Integer b) {
		if      (op.equals("==")) return a.equals(b) ;
		else if (op.equals(">"))  return a>b;
		else if (op.equals(">=")) return a>=b;
		else if (op.equals("<"))  return a<b;
		else if (op.equals("<=")) return a<=b;
		else return false;
	
	}
	@Override public Integer visitProg(ExprParser.ProgContext ctx) { 
		int childCount = ctx.getChildCount(), i = 0 ;
		while( i < childCount ) {
			Integer res = visit( ctx.getChild(i)) ;
			System.out.println(res) ;
			i = i + 1 ; 
		}
		return 0 ;
	}
	
	@Override public Integer visitArithmetic(ExprParser.ArithmeticContext ctx) { 
		return arithmetic(ctx.ARITHMETIC_OPERATOR().getText() , visit(ctx.args(0)), visit(ctx.args(1)));
	}

	@Override public Integer visitComparison(ExprParser.ComparisonContext ctx) { 
		return comparison(ctx.COMPARISON_OPERATOR().getText(), visit(ctx.args(0)), visit(ctx.args(1))) == true ? 1 : 0 ;
	}

	@Override public Integer visitAnd(ExprParser.AndContext ctx) {
		return (visit(ctx.args(0)) != 0 && visit(ctx.args(1)) != 0) == true ? 1 : 0 ;
	}

	@Override public Integer visitOr(ExprParser.OrContext ctx) {
		return (visit(ctx.args(0)) != 0 || visit(ctx.args(1)) != 0) == true ? 1 : 0 ;
	}

	@Override public Integer visitAssign(ExprParser.AssignContext ctx) { 
		String id = ctx.ID().getText() ;
		Integer value = visit(ctx.expr()) ;
		memory.put(id, value) ;
		return value ;
	}

	@Override public Integer visitIf(ExprParser.IfContext ctx) { 
		if ( visit(ctx.expr(0)).equals(0) ) return visit(ctx.expr(2)) ;
		else return visit(ctx.expr(1)) ;
	}



	@Override public Integer visitId(ExprParser.IdContext ctx) { 
		String id = ctx.ID().getText() ;
		if (memory.containsKey(id)) return memory.get(id) ;
		else return 0;
	}

	@Override public Integer visitInt(ExprParser.IntContext ctx) { 
		return Integer.valueOf(ctx.INT().getText()) ;
	}
}
