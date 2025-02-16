package a12236167;

public class ManaPotion extends Potion{
	private int mana ; // must not be negative
	
	protected ManaPotion(String name, int usages, int price, int weight, int mana) {
        super(name, usages, price, weight);
        
        if (mana < 0) {
        	throw new IllegalArgumentException("health negative HealthPotion");
        }
        this.mana = mana;
    }

	@Override
	public String additionalOutputString () {
		return "; +" + mana + " MP";
	}
	// returns "; + ’ mana ’ MP ";
	// e . g . ( total result of toString ) "[ Mana Potion ; 1 g ; 2 Knuts ; 1 gulp ;
	// +20 MP ]"
	
	
	@Override
	public void useOn(MagicEffectRealization target) {
		if (target == null ) {
			throw new IllegalArgumentException("target == null useon health potion");
		}
		if(tryUsage()) {
			target.enforceMagic(mana);
		}
	}
}
