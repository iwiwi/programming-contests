import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.util.*;

public class Main {
	Scanner sc = new Scanner(System.in);
	
	String min(String s, String t) {
		if (s == null) return t;
		if (t == null) return s;
		return (s.compareTo(t) < 0 ? s : t); 
	}
	
	void run() {
		char[] cs = sc.next().toCharArray();
		int n = cs.length;
		ArrayList<String>[][] dp = new ArrayList[n + 1][n + 1];
		for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) dp[i][j] = new ArrayList<String>();
		for (int i = 0; i <= n; i++) dp[i][i].add("");
		for (int i = 0; i < n; i++) {
			dp[i][i + 1].add("");
			dp[i][i + 1].add("" + cs[i]);
		}
		for (int len = 2; len <= n; len++) {
			for (int s = 0; s + len <= n; s++) {
				int t = s + len;
				TreeSet<String> set = new TreeSet<String>();
				if (cs[s] == cs[t - 1]) {
					for (String str : dp[s + 1][t - 1]) set.add(str);
				}
				for (String str : dp[s + 1][t]) set.add(cs[s] + str);
				for (String str : dp[s][t - 1]) set.add(str + cs[t - 1]);
				for (String str : set) if (dp[s][t].size() < 10) dp[s][t].add(str);
			}
		}
		System.out.println(dp[0][n].get(0));
	}
	
	void debug(Object...os) {
		System.err.println(deepToString(os));
	}
	
	public static void main(String[] args) {
		new Main().run();
	}
}
