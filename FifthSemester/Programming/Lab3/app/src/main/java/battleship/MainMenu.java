package battleship;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;

/**
 * @author chastis
 */
public class MainMenu extends AppCompatActivity implements View.OnClickListener {
    Button button1;
    Button button11;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_menu);

        button1 = (Button) findViewById(R.id.button2);
        button1.setOnClickListener(this);
        button11 = (Button) findViewById(R.id.button5);
        button11.setOnClickListener(this);
    }

    private void button2Click() {
        startActivity(new Intent("battleship.MainActivity"));
    }

    private void button5Click() {
        startActivity(new Intent("battleship.Credits"));
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.button2:
                button2Click();
                break;

            case R.id.button5:
                button5Click();
                break;
        }
    }
}
