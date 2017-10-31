/*

Programmer: Cade Archer
Class: CSC 435
Program Name: Battleship Game


Ship Names:
 B= Battleship
 C= Carrier
 D= Destroyer
 S= Submarine
 P= Patrol

*/

import java.util.Scanner;

public class Main{

    public static void main(String[] args){

        //Hardcoded Battleship Board
        String[][] board= new String[][]{

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


        //Different Ship Lengths
        int battleship = 6;
        int carrier = 5;
        int destroyer = 4;
        int submarine = 3;
        int patrol = 2;

        //Creates the Scanner
        Scanner input = new Scanner(System.in);

        //Holds the x-coordinate of the attack
        int x=0;

        //Holds the y-coordinate of the attack
        int y;

        String readInx;

        //Boolean that keeps that determines if the games while loop ends
        boolean gameOver=false;

        /*
         Message format:
                    PACKET_NUM MESSAGE

         Different Messages:
                    READY (exchanged by both sides.  The server always moves first after exchanging READY.
                 MOVE {a-j}{1-10)
                    HIT
                    MISS
                    YOU SUNK MY {CARRIER, DESTROYER, SUBMARINE, PATROL}
                    YOU SUNK MY BATTLESHIP.  YOU WIN!  GAME OVER.
                    MESSAGE {String from users}

         */

        String message;
        String[] messageSplit;

        //Runs until the battleship is sunk
        while(!gameOver) {

            System.out.println("Enter Message: (Format PACKET_NUMBER COMMAND )");

            message = input.nextLine();

            messageSplit = message.split(" ");


            if (messageSplit[1].equalsIgnoreCase("MOVE")) {
                readInx = messageSplit[2].toUpperCase();
                y = Integer.parseInt(messageSplit[3]) - 1;
                
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
                        System.out.println("Invalid value entered: x=0");


                }//end switch


                if (board[x][y].equals("B")) {
                    System.out.println("Hit!");
                    board[x][y] = " ";
                    battleship--;

                    if (battleship == 0) {
                        System.out.println("You sunk my battleship! You Win");
                        gameOver = true;
                    }
                }

                else if (board[x][y].equals("C")) {
                    System.out.println("Hit!");
                    board[x][y] = " ";
                    carrier--;

                    if (carrier == 0) {
                        System.out.println("You sunk my carrier");

                    }
                }

                else if (board[x][y].equals("D")) {
                    System.out.println("Hit!");
                    board[x][y] = " ";
                    destroyer--;

                    if (destroyer == 0) {
                        System.out.println("You sunk my destroyer");

                    }

                }

                else if (board[x][y].equals("S")) {
                    System.out.println("Hit!");
                    board[x][y] = " ";
                    submarine--;

                    if (submarine == 0) {
                        System.out.println("You sunk my submarine");

                    }
                }

                else if (board[x][y].equals("P")) {
                    System.out.println("Hit!");
                    board[x][y] = " ";
                    patrol--;

                    if (patrol == 0) {
                        System.out.println("You sunk my patrol");

                    }
                }

                else {
                    System.out.println("Miss!");
                }


            }//end MOVE if

            else if(messageSplit[1].equalsIgnoreCase("MESSAGE")){

                for(int i=2; i<messageSplit.length;i++){
                    System.out.print(messageSplit[i]+" ");
                }

                System.out.println();

            }//end "MESSAGE" IF

            else if(messageSplit[1].equalsIgnoreCase("HIT")){}//end "HIT" IF

            else if(messageSplit[1].equalsIgnoreCase("MISS")){}//end "MISS" IF

            else if(messageSplit[1].equalsIgnoreCase("READY")){}//end "READY" IF

            else if(messageSplit[1].equalsIgnoreCase("YOU") && messageSplit.length==4){}//end "YOU SUNK MY {CARRIER, DESTROYER, SUBMARINE, PATROL}" message

            else if(messageSplit[1].equalsIgnoreCase("YOU") && messageSplit.length>4){}//end "YOU SUNK MY BATTLESHIP.  YOU WIN!  GAME OVER." message

            else{}//end unknown message else


        }//end while

    }//end main methodxc


}//end Main Class

