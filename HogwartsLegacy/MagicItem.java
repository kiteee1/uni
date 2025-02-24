package a12236167;

public abstract class MagicItem implements Tradeable, MagicEffectRealization, MagicSource {
	private String name ; // must not be null or empty
	private int usages ; // number of usages remaining ; must not be negative
	private int price ; // must not be negative
	private int weight ; // must not be negative
	
	protected MagicItem(String name, int usages, int price, int weight) {
		if (name == null || name.isBlank()) {
			throw new IllegalArgumentException("name null or empty MagicItem");
		}
		if (usages < 0) {
			throw new IllegalArgumentException("usages < 0 MagicItem");
		}
		if (price < 0) {
			throw new IllegalArgumentException("price < 0 MagicItem");
		}
		if (weight < 0) {
			throw new IllegalArgumentException("weight < 0 MagicItem");
		}
		
		this.name = name;
        this.usages = usages;
        this.price = price;
        this.weight = weight;
	}
	
	public int getUsages () {
		return usages;
	}
		// returns value of usages ( for access from deriving classes )
		
	public boolean tryUsage () {
		if (usages > 0) {
			usages = usages - 1;
			return true;
		}
		else {
			return false;
		}
	}
		// if usages > 0 reduce usage by 1 and return true , otherwise return
		// false
		
	public String usageString () {
		if (usages == 1) {
			return "use";
		}
		else {
			return "uses";
		}
	}
		// returns " use " if usages is equal to 1 , " uses " otherwise
		
	public String additionalOutputString () {
		return "";
	}
		// returns empty string . Is overridden in deriving classes as needed
		
	@Override
	public String toString () {
		String knuts = price == 1 ? "Knut" : "Knuts";
	    return String.format("[%s; %d g; %d %s; %d %s%s]", 
	        name, weight, price, knuts, usages, usageString(), additionalOutputString());
	}
		
		// formats this object according to "[ ’ name ’; ’ weight ’ g ; ’ price ’ ’
		// currencyString ’; ’ usages ’ ’ usageString ’’ additionalOutputString ’]"
		// ’ currencyString ’ is " Knut " if price is 1 , " Knuts " otherwise
		// e . g . ( when additionalOutput () returns an empty string ) "[ Accio
		// Scroll ; 1 g ; 1 Knut ; 5 uses ]" or "[ Alohomora Scroll ; 1 g ; 10 Knuts ;
		// 1 use ]"
		
	@Override
	public boolean provideMana(MagicLevel levelNeeded, int manaAmount) {
		if (levelNeeded == null) {
            throw new IllegalArgumentException("The needed level must not be null.");
        }

        if (manaAmount < 0) {
            throw new IllegalArgumentException("Mana amount must not be negative.");
        }
		return true;
	}

	@Override
	public int getPrice() {
		return price;
	}

	@Override
	public int getWeight() {
		return weight;
	}

	@Override
	public void takeDamagePercent ( int percentage ) {
		if (percentage < 0 || percentage > 100) {
			throw new IllegalArgumentException("percentage out of bounds takeDamagePercent");
		}
		usages = (int) (usages * (1 - percentage / 100.0));
	}
	// reduce usages to usages *(1 - percentage /100.)
	

}
