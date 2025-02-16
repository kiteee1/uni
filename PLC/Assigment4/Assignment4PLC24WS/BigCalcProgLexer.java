// Generated from C:/Users/roman/Desktop/unik/PLC/Assigment4/Assignment4PLC24WS/BigCalcProg.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class BigCalcProgLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, VARIABLE=11, Number=12, Digit=13, WS=14, COMMENT=15, LINE_COMMENT=16;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "VARIABLE", "Number", "Digit", "WS", "COMMENT", "LINE_COMMENT"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'='", "';'", "'*'", "'/'", "'+'", "'-'", "'('", "')'", "'?'", 
			"':'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, "VARIABLE", 
			"Number", "Digit", "WS", "COMMENT", "LINE_COMMENT"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public BigCalcProgLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "BigCalcProg.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u0010q\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002\u0001"+
		"\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004"+
		"\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007"+
		"\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b"+
		"\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002"+
		"\u000f\u0007\u000f\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0001"+
		"\u0002\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0004\u0001\u0004\u0001"+
		"\u0005\u0001\u0005\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001"+
		"\b\u0001\b\u0001\t\u0001\t\u0001\n\u0001\n\u0005\n8\b\n\n\n\f\n;\t\n\u0001"+
		"\u000b\u0005\u000b>\b\u000b\n\u000b\f\u000bA\t\u000b\u0001\u000b\u0001"+
		"\u000b\u0004\u000bE\b\u000b\u000b\u000b\f\u000bF\u0001\u000b\u0004\u000b"+
		"J\b\u000b\u000b\u000b\f\u000bK\u0003\u000bN\b\u000b\u0001\f\u0001\f\u0001"+
		"\r\u0004\rS\b\r\u000b\r\f\rT\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0005\u000e]\b\u000e\n\u000e\f\u000e`\t\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000f\u0001"+
		"\u000f\u0001\u000f\u0001\u000f\u0005\u000fk\b\u000f\n\u000f\f\u000fn\t"+
		"\u000f\u0001\u000f\u0001\u000f\u0001^\u0000\u0010\u0001\u0001\u0003\u0002"+
		"\u0005\u0003\u0007\u0004\t\u0005\u000b\u0006\r\u0007\u000f\b\u0011\t\u0013"+
		"\n\u0015\u000b\u0017\f\u0019\r\u001b\u000e\u001d\u000f\u001f\u0010\u0001"+
		"\u0000\u0005\u0002\u0000AZaz\u0003\u000009AZaz\u0001\u000009\u0003\u0000"+
		"\t\n\f\r  \u0002\u0000\n\n\r\rx\u0000\u0001\u0001\u0000\u0000\u0000\u0000"+
		"\u0003\u0001\u0000\u0000\u0000\u0000\u0005\u0001\u0000\u0000\u0000\u0000"+
		"\u0007\u0001\u0000\u0000\u0000\u0000\t\u0001\u0000\u0000\u0000\u0000\u000b"+
		"\u0001\u0000\u0000\u0000\u0000\r\u0001\u0000\u0000\u0000\u0000\u000f\u0001"+
		"\u0000\u0000\u0000\u0000\u0011\u0001\u0000\u0000\u0000\u0000\u0013\u0001"+
		"\u0000\u0000\u0000\u0000\u0015\u0001\u0000\u0000\u0000\u0000\u0017\u0001"+
		"\u0000\u0000\u0000\u0000\u0019\u0001\u0000\u0000\u0000\u0000\u001b\u0001"+
		"\u0000\u0000\u0000\u0000\u001d\u0001\u0000\u0000\u0000\u0000\u001f\u0001"+
		"\u0000\u0000\u0000\u0001!\u0001\u0000\u0000\u0000\u0003#\u0001\u0000\u0000"+
		"\u0000\u0005%\u0001\u0000\u0000\u0000\u0007\'\u0001\u0000\u0000\u0000"+
		"\t)\u0001\u0000\u0000\u0000\u000b+\u0001\u0000\u0000\u0000\r-\u0001\u0000"+
		"\u0000\u0000\u000f/\u0001\u0000\u0000\u0000\u00111\u0001\u0000\u0000\u0000"+
		"\u00133\u0001\u0000\u0000\u0000\u00155\u0001\u0000\u0000\u0000\u0017M"+
		"\u0001\u0000\u0000\u0000\u0019O\u0001\u0000\u0000\u0000\u001bR\u0001\u0000"+
		"\u0000\u0000\u001dX\u0001\u0000\u0000\u0000\u001ff\u0001\u0000\u0000\u0000"+
		"!\"\u0005=\u0000\u0000\"\u0002\u0001\u0000\u0000\u0000#$\u0005;\u0000"+
		"\u0000$\u0004\u0001\u0000\u0000\u0000%&\u0005*\u0000\u0000&\u0006\u0001"+
		"\u0000\u0000\u0000\'(\u0005/\u0000\u0000(\b\u0001\u0000\u0000\u0000)*"+
		"\u0005+\u0000\u0000*\n\u0001\u0000\u0000\u0000+,\u0005-\u0000\u0000,\f"+
		"\u0001\u0000\u0000\u0000-.\u0005(\u0000\u0000.\u000e\u0001\u0000\u0000"+
		"\u0000/0\u0005)\u0000\u00000\u0010\u0001\u0000\u0000\u000012\u0005?\u0000"+
		"\u00002\u0012\u0001\u0000\u0000\u000034\u0005:\u0000\u00004\u0014\u0001"+
		"\u0000\u0000\u000059\u0007\u0000\u0000\u000068\u0007\u0001\u0000\u0000"+
		"76\u0001\u0000\u0000\u00008;\u0001\u0000\u0000\u000097\u0001\u0000\u0000"+
		"\u00009:\u0001\u0000\u0000\u0000:\u0016\u0001\u0000\u0000\u0000;9\u0001"+
		"\u0000\u0000\u0000<>\u0003\u0019\f\u0000=<\u0001\u0000\u0000\u0000>A\u0001"+
		"\u0000\u0000\u0000?=\u0001\u0000\u0000\u0000?@\u0001\u0000\u0000\u0000"+
		"@B\u0001\u0000\u0000\u0000A?\u0001\u0000\u0000\u0000BD\u0005.\u0000\u0000"+
		"CE\u0003\u0019\f\u0000DC\u0001\u0000\u0000\u0000EF\u0001\u0000\u0000\u0000"+
		"FD\u0001\u0000\u0000\u0000FG\u0001\u0000\u0000\u0000GN\u0001\u0000\u0000"+
		"\u0000HJ\u0003\u0019\f\u0000IH\u0001\u0000\u0000\u0000JK\u0001\u0000\u0000"+
		"\u0000KI\u0001\u0000\u0000\u0000KL\u0001\u0000\u0000\u0000LN\u0001\u0000"+
		"\u0000\u0000M?\u0001\u0000\u0000\u0000MI\u0001\u0000\u0000\u0000N\u0018"+
		"\u0001\u0000\u0000\u0000OP\u0007\u0002\u0000\u0000P\u001a\u0001\u0000"+
		"\u0000\u0000QS\u0007\u0003\u0000\u0000RQ\u0001\u0000\u0000\u0000ST\u0001"+
		"\u0000\u0000\u0000TR\u0001\u0000\u0000\u0000TU\u0001\u0000\u0000\u0000"+
		"UV\u0001\u0000\u0000\u0000VW\u0006\r\u0000\u0000W\u001c\u0001\u0000\u0000"+
		"\u0000XY\u0005/\u0000\u0000YZ\u0005*\u0000\u0000Z^\u0001\u0000\u0000\u0000"+
		"[]\t\u0000\u0000\u0000\\[\u0001\u0000\u0000\u0000]`\u0001\u0000\u0000"+
		"\u0000^_\u0001\u0000\u0000\u0000^\\\u0001\u0000\u0000\u0000_a\u0001\u0000"+
		"\u0000\u0000`^\u0001\u0000\u0000\u0000ab\u0005*\u0000\u0000bc\u0005/\u0000"+
		"\u0000cd\u0001\u0000\u0000\u0000de\u0006\u000e\u0000\u0000e\u001e\u0001"+
		"\u0000\u0000\u0000fg\u0005/\u0000\u0000gh\u0005/\u0000\u0000hl\u0001\u0000"+
		"\u0000\u0000ik\b\u0004\u0000\u0000ji\u0001\u0000\u0000\u0000kn\u0001\u0000"+
		"\u0000\u0000lj\u0001\u0000\u0000\u0000lm\u0001\u0000\u0000\u0000mo\u0001"+
		"\u0000\u0000\u0000nl\u0001\u0000\u0000\u0000op\u0006\u000f\u0000\u0000"+
		"p \u0001\u0000\u0000\u0000\t\u00009?FKMT^l\u0001\u0006\u0000\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}