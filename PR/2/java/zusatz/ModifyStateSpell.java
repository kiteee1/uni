package a12236167;

public class ModifyStateSpell extends Spell{
	private WizardState type;
	
	protected ModifyStateSpell(String name, int manaCost, MagicLevel levelNeeded, WizardState type) {
		super(name, manaCost, levelNeeded);
		
        if (type == null) {
            throw new IllegalArgumentException("type null ModifyStateSpell");
        }
        this.type = type;
        
	}

	@Override
	public void doEffect(MagicEffectRealization target) {
		if (target == null) {
			throw new IllegalArgumentException("traget null AttackingSpell");
		}
		if (target.hasState(type)) {
			target.removeState(type);
		}
		else {
			target.addState(type);
		}
		
	}

}
