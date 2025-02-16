package a12236167;

import java.util.Set;
import java.util.HashSet;

public class ProtectingSpell extends Spell{
	private Set < AttackingSpell > attacks ; // must not be null or empty ; use
	// HashSet as concrete type
	
	protected ProtectingSpell(String name, int manaCost, MagicLevel levelNeeded, Set < AttackingSpell > attacks) {
		super(name, manaCost, levelNeeded);
		if (attacks == null || attacks.isEmpty()) {
			throw new IllegalArgumentException("attacks is null or empty ProtectingSpell");
		}
		this.attacks = new HashSet<>(attacks);
	}

	@Override
	public void doEffect(MagicEffectRealization target) {
		if (target == null) {
			throw new IllegalArgumentException("target is null ProtectingSpell");
		}
		target.setProtection(attacks);
	}
	
	@Override
	public String additionalOutputString () {
		return String.format("; protects against %s", attacks);
	}
	// returns "; protects against ’ listOfAttackSpells ’" where ’
	// listOfAttackSpells ’ is a bracketed list of all the attack spells (
	// Java default toString method for sets )
	// e . g . "; protects against [[ Confringo (*) : 10 mana ; -20 HP ] , [
	// Bombarda (**) : 20 mana ; -50 % HP ]]"
	
}
