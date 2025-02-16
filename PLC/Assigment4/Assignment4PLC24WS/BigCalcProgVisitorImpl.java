import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.HashMap;
import java.util.Map;

public class BigCalcProgVisitorImpl extends BigCalcProgBaseVisitor<BigDecimal> {

    private final Map<String, BigDecimal> memory = new HashMap<>();
    private BigDecimal lastResult = BigDecimal.ZERO;



    @Override public BigDecimal visitProgram(BigCalcProgParser.ProgramContext ctx) {

        for (BigCalcProgParser.StatementContext stmtCtx : ctx.statement()) {
            lastResult = this.visit(stmtCtx);
        }

        return lastResult;
    }

    @Override public BigDecimal visitStatement(BigCalcProgParser.StatementContext ctx) {

        if (ctx.assigmentStatement() != null) {
            return visit(ctx.assigmentStatement());
        }

        else {
            return  visit(ctx.expressionStatement());
        }

    }

    @Override public BigDecimal visitAssigmentStatement(BigCalcProgParser.AssigmentStatementContext ctx) {
        String varName = ctx.variable().getText();
        BigDecimal value = this.visit(ctx.expression());

        memory.put(varName, value);

        return value;
    }

    @Override public BigDecimal visitExpressionStatement(BigCalcProgParser.ExpressionStatementContext ctx) {return this.visit(ctx.expression()); }

    @Override public BigDecimal visitVar(BigCalcProgParser.VarContext ctx) {
        String varName = ctx.variable().getText();

        if(memory.containsKey(varName)) {
            System.out.println("Warning: undefined variable: " + varName);
            return BigDecimal.ZERO;
        }

        return memory.getOrDefault(varName, BigDecimal.ZERO);
    }

    @Override public BigDecimal visitNum(BigCalcProgParser.NumContext ctx) { return new BigDecimal(ctx.Number().getText()); }

    @Override public BigDecimal visitAddSub(BigCalcProgParser.AddSubContext ctx) {
        final BigDecimal left = visit(ctx.expression(0));
        final BigDecimal right = visit(ctx.expression(1));
        if (ctx.op.getText().equals("+")) {
            return left.add(right);
        } else {
            return left.subtract(right);
        }
    }

    @Override public BigDecimal visitParenExpr(BigCalcProgParser.ParenExprContext ctx) { return visit(ctx.expression()); }

    @Override public BigDecimal visitMulDiv(BigCalcProgParser.MulDivContext ctx) {
        final BigDecimal left = visit(ctx.expression(0));
        final BigDecimal right = visit(ctx.expression(1));
        if (ctx.op.getText().equals("*")) {
            return left.multiply(right);
        } else {
            return left.divide(right, 10, RoundingMode.HALF_UP);
        }
    }

    @Override public BigDecimal visitTernary(BigCalcProgParser.TernaryContext ctx) {
        BigDecimal condition = visit(ctx.expression(0));

        if(condition.compareTo(BigDecimal.ZERO) != 0) { return visit(ctx.expression(1)); }
        else { return visit(ctx.expression(0)); }
    }


}
