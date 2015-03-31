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
            int lineLength = line.length();
            int arrayLength = (lineLength + 1) / 2;
            
            int[] map = new int[9];//a meta hash map
            for(int i = 0; i < 9; i++)
            {
                map[i] = 0;
            }
            
            int[] input = new int[arrayLength];
            for(int i = 0; i < arrayLength; i++)
            {
                input[i] = Character.getNumericValue(line.charAt(i*2));
                map[(input[i]-1)]++;//one people pick on number, increase the count
            }
            int winnerNumber = 0;
            for(int i = 0; i < 9; i++)
            {
                if(map[i] == 1)
                {
                    winnerNumber = i+1;//the smallest number only picked once
                    break;
                }
            }
            if(winnerNumber == 0) System.out.println("0");
            else
            {
                 for(int i = 0; i < arrayLength; i++)
                 {
                     if(input[i] == winnerNumber)
                     {
                        System.out.println(i+1);
                        break;
                     }
                 }
            }
        }
    }
}
