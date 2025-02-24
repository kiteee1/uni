package a12236167;

import java.util.Set;
import java.util.HashSet;
import java.util.Random;
import java.util.Iterator;

public class Wizard implements MagicSource, Trader, MagicEffectRealization {
	private String name ; // not null not empty
	private MagicLevel level ; // not null
	private int basicHP ; // not negative
	private int HP ; // not negative ; defaults to basicHP
	private int basicMP ; // not less than the manapoints associated with the
	// magic level
	private int MP ; // not negative ; defaults to basicMP
	private int money ; // not negative
	private Set < Spell > knownSpells ; // not null , may be empty ; use HashSet
	// for instantiation
	private Set < AttackingSpell > protectedFrom ; // not null , may be empty ; use
	// HashSet for instantiation
	private int carryingCapacity ; // not negative
	private Set < Tradeable > inventory ; // not null , may be empty , use HashSet
	// for instantiation , total weight of inventory may never exceed
	// carryingCapacity
	public Wizard(String name, MagicLevel level, int basicHP, int HP, int basicMP, int MP, int money, Set < ? extends Spell > knownSpells, Set <? extends AttackingSpell > protectedFrom, int carryingCapacity, Set <? extends Tradeable > inventory) {
		if (name == null || name.isBlank()) {
			throw new IllegalArgumentException("name null or empty Wizard");
		}
		if (level == null) {
			throw new IllegalArgumentException("level null Wizard");
		}
		if(basicHP < 0) {
			throw new IllegalArgumentException("basic hp < 0 Wizard");
		}
		if(HP < 0) {
			throw new IllegalArgumentException("hp < 0 Wizard");
		}
		if(basicMP < 0) {
			throw new IllegalArgumentException("basicMP < 0 Wizard");
		}
		if(basicMP < level.toMana()) {
			throw new IllegalArgumentException("basicmp < mana of level Wizard");
		}
		if(MP < 0) {
			throw new IllegalArgumentException("mp < 0 Wizard");
		}
		if(money < 0) {
			throw new IllegalArgumentException("money < 0 Wizard");
		}
		if(knownSpells == null) {
			throw new IllegalArgumentException("knownSpells null Wizard");
		}
		if(protectedFrom == null) {
			throw new IllegalArgumentException("protectedFrom null Wizard");
		}
		if(carryingCapacity < 0) {
			throw new IllegalArgumentException("carryingCapacity < 0 Wizard");
		}
		if (inventory == null) {
			throw new IllegalArgumentException("inventory null Wizard");
		}
		int totalWeight = 0;
	    for (Tradeable item : inventory) {
	        totalWeight += item.getWeight();
	    }
        if (totalWeight > carryingCapacity) {
            throw new IllegalArgumentException("The initial inventory of the wizard must not exceed the carrying capacity.");
        }
        this.name = name;
        this.level = level;
        this.basicHP = basicHP;
        this.HP = HP;
        this.basicMP = basicMP;
        this.MP = MP;
        this.money = money;
        this.knownSpells = new HashSet<>(knownSpells);
        this.protectedFrom = new HashSet<>(protectedFrom);
        this.carryingCapacity = carryingCapacity;
        this.inventory = new HashSet<>(inventory);
	}
	
	public boolean isDead () {return HP == 0;}
		// return true , if HP is 0 , false otherwise
		
	private int inventoryTotalWeight () {
		int totalWeight = 0;
	    for (Tradeable item : inventory) {
	        totalWeight += item.getWeight();
	    }
	    return totalWeight;
	}
		// calculates and returns the total weight of all the items in the
		// inventory
		
	public boolean learn ( Spell s ) {
		if (s == null) {
            throw new IllegalArgumentException("spell is null Wizard");
        }

        if (isDead()) {
            return false;
        }

        return knownSpells.add(s);
	}
		// if spell is null , IllegalArgumentException has to be thrown
		// if wizard is dead ( isDead ) no action can be taken and false is
		// returned
		// add spell to the set of knownSpells
		// returns true , if insertion was successful , false otherwise
		
