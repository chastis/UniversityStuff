package battleship;

import android.content.Context;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.GridView;
import android.widget.TextView;

import java.util.Random;

/**
 * controls game flow
 *
 * @author chastis
 */
public class Game {
    private static Game instance;
    private Stage stage;
    private Context context;
    private int numCells1side;
    private TextView textViewGameStage, textViewMessage;
    private Button buttonAttack, buttonUpgrade, buttonRestart;
    private GridView gridViewBoard1, gridViewBoard2;
    private AdapterBoard adapterBoard1, adapterBoard2;
    private Player player1, player2;

    Cell checkL1, checkL2, checkL3, checkL4, checkL5;
    Cell checkM1, checkM2, checkM3;

    private Game() {
    }

    public static Game getInstance() {
        if (instance == null)
            instance = new Game();
        return instance;
    }

    public void setFields(Context context, int numCells1side,
                          TextView textViewGameStage, TextView textViewMessage,
                          Button buttonAttack, Button buttonUpgrade, Button buttonRestart,
                          GridView gridViewBoard1, GridView gridViewBoard2,
                          AdapterBoard adapterBoard1, AdapterBoard adapterBoard2) {
        this.context = context;
        this.numCells1side = numCells1side;
        this.textViewGameStage = textViewGameStage;
        this.textViewMessage = textViewMessage;
        this.buttonAttack = buttonAttack;
        this.buttonUpgrade = buttonUpgrade;
        this.buttonRestart = buttonRestart;
        this.gridViewBoard1 = gridViewBoard1;
        this.gridViewBoard2 = gridViewBoard2;
        this.adapterBoard1 = adapterBoard1;
        this.adapterBoard2 = adapterBoard2;
    }

