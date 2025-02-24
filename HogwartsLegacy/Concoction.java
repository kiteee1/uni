package a12236167;

import java.util.ArrayList;
import java.util.List;

public class Concoction extends Potion{
	private int health ; // may be any int value
	private int mana ; // may be any int value
	private List<Spell> spells ; // must not be null but may be empty ; Use
	// ArrayList as concrete type
	// it is not allowed for health and mana to be both 0 and spells to be
	// empty ; The potion must at least have one effect
	
	
	protected Concoction(String name, int usages, int price, int weight, int health, int mana, List<Spell> spells) {
		super(name, usages, price, weight);
		if (health == 0 && mana == 0 && spells.isEmpty()) {
			throw new IllegalArgumentException("healt and mana == 0 Concoction");
		}
		if (spells == null) {
			throw new IllegalArgumentException("spell is null Concoction");
		} 
		this.health = health;
        this.mana = mana;
        this.spells = new ArrayList<>(spells);
	}

	@Override
	public String additionalOutputString () {
		StringBuilder sb = new StringBuilder();
        if (health != 0) {
            sb.append(String.format("%+d HP; ", health));
        }
        if (mana != 0) {
            sb.append(String.format("%+d MP; ", mana));
        }
        if (!spells.isEmpty()) {
            sb.append("cast '").append(spells.toString()).append("'");
        }
        if (sb.length() > 0 && sb.charAt(sb.length() - 1) == ' ') {
            sb.setLength(sb.length() - 2); // remove the last semicolon and space
        }
        return sb.toString();
	}
	// returns "; ’+/ - ’ ’ health ’ HP ; ’+/ - ’ ’ mana ’ MP ; cast ’ spells ’";
	// here ’+/ - ’ denotes the appropriate sign , spells will be a bracketed
	// list of spells ( Java default toString method for lists )
	// e . g . ( total result of toString ) "[ My Brew ; 2 g ; 2 Knuts ; 4 gulps ; -5
	// HP ; +10 MP ; cast [[ Confringo (*) -20 HP ] , [ Diffindo (*) -15 HP ]]]"
	// if health or mana is 0 or spells is empty , then the respective part (
	// s ) are suppressed e . g . "[ Your Brew ; 2 g ; 1 Knut ; 1 gulp ; +5 MP ]"
	
	
	@Override
	public void useOn(MagicEffectRealization target) {
		if (target == null ) {
			throw new IllegalArgumentException("target == null useon health potion");
		}
		
		if (!tryUsage()) {
			return;
		}
		
		if (health >= 0) {
            target.heal(health);
        } 
		
		else {
            target.takeDamage(-health);
        }

        if (mana >= 0) {
            target.enforceMagic(mana);
        }
        
        else {
            target.weakenMagic(-mana);
        }

        for (Spell spell : spells) {
            spell.cast(this, target);
        }
	}

}
