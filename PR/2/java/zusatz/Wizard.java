package a12236167;

import java.util.Set;
import java.util.HashSet;
import java.util.Random;
import java.util.Iterator;

public class Wizard implements MagicSource, Trader, MagicEffectRealization {
	
	
	private WizardArgsRealization wizardArgs; //Additional Task 2.1
	
	
	private Set < Spell > knownSpells ; // not null , may be empty ; use HashSet
	// for instantiation
	private Set < AttackingSpell > protectedFrom ; // not null , may be empty ; use
	// HashSet for instantiation
	private int carryingCapacity ; // not negative
	private Set < Tradeable > inventory ; // not null , may be empty , use HashSet
	// for instantiation , total weight of inventory may never exceed
	// carryingCapacity
	
	
	private Set<WizardState> states; //not initialized in the constructor since per default wizard does not have any states; Additional Task 2.3
	
	
	public Wizard(WizardArgsRealization wizardArgs, Set < ? extends Spell > knownSpells, Set <? extends AttackingSpell > protectedFrom, int carryingCapacity, Set <? extends Tradeable > inventory) {
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
        this.wizardArgs = wizardArgs;
        this.knownSpells = new HashSet<>(knownSpells);
        this.protectedFrom = new HashSet<>(protectedFrom);
        this.carryingCapacity = carryingCapacity;
        this.inventory = new HashSet<>(inventory);
        
        this.states = new HashSet<>(); //Additional Task 2.3
	}
	
