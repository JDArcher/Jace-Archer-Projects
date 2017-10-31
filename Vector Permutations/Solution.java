import java.io.*;
import java.util.*;

/*
 * To execute Java, please define "static void main" on a class
 * named Solution.
 *
 * If you need more classes, simply define them inline.
 */

/*
You're given a vector of vectors of words, e.g.: 
[['quick', 'lazy'], ['brown', 'black', 'grey'], ['fox', 'dog']]. 

Write a generalized function that prints all combinations of one word from the first vector, one word from the second vector, etc.
The solution may not use recursion. 
NOTE: the number of vectors and number of elements within each vector may vary.

For the input above, it should print (in any order): 
quick brown fox 
quick brown dog 
quick black fox 
quick black dog 
... 
lazy grey dog
*/

//Completed by Jace Archer on October 25th, 2017

class Solution {
  public static void main(String[] args) {
    
    //Creates the vector of vectors that will be used for testing
    Vector<Vector<String>> test = new Vector<Vector<String>>();
    
    //First Vector for testing
    Vector<String> t1 = new Vector<String>();    
    t1.add("quick");    
    t1.add("lazy");    
    test.add(t1);
    
    //Second vector for testing
    Vector<String> t2 = new Vector<String>();
    t2.add("brown");
    t2.add("black");
    t2.add("grey");
    test.add(t2);
    
    //Third Vector for testing
    Vector<String> t3 = new Vector<String>();
    t3.add("fox");
    t3.add("dog");
    test.add(t3);
    
    Vector<String> t4 = new Vector<String>();
    t4.add("happy");
    t4.add("sad");
    t4.add("angry");
    t4.add("sleepy");
    test.add(t4);
    
    //Sends the vector of vectors to have all combinations printed out
    vectorCombos(test);
    
    
    
  }//end main
  
  public static void vectorCombos(Vector<Vector<String>> masterVector){
    
    int totalVectors = masterVector.size();
    
    
    //If the passed in vector is empty, then the method will exit
    if(totalVectors <= 0){
      
      System.out.println("ERROR, NO INPUT GIVEN!!");
      return;
      
    }
    
    //If the passed in vector only contains one vector, the method will just print out that vector's         //content
    else if(totalVectors == 1){
      
     for(int i = 0; i < masterVector.get(0).size(); i++)
       System.out.println(masterVector.get(0).get(i));
        
      
      
      return;      
      
    }//end else if
    
      
    //Will be used to hold the number of elements in each Vector
    int [] sizes = new int [totalVectors];
    
    //Will be used to count what index of the vector is being added to the combination
    int [] sizeCounters = new int [totalVectors];
    
    
    for(int i = 0; i < totalVectors; i++){
      
    
      sizes[i] = masterVector.get(i).size();
            
      sizeCounters [i] = 0;
      
      if(sizes[i] <= 0){
        
        System.out.println("ERROR, A VECTOR GIVEN HAS NO ELEMENTS!!");
        return;
        
      }//end if
      
      
    }//end for
    
    
    //This loop will run until all permutations of the vectors have been found and printed out
    while(sizes[0] > sizeCounters[0]){
      
      //This loop will grab one string from each vector to print out one combination
      for(int i = 0; i < totalVectors; i++)
        System.out.print(masterVector.get(i).get(sizeCounters[i]) + " ");
        
      //Prints a blank line to seperate output
      System.out.println();
      
      //The index of the last vector will be incremented so another combination can be found
      sizeCounters[totalVectors - 1]++;
      
      //If the last vector has no more elements, then another index of another vector needs to be moved
      if(sizeCounters[totalVectors - 1] >= sizes[totalVectors - 1]){
        
        
        //Sets the last vector's index to 0, so that all of its elements can be examined again
        //sizeCounters[totalVectors - 1] = 0;
        
        //This loop will find the furthest back vector that needs to be incremented
        for(int j = totalVectors - 1; j > 0; j--){
          
          
          if(sizeCounters[j] >= sizes[j]){
            
            //Since all combinations have been found with this index, it is reset
            sizeCounters[j] = 0;

          
            //To print out new combinations, the index before the newly reset index is incremented
            sizeCounters[j - 1]++;
            
            
          }//end if          
          
        }//end for
        
      }//end if
      
      
    }//end while 
    
    
  }//end vectorCombos
  
  
}//end Solution
