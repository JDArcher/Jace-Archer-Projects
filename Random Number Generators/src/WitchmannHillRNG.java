/*

Jace Archer
Problem: Java-based Random Number Generator (RNG)
Date Completed: October 26, 2017
*/

import java.math.BigInteger;
import java.util.Random;

/**The WitchmannHillRNG class will use the Witchmann-Hill pseudorandom number generation algorithm to return
 a random BigInteger. This algorithm uses a mix of modulus division, random starting numbers, and hard coded
 values to ensure that its numbers are not predictable. Once the number has been generated, it is converted into
 a String where it removes the decimal point, and then converts the String into a BigInteger. This new number is
 then returned.
 */
public class WitchmannHillRNG {

    /**Generates a random Biginteger number
     * @return a random BigInteger number
     * */
    public BigInteger whRNG(){

        Random rand = new Random();


        //Generates the seeds, a random number between 0 and 30000
        double s1 = rand.nextInt(30000);
        double s2 = rand.nextInt(30000);
        double s3 = rand.nextInt(30000);

        //Recomputes the seeds to give to each one various numbers to the right of the decimal
        s1 = 171 * (s1 % 177) - 2 * (s1 / 177);
        s2 = 172 * (s2 % 176) - 35 * (s2 / 176);
        s3 = 170 * (s3 % 178) - 63 * (s3 / 178);

        //Combines the numbers into one value that will be less than zero
        double result = ((s1/30269 + s2/30307 + s3/30332) % 1);

        //Converts the double into a String so that the decimal place can be removed
        String temp = Double.toString(result);
        temp = temp.replace(".","");

        //Converts the String into a BigInteger, which will be the random number returned
        BigInteger intResult = new BigInteger(temp);

        return intResult;

    }//end whRNG

}//end WitchmannHillRNG
