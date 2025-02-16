package assigment1;

import java.util.List;
import java.io.*;
import java.util.ArrayList;

public class PropertyManagementSerializationDAO implements PropertyManagementDAO {

	private String filename;
    private List<Apartment> apartments;
    
    @SuppressWarnings("unchecked")
	public PropertyManagementSerializationDAO(String filename) {
        this.filename = filename;
        this.apartments = new ArrayList<>();
        
        File file = new File(filename);
        if (file.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(file))) {
                apartments = (List<Apartment>) ois.readObject();
            } catch (IOException | ClassNotFoundException e) {
                System.out.println("Deserialization error: " + e.getMessage());
                System.exit(1);
            }
        } else {
            apartments = new ArrayList<>();
        }
    }
	
	@Override
	public List<Apartment> getApartments() {
		return new ArrayList<>(apartments);
	}

	@Override
	public Apartment getApartmentById(int id) {
		for (Apartment apt : apartments) {
            if (apt.getId() == id) {
                return apt;
            }
        }
        return null;
	}

	@Override
	public void saveApartment(Apartment apartment) {
        if (getApartmentById(apartment.getId()) != null) {
            throw new IllegalArgumentException("Apartment already exists. (id=" + apartment.getId() + ")");
        }
        apartments.add(apartment);

        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) {
            oos.writeObject(apartments);
        } catch (IOException e) {
            System.out.println("Serialization error: " + e.getMessage());
            System.exit(1);
        }
		
	}

	@Override
	public void deleteApartment(int id) {
		Apartment apt = getApartmentById(id);
        if (apt == null) {
            throw new IllegalArgumentException("Apartment not found. (id=" + id + ")");
        }
        apartments.remove(apt);
        
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) {
            oos.writeObject(apartments);
        } catch (IOException e) {
            System.out.println("Serialization error: " + e.getMessage());
            System.exit(1);
        }
		
	}

}
