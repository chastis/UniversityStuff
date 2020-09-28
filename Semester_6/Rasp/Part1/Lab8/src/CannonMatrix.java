import mpi.Cartcomm;
import mpi.MPI;

import java.util.Arrays;

// Метод Кенона
public class CannonMatrix {
    // Координати поточного потоку в декартовій решітці потоків
    private static int[] gridCoords = new int[2];

    // Комунікатор для рядків потоків
    private static Cartcomm ColComm;

    // Комунікатор для ствпчиків потоків
    private static Cartcomm RowComm;

    // Розподілення блоків між потоками
    private static void matrixScatter(int[] matrix, int[] matrixBlock, int matrixSize, int blockSize) {
        int[] matrixRow = new int[blockSize * matrixSize];
        if (gridCoords[1] == 0)
            ColComm.Scatter(matrix, 0, blockSize * matrixSize, MPI.INT, matrixRow, 0, blockSize * matrixSize, MPI.INT, 0);
        for (int i = 0; i < blockSize; i++) {
            int[] subRow = Arrays.copyOfRange(matrixRow, i * matrixSize, matrixRow.length);
            int[] subRowRes = new int[blockSize];

            RowComm.Scatter(subRow, 0, blockSize, MPI.INT, subRowRes, 0, blockSize, MPI.INT, 0);
            System.arraycopy(subRowRes, 0, matrixBlock, i * blockSize, blockSize);
        }
    }

