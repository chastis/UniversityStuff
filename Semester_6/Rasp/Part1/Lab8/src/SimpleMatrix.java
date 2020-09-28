import mpi.MPI;

// Послідовний алгоритм
public class SimpleMatrix {
    public static void calculate(String[] args, int matrixSize) {
        /*
        Будь-яка прикладна MPI-програма починається з виклику функції ініціалізації MPI: функції MPI.Init. В результаті
        виконання цієї функції створюється група процесів, в яку поміщаються всі процеси-додатки, і створюється область
        зв'язку, що описується визначеним комунікатором MPI.COMM_WORLD. Ця область зв'язку об'єднує всі процеси-додатки.
        */
        MPI.Init(args);

        // Номер процесу
        int procRank = MPI.COMM_WORLD.Rank();

        var matrixA = new Matrix(matrixSize, "A");
        var matrixB = new Matrix(matrixSize, "B");
        var matrixC = new Matrix(matrixSize, "C");
        long startTime = 0L;

        // Початкове наповнення виконується процесом номер 0
        if (procRank == 0) {
            matrixA.fillRandom(3);
            matrixB.fillRandom(3);
            startTime = System.currentTimeMillis();
        }

        // Перемноження
        for (int i = 0; i < matrixA.width; i++)
            for (int j = 0; j < matrixB.height; j++)
                for (int k = 0; k < matrixA.height; k++)
                    matrixC.matrix[i * matrixA.width + j] += matrixA.matrix[i * matrixA.width + k] * matrixB.matrix[k * matrixB.width + j];

        // Повідомлення результатів
        if (procRank == 0) {
            System.out.print("1) matrixSize = " + matrixSize + ", ");
            System.out.println(System.currentTimeMillis() - startTime + " ms");
        }
        MPI.Finalize();
    }
}