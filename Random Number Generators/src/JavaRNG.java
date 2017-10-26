import java.util.Random;

/*
Jace Archer
Problem: Java-based Random Number Generator (RNG)
Date Completed: October 26, 2017
 */

/**The JavaRNG class uses java's built in random number generator to return a random integer
 */
public class JavaRNG {

    /**This uses Java's built in RNG and returns a random integer
     *
     * @return the randomly generated integer
     */
    public int javaRNG(){

        Random rand = new Random();

        int result = rand.nextInt();

        return result;

    }//end javaRNG

}
