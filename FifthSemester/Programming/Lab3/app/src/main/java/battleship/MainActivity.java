package battleship;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.Button;
import android.widget.GridView;
import android.widget.TextView;

import java.util.ArrayList;

/**
 * android activity for game play
 *
 * @author chastis
 */
public class MainActivity extends AppCompatActivity {
    private int numCellsBoardSide;
    private TextView textViewGameStage, textViewMessage;
    private Button buttonAttack, buttonUpgrade, buttonRestart;
    private GridView gridViewBoard1, gridViewBoard2;
    private AdapterBoard adapterBoard1, adapterBoard2;

    /**
     * passes variables to class Game and initializes game
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_activity);

        setFields();
        enableGame();
    }

    private void enableGame() {
        Game game = Game.getInstance();
        game.setFields(this, numCellsBoardSide, textViewGameStage, textViewMessage,
                buttonAttack, buttonUpgrade, buttonRestart,
                gridViewBoard1, gridViewBoard2, adapterBoard1, adapterBoard2);
        game.initialize();
    }

    private void setFields() {
        numCellsBoardSide = getResources().getInteger(R.integer.num_cells_board_side);
        textViewGameStage = (TextView) findViewById(R.id.text_view_game_stage);
        textViewMessage = (TextView) findViewById(R.id.text_view_message);
        buttonRestart = (Button) findViewById(R.id.button_initialize);
        buttonAttack = (Button) findViewById(R.id.button_attack);
        buttonUpgrade = (Button) findViewById(R.id.button_upgrade);
        gridViewBoard1 = (GridView) findViewById(R.id.gridViewBoard1);
        gridViewBoard2 = (GridView) findViewById(R.id.gridViewBoard2);
        adapterBoard1 = new AdapterBoard(this, new ArrayList<Cell>());
        adapterBoard2 = new AdapterBoard(this, new ArrayList<Cell>());
    }
}
