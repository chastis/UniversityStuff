import mpi.MPI;

// Стрічкова схема
public class StringMatrix {
    public static void calculate(String[] args, int matrixSize) {
        MPI.Init(args);
        int procRank = MPI.COMM_WORLD.Rank();

        // Кількість потоків
        int procNum = MPI.COMM_WORLD.Size();

        var matrixA = new Matrix(matrixSize, "A");
        var matrixB = new Matrix(matrixSize, "B");
        var matrixC = new Matrix(matrixSize, "C");
        long startTime = 0L;

        if (procRank == 0) {
            matrixB.fillRandom(4);
            matrixA.fillRandom(4);
            startTime = System.currentTimeMillis();
        }

        /*
        В даному алгоритмі матриці розбиваються на неперервні послідовності рядків (стрічки). Нижче кожен процес
        використовується для обчислення однієї стрічки результуючого добутку матриць A і B. В цьому випадку процес
        повинен мати доступ до відповідної стрічки матриці A і всієї матриці B. Оскільки одночасне зберігання всієї
        матриці B у всіх процесах паралельної програми вимагає надмірних витрат пам'яті, обчислення організовуються
        таким чином, щоб у кожен момент часу процеси містили лише частину елементів матриці B (одну стрічку), а доступ
        до решти забезпечувався б за допомогою передачі повідомлень.
        */
        int lineHeight = matrixSize / procNum;

        /*
        Розмір буфера відповідає загальному розміру матриці, розділеному на кількість потоків (наприклад, якщо матриця
        має розмірність 100 * 100, а потоків - 4, тоді кожен буфер міститиме (lineHeight = 100 / 4 = 25) 25 * 100 = 2500
        елементів. Кожному потоку виділяється по три буфера.
        */
        int[] bufferA = new int[lineHeight * matrixSize];
        int[] bufferB = new int[lineHeight * matrixSize];
        int[] bufferC = new int[lineHeight * matrixSize];

        /*
        Scatter розподіляє частини задачі по всіх потоках з комунікатора (якщо потоків 4, то кожному дістається четверта
        частина кожної матриці. Перший параметр - звідки розподіляються дані, другий - зсув, третій - скільки припаде на
        1 потік, четвертий - тип даних (ціле), п'ятий - приймаючий буфер, далі - його розмір та тип даних, останній
        параметр - потік, що розподіляє дані.
        */
        MPI.COMM_WORLD.Scatter(matrixA.matrix, 0, lineHeight * matrixSize, MPI.INT, bufferA, 0, lineHeight * matrixSize, MPI.INT, 0);
        MPI.COMM_WORLD.Scatter(matrixB.matrix, 0, lineHeight * matrixSize, MPI.INT, bufferB, 0, lineHeight * matrixSize, MPI.INT, 0);

        // Для кожного потоку визначається його наступник та попередник для циклічного обміну даними
        int nextProc = (procRank + 1) % procNum;
        int prevProc = procRank - 1;
        if (prevProc < 0)
            prevProc = procNum - 1;
        int prevDataNum = procRank;

        // Стрічкове перемноження матриць
        for (int p = 0; p < procNum; p++) {
            for (int i = 0; i < lineHeight; i++)
                for (int j = 0; j < matrixSize; j++)
                    for (int k = 0; k < lineHeight; k++)
                        /*
                        Виконується множення стрічки матриці A на стрічку матриці B, що містяться в даному потоці, і
                        результат записується у відповідний елемент стрічки с результуючої матриці.
                        */
                        bufferC[i * matrixSize + j] += bufferA[prevDataNum * lineHeight + i * matrixSize + k] * bufferB[k * matrixSize + j];
            prevDataNum -= 1;
            if (prevDataNum < 0)
                prevDataNum = procNum - 1;

            /*
            Виконується циклічне пересилання стрічки з матриці B у сусідні процеси (напрямок пересилки - за зростанням
            рангів процесів).
            */
            MPI.COMM_WORLD.Sendrecv_replace(bufferB, 0, lineHeight * matrixSize, MPI.INT, nextProc, 0, prevProc, 0);
        }

        /*
        Після завершення циклу в кожному процесі буде міститися стрічка с, рівна одній з стрічок добутку A і B.
        Залишається переслати їх головному процесу.
        */
        MPI.COMM_WORLD.Gather(bufferC, 0, lineHeight * matrixSize, MPI.INT, matrixC.matrix, 0, lineHeight * matrixSize, MPI.INT, 0);

        if (procRank == 0) {
            System.out.print("2) matrixSize = " + matrixSize + ", ");
            System.out.println(System.currentTimeMillis() - startTime + " ms");
        }
        MPI.Finalize();
    }
}