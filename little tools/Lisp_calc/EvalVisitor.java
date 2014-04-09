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
			if(ctx.getChild(i) instanceof ExprParser.ExprContext) System.out.println(res) ;
			i = i + 1 ; 
		}
		return 0 ;
	}
	
	@Override public Integer visitArithmetic(ExprParser.ArithmeticContext ctx) { 
		String op = ctx.ARITHMETIC_OPERATOR().getText() ;
		Integer result = visit(ctx.args(0)) ;
		int size = ctx.args().size(), i = 1;
		while( i < size ) {
			result = arithmetic(op, result, visit(ctx.args(i)));
			i = i + 1;
		}
		return result ;
	}

	@Override public Integer visitComparison(ExprParser.ComparisonContext ctx) { 
		String  op = ctx.COMPARISON_OPERATOR().getText() ;
		int size = ctx.args().size(), i = 1;
		while( i < size ) {
			if( comparison(op, visit(ctx.args(i-1)), visit(ctx.args(i))) == false ) return 0;
			i = i + 1 ;
		}
		return 1 ;
	}

	@Override public Integer visitAnd(ExprParser.AndContext ctx) {
		if( visit(ctx.args(0)) == 0 ) return 0;
		int size = ctx.args().size(), i = 1;
		while( i < size ) {
			if (visit(ctx.args(i)) == 0) return 0;
			i = i + 1 ;
		}
		return 1 ;
	}

	@Override public Integer visitOr(ExprParser.OrContext ctx) {
		if( visit(ctx.args(0)) != 0 ) return 1;
		int size = ctx.args().size(), i = 1;
		while( i < size ) {
			if (visit(ctx.args(i)) != 0) return 1;
			i = i + 1 ;
		}
		return 0 ;
	}

	@Override public Integer visitAssign(ExprParser.AssignContext ctx) { 
		String id = ctx.ID().getText() ;
		Integer value = visit(ctx.args()) ;
		memory.put(id, value) ;
		return value ;
	}

	@Override public Integer visitIf(ExprParser.IfContext ctx) { 
		if ( visit(ctx.expr(0)).equals(0) ) return visit(ctx.expr(2)) ;
		else if(ctx.expr().size() > 1) return visit(ctx.expr(1)) ;
		else return 0;
	}

	@Override public Integer visitCond(ExprParser.CondContext ctx) {
		int size = ctx.expr().size(), i = 0;
		while( i < size-1 ) {
			if( visit(ctx.expr(i)) > 0 ) return visit(ctx.expr(i+1)) ;
			i = i + 2 ;
		}
		return ((size & 1) == 0) ? 0 : visit(ctx.expr(size-1)) ;
	}

	@Override public Integer visitPrint(ExprParser.PrintContext ctx) {
		int size = ctx.args().size() , i = 0 ;
		while (i < size ) {
			System.out.print( visit(ctx.args(i)) ) ;
			System.out.print( ' ' ) ;
			i = i + 1 ; 
		}
		System.out.println() ;
		return 0;
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