	public boolean forget ( Spell s ) {
		if (s == null) {
            throw new IllegalArgumentException("spell is null Wizard forget");
        }

        if (isDead()) {
            return false;
        }

        return knownSpells.remove(s);
	}
		// if spell is null , IllegalArgumentException has to be thrown
		// if wizard is dead ( isDead ) no action can be taken and false is
		// returned
		// remove spell from the set of knownSpells
		// returns true , if removal was successful , false otherwise
		
	public boolean castSpell ( Spell s , MagicEffectRealization target ) {
		if (s == null) {
            throw new IllegalArgumentException("spell is null Wizard castSpell");
		}
		if (target == null) {
            throw new IllegalArgumentException("target is null Wizard castSpell");
		}
		if (isDead() || !knownSpells.contains(s)) {
			return false;
		}
		s.cast(this, target);
		return true;
	}
		// if s or target is null , IllegalArgumentException has to be thrown
		// if wizard is dead ( isDead ) no action can be taken and false is
		// returned
		// if wizard does not know the spell , false is returned
		// call cast on s with this as source and parameter target as target
		// return true , if cast was called
	
	public boolean castRandomSpell ( MagicEffectRealization target ) {
		if (target == null) {
            throw new IllegalArgumentException("target is null Wizard castRandomSpell");
		}
		if (isDead() || knownSpells.isEmpty()) {
            return false;
		}
		
		Random random = new Random();
		int randomIndex = random.nextInt(knownSpells.size());
		Iterator<Spell> iterator = knownSpells.iterator();
		Spell randomSpell = null;
		
		for (int i = 0; i <= randomIndex; i++) {
			randomSpell = iterator.next();
		}
		
		randomSpell.cast(this, target);
		return true;
	}
		// if this object ’s knownSpells is empty , return false
		// otherwise choose a random spell from knownSpells and delegate to
		// castSpell ( Spell , MagicEffectRealization )
		
	
	public boolean useItem ( Tradeable item , MagicEffectRealization target ) {
		if (item == null) {
            throw new IllegalArgumentException("item is null Wizard useItem");
		}
		if (target == null) {
            throw new IllegalArgumentException("target is null Wizard useItem");
		}
		if (isDead() || !possesses(item)) {
			return false;
		}
		item.useOn(target);
		return true;
	}
		// if item or target is null , IllegalArgumentException has to be thrown
		// if wizard is dead ( isDead ) no action can be taken and false is
		// returned
		// if wizard does not possess the item , false is returned
		// call useOn on the item with parameter target as target
		// return true if useOn was called
		
	public boolean useRandomItem ( MagicEffectRealization target ) {
		if (target == null) {
            throw new IllegalArgumentException("target is null Wizard useRandomItem");
		}
		if (isDead() || inventory.isEmpty()) {
            return false;
		}
		
		Random random = new Random();
		int randomIndex = random.nextInt(inventory.size());
		Iterator<Tradeable> iterator = inventory.iterator();
		Tradeable randomItem = null;
		
		for (int i = 0; i <= randomIndex; i++) {
			randomItem = iterator.next();
		}
		
		randomItem.useOn(target);
		return true;
	}
		// if this object ’s inventory is empty , return false
		// otherwise choose a random item from inventory and delegate to
		// useItem ( Tradeable , MagicEffectRealization )
		
	
	public boolean sellItem ( Tradeable item , Trader target ) {
		if (item == null) {
            throw new IllegalArgumentException("item is null Wizard sellItem");
		}
		if (target == null) {
            throw new IllegalArgumentException("target is null Wizard sellItem");
		}
		if (isDead() || !possesses(item)) {
			return false;
		}
		
		return item.purchase(this, target);
	}
		// if item or target is null , IllegalArgumentException has to be thrown
		// if wizard is dead ( isDead ) , no action can be taken and false is
		// returned
		// call purchase on the item with this as seller and target as buyer
		// return true , if purchase was called successfully ( returned true ) ,
		// false otherwise .
		
