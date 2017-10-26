import java.math.BigInteger;
import java.util.Random;

/*
Jace Archer
Problem: Java-based Random Number Generator (RNG)
Date Completed: October 26, 2017
*/

/**The RSARNG class generates a random integer by using RSA's method for creating a pubic exponent. Two prime
 values are first generated using Java's built in RNG, and are then "discarded". Using Euler's function, phi
 is generated and will be used as an upper bound for the public exponent. The public exponent, e, is found by
 generating a random number where e is greater than 1 but less than phi, and the greatest common divisor of
 phi and e, is one. This method  ensures that the result is very hard to reverse engineer, while still generating
 an integer that pulls from a large enough pool so that the result cannot be predicted.
 */
public class RSARNG {


    /**This function will use the RSA encryption method of generating a public exponent that will be used as the
     * random number
     *
     * @return the randomly generated public exponent
     */
    public int rsaRandom(){

        //Used to generate a randoms needed for the computation
        Random rand = new Random();

        //Loads the initial values with random numbers using the built in method
        int p = rand.nextInt();
        int q = rand.nextInt();

        //Resets p until a prime number is generated
        while(!isPrime(p))
            p = rand.nextInt();

        //Resets q until a prime number is generated
        while(!isPrime(q))
            q = rand.nextInt();



        //Uses the property of Euler's function to generate phi(pq)
        int phi = Math.abs((p - 1) * (q - 1));

        //To simulate throwing away the numbers used to generate the keys, p and q are set to 0 so that their original
        //value is no longer stored
        p = 0;
        q = 0;


        //Used to hold the public exponent that will be the random number returned
        int e = rand.nextInt();


        //Used to check hold the greatest common divisor of phi and e
        BigInteger gcd = BigInteger.valueOf(e).gcd(BigInteger.valueOf(phi));



        //Resets e until e is: greater than one, less than phi, and the gcd of phi and e is 1
        while(gcd.intValue() != 1){

            e = rand.nextInt((phi - 1) + 1) + 1;

            gcd = BigInteger.valueOf(e).gcd(BigInteger.valueOf(phi));

        }//end while

        return  e;

    }//end rsaRandom


    /**This will determine if a number passed in is prime or not
     *
     * @param num the number whose prime status is being checked
     * @return whether or not the number passed in was prime
     */
    public boolean isPrime(int num){

        if(num == 2){

            return true;

        }

        //This will loop through from 2 to the square root of the passed in num to determine if the number is prime
        for(int i = 2; i < Math.sqrt(num) + 1; i++){

            //If a number evenly divides into num, then it is not prime and false is returned
            if(num % i == 0)
                return false;

        }//end for

        //If no number divided evenly into num, then num is a prime number and true is returned
        return true;


    }//end isPrime

}