    /**
     * [re]starts game by clearing boards and letting bot secretly arrange its fleet
     */
    public void initialize() {
        buttonRestart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                initialize();
            }
        });
        disableClicking();

        adapterBoard1.clear();
        adapterBoard2.clear();
        adapterBoard1.addCells(gridViewBoard1, 1, getNumCellsBoardArea());
        adapterBoard2.addCells(gridViewBoard2, 2, getNumCellsBoardArea());

        player1 = new Player(1);
        player2 = new Player(2);

        letP2arrange();
    }

    private void letP2arrange() {
//        generateShipPlacementDeprecated();
        MathModel.generateShipPlacement(player2, adapterBoard2, numCells1side); // Zach's code
        enableGameStageArranging();
    }

    private void enableGameStageArranging() {
        putGameStage(Stage.ARRANGING);
        letP1arrange();
    }

    private void letP1arrange() {
        gridViewBoard1.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Cell cell = (Cell) parent.getAdapter().getItem(position);
                player1.addCell(cell);
                adapterBoard1.notifyDataSetChanged();

                if (player1.canAddCell())
                    setMessage(player1.getShips().get(player1.getNumShipsArranged()).getNumCellsToAdd() +
                            " cell(s) left to add to your ship " +
                            (player1.getNumShipsArranged() + 1));
                else {
                    gridViewBoard1.setOnItemClickListener(null);

                    if (checkArrange()) // Paul's code
                        enableGameStageBattling();
                    else
                        setMessage("Invalid arrangement; click RESTART");
                }
            }
        });
    }

    private boolean checkArrange() {
        AdapterBoard adapterBoard = adapterBoard1;
        int c = 0;
        for (int i = 0; i < adapterBoard.getCount(); i++) {
            Cell cell = adapterBoard1.getItem(i);
            if (cell.getStatus() == Cell.Status.OCCUPIED) {
                c = c + 1;
                if (c == 10) {
                    if (((checkArrangeLH(adapterBoard)) || (checkArrangeLV(adapterBoard)))) {
                        if (((checkArrangeMH(adapterBoard)) || (checkArrangeMV(adapterBoard)))) {
                            if (((checkArrangeSH(adapterBoard)) || (checkArrangeSV(adapterBoard)))) {
                                return true;
                            }
                        }
                    }

                }
            }
        }
        return false;
    }

    private void enableGameStageBattling() {
        putGameStage(Stage.BATTLING);
        enableGameStageAttacking();

        buttonUpgrade.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                player1.upgrade();
                buttonUpgrade.setOnClickListener(null);
                letP2attack();
            }
        });
    }

    private void enableGameStageAttacking() {
        buttonAttack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                putGameStage(Stage.ATTACKING);
                buttonUpgrade.setOnClickListener(null);
                buttonAttack.setOnClickListener(null);
                letP1attack();
            }
        });
    }

    private void letP1attack() {
        gridViewBoard2.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Cell cell = (Cell) parent.getAdapter().getItem(position);
                player1.attackCell(cell);
                adapterBoard2.notifyDataSetChanged();

                if (!player2.isAlive()) {
                    disableClicking();
                    setMessage("you won; click RESTART");
                } else if (player1.canAttack()) {
                    Ship ship = player1.getNextShipCanAttack();
                    setMessage(ship.getNumAttacksLeft() + " attack(s) left for your ship " +
                            (player1.getShips().indexOf(ship) + 1));
                } else {
                    gridViewBoard2.setOnItemClickListener(null);
                    player1.resetNumsAttacksMade();
                    letP2attack();
                }
            }
        });
    }

    private void letP2attack() {
        Random random = new Random();
        while (player2.canAttack()) {
            Cell cell;
            do {
                cell = adapterBoard1.getItem(random.nextInt(getNumCellsBoardArea()));
            }
            while (cell.getStatus() == Cell.Status.HIT ||
                    cell.getStatus() == Cell.Status.MISSED);
            player2.attackCell(cell);
            adapterBoard1.notifyDataSetChanged();

            if (!player1.isAlive()) {
                disableClicking();
                setMessage("you lost; click RESTART");
                break;
            }
        }
        if (player1.isAlive()) {
            player2.resetNumsAttacksMade();
            enableGameStageBattling();
        }
    }

    private void putGameStage(Stage stage) {
        this.stage = stage;
        String msg = "Game stage: " + stage;
        textViewGameStage.setText(msg);
        describeGameStage();
    }

    private void describeGameStage() {
        String msg;
        if (stage == Stage.ARRANGING)
            msg = "tap cell on your board to arrange your " +
                    player1.getNumShips() + " ships";
        else if (stage == Stage.BATTLING)
            msg = "click ATTACK or UPGRADE";
        else
            msg = "tap cell on bot's board to attack its " +
                    player2.getNumShipsAlive() + " alive ship(s)";
        setMessage(msg);
    }

    private void setMessage(String msg) {
        textViewMessage.setText("Message: " + msg);
    }

    private void disableClicking() {
        buttonAttack.setOnClickListener(null);
        buttonUpgrade.setOnClickListener(null);
        gridViewBoard1.setOnItemClickListener(null);
        gridViewBoard2.setOnItemClickListener(null);
    }

    private int getNumCellsBoardArea() {
        return (int) Math.pow(numCells1side, 2);
    }

    private enum Stage {
        ARRANGING, BATTLING, ATTACKING
    }

    //checks to see if there is a valid Large Horizontal arrangement
    public boolean checkArrangeLH(AdapterBoard board) {
        int boardSize = (int) Math.sqrt(board.getCount());
        for (int i = 0; i < board.getCount() - 4; i++) {
            Cell cell = board.getItem(i);
            if (cell.getStatus() == Cell.Status.OCCUPIED) {
                if (((i + 1) % boardSize == boardSize - 1) ||
                        ((i + 2) % boardSize == boardSize - 1) ||
                        ((i + 3) % boardSize == boardSize - 1)) {
                    //loop continues
                } else {
                    Cell cell2 = board.getItem(i + 1);
                    if (cell2.getStatus() == Cell.Status.OCCUPIED) {
                        Cell cell3 = board.getItem(i + 2);
                        if (cell3.getStatus() == Cell.Status.OCCUPIED) {
                            Cell cell4 = board.getItem(i + 3);
                            if (cell4.getStatus() == Cell.Status.OCCUPIED) {
                                Cell cell5 = board.getItem(i + 4);
                                if (cell5.getStatus() == Cell.Status.OCCUPIED) {
                                    checkL1 = board.getItem(i);
                                    checkL2 = board.getItem(i + 1);
                                    checkL3 = board.getItem(i + 2);
                                    checkL4 = board.getItem(i + 3);
                                    checkL5 = board.getItem(i + 4);
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    //checks to see if there is a valid Large Vertical arrangement
    public boolean checkArrangeLV(AdapterBoard board) {
        int boardSize = (int) Math.sqrt(board.getCount());
        for (int i = 0; i < (board.getCount() - (boardSize * 4)); i++) {
            Cell cell = board.getItem(i);
            if (cell.getStatus() == Cell.Status.OCCUPIED) {
                Cell cell2 = board.getItem(i + boardSize);
                if (cell2.getStatus() == Cell.Status.OCCUPIED) {
                    Cell cell3 = board.getItem(i + boardSize * 2);
                    if (cell3.getStatus() == Cell.Status.OCCUPIED) {
                        Cell cell4 = board.getItem(i + boardSize * 3);
                        if (cell4.getStatus() == Cell.Status.OCCUPIED) {
                            Cell cell5 = board.getItem(i + boardSize * 4);
                            if (cell5.getStatus() == Cell.Status.OCCUPIED) {
                                checkL1 = board.getItem(i);
                                checkL2 = board.getItem(i + boardSize);
                                checkL3 = board.getItem(i + boardSize * 2);
                                checkL4 = board.getItem(i + boardSize * 3);
                                checkL5 = board.getItem(i + boardSize * 4);
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    //checks to see if there is a valid Medium Horizontal arrangement
    public boolean checkArrangeMH(AdapterBoard board) {
        int boardSize = (int) Math.sqrt(board.getCount());
        for (int i = 0; i < board.getCount() - 2; i++) {
            Cell cell = board.getItem(i);
            if (cell.getStatus() == Cell.Status.OCCUPIED) {
                if ((board.getItem(i) != checkL1) && (board.getItem(i) != checkL2) && (board.getItem(i) != checkL3) && (board.getItem(i) != checkL4) && (board.getItem(i) != checkL5)) {
                    if (((i + 1) % boardSize == boardSize - 1) ||
                            ((i + 2) % boardSize == boardSize - 1)) {
                        //loop continues
                    } else {
                        Cell cell2 = board.getItem(i + 1);
                        if (cell2.getStatus() == Cell.Status.OCCUPIED) {
                            Cell cell3 = board.getItem(i + 2);
                            if (cell3.getStatus() == Cell.Status.OCCUPIED) {
                                if ((cell3 != checkL1) && (cell3 != checkL2) && (cell3 != checkL3)
                                        && (cell3 != checkL4) && (cell3 != checkL5)) {
                                    checkM1 = board.getItem(i);
                                    checkM2 = board.getItem(i + 1);
                                    checkM3 = board.getItem(i + 2);
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }


    //checks to see if there is a valid Medium Vertical arrangement
    public boolean checkArrangeMV(AdapterBoard board) {
        int boardSize = (int) Math.sqrt(board.getCount());
        for (int i = 0; i < (board.getCount() - (boardSize * 2)); i++) {
            Cell cell = board.getItem(i);
            if (cell.getStatus() == Cell.Status.OCCUPIED) {
                if ((board.getItem(i) != checkL1) && (board.getItem(i) != checkL2) && (board.getItem(i) != checkL3) && (board.getItem(i) != checkL4) && (board.getItem(i) != checkL5)) {
                    Cell cell2 = board.getItem(i + boardSize);
                    if (cell2.getStatus() == Cell.Status.OCCUPIED) {
                        Cell cell3 = board.getItem(i + boardSize * 2);
                        if (cell3.getStatus() == Cell.Status.OCCUPIED) {
                            if ((cell3 != checkL1) && (cell3 != checkL2) && (cell3 != checkL3)
                                    && (cell3 != checkL4) && (cell3 != checkL5)) {
                                checkM1 = board.getItem(i);
                                checkM2 = board.getItem(i + boardSize);
                                checkM3 = board.getItem(i + boardSize * 2);
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }


    //checks to see if there is a valid Small Horizontal arrangement
    public boolean checkArrangeSH(AdapterBoard board) {
        int boardSize = (int) Math.sqrt(board.getCount());
        for (int i = 0; i < board.getCount(); i++) {
            Cell cell = board.getItem(i);
            if (cell.getStatus() == Cell.Status.OCCUPIED) {
                if ((board.getItem(i) != checkM1) && (board.getItem(i) != checkM2) && (board.getItem(i) != checkM3)
                        && ((board.getItem(i) != checkL1) && (board.getItem(i) != checkL2) && (board.getItem(i) != checkL3) && (board.getItem(i) != checkL4) && (board.getItem(i) != checkL5))) {
                    if ((i + 1) % boardSize == boardSize - 1) {
                        //loop continues
                    } else {
                        Cell cell2 = board.getItem(i + 1);
                        if (cell2.getStatus() == Cell.Status.OCCUPIED) {
                            if ((cell2 != checkM1) && (cell2 != checkM2) && (cell2 != checkM3)
                                    && (cell2 != checkL1) && (cell2 != checkL2) && (cell2 != checkL3)
                                    && (cell2 != checkL4) && (cell2 != checkL5)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }


    //checks to see if there is a valid Small Vertical arrangement
    public boolean checkArrangeSV(AdapterBoard board) {
        int boardSize = (int) Math.sqrt(board.getCount());
        for (int i = 0; i < (board.getCount() - boardSize); i++) {
            Cell cell = board.getItem(i);
            if (cell.getStatus() == Cell.Status.OCCUPIED) {
                if ((board.getItem(i) != checkM1) && (board.getItem(i) != checkM2) && (board.getItem(i) != checkM3)
                        && ((board.getItem(i) != checkL1) && (board.getItem(i) != checkL2) && (board.getItem(i) != checkL3) && (board.getItem(i) != checkL4) && (board.getItem(i) != checkL5))) {
                    Cell cell2 = board.getItem(i + boardSize);
                    if (cell2.getStatus() == Cell.Status.OCCUPIED) {
                        if ((cell2 != checkM1) && (cell2 != checkM2) && (cell2 != checkM3)
                                && (cell2 != checkL1) && (cell2 != checkL2) && (cell2 != checkL3)
                                && (cell2 != checkL4) && (cell2 != checkL5)) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
}
