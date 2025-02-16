package assigment1;

import java.io.Serializable;
import java.text.DecimalFormat;


public class RentedApartment extends Apartment implements Serializable{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private double monthlyRentPerSqMeter;
    private int numberOfTenants;
	
	public RentedApartment(int id, double area, int numberOfRooms, int floor, int yearOfConstruction, int postalCode,
			String street, int houseNumber, int apartmentNumber,
			 double monthlyRentPerSqMeter, int numberOfTenants) {
		super(id, area, numberOfRooms, floor, yearOfConstruction, postalCode, street, houseNumber, apartmentNumber);
		
		if(monthlyRentPerSqMeter < 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		
		if(numberOfTenants < 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		
		this.monthlyRentPerSqMeter = monthlyRentPerSqMeter;
        this.numberOfTenants = numberOfTenants;
    }
	

	

	public double getMonthlyRentPerSqMeter() {
        return monthlyRentPerSqMeter;
    }

    public void setMonthlyRentPerSqMeter(double monthlyRentPerSqMeter) {
        if (monthlyRentPerSqMeter <= 0) {
        	throw new IllegalArgumentException("Error: Invalid parameter.");
        }
        this.monthlyRentPerSqMeter = monthlyRentPerSqMeter;
    }

    public int getNumberOfTenants() {
        return numberOfTenants;
    }

    public void setNumberOfTenants(int numberOfTenants) {
        if (numberOfTenants <= 0) {
        	throw new IllegalArgumentException("Error: Invalid parameter.");
        }
        this.numberOfTenants = numberOfTenants;
    }
	
	@Override
	public double getTotalCost() {
		double baseRent = monthlyRentPerSqMeter * getArea();
        int additionalTenants = numberOfTenants - 1;
        double surchargePercentage = 0.0;

        if (additionalTenants > 0) {
            surchargePercentage = Math.min(additionalTenants * 0.025, 0.10); // 2.5% per additional tenant, max 10%
        }

        double surcharge = baseRent * surchargePercentage;
        return baseRent + surcharge;
	}

	@Override
	public String toString() {
		 DecimalFormat df = Apartment.getDecimalFormat();
	        return "RentedApartment [ID: " + getId() +
	                ", Area: " + df.format(getArea()) +
	                ", Rooms: " + getNumberOfRooms() +
	                ", Floor: " + getFloor() +
	                ", Year: " + getYearOfConstruction() +
	                ", Age: " + getAge() +
	                ", Monthly Rent per m²: " + df.format(monthlyRentPerSqMeter) +
	                ", Number of Tenants: " + numberOfTenants +
	                ", Total Cost: " + df.format(getTotalCost()) +
	                ", " + getAddress().toString() + "]";
	    
	}

}
