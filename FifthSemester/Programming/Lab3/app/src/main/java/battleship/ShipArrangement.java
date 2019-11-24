package battleship;

/**
 * @author chastis
 */
public class ShipArrangement {
    Cell checkL1, checkL2, checkL3, checkL4, checkL5;
    Cell checkM1, checkM2, checkM3;


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
