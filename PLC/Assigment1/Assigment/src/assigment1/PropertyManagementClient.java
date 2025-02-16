package assigment1;

import java.text.DecimalFormat;
import java.util.List;

public class PropertyManagementClient {
	 public static void main(String[] args) {
	    try {    
            if (args.length < 2) {
	            throw new IllegalArgumentException("Error: Invalid parameter.");
	        }

	        String filename = args[0];
	        String command = args[1];

	        PropertyManagementDAO dao = new PropertyManagementSerializationDAO(filename);
	        PropertyManagement propertyManagement = new PropertyManagement(dao);

	        try {
	            switch (command.toLowerCase()) {
	                case "list":
	                    handleListCommand(args, propertyManagement);
	                    break;
	                case "add":
	                    handleAddCommand(args, propertyManagement);
	                    break;
	                case "delete":
	                    handleDeleteCommand(args, propertyManagement);
	                    break;
	                case "count":
	                    handleCountCommand(args, propertyManagement);
	                    break;
	                case "meancosts":
	                    handleMeanCostsCommand(propertyManagement);
	                    break;
	                case "oldest":
	                    handleOldestCommand(propertyManagement);
	                    break;
	                default:
	                    System.out.println("Error: Invalid parameter.");
	            }
	        } catch (IllegalArgumentException e) {
	            System.out.println("Error: " + e.getMessage());
	        }
        } catch (Exception e) {
            System.out.println("Error: Invalid parameter.");
        }
	}


	    private static void handleListCommand(String[] args, PropertyManagement propertyManagement) {
	        if (args.length == 2) {

	            List<Apartment> apartments = propertyManagement.getAllApartments();
	            for (Apartment apt : apartments) {
	                printApartmentDetails(apt);
	            }
	        } else if (args.length == 3) {

	            int id;
	            try {
	                id = Integer.parseInt(args[2]);
	            } catch (NumberFormatException e) {
	                System.out.println("Error: Invalid parameter.");
	                return;
	            }
	            Apartment apt = propertyManagement.getApartmentById(id);
	            if (apt != null) {
	                printApartmentDetails(apt);
	            }
	        } else {
	            System.out.println("Error: Invalid parameter.");
	        }
	    }


	    private static void handleAddCommand(String[] args, PropertyManagement propertyManagement) {
	        if (args.length < 3) {
	            System.out.println("Error: Invalid parameter.");
	            return;
	        }

	        String type = args[2];

	        try {
	            if (type.equalsIgnoreCase("OA")) {
	                if (args.length != 14) {
	                    System.out.println("Error: Invalid parameter.");
	                    return;
	                }

	                int index = 3;
	                int id = Integer.parseInt(args[index++]);
	                double area = Double.parseDouble(args[index++]);
	                int rooms = Integer.parseInt(args[index++]);
	                int floor = Integer.parseInt(args[index++]);
	                int year = Integer.parseInt(args[index++]);
	                int postalCode = Integer.parseInt(args[index++]);
	                String street = args[index++];
	                int houseNumber = Integer.parseInt(args[index++]);
	                int apartmentNumber = Integer.parseInt(args[index++]);
	                double operatingCosts = Double.parseDouble(args[index++]);
	                double reserveFund = Double.parseDouble(args[index++]);

	                OwnedApartment ownedApt = new OwnedApartment(id, area, rooms, floor, year,
	                        postalCode, street, houseNumber, apartmentNumber, operatingCosts, reserveFund);

	                propertyManagement.addApartment(ownedApt);
	                System.out.println("Info: Apartment " + id + " added.");
	            } else if (type.equalsIgnoreCase("RA")) {
	                if (args.length != 14) {
	                    System.out.println("Error: Invalid parameter.");
	                    return;
	                }

	                int index = 3;
	                int id = Integer.parseInt(args[index++]);
	                double area = Double.parseDouble(args[index++]);
	                int rooms = Integer.parseInt(args[index++]);
	                int floor = Integer.parseInt(args[index++]);
	                int year = Integer.parseInt(args[index++]);
	                int postalCode = Integer.parseInt(args[index++]);
	                String street = args[index++];
	                int houseNumber = Integer.parseInt(args[index++]);
	                int apartmentNumber = Integer.parseInt(args[index++]);
	                double rentPerSqMeter = Double.parseDouble(args[index++]);
	                int tenants = Integer.parseInt(args[index++]);

	                RentedApartment rentedApt = new RentedApartment(id, area, rooms, floor, year,
	                        postalCode, street, houseNumber, apartmentNumber, rentPerSqMeter, tenants);

	                propertyManagement.addApartment(rentedApt);
	                System.out.println("Info: Apartment " + id + " added.");
	            } else {
	                System.out.println("Error: Invalid parameter.");
	            }
	        } catch (NumberFormatException e) {
	            System.out.println("Error: Invalid parameter.");
	        } catch (IllegalArgumentException e) {
	            System.out.println("Error: " + e.getMessage());
	        }
	    }

