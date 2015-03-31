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
            int firstSpaceIndex = line.indexOf(" ");
            int secondSpaceIndex = line.lastIndexOf(" ");
            int first = Integer.parseInt(line.substring(0,firstSpaceIndex));
            int second = Integer.parseInt(line.substring(firstSpaceIndex+1,secondSpaceIndex));
            int goal = Integer.parseInt(line.substring(secondSpaceIndex+1));
            
            String[] result = new String[goal];
            for(int i = 0; i < goal; i++)
            {
                result[i] = Integer.toString(i+1);
            }
            for(int i = 1; (i*first)-1 < goal; i++)
            {
                result[(i*first)-1] = "F";
            }
            for(int i = 1; (i*second)-1 < goal; i++)
            {
                if(result[(i*second)-1] != "F") result[(i*second)-1] = "B";
                else result[(i*second)-1] = "FB";
            }
            for(int i = 0; i < goal-1; i++)
            {
                System.out.printf(result[i]+" ");
            }
            System.out.printf(result[goal-1]+"\n");
        }
    }
}
