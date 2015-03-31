//Sample code to read in test cases:
import java.io.*;
public class Main {
    public static void main (String[] args) throws IOException {
        File file = new File(args[0]);
        BufferedReader buffer = new BufferedReader(new FileReader(file));
        String line;
        while ((line = buffer.readLine()) != null) {
            line = line.trim();
            // Process line of input Here
            int input = Integer.parseInt(line);
            int result = sumOfDigits(input);
            System.out.println(result);
        }
    }
    
    public static int sumOfDigits(int input)
    {
        if(input < 10) return input;
        int lastDigit = input - (input/10)*10;
        int rest = input/10;
        return (lastDigit + sumOfDigits(rest));
    }
}
