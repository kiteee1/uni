package assigment1;

import java.io.Serializable;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.Locale;
import java.time.Year;

public abstract class Apartment implements Serializable{

    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public static DecimalFormat getDecimalFormat() {
		DecimalFormatSymbols dfs = DecimalFormatSymbols.getInstance();
		dfs.setDecimalSeparator('.');
		return new DecimalFormat("0.00", dfs);
	}	

	private int id;
	private double area;
	private int numberOfRooms;
	private int floor;
	private int yearOfConstruction;
	private Address address;

	public Apartment(int id, double area, int numberOfRooms, int floor, int yearOfConstruction,
                   int postalCode, String street, int houseNumber, int apartmentNumber) {
		if(id <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		if(area <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		if(numberOfRooms <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		if(floor <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		int currentYear = Year.now().getValue();
		if(yearOfConstruction > currentYear) {
			throw new IllegalArgumentException("Invalid year of construction.");
		}
		if(postalCode <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		if(street == null || street.isEmpty()) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		if(houseNumber <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		if(apartmentNumber <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		
		this.id = id;
        this.area = area;
        this.numberOfRooms = numberOfRooms;
        this.floor = floor;
        this.yearOfConstruction = yearOfConstruction;
        this.address = new Address(postalCode, street, houseNumber, apartmentNumber);
		
	}



	public int getId() {
		return id;
	}



	public void setId(int id) {
		if(id <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		this.id = id;
	}



	public double getArea() {
		return area;
	}



	public void setArea(double area) {
		if(area <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		this.area = area;
	}



	public int getNumberOfRooms() {
		return numberOfRooms;
	}



	public void setNumberOfRooms(int numberOfRooms) {
		if(numberOfRooms <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		this.numberOfRooms = numberOfRooms;
	}



	public int getFloor() {
		return floor;
	}



	public void setFloor(int floor) {
		if(floor <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		this.floor = floor;
	}



	public int getYearOfConstruction() {
		return yearOfConstruction;
	}



	public void setYearOfConstruction(int yearOfConstruction) {
		int currentYear = Year.now().getValue();
		if (yearOfConstruction > currentYear) {
			throw new IllegalArgumentException("Error: Invalid year of construction.");
		}
		this.yearOfConstruction = yearOfConstruction;
	}



	public Address getAddress() {
		return address;
	}



	public void setAddress(int postalCode, String street, int houseNumber, int apartmentNumber) {
		if(postalCode <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		if(street == null || street.isEmpty()) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		if(houseNumber <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		if(apartmentNumber <= 0) {
			throw new IllegalArgumentException("Error: Invalid parameter.");
		}
		this.address = new Address(postalCode, street, houseNumber, apartmentNumber);
	}
	
	public int getAge() {
        int currentYear = Year.now().getValue();
        return currentYear - this.yearOfConstruction;
    }

	public abstract double getTotalCost();


	class Address implements Serializable{
		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		private int postalCode;
		private String street;
		private int houseNumber;
		private int apartmentNumber;

		public Address(int postalCode, String street, int houseNumber, int apartmentNumber) {
			if(postalCode <= 0) {
				throw new IllegalArgumentException("Error: Invalid parameter.");
			}
			if(street == null || street.isEmpty()) {
				throw new IllegalArgumentException("Error: Invalid parameter.");
			}
			if(houseNumber <= 0) {
				throw new IllegalArgumentException("Error: Invalid parameter.");
			}
			if(apartmentNumber <= 0) {
				throw new IllegalArgumentException("Error: Invalid parameter.");
			}

			this.setPostalCode(postalCode);
			this.setStreet(street);
			this.setHouseNumber(houseNumber);
			this.setApartmentNumber(apartmentNumber);
		}

		public int getPostalCode() {
			return postalCode;
		}

		public void setPostalCode(int postalCode) {
			if(postalCode <= 0) {
				throw new IllegalArgumentException("Error: Invalid parameter.");
			}
			this.postalCode = postalCode;
		}

		public String getStreet() {
			return street;
		}

		public void setStreet(String street) {
			if(street == null || street.isEmpty()) {
				throw new IllegalArgumentException("Error: Invalid parameter.");
			}
			this.street = street;
		}

		public int getHouseNumber() {
			return houseNumber;
		}

		public void setHouseNumber(int houseNumber) {
			if(houseNumber <= 0) {
				throw new IllegalArgumentException("Error: Invalid parameter.");
			}
			this.houseNumber = houseNumber;
		}

		public int getApartmentNumber() {
			return apartmentNumber;
		}

		public void setApartmentNumber(int apartmentNumber) {
			if(apartmentNumber <= 0) {
				throw new IllegalArgumentException("Error: Invalid parameter.");
			}
			this.apartmentNumber = apartmentNumber;
		}
		
		@Override
		public String toString() {
			return "Address: " + street + " " + houseNumber + ", Apt " + apartmentNumber + ", " + postalCode;
		}
	}

	@Override
	public abstract String toString();
}

