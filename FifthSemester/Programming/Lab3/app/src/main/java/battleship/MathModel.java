package battleship;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class MathModel {
    static private Player player;

    private static MathModel ourInstance = new MathModel();
    private static AdapterBoard adapterBoard;
    private static int x, y, cols;
    private static Random random = new Random();

    private MathModel() {
        x = 0;
        y = 0;
        cols = 1;
    }

    public static MathModel getInstance() {
        if (ourInstance == null)
            ourInstance = new MathModel();
        return ourInstance;
    }

    private static void setXYFromPos(int cols, int pos) {
        x = pos % cols;
        y = pos / cols;
    }

    private static int getPosFromXY() {
        return x * cols + y;
    }

    public static int getPosFromXY(int x, int y) {
        return x * cols + y;
    }

    //find random cell to initialize from
    private static void getEmptyCell() {
        do {
            x = random.nextInt(cols);
            y = random.nextInt(cols);
        }
        while (adapterBoard.getItem(getPosFromXY()).getStatus() == Cell.Status.OCCUPIED);
    }

    private static boolean isNorthValid(int size) {
        if (y - size < 0)
            return false;

        int source = getPosFromXY(x, y);
        for (int i = 0; i < size; i++)
            if (adapterBoard.getItem(source - i).getStatus() == Cell.Status.OCCUPIED)
                return false;

        return true;
    }

    private static void setNorthPlacement(int size) {
        for (int i = 0; i < size; i++)
            player.addCell(adapterBoard.getItem(getPosFromXY(x, y - i)));
    }

    private static boolean isEastValid(int size) {
        if (x + size > cols)
            return false;

        for (int i = 0; i < size; i++)
            if (adapterBoard.getItem(getPosFromXY(x + i, y)).getStatus() == Cell.Status.OCCUPIED)
                return false;

        return true;
    }

    private static void setEastPlacement(int size) {
        for (int i = 0; i < size; i++)
            player.addCell(adapterBoard.getItem(getPosFromXY(x + i, y)));
    }

    private static boolean isSouthValid(int size) {
        if (y + size > cols)
            return false;

        for (int i = 0; i < size; i++)
            if (adapterBoard.getItem(getPosFromXY(x, y + i)).getStatus() == Cell.Status.OCCUPIED)
                return false;

        return true;
    }

    private static void setSouthPlacement(int size) {
        for (int i = 0; i < size; i++)
            player.addCell(adapterBoard.getItem(getPosFromXY(x, y + i)));
    }

    private static boolean isWestValid(int size) {
        if (x - size < 0)
            return false;

        for (int i = 0; i < size; i++) {
            int nextX = x - i;
            if (nextX < 0 || adapterBoard.getItem(getPosFromXY(nextX, y)).getStatus() == Cell.Status.OCCUPIED)
                return false;
        }

        return true;
    }

    private static void setWestPlacement(int size) {
        for (int i = 0; i < size; i++)
            player.addCell(adapterBoard.getItem(getPosFromXY(x - i, y)));
    }

    //performs random sampling
    private static void setPlacement(int size) {
        boolean notPlaced = true;

        while (notPlaced) {
            List<Integer> sample = new ArrayList<>(4);
            sample.add(0);
            sample.add(1);
            sample.add(2);
            sample.add(3);

            getEmptyCell();

            while (!sample.isEmpty()) {
                int i = random.nextInt(sample.size());
                switch (sample.get(i)) {
                    case 0:
                        if (isNorthValid(size)) {
                            setNorthPlacement(size);
                            notPlaced = false;
                        } else
                            sample.remove(i);
                        break;
                    case 1:
                        if (isEastValid(size)) {
                            setEastPlacement(size);
                            notPlaced = false;
                        } else
                            sample.remove(i);
                        break;
                    case 2:
                        if (isSouthValid(size)) {
                            setSouthPlacement(size);
                            notPlaced = false;
                        } else
                            sample.remove(i);
                        break;
                    case 3:
                        if (isWestValid(size)) {
                            setWestPlacement(size);
                            notPlaced = false;
                        } else
                            sample.remove(i);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    //the main public function. this places ships in available squares.
    public static void generateShipPlacement(Player player2, AdapterBoard adapterBoard, int dim) {
        player = player2;

        MathModel.adapterBoard = adapterBoard;
        cols = dim;

        setPlacement(2); //small
        setPlacement(3); //medium
        setPlacement(5); //large
        //testPlacement();

        MathModel.adapterBoard.notifyDataSetChanged();
    }

    public static void testPlacement() {
        getEmptyCell();
        //x = 0;
        //y = 0;
        if (isEastValid(5)) {
            setEastPlacement(5);
        }
        if (isWestValid(5)) {
            setWestPlacement(5);
        }
    }
}
