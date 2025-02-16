package a12236167;

public class HealthPotion extends Potion{
	private int health ; // must not be negative
	
	protected HealthPotion(String name, int usages, int price, int weight, int health) {
        super(name, usages, price, weight);
        
        if (health < 0) {
        	throw new IllegalArgumentException("health negative HealthPotion");
        }
        this.health = health;
    }

	@Override
	public void useOn(MagicEffectRealization target) {
		if (target == null ) {
			throw new IllegalArgumentException("target == null useon health potion");
		}
		if(tryUsage()) {
			target.heal(health);
		}
	}
}
