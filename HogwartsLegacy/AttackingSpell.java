package a12236167;

import java.util.Set;

public class AttackingSpell extends Spell{
	private boolean type ;
	private boolean percentage ;
	private int amount ; // has to be non negative ; if percentage == true ,
	// amount must be in the interval [0 ,100]
	
	protected AttackingSpell(String name, int manaCost, MagicLevel levelNeeded, boolean type, boolean percentage, int amount) {
		super(name, manaCost, levelNeeded);
		
		if (amount < 0) {
			throw new IllegalArgumentException("amount less than 0 AttackingSpell");
		}
		if (percentage && amount > 100) {
			throw new IllegalArgumentException("amount less than 0 AttackingSpell");
		}
		
		this.type = type;
        this.percentage = percentage;
        this.amount = amount;
	}

	@Override
	public void doEffect(MagicEffectRealization target) {
		if (target == null) {
			throw new IllegalArgumentException("traget null AttackingSpell");
		}
		if (target.isProtected(this)) {
            target.removeProtection(Set.of(this));
            return;
        }
		
		if (percentage) {
		    if (type) {
		        target.takeDamagePercent(amount);
		    } 
		    else {
		        target.weakenMagicPercent(amount);
		    }
		} 
		else {
		    if (type) {
		        target.takeDamage(amount);
		    }
		    else {
		        target.weakenMagic(amount);
		    }
		}

	}
	
	@Override
	public String additionalOutputString () {
		String percentageString = percentage ? "% " : "";
	    String HPorMP = type ? "HP" : "MP";

	    return String.format("; -%d %s%s", amount, percentageString, HPorMP);
	}
	
	
 	// returns "; -’ amount ’ ’ percentage ’’ HPorMP ’" , where ’ percentage ’ is a
	// percentage sign plus a space ("% ") if percentage is true , empty
	// otherwise and HPorMP
	// is HP if type is true , MP otherwise
	// e . g . "; -10 MP " or "; -50 % HP "
	

}
