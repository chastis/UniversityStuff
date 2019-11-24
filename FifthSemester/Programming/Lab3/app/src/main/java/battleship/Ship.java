package battleship;

import java.util.ArrayList;
import java.util.List;

/**
 * each ship: how many cells left to arrange, how many attacks left,...
 *
 * @author chastis
 */
public class Ship {
    private int numCellsAdded = 0;
    private int numAttacksMade = 0;
    private int numUpgradesMade = 0;
    private int numUpgradesAllowed = 3;
    private int playerNum;
    private ShipType shipType;
    private int numCells;
    private int numAttacksAllowed;
    private List<Cell> cells;

    /**
     * creates ship according to ship type
     */
    public Ship(int playerNum, ShipType shipType) {
        this.playerNum = playerNum;
        this.shipType = shipType;
        setShipTypeDependentFields();
        cells = new ArrayList<>(numCells);
    }

    public void setNumAttacksMade(int numAttacksMade) {
        this.numAttacksMade = numAttacksMade;
    }

    public int getNumCells() {
        return numCells;
    }

    private void setShipTypeDependentFields() {
        if (shipType == ShipType.LITTLE_GUY) {
            numCells = 2;
            numAttacksAllowed = 1;
        } else if (shipType == ShipType.MIDDLE_MAN) {
            numCells = 3;
            numAttacksAllowed = 2;
        } else {
            numCells = 5;
            numAttacksAllowed = 3;
        }
    }

    /**
     * how many cells left to arrange this ship
     */
    public int getNumCellsToAdd() {
        return numCells - numCellsAdded;
    }

    /**
     * not done arranging this ship yet
     */
    public boolean canAddCells() {
        return getNumCellsToAdd() > 0;
    }

    /**
     * add 1 cell to ship during arrangement
     */
    public void addCell(Cell cell) {
        cell.setStatus(Cell.Status.OCCUPIED);
        cells.add(cell);
        numCellsAdded++;
    }

    /**
     * @return how many attacks left for this ship
     */
    public int getNumAttacksLeft() {
        return numAttacksAllowed - numAttacksMade;
    }

    /**
     * @return can ship still attack?
     */
    public boolean canAttack() {
        return isAlive() && getNumAttacksLeft() > 0;
    }

    /**
     * this ship now attacks 1 cell
     */
    public void attackCell(Cell cell) {
        if (cell.getStatus() == Cell.Status.VACANT)
            cell.setStatus(Cell.Status.MISSED);
        if (cell.getStatus() == Cell.Status.OCCUPIED)
            cell.setStatus(Cell.Status.HIT);
        numAttacksMade++;
    }

    public int getNumUpgradesLeft() {
        return numUpgradesAllowed - numUpgradesMade;
    }

    public boolean canUpgrade() {
        return isAlive() && getNumUpgradesLeft() > 0;
    }

    /**
     * increment attack count of this ship
     */
    public void upgrade() {
        numAttacksAllowed++;
        numUpgradesMade++;
    }

    /**
     * @return some cell hasn't been hit
     */
    public boolean isAlive() {
        for (Cell cell : cells)
            if (cell.getStatus() != Cell.Status.HIT)
                return true;
        return false;
    }

    public enum ShipType {
        LITTLE_GUY, MIDDLE_MAN, BIG_BOY
    }
}