		public boolean sellRandomItem ( Trader target ) {
			if (target == null) {
	            throw new IllegalArgumentException("target is null Wizard sellRandomItem");
			}
			if (isDead() || inventory.isEmpty()) {
	            return false;
			}
			
			Random random = new Random();
			int randomIndex = random.nextInt(inventory.size());
			Iterator<Tradeable> iterator = inventory.iterator();
			Tradeable randomItem = null;
			
			for (int i = 0; i <= randomIndex; i++) {
				randomItem = iterator.next();
			}
			
			return randomItem.purchase(this, target);
		}
		// if this object ’s inventory is empty , return false
		// otherwise choose a random item from inventory and delegate to
		// sellItem ( Tradeable , MagicEffectRealization )
		
	
	@Override
	public String toString () {
		String knuts = money == 1 ? "Knut" : "Knuts";
		return String.format("[%s(%s): %d/%d %d/%d; %d %s; knows %s; carries %s]", name, level, HP, basicHP, MP, basicMP, money, knuts, knownSpells, inventory);
	}
	// returns a string in the format "[ ’ name ’( ’ level ’) : ’ HP ’/ ’ basicHP ’ ’ MP
	// ’/ ’ basicMP ’; ’ money ’ ’ KnutOrKnuts ’; knows ’ knownSpells ’; carries ’
	// inventory ’]"; where ’ level ’ is the asterisks representation of the
	// level ( see MagicLevel . toString ) and ’ knownSpells ’ and ’ inventory ’
	// use the default toString method of Java Set ; ’ KnutOrKnuts ’ is Knut
	// if ’ money ’ is 1 , Knuts otherwise
	// e . g . [ Ignatius (**) : 70/100 100/150; 72 Knuts ; knows [[ Episkey (*) : 5
	// mana ; +20 HP ] , [ Confringo (*) : 10 mana ; -20 HP ]]; carries []]
		
	
	@Override
	public boolean provideMana(MagicLevel levelNeeded, int manaAmount) {
		if(levelNeeded == null) {
            throw new IllegalArgumentException("levelNeeded is null Wizard");
		}
		if(manaAmount < 0) {
            throw new IllegalArgumentException("manaAmount < 0 Wizard");
		}
		if (isDead() || MP < manaAmount || level.compareTo(levelNeeded) < 0) {
			return false;
		}
		
		MP -= manaAmount;
		return true;
		
	}
	
	@Override
	public boolean possesses(Tradeable item) {
		if(item == null) {
            throw new IllegalArgumentException("item is null Wizard possesses");
		}
		return inventory.contains(item);
	}

	@Override
	public boolean canAfford(int amount) {
		if(amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard canAfford");
		}
		return money >= amount;
	}

	@Override
	public boolean hasCapacity(int weight) {
		if(weight < 0) {
            throw new IllegalArgumentException("weight < 0 Wizard hasCapacity");
		}
		return inventoryTotalWeight() + weight <= carryingCapacity; 
	}

	@Override
	public boolean pay(int amount) {
		if(amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard pay");
		}
		if (isDead() || !canAfford(amount)) {
			return false;
		}
		money -= amount;
		return true;
	}

	@Override
	public boolean earn(int amount) {
		if(amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard pay");
		}
		if (isDead()) {
			return false;
		}
		money += amount;
		return true;
	}

	@Override
	public boolean addToInventory(Tradeable item) {
		if(item == null) {
            throw new IllegalArgumentException("item is null Wizard addToInventory");
		}
		return hasCapacity(item.getWeight()) && inventory.add(item);
	}

	@Override
	public boolean removeFromInventory(Tradeable item) {
		if(item == null) {
            throw new IllegalArgumentException("item is null Wizard removeFromInventory");
		}
		return inventory.contains(item) && inventory.remove(item);
	}
	
	@Override
	public boolean canSteal () {
		return isDead();
	}

