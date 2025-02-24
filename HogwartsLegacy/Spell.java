package a12236167;

public abstract class Spell {
	private String name ; // must not be null or empty
	private int manaCost ; // must not be negative
	private MagicLevel levelNeeded ; // must not be null
	
	protected Spell(String name, int manaCost, MagicLevel levelNeeded) {
        if (name == null || name.isBlank()) {
            throw new IllegalArgumentException("name null or empty Spell");
        }

        if (manaCost < 0) {
            throw new IllegalArgumentException("manaCost < 0 Spell");
        }

        if (levelNeeded == null) {
            throw new IllegalArgumentException("levelNeede null Spell");
        }

        this.name = name;
        this.manaCost = manaCost;
        this.levelNeeded = levelNeeded;
    }
	
	public void cast ( MagicSource source , MagicEffectRealization target ) {
		if (source == null) {
            throw new IllegalArgumentException("Source of the spell must not be null.");
        }

        if (target == null) {
            throw new IllegalArgumentException("Target of the spell must not be null.");
        }
        if(!source.provideMana(levelNeeded, manaCost)) {
        	return;
        }
        doEffect(target);
	}
	// ensure necessary magic level and get necessary energy by calling
	// provideMana on source ( this will typically reduce MP in source )
	// if provideMana fails ( returns false ) cast is canceled
	// otherwise the abstract method doEffect is called
	
	public abstract void doEffect ( MagicEffectRealization target ) ;
	// the actual effect of the spell on target must be implemented by the
	// subclasses
	public String additionalOutputString () {return "";}
	// returns ""; is overridden in deriving classes when needed
	
	@Override
	public String toString () {
		return String.format("[%s(%s): %d mana%s]", 
		        name, levelNeeded, manaCost, additionalOutputString());
	}
	
	
	
	// return output in format "[ ’ name ’( ’ levelNeeded ’) : ’ manaCost ’ mana ’
	// additionalOutputString ’]"; where ’ levelNeeded ’ is displayed as
	// asterisks ( see MagicLevel . toString )
	// e . g . ( full Output containing additionalOutputString ) [ Episkey (*) : 5
	// mana ; +20 HP ]
	
}
