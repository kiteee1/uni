package a12236167;

public class HealingSpell extends Spell{
	private boolean type ;
	private boolean percentage ;
	private int amount ; // has to be non negative ; if percentage == true ,
	// amount must be in the interval [0 ,100]
	
	protected HealingSpell(String name, int manaCost, MagicLevel levelNeeded, boolean type, boolean percentage, int amount) {
		super(name, manaCost, levelNeeded);
		
		if (amount < 0) {
			throw new IllegalArgumentException("amount less than 0 HealingSpell");
		}
		if (percentage && amount > 100) {
			throw new IllegalArgumentException("amount less than 0 HealingSpell");
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
		
		if (percentage) {
		    if (type) {
		        target.healPercent(amount);
		    } 
		    else {
		        target.enforceMagicPercent(amount);
		    }
		} 
		else {
		    if (type) {
		        target.heal(amount);
		    }
		    else {
		        target.enforceMagic(amount);
		    }
		}
		
	}
	
	@Override
	public String additionalOutputString () {
		String percentageString = percentage ? "% " : "";
	    String HPorMP = type ? "HP" : "MP";

	    return String.format("; +%d %s%s", amount, percentageString, HPorMP);
	}

}
