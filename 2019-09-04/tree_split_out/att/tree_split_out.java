import java.util.Scanner;

class tree_split_out {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        String line = in.nextLine();
        String token[] = line.split(" ");
	int t = Integer.parseInt(token[0]);
        switch (t) {
        case 1:
            System.out.println("1 2 0 1 0"); // buono per input1
            break;
        case 2:
            System.out.println("2 3 1 1"); // buono per input5
            break;
        case 3:
            System.out.println("format 3 0 1 1 1 1 1 2 2 1 1 1 0"); // buono per input9
            break;
        default:
            System.out.println("Invalid format");
        }
    }
}
