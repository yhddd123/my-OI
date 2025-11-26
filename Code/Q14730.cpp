#include<bits/stdc++.h>
// #define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*1ll*10+ch-'0';ch=getchar();}
	return x*1ll*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

#pragma GCC target("avx2")
namespace NTT {
#include <type_traits>
#include <cstdint>

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
using i128 = __int128_t;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = __uint128_t;
using usize = std::size_t;
using f32 = float;
using f64 = double;
using f80 = long double;
template <class T>
using TI = std::type_identity_t<T>;

#include <immintrin.h>

using i256 = __m256i;
using i256u = __m256i_u;
using i32x8 = __m256i;
using i64x4 = __m256i;
using u32x8 = __m256i;
using u64x4 = __m256i;
using u128x2 = __m256i;
using f256 = __m256d;
using f64x4 = __m256d;


template <int imm>
inline u32x8 u32x8_shuffle(u32x8 a) {
  return _mm256_shuffle_epi32(a, imm);
}
template <int imm>
inline u32x8 u32x8_blend(u32x8 a, u32x8 b) {
  return _mm256_blend_epi32(a, b, imm);
}
inline i32x8 i32x8_permute2301(i32x8 a) { // 1, 0.5
  return u32x8_shuffle<0xf5>(a);
}
// https://stackoverflow.com/questions/37296289/fastest-way-to-multiply-an-array-of-int64-t
u128x2 u64x4_mul0246(u64x4 a, u64x4 b) {
  u64x4 b_swap = _mm256_shuffle_epi32(b, _MM_SHUFFLE(2, 3, 0, 1));
  u64x4 crossprod = _mm256_mullo_epi32(a, b_swap);
  u64x4 prodlh = _mm256_slli_epi64(crossprod, 32);
  u64x4 prodhl = _mm256_and_si256(crossprod, _mm256_set1_epi64x(0xFFFFFFFF00000000));
  u64x4 sumcross = _mm256_add_epi32(prodlh, prodhl);
  u64x4 prodll = _mm256_mul_epu32(a, b);
  u64x4 prod = _mm256_add_epi32(prodll, sumcross);
  return prod;
}



template <class U>
struct Mont {
  using S = std::make_signed_t<U>;
  using UU = std::conditional_t<std::is_same_v<U, u32>, u64, u128>;
  const U MOD, MOD2, R, IR, R2, ONE;
  explicit constexpr Mont(U mod)
      : MOD(mod), MOD2(mod * 2), R(getR(mod)), IR(-getNR(mod)), R2(UU(R) * R % MOD), ONE(trans(1)) {
  }
  constexpr static U getR(U mod) {
    return (UU(1) << (sizeof(U) * 8)) % mod;
  }
  constexpr static U getNR(U mod) {
    U x = 1;
    for (u32 i = 0; i != 6; ++i)
      x *= 2 - x * mod;
    return x;
  }
  inline constexpr U trans(U x) const {
    // return (u64(x) << 32) % MOD;
    return reduce(UU(x) * R2);
  }
  inline constexpr U reduce(UU x) const {
    return (x + UU(U(x) * IR) * MOD) >> (sizeof(U) * 8);
  }
  inline constexpr U add(U a, U b) const {
    U v1 = a + b, v2 = v1 - MOD2;
    return S(v2) < 0 ? v1 : v2;
  }
  inline constexpr U sub(U a, U b) const {
    U v1 = a - b, v2 = v1 + MOD2;
    return S(v1) >= 0 ? v1 : v2;
  }
  inline constexpr U mul(U a, U b) const {
    return reduce(UU(a) * b);
  }
  inline constexpr U qpow(U a, u64 n, U r) const {
    for (; n > 0; n /= 2) {
      if (n % 2 == 1)
        r = mul(r, a);
      a = mul(a, a);
    }
    return r;
  }
  inline constexpr U qpow(U a, u64 n) const {
    return qpow(a, n, ONE);
  }
  inline constexpr U inv(U x) const {
    return qpow(x, MOD - 2);
  }
  inline constexpr U div(U a, U b) const {
    return reduce(qpow(b, MOD - 2, a));
  }
  inline constexpr U get(U x) const {
    U v1 = reduce(x), v2 = v1 - MOD;
    return S(v2) < 0 ? v1 : v2;
  }
  inline constexpr U div2(U x) const {
    return (x % 2 == 1 ? x + MOD : x) >> 1;
  }
  inline constexpr bool cmp(U a, U b) const {
    return get(a) == get(b);
  }
  inline constexpr bool ncmp(U a, U b) const {
    return !cmp(a, b);
  }
  inline constexpr U neg(U x) const {
    return x != 0 ? MOD2 - x : 0;
  }
};
using Mont32 = Mont<u32>;
using Mont64 = Mont<u64>;
template <class ModT>
using ModU = ModT::U;
template <class ModT>
using ModUU = ModT::UU;


struct Mont32x8 {
  Mont32 M;
  u32x8 IR, R2, MOD, MOD2, ONE;
  static u32x8 loadu(const u32 *p) {
    return _mm256_loadu_si256(reinterpret_cast<const i256 *>(p));
  }
  static void storeu(u32 *p, u32x8 v) {
    _mm256_storeu_si256(reinterpret_cast<u32x8 *>(p), v);
  }
  static u32x8 set1(u32 v) {
    return _mm256_set1_epi32(v);
  }
  Mont32x8(Mont32 mod) : M(mod) {
    IR = set1(mod.IR), R2 = set1(mod.R2);
    MOD = set1(mod.MOD), MOD2 = set1(mod.MOD2);
    ONE = set1(mod.ONE);
  }
  u32x8 norm(u32x8 r) const {
    u32x8 rm = _mm256_sub_epi32(r, MOD);
    return _mm256_min_epu32(r, rm);
  }
  u32x8 add(u32x8 a, u32x8 b) const {
    u32x8 v1 = _mm256_add_epi32(a, b);
    u32x8 v2 = _mm256_sub_epi32(v1, MOD2);
    return _mm256_min_epu32(v1, v2);
  }
  u32x8 sub(u32x8 a, u32x8 b) const {
    u32x8 v1 = _mm256_sub_epi32(a, b);
    u32x8 v2 = _mm256_add_epi32(v1, MOD2);
    return _mm256_min_epu32(v1, v2);
  }
  template <i32 imm>
  u32x8 neg(u32x8 a) const {
    return u32x8_blend<imm>(a, _mm256_sub_epi32(MOD2, a));
  }
  u32x8 reduce(u64x4 x0246, u64x4 x1357) const {
    // (x + u64(u32(x) * IR) * MOD) >> 32;
    auto y0246 = _mm256_mul_epu32(_mm256_mul_epu32(x0246, IR), MOD);
    auto y1357 = _mm256_mul_epu32(_mm256_mul_epu32(x1357, IR), MOD);
    auto z0246 = _mm256_add_epi64(x0246, y0246);
    z0246 = i32x8_permute2301(z0246);
    auto z1357 = _mm256_add_epi64(x1357, y1357);
    return u32x8_blend<0xaa>(z0246, z1357);
  }
  u32x8 mul(u32x8 a, u32x8 b) const {
    // return reduce(u64(a) * b);
    u64x4 x0246 = _mm256_mul_epu32(a, b);
    a = i32x8_permute2301(a);
    b = i32x8_permute2301(b);
    u64x4 x1357 = _mm256_mul_epu32(a, b);
    return reduce(x0246, x1357);
  }
  u32x8 trans(u32x8 v) const {
    return mul(v, R2);
  }
  u32x8 get(u32x8 v) const {
    const u32x8 one = set1(1);
    u32x8 v1 = mul(v, one);
    return norm(v1);
  }
};

#include <bit>

struct NTT32OriginalRadix2AVX2 {
  std::array<u32, 32> rt, irt, rate2, irate2;
  u32x8 rate4ix[32], irate4ix[32];
  u32x8 _rt2, _irt2, _rt4, _irt4;
  Mont32x8 _MX;
  NTT32OriginalRadix2AVX2(Mont32 M, u32 G) : _MX(M) {
    const u32 rank2 = std::countr_zero(M.MOD - 1);
    rt[rank2] = M.qpow(M.trans(G), (M.MOD - 1) >> rank2);
    irt[rank2] = M.inv(rt[rank2]);
    for (u32 i = rank2; i != 0; --i) {
      rt[i - 1] = M.mul(rt[i], rt[i]);
      irt[i - 1] = M.mul(irt[i], irt[i]);
    }
    u32 prod = M.ONE, iprod = M.ONE;
    for (u32 i = 0; i != rank2 - 1; ++i) {
      rate2[i] = M.mul(prod, rt[i + 2]);
      irate2[i] = M.mul(iprod, irt[i + 2]);
      prod = M.mul(prod, irt[i + 2]);
      iprod = M.mul(iprod, rt[i + 2]);
    }
    prod = M.ONE, iprod = M.ONE;
    u32 arr[8];
    auto rotate = [&M, &arr](u32 x) {
      for (u32 i = 0; i != 8; ++i)
        arr[i] = i == 0 ? M.ONE : M.mul(x, arr[i - 1]);
    };
    for (u32 i = 0; i != rank2 - 3; ++i) {
      rotate(M.mul(prod, rt[i + 4]));
      rate4ix[i] = _MX.loadu(arr);
      rotate(M.mul(iprod, irt[i + 4]));
      irate4ix[i] = _MX.loadu(arr);
      prod = M.mul(prod, irt[i + 4]);
      iprod = M.mul(iprod, rt[i + 4]);
    }
    auto rotatex = [&M, &arr](u32 x, u32 k) {
      for (u32 i = 0; i != 8; i += k)
        for (u32 j = 0; j != k; ++j)
          arr[i + j] = (j <= k / 2) ? M.ONE : M.mul(x, arr[i + j - 1]);
    };
    rotatex(rt[2], 4), _rt2 = _MX.loadu(arr);
    rotatex(irt[2], 4), _irt2 = _MX.loadu(arr);
    rotatex(rt[3], 8), _rt4 = _MX.loadu(arr);
    rotatex(irt[3], 8), _irt4 = _MX.loadu(arr);
  }
  void ntt_small(u32 *f, usize n) {
    const auto M = _MX.M;
    for (u32 l = n / 2; l >= 1; l /= 2) {
      u32 r = M.ONE;
      for (u32 i = 0, k = 0; i != n; i += l * 2, ++k) {
        u32 *fx = f + i, *fy = fx + l;
        for (u32 j = 0; j != l; ++j) {
          u32 x = fx[j], y = M.mul(fy[j], r);
          fx[j] = M.add(x, y);
          fy[j] = M.sub(x, y);
        }
        r = M.mul(r, rate2[std::countr_one(k)]);
      }
    }
  }
  void intt_small(u32 *f, usize n) {
    const auto M = _MX.M;
    u32 ivn = M.trans(M.MOD - (M.MOD - 1) / n);
    for (u32 l = 1; l <= n / 2; l *= 2) {
      u32 r = M.ONE;
      for (u32 i = 0, k = 0; i != n; i += l * 2, ++k) {
        u32 *fx = f + i, *fy = fx + l;
        for (u32 j = 0; j != l; ++j) {
          u32 x = fx[j], y = fy[j];
          fx[j] = M.add(x, y);
          fy[j] = M.mul(M.sub(x, y), r);
        }
        r = M.mul(r, irate2[std::countr_one(k)]);
      }
    }
    for (u32 i = 0; i != n; ++i)
      f[i] = M.mul(f[i], ivn);
  }
  void ntt(u32 *f, usize n) {
    if (n < 8)
      return ntt_small(f, n);
    const auto MX = _MX;
    const auto M = MX.M;
    for (u32 l = n / 2; l >= 8; l /= 2) {
      u32 *f0 = f, *f1 = f + l;
      for (u32 j = 0; j != l; j += 8) {
        u32x8 x = MX.loadu(f0 + j), y = MX.loadu(f1 + j);
        MX.storeu(f0 + j, MX.add(x, y));
        MX.storeu(f1 + j, MX.sub(x, y));
      }
      u32 r = rate2[0];
      for (u32 i = l * 2, k = 1; i != n; i += l * 2, ++k) {
        u32x8 rx = MX.set1(r);
        f0 = f + i, f1 = f0 + l;
        for (u32 j = 0; j != l; j += 8) {
          u32x8 x = MX.loadu(f0 + j), y = MX.mul(rx, MX.loadu(f1 + j));
          MX.storeu(f0 + j, MX.add(x, y));
          MX.storeu(f1 + j, MX.sub(x, y));
        }
        r = M.mul(r, rate2[std::countr_one(k)]);
      }
    }
    u32x8 rtix = MX.ONE, rt2 = _rt2, rt4 = _rt4;
    for (u32 i = 0; i != n; i += 8) {
      u32x8 fi = MX.mul(rtix, MX.loadu(f + i)), a, b;
      a = MX.neg<0xf0>(fi), b = _mm256_permute2x128_si256(fi, fi, 0b01);
      fi = MX.mul(rt4, MX.add(a, b));
      a = MX.neg<0xcc>(fi), b = u32x8_shuffle<0x4e>(fi);
      fi = MX.mul(rt2, MX.add(a, b));
      a = MX.neg<0xaa>(fi), b = u32x8_shuffle<0xb1>(fi);
      MX.storeu(f + i, MX.add(a, b));
      rtix = MX.mul(rtix, rate4ix[std::countr_one(i / 8)]);
    }
  }
  void intt(u32 *f, usize n) {
    if (n < 8)
      return intt_small(f, n);
    const auto MX = _MX;
    const auto M = MX.M;
    u32x8 rtix = MX.set1(M.trans(M.MOD - (M.MOD - 1) / n));
    u32x8 irt2 = _irt2, irt4 = _irt4;
    for (u32 i = 0; i != n; i += 8) {
      u32x8 fi = MX.loadu(f + i), a, b;
      a = MX.neg<0xaa>(fi), b = u32x8_shuffle<0xb1>(fi);
      fi = MX.mul(irt2, MX.add(a, b));
      a = MX.neg<0xcc>(fi), b = u32x8_shuffle<0x4e>(fi);
      fi = MX.mul(irt4, MX.add(a, b));
      a = MX.neg<0xf0>(fi), b = _mm256_permute2x128_si256(fi, fi, 0b01);
      MX.storeu(f + i, MX.mul(MX.add(a, b), rtix));
      rtix = MX.mul(rtix, irate4ix[std::countr_one(i / 8)]);
    }
    for (u32 l = 8; l <= n / 2; l *= 2) {
      u32 *f0 = f, *f1 = f + l;
      for (u32 j = 0; j != l; j += 8) {
        u32x8 x = MX.loadu(f0 + j), y = MX.loadu(f1 + j);
        MX.storeu(f0 + j, MX.add(x, y));
        MX.storeu(f1 + j, MX.sub(x, y));
      }
      u32 r = irate2[0];
      for (u32 i = l * 2, k = 1; i != n; i += l * 2, ++k) {
        u32x8 rx = MX.set1(r);
        f0 = f + i, f1 = f0 + l;
        for (u32 j = 0; j != l; j += 8) {
          u32x8 x = MX.loadu(f0 + j), y = MX.loadu(f1 + j);
          MX.storeu(f0 + j, MX.add(x, y));
          MX.storeu(f1 + j, MX.mul(MX.sub(x, y), rx));
        }
        r = M.mul(r, irate2[std::countr_one(k)]);
      }
    }
  }
  void conv(u32 *f, u32 *g, u32 n) {
    ntt(f, n);
    if (f != g)
      ntt(g, n);
    if (n < 8) {
      const auto M = _MX.M;
      for (u32 i = 0; i != n; ++i)
        f[i] = M.mul(f[i], g[i]);
    } else {
      const auto MX = _MX;
      for (u32 i = 0; i != n; i += 8) {
        u32x8 fx = MX.loadu(f + i), gx = MX.loadu(g + i);
        MX.storeu(f + i, MX.mul(fx, gx));
      }
    }
    intt(f, n);
  }
};
}
namespace poly{
    inline vector<int> mul(vector<int> a, vector<int> b) {
	int n = (int)a.size() - 1, m = (int)b.size() - 1, k = 0;
	while ((1 << k) <= n + m) {
		++k;
	}
	const auto M = NTT::Mont32{998244353};
	NTT::NTT32OriginalRadix2AVX2 ntt(M, 3);
	vector<NTT::u32> A(1 << k), B(1 << k);
	for (int i = 0; i <= n; ++i) {
		A[i] = M.trans((signed)a[i]);
	}
	for (int i = 0; i <= m; ++i) {
		B[i] = M.trans((signed)b[i]);
	}
	ntt.conv(A.data(), B.data(), 1 << k);
	vector<int> res(n + m + 1);
	for (int i = 0; i <= n + m; ++i) {
		res[i] = M.get(A[i]);
	}
	return res;
}
}