	public boolean isDead() {return wizardArgs.isDead();}
		
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
		if (isDead() || !knownSpells.contains(s) || states.contains(WizardState.MUTED)) { //added state check; Additional task 2.3
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
		if (isDead() || knownSpells.isEmpty() || states.contains(WizardState.MUTED) || states.contains(WizardState.PARALIZED)) { //added state check; Additional task 2.3
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
		if (isDead() || !possesses(item) || states.contains(WizardState.PARALIZED)) { //added state check; Additional task 2.3
			return false;
		}
		if (states.contains(WizardState.BLIND) && item instanceof Scroll) { //added state check; Additional task 2.3
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
		if (isDead() || inventory.isEmpty() || states.contains(WizardState.PARALIZED)) { //added state check; Additional task 2.3
            return false;
		}
		
		
		Random random = new Random();
		int randomIndex = random.nextInt(inventory.size());
		Iterator<Tradeable> iterator = inventory.iterator();
		Tradeable randomItem = null;
		
		for (int i = 0; i <= randomIndex; i++) {
			randomItem = iterator.next();
		}
		
		if (states.contains(WizardState.BLIND) && randomItem instanceof Scroll) { //added state check; Additional task 2.3
            return false;
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
		
		
	//here either a function in WizardArgs can be implemented that would take knuts, knownSpells, inventory arguments
	//i decided to get info from wizazrdsArgs by using getters though
	@Override
	public String toString () {
		String knuts = wizardArgs.getMoney() == 1 ? "Knut" : "Knuts";
		return String.format("[%s(%s): %d/%d %d/%d; %d %s; knows %s; carries %s]", wizardArgs.getName(), wizardArgs.getLevel(), wizardArgs.getHP(),
				wizardArgs.getBasicHP(), wizardArgs.getMP(), wizardArgs.getBasicMP(), wizardArgs.getMoney(), knuts, knownSpells, inventory);
	}
	// returns a string in the format "[ ’ name ’( ’ level ’) : ’ HP ’/ ’ basicHP ’ ’ MP
	// ’/ ’ basicMP ’; ’ money ’ ’ KnutOrKnuts ’; knows ’ knownSpells ’; carries ’
	// inventory ’]"; where ’ level ’ is the asterisks representation of the
	// level ( see MagicLevel . toString ) and ’ knownSpells ’ and ’ inventory ’
	// use the default toString method of Java Set ; ’ KnutOrKnuts ’ is Knut
	// if ’ money ’ is 1 , Knuts otherwise
	// e . g . [ Ignatius (**) : 70/100 100/150; 72 Knuts ; knows [[ Episkey (*) : 5
	// mana ; +20 HP ] , [ Confringo (*) : 10 mana ; -20 HP ]]; carries []]
		
	
	//redone according to Move Method; Additional Task 2.1
	@Override
	public boolean provideMana(MagicLevel levelNeeded, int manaAmount) {
		return wizardArgs.provideMana(levelNeeded, manaAmount);		
	}
	
	@Override
	public boolean possesses(Tradeable item) {
		if(item == null) {
            throw new IllegalArgumentException("item is null Wizard possesses");
		}
		return inventory.contains(item);
	}

	//redone according to Move Method; Additional Task 2.1
	@Override
	public boolean canAfford(int amount) {
		return wizardArgs.canAfford(amount);
	}

	@Override
	public boolean hasCapacity(int weight) {
		if(weight < 0) {
            throw new IllegalArgumentException("weight < 0 Wizard hasCapacity");
		}
		return inventoryTotalWeight() + weight <= carryingCapacity; 
	}

	//redone according to Move Method; Additional Task 2.1
	@Override
	public boolean pay(int amount) {
		return wizardArgs.pay(amount);
	}

	//redone according to Move Method; Additional Task 2.1
	@Override
	public boolean earn(int amount) {
		return wizardArgs.pay(amount);
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
		return isDead(); //added state check; Additional task 2.3
	}
	// returns true , if this object ’s HP are 0 ( dead wizard )
	
	
	@Override
	public boolean canLoot () {
		return !isDead(); //added state check; Additional task 2.3
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
	
	//redone according to Move Method; Additional Task 2.1
	@Override
    public void takeDamage(int amount) {
       wizardArgs.takeDamage(amount);
    }
	
	//redone according to Move Method; Additional Task 2.1
	@Override
    public void takeDamagePercent(int percentage) {
        wizardArgs.takeDamagePercent(percentage);
    }
	
	//redone according to Move Method; Additional Task 2.1
	@Override
    public void weakenMagic(int amount) {
        wizardArgs.weakenMagic(amount);
    }
	
	//redone according to Move Method; Additional Task 2.1
	@Override
    public void weakenMagicPercent(int percentage) {
        wizardArgs.weakenMagicPercent(percentage);
	}
	
	//redone according to Move Method; Additional Task 2.1
	@Override
    public void heal(int amount) {
        wizardArgs.heal(amount);
    }
	
	//redone according to Move Method; Additional Task 2.1
	@Override
    public void healPercent(int percentage) {
        wizardArgs.healPercent(percentage);
	}
	
	//redone according to Move Method; Additional Task 2.1
	@Override
    public void enforceMagic(int amount) {
        wizardArgs.enforceMagic(amount);
    }
	
	//redone according to Move Method; Additional Task 2.1
	@Override
    public void enforceMagicPercent(int percentage) {
        wizardArgs.enforceMagicPercent(percentage);
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
	
	
	
	

	
	public void senseAttack(Wizard target) {
		for (Spell spell : knownSpells) {
			if (spell.isAttack() && !target.isProtected(spell)) {
				castSpell(spell, target);
			}
		}
	}
	
	
	public int getNumberOfKnownSpells() {
		return knownSpells.size();
	}
	
	
	
	//Additional task 2.3
	@Override
	public boolean hasState(WizardState state) {
		if (state == null) {
            throw new IllegalArgumentException("state is null Wizard hasState");
        }
		return states.contains(state);
	}
	@Override
	public void addState(WizardState state) {
		if (state == null) {
            throw new IllegalArgumentException("state is null Wizard hasState");
        }
		states.add(state);
	}
	@Override
	public void removeState(WizardState state) {
		if (state == null) {
            throw new IllegalArgumentException("state is null Wizard hasState");
        }
		states.remove(state);
	}

}
