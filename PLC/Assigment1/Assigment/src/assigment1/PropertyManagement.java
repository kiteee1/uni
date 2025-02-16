package assigment1;

import java.util.ArrayList;
import java.util.List;

public class PropertyManagement {
	
	private PropertyManagementDAO propertyManagementDAO;
	
	public PropertyManagement(PropertyManagementDAO propertyManagementDAO) {
        if (propertyManagementDAO == null) {
            throw new IllegalArgumentException("Error: Invalid parameter.");
        }
        this.propertyManagementDAO = propertyManagementDAO;
    }
	
	public List<Apartment> getAllApartments() {
        return propertyManagementDAO.getApartments();
    }
	
	public Apartment getApartmentById(int id) {
        return propertyManagementDAO.getApartmentById(id);
    }
	
	public void addApartment(Apartment apartment) {
        if (apartment == null) {
            throw new IllegalArgumentException("Error: Invalid parameter.");
        }
        propertyManagementDAO.saveApartment(apartment);
    }
	
	public void deleteApartment(int id) {
        propertyManagementDAO.deleteApartment(id);
    }
	
	public int getTotalNumberOfApartments() {
        return propertyManagementDAO.getApartments().size();
    }
	
	public int getTotalNumberOfOwnedApartments() {
        int count = 0;
        for (Apartment apt : propertyManagementDAO.getApartments()) {
            if (apt instanceof OwnedApartment) {
                count++;
            }
        }
        return count;
    }
	
	public int getTotalNumberOfRentedApartments() {
        int count = 0;
        for (Apartment apt : propertyManagementDAO.getApartments()) {
            if (apt instanceof RentedApartment) {
                count++;
            }
        }
        return count;
    }
	
	public double getAverageTotalCost() {
        List<Apartment> apartments = propertyManagementDAO.getApartments();
        if (apartments.isEmpty()) {
            return 0.0;
        }
        double totalCost = 0.0;
        for (Apartment apt : apartments) {
            totalCost += apt.getTotalCost();
        }
        return totalCost / apartments.size();
    }
	
	public List<Integer> getOldestApartmentIds() {
        List<Apartment> apartments = propertyManagementDAO.getApartments();
        List<Integer> oldestApartmentIds = new ArrayList<>();
        if (apartments.isEmpty()) {
            return oldestApartmentIds;
        }

        int oldestAge = apartments.get(0).getAge();
        for (Apartment apt : apartments) {
            int age = apt.getAge();
            if (age > oldestAge) {
                oldestAge = age;
            }
        }

        for (Apartment apt : apartments) {
            if (apt.getAge() == oldestAge) {
                oldestApartmentIds.add(apt.getId());
            }
        }

        return oldestApartmentIds;
    }
}