#define mod 998244353ll
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*1ll*a%mod;
        a=a*1ll*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn<<1],inv[maxn<<1];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*1ll*inv[n]%mod*1ll*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*1ll*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*1ll*(i+1)%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int a[maxn];
int f[210][210];
vector<int> sovle(int l,int r,int p,vector<int> &dw){
	if(r-l+1+a[r]-p+1<=128){
		for(int i=0;i<=r-l;i++)f[i][0]=dw[i];
		for(int i=0;i<=r-l;i++){
			for(int j=1;j<=a[i+l]-p;j++){
				f[i][j]=f[i][j-1];
				(i&&j<=a[i+l-1]-p)&&(inc(f[i][j],f[i-1][j]),0);
			}
		}
		vector<int> ans(a[r]-p+1);
		for(int i=0;i<=a[r]-p;i++)ans[i]=f[r-l][i];
		return ans;
	}
	if(l==r){
		vector<int> ans(a[l]-p+1,dw[0]);
		return ans;
	}
	int mid=l+r>>1;
	vector<int> dwl=dw;dwl.resize(mid-l+1);
	vector<int> mf=sovle(l,mid,p,dwl);
	vector<int> ans(a[r]-p+1),dwr(r-mid);
	{
		vector<int> ff(mf.size()),gg(r-mid+1+ff.size());
		for(int i=1;i<ff.size();i++)ff[i]=mf[i]*1ll*inv[a[mid]-p-i]%mod;
		for(int i=0;i<gg.size();i++)gg[i]=fac[i];
		ff=poly::mul(ff,gg);
		for(int i=0;i<r-mid;i++)inc(dwr[i],ff[i+a[mid]-p]*1ll*inv[i]%mod);
		// for(int i=1;i<=a[mid]-p;i++){
			// for(int j=0;j<r-mid;j++)(dwr[j]+=mf[i]*1ll*C(j+a[mid]-p-i,j))%=mod;
		// }
	}
	{
		vector<int> ff(r-mid),gg(r-mid);
		for(int i=0;i<r-mid;i++)ff[i]=dw[i+mid-l+1];
		for(int i=0;i<r-mid;i++)gg[i]=C(i+a[mid]-p-1,a[mid]-p-1);
		ff=poly::mul(ff,gg);
		for(int i=0;i<r-mid;i++)inc(dwr[i],ff[i]);
		// for(int i=0;i<r-mid;i++){
			// for(int j=i;j<r-mid;j++)(dwr[j]+=dw[i+mid-l+1]*1ll*C(j-i+a[mid]-p-1,a[mid]-p-1))%=mod;
		// }
	}
	{
		vector<int> ff(a[mid]-p+1),gg(a[mid]-p+1);
		for(int i=1;i<=a[mid]-p;i++)ff[i]=mf[i];
		for(int i=0;i<=a[mid]-p;i++)gg[i]=C(r-mid-1+i,r-mid-1);
		ff=poly::mul(ff,gg);
		for(int i=1;i<=a[mid]-p;i++)inc(ans[i],ff[i]);
		// for(int i=1;i<=a[mid]-p;i++){
			// for(int j=i;j<=a[mid]-p;j++)(ans[j]+=mf[i]*1ll*C(r-mid-1+j-i,r-mid-1))%=mod;
		// }
	}
	{
		vector<int> ff(r-mid),gg(r-mid-1+a[mid]-p);
		for(int i=0;i<r-mid;i++)ff[i]=dw[i+mid-l+1]*1ll*inv[r-mid-1-i]%mod;
		for(int i=0;i<gg.size();i++)gg[i]=fac[i];
		ff=poly::mul(ff,gg);
		for(int i=1;i<=a[mid]-p;i++)inc(ans[i],ff[r-mid-1+i-1]*1ll*inv[i-1]%mod);
		// for(int i=0;i<r-mid;i++){
			// for(int j=1;j<=a[mid]-p;j++)(ans[j]+=dw[i+mid-l+1]*1ll*C(r-mid-1-i+j-1,j-1))%=mod;
		// }
	}
	ans[0]=dw[r-mid];
	if(a[mid]==p){
		for(int i=0;i<r-mid;i++)dwr[i]=dw[i+mid-l+1];
	}
	// cout<<l<<" "<<r<<" "<<p<<" s\n";
	// for(int v:dw)cout<<v<<" ";cout<<"\n";
	// for(int v:dwr)cout<<v<<" ";cout<<"\n";
	// for(int i=0;i<=a[mid]-p;i++)cout<<ans[i]<<" ";cout<<"\n";
	vector<int> rf=sovle(mid+1,r,a[mid],dwr);
	for(int i=a[mid]+1;i<=a[r];i++)ans[i-p]=rf[i-a[mid]];
	return ans;
}
int n,m,k;
int calc(vector<int> &lim){
	for(int i=0;i<=n;i++)a[i]=lim[i];
	for(int i=n-1;~i;i--)a[i]=min(a[i],a[i+1]);
	// for(int i=0;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	vector<int> dw(n+1);
	for(int i=0;i<=n;i++)dw[i]=1;
	vector<int> f=sovle(0,n,0,dw);
	// for(int i=0;i<=m;i++)cout<<f[i]<<" ";cout<<"\n";
	return f[m];
}
void work(){
	m=read();n=read();k=read();init(n+m+10);
	vector<int> a(n+1,m),b(n+1,m);
	for(int i=1;i<=k;i++){
		int l2=read(),l1=read(),r2=read(),r1=read();
		a[r1-1]=min(a[r1-1],l2);
		b[l1+1]=min(b[l1+1],m-r2);
	}
	reverse(b.begin(),b.end());
	printf("%lld\n",(calc(a)+calc(b))*1ll*ksm(C(n+m,n))%mod);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}