import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.util.*;

public class Main {
	Scanner sc = new Scanner(System.in);
	
	void run() {
		int N = sc.nextInt(), L = sc.nextInt();
		System.out.println(L * 3 - N);
	}
	
	void debug(Object...os) {
		System.err.println(deepToString(os));
	}
	
	public static void main(String[] args) {
		new Main().run();
	}
}
