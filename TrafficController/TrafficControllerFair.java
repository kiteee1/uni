package assigment2;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class TrafficControllerFair implements TrafficController {
    private final TrafficRegistrar registrar;
    private final ReentrantLock lock;
    private final Condition bridgeAvailable;
    private boolean bridgeOccupied = false;

    public TrafficControllerFair(TrafficRegistrar registrar) {
        this.registrar = registrar;
        this.lock = new ReentrantLock(true);
        this.bridgeAvailable = lock.newCondition();
    }

    @Override
    public void enterRight(Vehicle v) {
        lock.lock();
        try {
            while (bridgeOccupied) {
                try {
                    bridgeAvailable.await();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
            bridgeOccupied = true;
            registrar.registerRight(v);
        } finally {
            lock.unlock();
        }
    }

    @Override
    public void enterLeft(Vehicle v) {
        lock.lock();
        try {
            while (bridgeOccupied) {
                try {
                    bridgeAvailable.await();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
            bridgeOccupied = true;
            registrar.registerLeft(v);
        } finally {
            lock.unlock();
        }
    }

    @Override
    public void leaveLeft(Vehicle v) {
        lock.lock();
        try {
            bridgeOccupied = false;
            registrar.deregisterLeft(v);
            bridgeAvailable.signal();
        } finally {
            lock.unlock();
        }
    }

    @Override
    public void leaveRight(Vehicle v) {
        lock.lock();
        try {
            bridgeOccupied = false;
            registrar.deregisterRight(v);
            bridgeAvailable.signal();
        } finally {
            lock.unlock();
        }
    }
}

