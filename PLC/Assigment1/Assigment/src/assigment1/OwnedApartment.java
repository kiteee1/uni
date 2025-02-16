package assigment1;

import java.io.Serializable;
import java.text.DecimalFormat;


public class OwnedApartment extends Apartment implements Serializable{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private double operatingCostsPerSqMeter;
    private double maintenanceReservePerSqMeter;
	
	public OwnedApartment(int id, double area, int numberOfRooms, int floor, int yearOfConstruction, int postalCode,
			String street, int houseNumber, int apartmentNumber,
			double operatingCostsPerSqMeter, double maintenanceReservePerSqMeter) {
		super(id, area, numberOfRooms, floor, yearOfConstruction, postalCode, street, houseNumber, apartmentNumber);
		
		if(operatingCostsPerSqMeter < 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		
		if(maintenanceReservePerSqMeter < 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		
		this.operatingCostsPerSqMeter = operatingCostsPerSqMeter;
        this.maintenanceReservePerSqMeter = maintenanceReservePerSqMeter;
    }
	

	

	public double getOperatingCostsPerSqMeter() {
		return operatingCostsPerSqMeter;
	}

	public void setOperatingCostsPerSqMeter(double operatingCostsPerSqMeter) {
		if(operatingCostsPerSqMeter < 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		this.operatingCostsPerSqMeter = operatingCostsPerSqMeter;
	}

	public double getMaintenanceReservePerSqMeter() {
		return maintenanceReservePerSqMeter;
	}

	public void setMaintenanceReservePerSqMeter(double maintenanceReservePerSqMeter) {
		if(maintenanceReservePerSqMeter < 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		this.maintenanceReservePerSqMeter = maintenanceReservePerSqMeter;
	}
	
	@Override
	public double getTotalCost() {
		double baseCost = (operatingCostsPerSqMeter + maintenanceReservePerSqMeter) * getArea();
        double surchargePercentage = getFloor() * 0.02;
        double surcharge = baseCost * surchargePercentage;
        return baseCost + surcharge;
	}

	@Override
	public String toString() {
		 DecimalFormat df = Apartment.getDecimalFormat();
	        return "OwnedApartment [ID: " + getId() +
	                ", Area: " + df.format(getArea()) +
	                ", Rooms: " + getNumberOfRooms() +
	                ", Floor: " + getFloor() +
	                ", Year: " + getYearOfConstruction() +
	                ", Age: " + getAge() +
	                ", Operating Costs per m²: " + df.format(operatingCostsPerSqMeter) +
	                ", Maintenance Reserve per m²: " + df.format(maintenanceReservePerSqMeter) +
	                ", Total Cost: " + df.format(getTotalCost()) +
	                ", " + getAddress().toString() + "]";
	    
	}

}