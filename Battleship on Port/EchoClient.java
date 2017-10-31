import com.sun.xml.internal.ws.policy.privateutil.PolicyUtils;

import java.io.*;
import java.net.*;
import java.util.*;

public class EchoClient {

    static Battleship  battleship = new Battleship();
    static PrintWriter outSend;
    static String response;
    static String opponentMessage;
    static String userMessage;
    static BufferedReader opponentInput;
    static BufferedReader userInput;
    static int packetNum = 0;

 public static void main(String[] args) throws IOException {
   
  if(args.length != 2) {
    
   System.err.println("Usuage: java EchoClient <host name> <port number>");
   System.exit(1);
   
  }//end if

  String hostName = args[0];
  int portNumber = Integer.parseInt(args[1]);

//SendMode
try {

    System.out.println("Starting");
    Socket echoSocket = new Socket(hostName, portNumber);
    System.out.println("Socket made");
    outSend = new PrintWriter(echoSocket.getOutputStream(), true);
    opponentInput = new BufferedReader(new InputStreamReader(echoSocket.getInputStream()));
    userInput = new BufferedReader(new InputStreamReader(System.in));


    userMessage = " ";
    opponentMessage = " ";

    String[] userMessageSplit;
    String[] opponentMessageSplit;



    System.out.println("Sending Ready to opponent");

    outSend.println("0 Ready");

    System.out.println("Waiting to Receive Ready command ...");

    opponentMessage = opponentInput.readLine();
    packetNum = Integer.parseInt(Character.toString(opponentMessage.charAt(0))) + 1;

    System.out.println("\tReceived " + opponentMessage);

    System.out.println("Let the game begin!");

    while ((!userMessage.equals("exit"))){

        //POINT A
        //User Message Read in block
        System.out.println("Type Message >>>");
        userMessage = userInput.readLine();
        userMessageSplit = userMessage.split(" ");

        userTurn(userMessageSplit);

        //POINT B
        System.out.println("Waiting to Receive message ...");

        opponentMessage = opponentInput.readLine();

        System.out.println("\tReceived " + opponentMessage);

        opponentMessageSplit = opponentMessage.split(" ");

        opponentTurn(opponentMessageSplit);

    }//end inner while loop

}//end try

catch (UnknownHostException e){

    System.err.println("Don't know about host "+ hostName);
    System.exit(1);

}//end UnknownHostException catch

catch (IOException e){

    System.err.println("Couldn't get I/O for the connection to " + hostName);
    System.exit(1);

}//end IOException catch

 }//end main

public static void userTurn(String [] userMessageSplit) throws IOException{

    String [] temp = userMessageSplit;


    Random rand = new Random();
    int  n = rand.nextInt(10) + 1;

    if(n == 1){

        userMessage = "5000000";

    }//end if


    if(userMessageSplit[1].equalsIgnoreCase("move")){

        outSend.println(userMessage);
        userMessageSplit = waitForAck();
        packetNum = Integer.parseInt(userMessageSplit[0]) + 1;

        if(!checkIfEqual(temp, userMessageSplit)) {

            opponentInput.readLine();

        }//end if

        System.out.println("User " + opponentInput.readLine());

    }//end if


    else if(userMessageSplit[1].equalsIgnoreCase("message")) {


        outSend.println(userMessage);
        userMessageSplit = waitForAck();
        packetNum = Integer.parseInt(userMessageSplit[0]);

        if(!checkIfEqual(temp, userMessageSplit)) {

            opponentInput.readLine();

        }//end if

        System.out.println("Type Message >>>");

        userMessage = userInput.readLine();

        userMessageSplit = userMessage.split(" ");

        userTurn(userMessageSplit);

    }//end if

}//end userTurn

public static void opponentTurn(String [] opponentMessageSplit) throws IOException{


    opponentMessageSplit = ack(opponentMessageSplit);

    if(opponentMessageSplit[1].equalsIgnoreCase("move")) {

        packetNum = Integer.parseInt(opponentMessageSplit[0]) + 1;
        response = battleship.move(battleship.convertX(opponentMessageSplit[2]), battleship.convertY(opponentMessageSplit[3]));
        outSend.println(packetNum + " " + response);
        System.out.println("Opponent " + response);

    }//end if

    else if(opponentMessageSplit[1].equalsIgnoreCase("message")) {

        packetNum = Integer.parseInt(opponentMessageSplit[0]);

        for(int i = 2; i < opponentMessageSplit.length; i++){

            System.out.print(opponentMessageSplit[i] + " ");

        }//end for

        System.out.println();

        System.out.println("Waiting to Receive message ...");

        opponentMessage = opponentInput.readLine();

        opponentMessageSplit = opponentMessage.split(" ");

        opponentTurn(opponentMessageSplit);

    }//end if

}//end opponentTurn


public static String [] ack(String [] opponentMessageSplit)throws IOException{

     //if(Character.isDigit(opponentMessageSplit[0].charAt(0))){

         if(Integer.parseInt(opponentMessageSplit[0]) != packetNum + 1){

            System.out.println("Error in Packet! Waiting to Receive new message ...");

            outSend.println("Resend " + (packetNum + 1));

            opponentMessage = opponentInput.readLine();

            opponentMessageSplit = opponentMessage.split(" ");

            ack(opponentMessageSplit);

         }//end inner if Means the Packet Num is Wrong


    outSend.println("Ack " + (packetNum + 1));

    return opponentMessageSplit;

}//end ack

public static String[] waitForAck()throws IOException{

     System.out.println("Waiting for Ack");
     opponentMessage = opponentInput.readLine();

    String [] opponentMessageSplit = opponentMessage.split(" ");

    if(opponentMessageSplit[0].equalsIgnoreCase("Resend")){

        System.out.println("Resend Packet Number " + opponentMessageSplit[1]);
        userMessage = userInput.readLine();
        outSend.println(userMessage);
        waitForAck();

    }//end if


    return userMessage.split(" ");

}//end waitForAck



public static boolean checkIfEqual(String[] data, String[]s) {

    if (data.length != s.length) {

        return false;

    }//end if

    for (int i = 0; i < data.length; i++) {

        if (!data[i].equals(s[i])) {

            return false;

        }//end if

    }//end for loop

    return true;

}//end checkIfEqual

}//end class
