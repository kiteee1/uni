// Generated from C:/Users/roman/Desktop/unik/PLC/Assigment4/Assignment4PLC24WS/BigCalcProg.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link BigCalcProgParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface BigCalcProgVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link BigCalcProgParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(BigCalcProgParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link BigCalcProgParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStatement(BigCalcProgParser.StatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link BigCalcProgParser#assigmentStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssigmentStatement(BigCalcProgParser.AssigmentStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link BigCalcProgParser#expressionStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpressionStatement(BigCalcProgParser.ExpressionStatementContext ctx);
	/**
	 * Visit a parse tree produced by the {@code var}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVar(BigCalcProgParser.VarContext ctx);
	/**
	 * Visit a parse tree produced by the {@code num}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNum(BigCalcProgParser.NumContext ctx);
	/**
	 * Visit a parse tree produced by the {@code addSub}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAddSub(BigCalcProgParser.AddSubContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ternary}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTernary(BigCalcProgParser.TernaryContext ctx);
	/**
	 * Visit a parse tree produced by the {@code parenExpr}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParenExpr(BigCalcProgParser.ParenExprContext ctx);
	/**
	 * Visit a parse tree produced by the {@code mulDiv}
	 * labeled alternative in {@link BigCalcProgParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMulDiv(BigCalcProgParser.MulDivContext ctx);
	/**
	 * Visit a parse tree produced by {@link BigCalcProgParser#variable}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVariable(BigCalcProgParser.VariableContext ctx);
}