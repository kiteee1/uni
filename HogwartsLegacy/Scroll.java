package a12236167;

public class Scroll extends MagicItem{
	private Spell spell ; // must not be null
	
	protected Scroll(String name, int usages, int price, int weight, Spell spell) {
		super(name, usages, price, weight);
		if (spell == null) {
			throw new IllegalArgumentException("spell null Scroll");
		}
		this.spell = spell;
	}

	@Override
	public String additionalOutputString () {
		return String.format("; casts %s", spell);
	}
	// returns "; casts ’ spell ’"
	// e . g . ( total result of toString ) "[ Scroll of doom ; 1 g ; 100 Knuts ; 5
	// usages ; casts [ Bombarda (**) : 20 mana ; -50 % HP ]]"
	

	@Override
	public void useOn(MagicEffectRealization target) {
		if (target == null) {
			throw new IllegalArgumentException("target null useon Scroll");
		}
		if (tryUsage()) {
			spell.cast(this, target);
		}
	}
}
