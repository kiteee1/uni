package a12236167;

public enum MagicLevel {
	NOOB(50, "*"),
    ADEPT(100, "**"),
    STUDENT(200, "***"),
    EXPERT(500, "****"),
    MASTER(1000, "*****");

    private int mp;
    private String representation;

    MagicLevel(int mp, String representation) {
        this.mp = mp;
        this.representation = representation;
    }

    public int toMana() {
        return mp;
    }

    @Override
    public String toString() {
        return representation;
    }
    
    /*
    public static void main(String[] args) {
        for (MagicLevel level : MagicLevel.values()) {
            System.out.println(level + " has " + level.toMana() + " MP.");
        }
    }
    */
}
