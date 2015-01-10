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
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define eb(e) emplace_back(e)
#define mp(a, b) make_pair(a, b)

//
// mod_int
//
long long P;

template<typename IntType = long long>
class mod_int {
 public:
  typedef IntType int_type;

  mod_int() : x_(0) {}
  mod_int(int_type x) : x_(normalize(x)) {}
  int_type value() const { return x_; }

  mod_int operator+(const mod_int &a) const {
    return mod_int(normalize_sub(x_ + a.x_));
  }
  mod_int operator-(const mod_int &a) const {
    return mod_int(normalize_sub(x_ - a.x_ + P));
  }
  mod_int operator*(const mod_int &a) const {
    return mod_int(normalize_mod(x_ * a.x_));
  }
  mod_int operator/(const mod_int &a) const {
    return mod_int(normalize_mod(x_ * inverse(a.x_)));
  }

  mod_int &operator+=(const mod_int &a) {
    return *this = *this + a;
  }
  mod_int &operator-=(const mod_int &a) {
    return *this = *this - a;
  }
  mod_int &operator*=(const mod_int &a) {
    return *this = *this * a;
  }
  mod_int &operator/=(const mod_int &a) {
    return *this = *this / a;
  }

  mod_int operator++(int) {
    mod_int y(*this);
    *this += 1;
    return y;
  }
  mod_int operator--(int) {
    mod_int y(*this);
    *this -= 1;
    return y;
  }
  mod_int &operator++() {
    return *this += 1;
  }
  mod_int &operator--() {
    return *this -= 1;
  }
  mod_int operator-() const {
    return mod_int(P - x_);
  }

  bool operator==(const mod_int &a) const {
    return x_ == a.x_;
  }
  bool operator!=(const mod_int &a) const {
    return x_ != a.x_;
  }
  bool operator<(const mod_int &a) const {
    return x_ < a.x_;
  }

 private:
  int_type x_;

  static constexpr int_type normalize(int_type x) {
    return (x % P + P) % P;
  }
  static constexpr int_type normalize_sub(int_type x) {
    return x >= P ? x - P : x;
  }
  static constexpr int_type normalize_mod(int_type x) {
    return x % P;
  }

  static int_type inverse(int_type x) {
    int_type y = P, u = 1, v = 0;
    while (y != 0) {
      int_type t = x / y;
      swap(x -= t * y, y);
      swap(u -= t * v, v);
    }
    return normalize(u);
  }
};

template<typename IntType>
std::ostream &operator<<(std::ostream &stream, const mod_int<IntType> &a) {
  return stream << a.value();
}

template<typename IntType>
std::istream &operator>>(std::istream &stream, mod_int<IntType> &a) {
  IntType x;
  stream >> x;
  a = x;
  return stream;
}

//
// polynomial
//
template<typename ValueType>
class polynomial {
 public:
  typedef ValueType value_type;

  polynomial(value_type a0) : a_(1, a0) { normalize(); }
  explicit polynomial(const vector<value_type> &a) : a_(a) {
    normalize();
  }
  polynomial(initializer_list<value_type> i) : a_(i.begin(), i.end()) {
    normalize();
  }

  size_t size() const {
    return a_.size();
  }
  value_type operator[](size_t i) const {
    return a_[i];
  }
  bool is_zero() const {
    return size() == 0;
  }
  void swap(polynomial &p) {
    a_.swap(p.a_);
  }

  polynomial &operator+=(const polynomial &p) {
    if (p.size() > size()) a_.resize(p.size());
    for (size_t i = 0; i < p.size(); ++i) a_[i] += p[i];
    normalize();
    return *this;
  }
  polynomial &operator-=(const polynomial &p) {
    if (p.size() > size()) a_.resize(p.size());
    for (size_t i = 0; i < p.size(); ++i) a_[i] -= p[i];
    normalize();
    return *this;
  }
  polynomial operator+(const polynomial &p) const {
    return polynomial(*this) += p;
  }
  polynomial operator-(const polynomial &p) const {
    return polynomial(*this) -= p;
  }

  polynomial operator*(const polynomial &p) const {
    vector<value_type> a(size() + p.size());
    for (size_t i = 0; i < size(); ++i) {
      for (size_t j = 0; j < p.size(); ++j) {
        a[i + j] += (*this)[i] * p[j];
      }
    }
    return polynomial(a);
  }
  polynomial operator/(const polynomial &p) const {
    vector<value_type> q, r;
    divmod(*this, p, q, r);
    return polynomial(q);
  }
  polynomial operator%(const polynomial &p) const {
    vector<value_type> q, r;
    divmod(*this, p, q, r);
    return polynomial(r);
  }
  polynomial &operator*=(const polynomial &a) {
    return *this = *this * a;
  }
  polynomial &operator/=(const polynomial &a) {
    return *this = *this / a;
  }
  polynomial &operator%=(const polynomial &a) {
    return *this = *this % a;
  }

  bool operator==(const polynomial &p) const {
    return a_ == p.x_;
  }
  bool operator!=(const polynomial &p) const {
    return a_ != p.a_;
  }
  bool operator<(const polynomial &p) const {
    return a_ < p.a_;
 }

 private:
  vector<value_type> a_;

  void normalize() {
    while (!a_.empty() && a_.back() == 0) {
      a_.pop_back();
    }
  }

  // a = b * q + r
  static void divmod(const polynomial &a, const polynomial &b,
                     vector<value_type> &q, vector<value_type> &r) {
    r = a.a_;
    size_t an = a.size(), bn = b.size();
    assert(bn > 0);
    if (bn > an) {
      q.clear();
      return;
    }

    q.assign(an - bn + 1, 0);
    for (size_t i = an - bn + 1; i--; ) {
      q[i] = r[bn - 1 + i] / b[bn - 1];
      for (size_t j = 0; j < bn; ++j) r[j + i] -= b[j] * q[i];
    }
  }
};

template<typename ValueType>
std::ostream &operator<<(std::ostream &stream, const polynomial<ValueType> &a) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (i > 0) stream << " + ";
    stream << a[i];
    if (i > 0) stream << "x^" << i;
  }
  return stream;
}

template<typename ValueType>
polynomial<ValueType> gcd(polynomial<ValueType> a, polynomial<ValueType> b) {
  while (!b.is_zero()) {
    polynomial<ValueType> t = a % b;
    a.swap(b);
    b.swap(t);
  }
  return a;
}

// a^k mod m
template<typename ValueType>
polynomial<ValueType> power_mod(const polynomial<ValueType> &a, long long k,
                                const polynomial<ValueType> &m) {
  if (k == 0) return {1};
  else if (k == 1) return a;
  else if (k % 2 == 0) return power_mod((a * a) % m, k / 2, m);
  else return power_mod((a * a) % m, k / 2, m) * (k % 2 ? a : polynomial<ValueType>({1})) % m;
}

//
// solution
//

typedef long long ll;
typedef mod_int<> mint;
typedef polynomial<mint> mpoly;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(false);

  int N;
  while (cin >> N >> P) {
    vector<mint> A(N + 1);
    rep (i, N + 1) cin >> A[i];
    mpoly f(A);

    if (f.size() == 0) {
      cout << P << endl;
    }
    else {
      // x*(x-1)*(x-2)*...*(x-P) = x^P - x
      // g = (x^P mod F) - x
      mpoly g = power_mod(mpoly({0, 1}), P, f) - mpoly({0, 1});
      mpoly h = gcd(g, f);
      cout << (int)h.size() - 1 << endl;
    }
  }
}