    public static void calculate(String[] args, int matrixSize) {
        MPI.Init(args);

        int procRank = MPI.COMM_WORLD.Rank();
        int procNum = MPI.COMM_WORLD.Size();
        int gridSize = (int) Math.sqrt(procNum);

        if (procNum != gridSize * gridSize) {
            if (procRank == 0)
                System.out.println("4) " + matrixSize + " x " + matrixSize + ", 0 ms (procNum != gridSize * gridSize)");
            MPI.Finalize();
            return;
        }

        // Комунікатор для декартової решітки потоків
        Cartcomm gridComm;

        // Розмір блоку
        int blockSize = matrixSize / gridSize;

        // Виділення кожному з потоків місця для зберігання блоків з кожної матриці
        var matrixA = new Matrix(matrixSize, "A");
        var matrixB = new Matrix(matrixSize, "B");
        var matrixC = new Matrix(matrixSize, "C");

        int[] ABlock = new int[blockSize * blockSize];
        int[] BBlock = new int[blockSize * blockSize];
        int[] CBlock = new int[blockSize * blockSize];

        long startTime = 0L;
        if (procRank == 0) {
            matrixA.fillRandom(5);
            matrixB.fillRandom(4);
            startTime = System.currentTimeMillis();
        }

        // Потреба у фіксації виміру решітки потоків
        boolean[] subdims = new boolean[2];

        /*
        Створення комунікатора COMM_CART з декартовою топологією з процесів комунікатора COMM_WORLD. Перший параметр
        задає розмірність одержуваної декартовой решітки, другий - це логічний масив, що визначає, чи є решітка
        періодичною (значення false) уздовж кожного виміру. reorder - логічний параметр, що визначає, що при значенні
        true системі дозволено змінювати порядок нумерації потоків для оптимізації розподілу потоків по фізичним
        процесорам використовуваного паралельного комп'ютера.
        */
        gridComm = MPI.COMM_WORLD.Create_cart(new int[]{gridSize, gridSize}, new boolean[]{false, false}, true);

        // Визначення декартових координат для кожного потоку
        gridCoords = gridComm.Coords(procRank);

        // Створення комунікаторів для кожного з рядків решітки потоків
        subdims[1] = true;
        RowComm = gridComm.Sub(subdims);

        // Створення комунікаторів для кожного зі стовпчиків решітки потоків
        subdims[0] = true;
        subdims[1] = false;
        ColComm = gridComm.Sub(subdims);

        // Розподілення задач для потоків декартової решітки
        matrixScatter(matrixA.matrix, ABlock, matrixSize, blockSize);
        matrixScatter(matrixB.matrix, BBlock, matrixSize, blockSize);

        /*
        Для кожного рядка і декартової решітки потоків (крім першого рядка) виконується циклічний зсув блоків матриці A
        на (i - 1) позицій вліво (тобто в напрямку зменшення номерів стовпців).
        */
        if (gridCoords[0] != 0) {
            int nextProc = gridCoords[1] - gridCoords[0];
            if (nextProc < 0)
                nextProc += gridSize;
            RowComm.Sendrecv_replace(ABlock, 0, blockSize * blockSize, MPI.INT, nextProc, 0, MPI.ANY_SOURCE, 0);
        }

        /*
        Для кожного стовпця j декартової решітки потоків (крім першого стовпця) виконується циклічний зсув блоків
        матриці B на (j - 1) позицій вгору (тобто в напрямку зменшення номерів рядків).
        */
        if (gridCoords[1] != 0) {
            int nextProc = gridCoords[0] - gridCoords[1];
            if (nextProc < 0) nextProc += gridSize;
            ColComm.Sendrecv_replace(BBlock, 0, blockSize * blockSize, MPI.INT, nextProc, 1, MPI.ANY_SOURCE, 1);
        }

        // Встановлення бар'єру
        MPI.COMM_WORLD.Barrier();

        // Блоки матриць A і B, які містяться в процесі (i, j) перемножуються, і результат додається до матриці Сij
        for (int i = 0; i < blockSize; i++)
            for (int j = 0; j < blockSize; j++)
                for (int k = 0; k < blockSize; k++)
                    CBlock[i * blockSize + j] += ABlock[i * blockSize + k] * BBlock[k * blockSize + j];

        /*
        Для кожного рядка виконується циклічне пересилання блоків матриці A, які містяться в кожному потоці цього рядка,
        в напрямку зменшення номерів стовпців.
        */
        for (int iter = 0; iter < gridSize - 1; iter++) {
            int nextProc = gridCoords[1] - 1;
            if (nextProc < 0)
                nextProc += gridSize;
            RowComm.Sendrecv_replace(ABlock, 0, blockSize, MPI.INT, nextProc, 0, MPI.ANY_SOURCE, 0);

            nextProc = gridCoords[0] - 1;
            if (nextProc < 0)
                nextProc += gridSize;

            /*
            Для кожного стовпця виконується циклічне пересилання блоків матриці B, які містяться в кожному потоці цього
            стовпця, в напрямку зменшення номерів рядків.
            */
            ColComm.Sendrecv_replace(BBlock, 0, blockSize, MPI.INT, nextProc, 1, MPI.ANY_SOURCE, 1);

            for (int i = 0; i < blockSize; i++)
                for (int j = 0; j < blockSize; j++)
                    for (int k = 0; k < blockSize; k++)
                        CBlock[i * blockSize + j] += ABlock[i * blockSize + k] * BBlock[k * blockSize + j];
        }

        // Результат
        int[] resultRow = new int[matrixSize * blockSize];
        for (int i = 0; i < blockSize; i++) {
            int[] subRow = Arrays.copyOfRange(CBlock, i * blockSize, CBlock.length);
            int[] subRowRes = new int[gridSize * blockSize];

            RowComm.Gather(subRow, 0, blockSize, MPI.INT, subRowRes, 0, blockSize, MPI.INT, 0);
            System.arraycopy(subRowRes, 0, resultRow, i * matrixSize, gridSize * blockSize);
        }

        if (gridCoords[1] == 0)
            ColComm.Gather(resultRow, 0, blockSize * matrixSize, MPI.INT, matrixC.matrix, 0, blockSize * matrixSize, MPI.INT, 0);

        if (procRank == 0) {
            System.out.print("4) matrixSize = " + matrixSize + ", ");
            System.out.println(System.currentTimeMillis() - startTime + " ms\n");
        }
        MPI.Finalize();
    }
}