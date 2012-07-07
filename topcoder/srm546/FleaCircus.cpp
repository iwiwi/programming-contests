#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <climits>
#include <numeric>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

struct FleaCircus {
  int countArrangements(vector <string> afterFourClicks);
};

typedef long long ll;

const ll MOD = 1000000009;

int FleaCircus::countArrangements(vector <string> afterFourClicks) {
  stringstream ss(accumulate(all(afterFourClicks), string()));
  vector<int> A;
  for (int t; ss >> t; ) A.pb(t);
  int N = A.size();

  map<int, int> cnt;
  {
    vector<bool> usd(N) ;
    rep (i, N) if (!usd[i]) {
      int k = i, c = 0;
      while (!usd[k]) {
        usd[k] = true;
        k = A[k];
        ++c;
      }
      ++cnt[c];
    }
  }

  ll ans = 1;
  tr (cnt, ite) {
    int K = ite->first;
    int M = ite->second;

    vector<ll> dp(M + 1);
    dp[0] = 1;

    for (int m = 1; m <= M; ++m) {
      dp[m] = 0;

      for (int d = 1; d <= 4; d *= 2) {
        if (d > m) continue;

        int s = K * d;
        int t = s % 4 == 0 ? s / 4 : (s % 2 == 0 ? s / 2 : s);
        if (t != K) continue;

        ll c = 1;
        rep (i, d - 1) {
          (c *= m - 1 - i) %= MOD;
          (c *= t) %= MOD;
        }
        (dp[m] += dp[m - d] * c) %= MOD;
      }
    }

    printf("size %d X %d = %lld\n", K, M, dp[M]);
    (ans *= dp[M]) %= MOD;
  }

  return ans;
}











// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			}
			return;
		}

		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}

		if (total == 0) {
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}

	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) {
		cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;

		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl;
			cerr << "    Received: " << received << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string afterFourClicks[]  = {"1 2 0 3"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = FleaCircus().countArrangements(vector <string>(afterFourClicks, afterFourClicks + (sizeof afterFourClicks / sizeof afterFourClicks[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string afterFourClicks[]  = {"1 2 ", "0 3"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = FleaCircus().countArrangements(vector <string>(afterFourClicks, afterFourClicks + (sizeof afterFourClicks / sizeof afterFourClicks[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string afterFourClicks[]  = {"0 1 2"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = FleaCircus().countArrangements(vector <string>(afterFourClicks, afterFourClicks + (sizeof afterFourClicks / sizeof afterFourClicks[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string afterFourClicks[]  = {"0 1 2 3 5 4"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = FleaCircus().countArrangements(vector <string>(afterFourClicks, afterFourClicks + (sizeof afterFourClicks / sizeof afterFourClicks[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string afterFourClicks[]  = {"3 6 7 9 8 2 1", "0 5 1 0 4"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = FleaCircus().countArrangements(vector <string>(afterFourClicks, afterFourClicks + (sizeof afterFourClicks / sizeof afterFourClicks[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string afterFourClicks[]  = {"1 0 7 5 6 3 4 2"};
			int expected__            = 48;

			clock_t start__           = clock();
			int received__            = FleaCircus().countArrangements(vector <string>(afterFourClicks, afterFourClicks + (sizeof afterFourClicks / sizeof afterFourClicks[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
			string afterFourClicks[]  = {"247 64 181 30 134 289 81 148 116 395 127 235 72 31", " 529 26 109 160 421 277 512 427 294 496 426 463 75", " 103 491 508 332 323 303 151 497 542 369 454 304 1", "74 61 532 498 436 473 384 0 265 420 130 439 191 40", "0 507 464 111 409 94 169 192 92 93 196 286 522 8 1", "63 401 504 477 494 540 282 313 190 327 91 338 166 ", "246 80 261 23 46 543 530 175 417 119 493 11 14 260", " 489 241 287 407 34 412 376 457 467 213 438 281 45", "2 525 441 177 35 182 534 102 295 321 408 523 171 3", "11 299 165 145 368 47 79 208 100 374 19 300 147 36", " 458 54 90 488 519 245 316 236 462 358 121 16 539 ", "227 141 233 128 255 203 404 371 118 334 216 188 26", "4 350 524 173 231 48 424 195 83 415 6 38 204 361 1", "01 139 541 2 67 176 184 114 262 298 526 221 516 97", " 104 115 85 472 1 490 251 249 266 32 425 17 381 45", "0 267 212 305 69 482 279 353 229 280 330 290 135 2", "15 200 291 167 278 538 170 378 189 44 132 250 82 5", "28 443 331 230 20 447 363 49 434 63 225 272 113 56", " 419 202 389 410 444 254 399 41 500 168 537 185 24", "8 53 65 483 252 98 210 392 297 256 45 373 318 499 ", "386 377 509 228 89 356 77 461 527 15 131 359 391 1", "44 156 336 337 514 108 172 5 422 42 355 535 146 31", "2 243 533 502 205 475 481 366 253 164 162 319 487 ", "335 138 214 218 492 142 293 234 430 136 357 125 43", "2 120 29 107 307 352 347 302 296 372 58 9 428 423 ", "24 393 105 506 59 375 194 137 207 276 324 198 501 ", "520 431 413 354 322 178 259 416 449 220 518 12 25 ", "133 74 468 310 418 154 480 448 397 414 33 226 269 ", "275 123 315 18 284 531 13 536 471 511 403 152 183 ", "129 348 10 66 309 21 271 199 110 263 43 257 238 50", "3 411 99 117 222 351 396 76 479 87 155 445 122 470", " 346 211 57 398 27 485 406 224 86 306 60 453 197 4", "84 383 476 364 68 388 478 106 7 193 341 367 201 51", "0 433 70 283 78 71 150 239 223 339 370 50 446 455 ", "301 159 140 161 465 73 437 88 343 22 240 326 232 3", "28 345 340 3 258 314 308 505 288 515 273 495 186 9", "5 37 365 521 157 39 180 380 270 217 379 187 440 24", "4 517 268 442 28 344 84 486 237 242 126 451 390 12", "4 96 158 52 206 466 474 51 317 153 112 274 329 513", " 4 405 285 382 459 209 342 179 219 460 143 394 402", " 333 149 349 362 435 360 55 292 469 325 320 387 42", "9 456 62 385 40"}
;
			int expected__            = 53231327;

			clock_t start__           = clock();
			int received__            = FleaCircus().countArrangements(vector <string>(afterFourClicks, afterFourClicks + (sizeof afterFourClicks / sizeof afterFourClicks[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			string afterFourClicks[]  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FleaCircus().countArrangements(vector <string>(afterFourClicks, afterFourClicks + (sizeof afterFourClicks / sizeof afterFourClicks[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string afterFourClicks[]  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FleaCircus().countArrangements(vector <string>(afterFourClicks, afterFourClicks + (sizeof afterFourClicks / sizeof afterFourClicks[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