	@Override
	public boolean steal(Trader thief) {
		if(thief == null) {
            throw new IllegalArgumentException("thies is null Wizard steal");
		}
		if(!thief.canSteal()) {
			return false;
		}
		if (inventory.isEmpty()) {
			return false;
		}
		
		Random random = new Random();
		int randomIndex = random.nextInt(inventory.size());
		Iterator<Tradeable> iterator = inventory.iterator();
		Tradeable randomItem = null;
		
		for (int i = 0; i <= randomIndex; i++) {
			randomItem = iterator.next();
		}
		
		if(!thief.hasCapacity(randomItem.getWeight())) {
			inventory.remove(randomItem);
			return false;
		}
		removeFromInventory(randomItem);
		return thief.addToInventory(randomItem);
	}

	@Override
	public boolean isLootable () {
		return isDead();
	}
	// returns true , if this object ’s HP are 0 ( dead wizard )
	
	
	@Override
	public boolean canLoot () {
		return !isDead();
	}
	// returns true , if this object ’s HP are not 0 ( alive wizard )
	
	
	@Override
	public boolean loot(Trader looter) {
		if(looter == null) {
            throw new IllegalArgumentException("looter is null Wizard loot");
		}
		if(!looter.canLoot()) {
			return false;
		}
		if(!isLootable()) {
			return false;
		}
		
		boolean transferred = false;
		Iterator<Tradeable> iterator = inventory.iterator();
		
		while (iterator.hasNext()) {
			Tradeable item = iterator.next();
			if (looter.hasCapacity(item.getWeight())) {
				looter.addToInventory(item);
				iterator.remove();
				transferred = true;
			}
			else {
				iterator.remove();
			}
		}
		return transferred;
	}
	
	@Override
    public void takeDamage(int amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard takeDamage");
        }

        HP = Math.max(HP - amount, 0);
    }
	
	@Override
    public void takeDamagePercent(int percentage) {
        if (percentage < 0 || percentage > 100) {
            throw new IllegalArgumentException("percentage out of bounds Wizard takeDamagePercent");
        }

        HP = (int) Math.max(HP - basicHP * (percentage / 100.0), 0);
    }
	
	@Override
    public void weakenMagic(int amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard weakenMagic");
        }

        HP = Math.max(MP - amount, 0);
    }
	
	@Override
    public void weakenMagicPercent(int percentage) {
        if (percentage < 0 || percentage > 100) {
            throw new IllegalArgumentException("percentage out of bounds Wizard weakenMagicPercent");
        }

        HP = (int) Math.max(MP - basicMP * (percentage / 100.0), 0);
	}
	
	@Override
    public void heal(int amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard heal");
        }

        HP += amount;
    }
	
	@Override
    public void healPercent(int percentage) {
        if (percentage < 0 || percentage > 100) {
            throw new IllegalArgumentException("percentage out of bounds Wizard healPercent");
        }

        HP = (int) Math.max(HP + basicHP * (percentage / 100.0), 0);
	}
	
	@Override
    public void enforceMagic(int amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard enforceMagic");
        }

        MP += amount;
    }
	
	@Override
    public void enforceMagicPercent(int percentage) {
        if (percentage < 0 || percentage > 100) {
            throw new IllegalArgumentException("percentage out of bounds Wizard enforceMagicPercent");
        }

        HP = (int) Math.max(MP + basicMP * (percentage / 100.0), 0);
	}
	
	@Override
    public boolean isProtected(Spell spell) {
        if (spell == null) {
            throw new IllegalArgumentException("spell is null Wizard isProtected");
        }

        if (spell instanceof AttackingSpell) {
            return protectedFrom.contains(spell);
        }

        return false;
    }
	
	@Override
    public void setProtection(Set<AttackingSpell> attacks) {
        if (attacks == null) {
            throw new IllegalArgumentException("attacks is null Wizard setProtection");
        }

        protectedFrom.addAll(attacks);
    }
	
	@Override
    public void removeProtection(Set<AttackingSpell> attacks) {
        if (attacks == null) {
            throw new IllegalArgumentException("attacks is null Wizard setProtection");
        }

        protectedFrom.removeAll(attacks);
    }

}
