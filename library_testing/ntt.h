typedef long long ll;

inline ll mod_pow(ll a, ll k, ll m) {
  ll r = 1;
  for (; k > 0; k >>= 1) {
    if (k & 1) (r *= a) %= m;
    (a *= a) %= m;
  }
  return r;
}

inline ll mod_inv(ll a, ll m) {
  ll b = m, u = 1, v = 0;
  while (b) {
    ll t = a / b;
    swap(a -= t * b, b);
    swap(u -= t * v, v);
  }
  return (u % m + m) % m;
}

// http://math314.hateblo.jp/entry/2015/05/07/014908
template<int Mod, int PrimitiveRoot>
class number_theoretic_transform {
 public:
  static void transform_forward(vector<ll> &a) {
    transform<1>(a);
  }

  static void transform_inverse(vector<ll> &a) {
    transform<-1>(a);
    const ll inv_n = mod_inv(a.size(), Mod);
    for (auto &x : a) (x *= inv_n) %= Mod;
  }

  static vector<ll> convolution(vector<ll> a, vector<ll> b) {
    size_t n = 1;
    while (n < a.size() + b.size()) n *= 2;
    a.resize(n);
    b.resize(n);

    transform_forward(a);
    transform_forward(b);
    for (size_t i = 0; i < n; ++i) (a[i] *= b[i]) %= Mod;
    transform_inverse(a);
    return a;
  }

 private:
  template<int Sign>
  static void transform(vector<ll> &a) {
    const size_t n = a.size();
    assert((n ^ (n & -n)) == 0);  // n = 2^k

    const ll h = Sign == 1 ?
        mod_pow(PrimitiveRoot, (Mod - 1) / n, Mod):
        mod_inv(mod_pow(PrimitiveRoot, (Mod - 1) / n, Mod), Mod);

    for (size_t i = 0, j = 0; j < n; ++j) {
      if (j < i) swap(a[i], a[j]);
      for (size_t k = n >> 1; k > (i ^= k); k >>= 1);
    }

    for (size_t m = 1; m < n; m *= 2) {
      const size_t m2 = m * 2;
      const ll b = mod_pow(h, n / m2, Mod);
      ll w = 1;
      for (size_t j = 0; j < m; ++j) {
        for (size_t k = j; k < n; k += m2) {
          const ll x = a[k];
          const ll y = (a[k + m] * w) % Mod;
          const ll tx = x + y;
          const ll ty = x - y;
          a[k] = tx >= Mod ? tx - Mod : tx;
          a[k + m] = ty < 0 ? ty + Mod : ty;
        }
        (w *= b) %= Mod;
      }
    }
  }
};

vector<ll> mod_convolution(vector<ll> a, vector<ll> b, ll mod) {
  constexpr ll m1 = 167772161;
  constexpr ll m2 = 469762049;
  constexpr ll m3 = 1224736769;

  auto c1 = number_theoretic_transform<m1, 3>::convolution(a, b);
  const auto c2 = number_theoretic_transform<m2, 3>::convolution(a, b);
  const auto c3 = number_theoretic_transform<m3, 3>::convolution(a, b);

  const ll m1_inv_m2 = mod_inv(m1, m2);
  const ll m12_inv_m3 = mod_inv(m1 * m2, m3);
  const ll m12_mod = m1 * m2 % mod;
  for (size_t i = 0; i < c1.size(); ++i) {
    const ll v1 = (c2[i] - c1[i] + m2) * m1_inv_m2 % m2;
    const ll v2 = (c3[i] - (c1[i] + m1 * v1) % m3 + m3) * m12_inv_m3 % m3;
    c1[i] = (c1[i] + m1 * v1 + m12_mod * v2) % mod;
  }
  return c1;
}
