/*
Jace Archer
Problem: Java-based Random Number Generator (RNG)
Date Completed: October 26, 2017
*/

/**The main class will call the two random number generators to generate 5 random numbers. The built in
 solution will be called once, my custom Witchmann-Hill RNG will be called once, and my custom RSA generator
 will be called three times.
 */
public class Main {

    public static void main(String[] args) {


        JavaRNG r1 = new JavaRNG();

        WitchmannHillRNG r2 = new WitchmannHillRNG();

        RSARNG r3 = new RSARNG();

        //Calls Java's built in RNG
        System.out.println("Built-In RNG: " + r1.javaRNG());

        //Calls custom Witchmann-Hill RNG
        System.out.println("Custom Witchmann-Hill RNG RNG: " + r2.whRNG());

        for(int i = 0; i < 3; i++)
            //Calls custom RSA RNG three times
            System.out.println("Custom RSA RNG: " + r3.rsaRandom());


    }//end main

}//end Main
