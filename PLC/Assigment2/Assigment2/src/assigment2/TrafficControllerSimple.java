package assigment2;

public class TrafficControllerSimple implements TrafficController {
    private final TrafficRegistrar registrar;
    private boolean bridgeOccupied = false;

    public TrafficControllerSimple(TrafficRegistrar registrar) {
        this.registrar = registrar;
    }

    @Override
    public synchronized void enterRight(Vehicle v) {
        while (bridgeOccupied) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        bridgeOccupied = true;
        this.registrar.registerRight(v);
    }

    @Override
    public synchronized void enterLeft(Vehicle v) {
        while (bridgeOccupied) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        bridgeOccupied = true;
        this.registrar.registerLeft(v);
    }

    @Override
    public synchronized void leaveLeft(Vehicle v) {
        bridgeOccupied = false;
        this.registrar.deregisterLeft(v);
        notifyAll();
    }

    @Override
    public synchronized void leaveRight(Vehicle v) {
        bridgeOccupied = false;
        this.registrar.deregisterRight(v);
        notifyAll();
    }
}
