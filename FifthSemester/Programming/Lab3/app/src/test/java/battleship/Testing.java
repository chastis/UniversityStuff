package battleship;

import org.junit.Test;
//import android.support.test.rule.ActivityTestRule;

public class Testing {
//Can't test GUI elements without Espresso
//    @Test
//    public void MenuTest() throws Exception
//    {
//
//        MainMenu menu = new MainMenu();
//        menu.onCreate(null);
//        menu.startActivity(new Intent("team2.battleship.MainActivity"));
//        assert (menu != null);
//        MainActivity activity = new MainActivity();
//        activity.onCreate(null);
//        System.out.println();
//    }

    //tests the cell class
    @Test
    public void CellTest() throws Exception
    {
        Cell cell = new Cell(2, Cell.Status.VACANT);
        assert cell.getPlayerNum() == 2;
        assert cell.getStatus() == Cell.Status.VACANT;
        cell.setStatus(Cell.Status.HIT);
        assert cell.getStatus() == Cell.Status.HIT;
    }

    //tests the mathmodel class
    @Test
    public void MathTest() throws Exception
    {
        Player p2;
        MathModel math = MathModel.getInstance();
        assert (math != null);
    }

    //tests the game class
    @Test
    public void GameTest() throws Exception
    {
        Game game = Game.getInstance();
        game.setFields(null,0,null,null,null,null,null,null,null,null,null);

        //Can't test this without Espresso
        //game.initialize();
        //assert game.
    }

    //tests the ship class
    @Test
    public void ShipTest() throws Exception
    {
        Ship ship1 = new Ship(2, Ship.ShipType.LITTLE_GUY);

        assert ship1.getNumCells() == 2;
        assert ship1.getNumCellsToAdd() == 2;
        assert ship1.canAddCells();
        Cell cell1 = new Cell(1, Cell.Status.HIT);
        Cell cell2 = new Cell(2, Cell.Status.HIT);
        ship1.addCell(cell1);
        ship1.addCell(cell2);
        assert !ship1.canAddCells();
        assert ship1.getNumCellsToAdd() == 0;
        assert ship1.isAlive(); //it should be alive even though we added cells that were constructed as hits
        assert ship1.canAttack();
        assert ship1.getNumAttacksLeft() == 1;
        ship1.attackCell(cell1);
        assert ship1.getNumAttacksLeft() == 0;
        assert ship1.isAlive(); //ship shouldn't die from one shot. yes, we're firing on ourselves here.
        assert ship1.canUpgrade();
        assert ship1.getNumUpgradesLeft() == 3;
        ship1.upgrade();
        assert ship1.getNumUpgradesLeft() == 2;
        assert ship1.getNumAttacksLeft() == 1;
    }

    //tests the player class
    @Test
    public void PlayerTest() throws Exception {
        Player player = new Player(2);
        assert !player.getShips().isEmpty();
        assert player.getShips().size() == player.getNumShips();
        assert player.getNumShipsArranged() == player.getShips().size() - player.getNumShips();
        assert player.canAddCell();
        Cell cell1 = new Cell(1, Cell.Status.HIT);
        player.addCell(cell1);
        player.addCell(cell1);
        assert player.getNumShipsArranged() == 1;
        assert player.canAttack();
        player.attackCell(cell1);
        player.upgrade();
        player.resetNumsAttacksMade();
        assert !player.canAttack(); //even though we reset attacks, player should not be able to attack because we fired on ourselves and destroyed our own ship
        assert player.getNumShipsAlive() == 0; //we only had one ship, and it's dead
        assert !player.isAlive(); //player has no living ships
    }
}