	    private static void handleDeleteCommand(String[] args, PropertyManagement propertyManagement) {
	        if (args.length != 3) {
	            System.out.println("Error: Invalid parameter.");
	            return;
	        }
	        int id;
	        try {
	            id = Integer.parseInt(args[2]);
	        } catch (NumberFormatException e) {
	            System.out.println("Error: Invalid parameter..");
	            return;
	        }

	        try {
	            propertyManagement.deleteApartment(id);
	            System.out.println("Info: Apartment " + id + " deleted.");
	        } catch (IllegalArgumentException e) {
	            System.out.println("Error: " + e.getMessage());
	        }
	    }

	    private static void handleCountCommand(String[] args, PropertyManagement propertyManagement) {
	        if (args.length == 2) {
	            int total = propertyManagement.getTotalNumberOfApartments();
	            System.out.println(total);
	        } else if (args.length == 3) {
	            String type = args[2];
	            if (type.equalsIgnoreCase("RA")) {
	                int total = propertyManagement.getTotalNumberOfRentedApartments();
	                System.out.println(total);
	            } else if (type.equalsIgnoreCase("OA")) {
	                int total = propertyManagement.getTotalNumberOfOwnedApartments();
	                System.out.println(total);
	            } else {
	                System.out.println("Error: Invalid parameter.");
	            }
	        } else {
	            System.out.println("Error: Invalid parameter.");
	        }
	    }

	    private static void handleMeanCostsCommand(PropertyManagement propertyManagement) {
	        double meanCosts = propertyManagement.getAverageTotalCost();
	        DecimalFormat df = Apartment.getDecimalFormat();
	        System.out.println(df.format(meanCosts));
	    }

	    private static void handleOldestCommand(PropertyManagement propertyManagement) {
	        List<Integer> oldestIds = propertyManagement.getOldestApartmentIds();
	        for (int id : oldestIds) {
	            System.out.println("Id: " + id);
	        }
	    }

	    private static void printApartmentDetails(Apartment apt) {
	        if (apt instanceof OwnedApartment) {
	            System.out.println("Type:              OA");
	        } else if (apt instanceof RentedApartment) {
	            System.out.println("Type:              RA");
	        }
	        System.out.println("Id:                " + apt.getId());
	        DecimalFormat df = Apartment.getDecimalFormat();
	        System.out.println("Area:              " + df.format(apt.getArea()));
	        System.out.println("Rooms:             " + apt.getNumberOfRooms());
	        System.out.println("Floor:             " + apt.getFloor());
	        System.out.println("Year Built:        " + apt.getYearOfConstruction());
	        Apartment.Address address = apt.getAddress();
	        System.out.println("Postal Code:       " + address.getPostalCode());
	        System.out.println("Street:            " + address.getStreet());
	        System.out.println("House Number:      " + address.getHouseNumber());
	        System.out.println("Apartment:         " + address.getApartmentNumber());
	        if (apt instanceof OwnedApartment) {
	            OwnedApartment oa = (OwnedApartment) apt;
                System.out.println("Operating Costs:   " + df.format(oa.getOperatingCostsPerSqMeter()));
	            System.out.println("Reserve Fund:      " + df.format(oa.getMaintenanceReservePerSqMeter()));
	        } else if (apt instanceof RentedApartment) {
	            RentedApartment ra = (RentedApartment) apt;
	            System.out.println("Rent/m2:           " + df.format(ra.getMonthlyRentPerSqMeter()));
	            System.out.println("Number of Tenants: " + ra.getNumberOfTenants());
	        }
	    }
}
