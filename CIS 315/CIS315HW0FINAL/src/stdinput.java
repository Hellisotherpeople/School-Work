import java.util.Scanner;

//Allen Roush
//CIS 315
// stinput.java has the exact functionality requested in the project description  https://www.cs.uoregon.edu/Classes/16S/cis315/asst0/asst0.pdf
// 4/2/2016
// This time it's correct!

public class stdinput
{

    public static void main(String[] args)
    {

        Scanner scanner = new Scanner(System.in);
        int numlines = scanner.nextInt();
        scanner.nextLine(); // force it to start scanning after the first value
        for (int i = 0; i < numlines; i++)
        {
            printnum(scanner.nextInt(), scanner.nextInt());
            scanner.nextLine();
        }
        scanner.close();

    }

    public static void printnum(int num1, int num2)
    {
        System.out.println((num1 + num2) + " " + (num1 * num2));
       // System.out.println(System.getProperty("java.runtime.version"));
    }

}
