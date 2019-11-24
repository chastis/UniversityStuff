package battleship;

import java.util.ArrayList;
import java.util.List;

/**
 * player's fleet: how many ships have been arranged, which ship is attacking,...
 *
 * @author chastis
 */
public class Player {
    private int numShipsArranged = 0;
    private int numShips = 3;
    private int playerNum;
    private List<Ship> ships = new ArrayList<>(numShips);

    /**
     * fleet:
     * - little guy: occupies 2 cells, has 1 attack initially
     * - middle man: 3, 2
     * - big boy: 5, 3
     * each upgrade increments attack count of each (alive) ship
     */
    public Player(int playerNum) {
        this.playerNum = playerNum;

        Ship ship = new Ship(playerNum, Ship.ShipType.LITTLE_GUY);
        ships.add(ship);
        ship = new Ship(playerNum, Ship.ShipType.MIDDLE_MAN);
        ships.add(ship);
        ship = new Ship(playerNum, Ship.ShipType.BIG_BOY);
        ships.add(ship);
    }

    public int getNumShipsArranged() {
        return numShipsArranged;
    }

    public int getNumShips() {
        return numShips;
    }

    public List<Ship> getShips() {
        return ships;
    }

    private int getNumShipsToArrange() {
        return numShips - numShipsArranged;
    }

    public boolean canAddCell() {
        return getNumShipsToArrange() > 0;
    }

    /**
     * add cell to the ship being arranged
     */
    public void addCell(Cell cell) {
        Ship ship = ships.get(numShipsArranged);

        ship.addCell(cell);
        if (!ship.canAddCells())
            numShipsArranged++;
    }

    /**
     * @return 1 alive ship didn't finish attacking
     */
    public boolean canAttack() {
        for (Ship ship : ships)
            if (ship.canAttack())
                return true;
        return false;
    }

    /**
     * let attacking ship attack tapped cell
     */
    public void attackCell(Cell cell) {
        Ship ship = getNextShipCanAttack();
        ship.attackCell(cell);
    }

    /**
     * @return next attack will be made by which ship?
     */
    public Ship getNextShipCanAttack() {
        int index = 0;
        Ship ship;
        do {
            ship = ships.get(index);
            index++;
        } while (!ship.canAttack());
        return ship;
    }

    /**
     * upgrade fleet
     */
    public void upgrade() {
        for (Ship ship : ships)
            ship.upgrade();
    }

    /**
     * after done attacking
     */
    public void resetNumsAttacksMade() {
        for (Ship ship : ships)
            ship.setNumAttacksMade(0);
    }

    /**
     * @return how many ships in fleet are still alive?
     */
    public int getNumShipsAlive() {
        int numShipsAlive = 0;
        for (Ship ship : ships)
            if (ship.isAlive())
                numShipsAlive++;
        return numShipsAlive;
    }

    /**
     * @return >= 1 ship still alive
     */
    public boolean isAlive() {
        return getNumShipsAlive() > 0;
    }
}
