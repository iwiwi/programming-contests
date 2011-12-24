import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.util.*;
import java.io.*;

public class Main {
	Scanner sc = new Scanner(System.in);
	
	int INF = 1 << 29;
	void run() {
		int N = sc.nextInt(), M = sc.nextInt(), D = sc.nextInt();
		if (N <= 15) {
			int[][] g = new int[N][N];
			for (int i = 0; i < N; i++) fill(g[i], D);
			for (int i = 0; i < M; i++) {
				int u = sc.nextInt(), v = sc.nextInt();
				g[u][v] = g[v][u] = sc.nextInt();
			}
			for (int k = 0; k < N; k++) for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			int[][] dp = new int[1 << N][N];
			for (int i = 0; i < 1 << N; i++) fill(dp[i], INF);
			dp[0][0] = 0;
			for (int i = 0; i < 1 << N; i++) for (int j = 0; j < N; j++) for (int k = 0; k < N; k++) if ((i >> k & 1) == 0) {
				dp[i | 1 << k][k] = min(dp[i | 1 << k][k], dp[i][j] + g[j][k]);
			}
			System.out.println(dp[(1 << N) - 1][0]);
			return;
		}
		V[] vs = new V[N];
		for (int i = 0; i < N; i++) vs[i] = new V(i);
		for (int i = 0; i < M; i++) {
			int u = sc.nextInt(), v = sc.nextInt(), c = sc.nextInt();
			vs[u].add(new E(vs[v], c));
			vs[v].add(new E(vs[u], c));
		}
		/*
		int[] cost = new int[N];
		for (int i = 0; i < N; i++) {
			for (E e : vs[i]) if (e.cost > 2 * D) {
				if (vs[i].size() - 1 + e.to.size() - 1 < N - 2) {
					e.cost = 2 * D;
				} else {
					e.cost = min(e.cost, 3 * D);
					int num = 0;
					for (E f : vs[i]) if (f.to != e.to) {
						cost[f.to.id] = f.cost; 
						num++;
					}
					for (E f : e.to) if (f.to != vs[i]) {
						if (cost[f.to.id] == 0) {
							num++;
							e.cost = min(e.cost, f.cost + D);
						} else {
							e.cost = min(e.cost, f.cost + cost[f.to.id]);
						}
					}
					if (num < N - 2) e.cost = 2 * D;
					for (E f : vs[i]) {
						cost[f.to.id] = 0;
					}
				}
			}
		}
		*/
		for (int i = 0; i < N; i++) if (vs[i].size() >= N - 2) {
			int min1 = INF, min2 = INF;
			if (vs[i].size() == N - 2) {
				min1 = D;
			}
			for (E e : vs[i]) {
				int c = e.cost;
				if (min1 > c) {
					int t = min1; min1 = c; c = t;
				}
				if (min2 > c) min2 = c;
			}
			min2 = min(min2, min1 + D);
			System.out.println(D * (N - 2) + min1 + min2);
			return;
		}
		System.out.println(D * N);
	}
	
	class V extends ArrayList<E> {
		int id;
		V(int id) {
			this.id = id;
		}
	}
	
	class E {
		V to;
		int cost;
		E(V to, int cost) {
			this.to = to;
			this.cost = cost;
		}
	}
	
	class Scanner {
		InputStream in;
		byte[] buf = new byte[1 << 10];
		int p, n;
		boolean[] isSpace = new boolean[128];
		Scanner(InputStream in) {
			this.in = in;
			isSpace[' '] = isSpace['\n'] = isSpace['\r'] = isSpace['\t'] = true;
		}
		int read() {
			if (n == -1) return -1;
			if (p >= n) {
				p = 0;
				try {
					n = in.read(buf);
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
				if (n <= 0) return -1;
			}
			return buf[p++];
		}
		boolean hasNext() {
			int c = read();
			while (c >= 0 && isSpace[c]) c = read();
			if (c == -1) return false;
			p--;
			return true;
		}
		String next() {
			if (!hasNext()) throw new InputMismatchException();
			StringBuilder sb = new StringBuilder();
			int c = read();
			while (c >= 0 && !isSpace[c]) {
				sb.append((char)c);
				c = read();
			}
			return sb.toString();
		}
		int nextInt() {
			if (!hasNext()) throw new InputMismatchException();
			int c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			int res = 0;
			do {
				if (c < '0' || c > '9') throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			} while (c >= 0 && !isSpace[c]);
			return res * sgn;
		}
		long nextLong() {
			if (!hasNext()) throw new InputMismatchException();
			int c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			long res = 0;
			do {
				if (c < '0' || c > '9') throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			} while (c >= 0 && !isSpace[c]);
			return res * sgn;
		}
		double nextDouble() {
			return Double.parseDouble(next());
		}
	}
	
	void debug(Object...os) {
		System.err.println(deepToString(os));
	}
	
	public static void main(String[] args) {
		new Main().run();
	}
}
