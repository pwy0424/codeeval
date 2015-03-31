// Sample code to read in test cases:
import java.io.*;
public class Main {
    public static void main (String[] args) throws IOException
    {
        /*File file = new File(args[0]);
        BufferedReader buffer = new BufferedReader(new FileReader(file));
        String line;
        while ((line = buffer.readLine()) != null) {
            line = line.trim();
            // Process line of input Here
        }
        */
        for(int result = 999; result > 0; result-=2)
        {
            if(isPrime(result))
            {
                if(isPalindrome(result))
                {
                    System.out.printf("%d\n",result);
                    isPalindrome(result);
                    break;
                }
            }
        }
    }
    
    public static boolean isPalindrome(int input)
    {
        //only consider positive integers
        if(0 <= input && input < 10)//base case
        {
            return true;
        }
        int lastDigit = input - (input/10)*10;
        int firstDigit = 0;
        int temp = input;
        int count = 0;
        while(temp > 10)
        {
            temp = temp/10;
            count++;
        }
        if(temp == 10) firstDigit = 1;
        else firstDigit = temp;
        if(firstDigit != lastDigit) return false;
        int tenPower = firstDigit;
        for(int i = 0; i < count; i++)
        {
           tenPower = tenPower * 10; 
        }
        int rest = (input - tenPower)/10;
        return isPalindrome(rest);
    }
    
    public static boolean isPrime(int input)
    {
        if(input < 2) return false;
        if(input == 2) return true;
        if(input == 3) return true;
        int inputSqrt = (int)Math.sqrt(input);
        for(int i = 2; i <= inputSqrt; i++)
        {
            if(input % i == 0) return false;
        }
        return true;
    }
}
