package a12236167;

public abstract class Potion extends MagicItem{
	protected Potion(String name, int usages, int price, int weight) {
        super(name, usages, price, weight);
    }
	public void drink ( Wizard drinker ) {
		if (drinker == null ) {
			throw new IllegalArgumentException("drinker == null drink");
		}
		useOn(drinker);
	}
		// delegates to method call useOn ( drinker )
		
	@Override
	public String usageString () {
		if (getUsages() == 1) {
			return "gulp";
		}
		else {
			return "gulps";
		}
	}
		// returns " gulp " if usages is equal to 1 , " gulps " otherwise
		
}
