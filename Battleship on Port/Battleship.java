/*

Programmer: Jace Archer
Class: CSC 435
Program Name: Battleship Game


Ship Names:
 B= Battleship
 C= Carrier
 D= Destroyer
 S= Submarine
 P= Patrol

*/



public class Battleship{

    private String[][] board;
    private int battleship;
    private int carrier;
    private int destroyer;
    private int submarine;
    private int patrol;

    Battleship(){

        board = new String[][]{

                {" ","B" ,"B" ,"B" ,"B" ,"B" ,"B" ," "," " ," " },
                {" "," " ," " ," " ," " ," " ," " ," ","P" ,"P" },
                {" "," " ,"C" ," " ," " ," " ," " ," "," " ," " },
                {" "," " ,"C" ," " ," " ," " ," " ," "," " ," " },
                {" "," " ,"C" ," " ," " ," " ," " ," "," " ," " },
                {" "," " ,"C" ," " ," " ," " ," " ," "," " ," " },
                {"S"," " ,"C" ," " ," " ," " ," " ," "," " ," " },
                {"S"," " ,"C" ," " ," " ," " ," " ," "," " ," " },
                {"S"," " ," " ," " ," " ,"D" ,"D" ,"D","D" ," " },
                {" "," " ," " ," " ," " ," " ," " ," "," " ," " }

        };

        battleship = 6;
        carrier = 5;
        destroyer = 4;
        submarine = 3;
        patrol = 2;

    }//end Battleship

    public int convertX (String readInx){

        int x = 0;

        readInx = readInx.toUpperCase();

        switch (readInx) {

            case "A":
                x = 0;
                break;

            case "B":
                x = 1;
                break;

            case "C":
                x = 2;
                break;

            case "D":
                x = 3;
                break;

            case "E":
                x = 4;
                break;

            case "F":
                x = 5;
                break;

            case "G":
                x = 6;
                break;

            case "H":
                x = 7;
                break;

            case "I":
                x = 8;
                break;

            case "J":
                x = 9;
                break;

            default:
                System.out.println("Invalid value entered: x = 0");


        }//end switch

        return x;

    }//end convertX


    public int convertY(String readInY){

        int y = Integer.parseInt(readInY) - 1;

        return y;

    }//end convertY


    public String move(int x, int y) {

        if (board[x][y].equals("B")) {

            board[x][y] = " ";
            battleship--;

            if (battleship == 0) {

                return "You sunk my battleship! You Win";

            }//end if

            return "Hit!";

        } //end B case If

        else if (board[x][y].equals("C")) {

            board[x][y] = " ";
            carrier--;

            if (carrier == 0) {

                return "You sunk my carrier";

            }//end if

            return "Hit!";

        }//end C else if

        else if (board[x][y].equals("D")) {

            board[x][y] = " ";
            destroyer--;

            if (destroyer == 0) {

                return "You sunk my destroyer";

            }//end if

            return "Hit!";

        }//end D else if

        else if (board[x][y].equals("S")) {

            board[x][y] = " ";
            submarine--;

            if (submarine == 0) {

                return "You sunk my submarine";

            }//end if

            return "Hit!";

        }//end S else if

        else if (board[x][y].equals("P")) {

            board[x][y] = " ";
            patrol--;

            if (patrol == 0) {

                return "You sunk my patrol boat";

            }//end if

            return "Hit!";

        }//end P else if

        return "Miss!";

    }//end move


}//end Main Class
