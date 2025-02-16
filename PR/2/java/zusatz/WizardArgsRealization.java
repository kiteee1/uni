package a12236167;

public class WizardArgsRealization {
	private String name ; // not null not empty
	private MagicLevel level ; // not null
	private int basicHP ; // not negative
	private int HP ; // not negative ; defaults to basicHP
	private int basicMP ; // not less than the manapoints associated with the
	// magic level
	private int MP ; // not negative ; defaults to basicMP
	private int money ; // not negative
	
	public WizardArgsRealization(String name, MagicLevel level, int basicHP, int HP, int basicMP, int MP, int money) {
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
		
        this.setName(name);
        this.setLevel(level);
        this.setBasicHP(basicHP);
        this.setHP(HP);
        this.setBasicMP(basicMP);
        this.setMP(MP);
        this.setMoney(money);
	}
	
	
	//Get and Set
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public MagicLevel getLevel() {
		return level;
	}

	public void setLevel(MagicLevel level) {
		this.level = level;
	}

	public int getBasicHP() {
		return basicHP;
	}

	public void setBasicHP(int basicHP) {
		this.basicHP = basicHP;
	}

	public int getHP() {
		return HP;
	}

	public void setHP(int HP) {
		this.HP = HP;
	}

	public int getBasicMP() {
		return basicMP;
	}

	public void setBasicMP(int basicMP) {
		this.basicMP = basicMP;
	}

	public int getMP() {
		return MP;
	}

	public void setMP(int mP) {
		MP = mP;
	}

	public int getMoney() {
		return money;
	}

	public void setMoney(int money) {
		this.money = money;
	}
	
	
	
	 
	public boolean isDead () {return HP == 0;}
	// return true , if HP is 0 , false otherwise
	
	
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
	
	public boolean canAfford(int amount) {
		if(amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard canAfford");
		}
		return money >= amount;
	}
	
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
	
	public void takeDamage(int amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard takeDamage");
        }

        HP = Math.max(HP - amount, 0);
    }
	
	public void takeDamagePercent(int percentage) {
        if (percentage < 0 || percentage > 100) {
            throw new IllegalArgumentException("percentage out of bounds Wizard takeDamagePercent");
        }

        HP = (int) Math.max(HP - basicHP * (percentage / 100.0), 0);
    }
	
	public void weakenMagic(int amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard weakenMagic");
        }

        HP = Math.max(MP - amount, 0);
    }
	
	public void weakenMagicPercent(int percentage) {
        if (percentage < 0 || percentage > 100) {
            throw new IllegalArgumentException("percentage out of bounds Wizard weakenMagicPercent");
        }

        HP = (int) Math.max(MP - basicMP * (percentage / 100.0), 0);
	}
	
    public void heal(int amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard heal");
        }

        HP += amount;
    }
	
    public void healPercent(int percentage) {
        if (percentage < 0 || percentage > 100) {
            throw new IllegalArgumentException("percentage out of bounds Wizard healPercent");
        }

        HP = (int) Math.max(HP + basicHP * (percentage / 100.0), 0);
	}
	
    public void enforceMagic(int amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("amount < 0 Wizard enforceMagic");
        }

        MP += amount;
    }
	
    public void enforceMagicPercent(int percentage) {
        if (percentage < 0 || percentage > 100) {
            throw new IllegalArgumentException("percentage out of bounds Wizard enforceMagicPercent");
        }

        HP = (int) Math.max(MP + basicMP * (percentage / 100.0), 0);
	}
	
}
