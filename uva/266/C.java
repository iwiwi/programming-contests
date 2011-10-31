import java.math.*;
import java.util.*;

class Main {
    public static void main(String args[]) {
        Scanner cin = new Scanner(System.in);
        for (;;) {
            BigInteger n = cin.nextBigInteger();
            if (n.signum() == 0) break;

            if (n.mod(BigInteger.valueOf(17)).signum() == 0) {
                System.out.println("1");
            }
            else {
                System.out.println("0");
            }
        }
    }
}