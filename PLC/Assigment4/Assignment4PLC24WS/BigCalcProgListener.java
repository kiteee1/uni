// Generated from C:/Users/roman/Desktop/unik/PLC/Assigment4/Assignment4PLC24WS/BigCalcProg.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link BigCalcProgParser}.
 */
public interface BigCalcProgListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link BigCalcProgParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(BigCalcProgParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link BigCalcProgParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(BigCalcProgParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link BigCalcProgParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(BigCalcProgParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link BigCalcProgParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(BigCalcProgParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link BigCalcProgParser#assigmentStatement}.
	 * @param ctx the parse tree
	 */
	void enterAssigmentStatement(BigCalcProgParser.AssigmentStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link BigCalcProgParser#assigmentStatement}.
	 * @param ctx the parse tree
	 */
	void exitAssigmentStatement(BigCalcProgParser.AssigmentStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link BigCalcProgParser#expressionStatement}.
	 * @param ctx the parse tree
	 */
	void enterExpressionStatement(BigCalcProgParser.ExpressionStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link BigCalcProgParser#expressionStatement}.
	 * @param ctx the parse tree
	 */
	void exitExpressionStatement(BigCalcProgParser.ExpressionStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code var}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterVar(BigCalcProgParser.VarContext ctx);
	/**
	 * Exit a parse tree produced by the {@code var}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitVar(BigCalcProgParser.VarContext ctx);
	/**
	 * Enter a parse tree produced by the {@code num}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterNum(BigCalcProgParser.NumContext ctx);
	/**
	 * Exit a parse tree produced by the {@code num}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitNum(BigCalcProgParser.NumContext ctx);
	/**
	 * Enter a parse tree produced by the {@code addSub}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterAddSub(BigCalcProgParser.AddSubContext ctx);
	/**
	 * Exit a parse tree produced by the {@code addSub}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitAddSub(BigCalcProgParser.AddSubContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ternary}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterTernary(BigCalcProgParser.TernaryContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ternary}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitTernary(BigCalcProgParser.TernaryContext ctx);
	/**
	 * Enter a parse tree produced by the {@code parenExpr}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterParenExpr(BigCalcProgParser.ParenExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code parenExpr}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitParenExpr(BigCalcProgParser.ParenExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code mulDiv}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterMulDiv(BigCalcProgParser.MulDivContext ctx);
	/**
	 * Exit a parse tree produced by the {@code mulDiv}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitMulDiv(BigCalcProgParser.MulDivContext ctx);
	/**
	 * Enter a parse tree produced by {@link BigCalcProgParser#variable}.
	 * @param ctx the parse tree
	 */
	void enterVariable(BigCalcProgParser.VariableContext ctx);
	/**
	 * Exit a parse tree produced by {@link BigCalcProgParser#variable}.
	 * @param ctx the parse tree
	 */
	void exitVariable(BigCalcProgParser.VariableContext ctx);
}