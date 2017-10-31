import java.net.*;
import java.io.*;

public class EchoServer{
 public static void main(String args[]) throws IOException{
  if (args.length != 1){
   System.err.println("Usage: java EchoServer <port number>");
   System.exit(1);
  }

  int portNumber = Integer.parseInt(args[0]);

  //Recieve Mode
  try {

   ServerSocket serverSocket = new ServerSocket(portNumber);
   Socket clientSocket = serverSocket.accept();
   BufferedReader in  = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
   BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
   PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

   String inputLine;
   String outputLine="";
   System.out.println("Waiting to Recieve message ...");
   inputLine= in.readLine();
  // while((inputLine = in.readLine()) != null){
   while(!outputLine.equals("exit")||inputLine!=null){
    
    //POINT A
    //
    //At this point the user has sent the information to the host (this program)

    System.out.println("\tRecieved "+inputLine);
    System.out.println("Swtiching to SendMode");
    System.out.println("Type Message >>>");
    outputLine = stdIn.readLine();

    //POINT B
    //
    //User input is waiting in the userInput variable at this point
    //The below funciton is the variable that is sent to the client

    out.println(outputLine);
    System.out.println("Waiting to Recieve message ...");
    
    inputLine=in.readLine();
   }
  } catch (IOException e){
   System.out.println("Excpetion caught when trying to listen on port " + portNumber + " or listening for a connection");
   System.out.println(e.getMessage());
  }
 }
}

