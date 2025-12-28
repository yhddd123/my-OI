#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
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
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=50010;
const int inf=1e9;
bool mbe;

int n,m;
#define ull unsigned long long
ull pw[65];
struct bs{
	vector<ull> a;
	int len,n;
	void init(int _n){
		n=_n,len=(n+63)/64;a.resize(len+1,0);
	}
	void set0(int x){a[x>>6]&=~pw[x&63];}
	void set1(int x){a[x>>6]|=pw[x&63];}
	bool operator[](int x){return (a[x>>6]>>(x&63))&1;}
	bs operator|(const bs&b)const{
		bs c;c.init(max(n,b.n));
		for(int i=0;i<c.len;i++)c.a[i]=a[i]|b.a[i];
		return c;
	}
	bs operator&(const bs&b)const{
		bs c;c.init(min(n,b.n));
		for(int i=0;i<c.len;i++)c.a[i]=a[i]&b.a[i];
		return c;
	}
	bs operator^(const bs&b)const{
		bs c;c.init(min(n,b.n));
		for(int i=0;i<c.len;i++)c.a[i]=a[i]^b.a[i];
		return c;
	}
	bs operator<<(int x)const{
		bs res;res.init(n);
		int y=x>>6,z=x&63;
		ull lst=0;
		for(int i=0;i+y<res.len;i++){
			res.a[i+y]=lst|(a[i]<<z);
			if(z)lst=a[i]>>(64ll-z);
		}
		return res;
	}
	bs operator-(const bs&b){
		bs res;res.init(n);
		for(int i=0,op=0;i<res.len;i++){
			__int128 val=(__int128)a[i]-b.a[i]-op;
			if(val<0)val+=(__int128)(-1ull)+1,op=1;
			else op=0;
			res.a[i]=val;
		}
		return res;
	}
	int count(){
		int res=0;for(int i=0;i<len;i++)res+=__builtin_popcountll(a[i]);
		return res;
	}
};
char s[maxn],t[maxn];
bs f[maxn],pos[26];
void work(){
	scanf("%s%s",s+1,t+1);n=strlen(s+1),m=strlen(t+1);
	pw[0]=1;for(int i=1;i<=64;i++)pw[i]=pw[i-1]*2;
	for(int i=0;i<=n;i++)f[i].init(m+1);
	for(int i=0;i<26;i++)pos[i].init(m+1);
	for(int i=1;i<=m;i++)pos[t[i]-'a'].set1(i);
	for(int i=1;i<=n;i++){
		bs g=f[i-1]|pos[s[i]-'a'];
		bs h=f[i-1]<<1;h.set1(0);
		f[i]=g&(g^(g-h));
	}
	printf("%d\n",f[n].count());
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