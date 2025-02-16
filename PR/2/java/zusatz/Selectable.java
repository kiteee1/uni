package a12236167;

public interface Selectable {
	
	int getSelectionValue();
	
	default boolean select(int digit) {
		return String.valueOf(getSelectionValue()).contains(String.valueOf(digit));
	}
	
}
