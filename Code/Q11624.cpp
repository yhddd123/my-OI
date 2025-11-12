#include<bits/stdc++.h>
#define int long long
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
const int maxn=100010;
const int maxm=510;
const int inf=1e9;
bool mbe;

class Crypto {
public:
Crypto() {
sm = cnt = 0;
seed();
}
int decode(int z) {
z ^= next();
z ^= (next() << 8);
z ^= (next() << 16);
z ^= (next() << 22);
return z;
}
void query(long long z) {
const long long B = 425481007;
const long long MD = 1000000007;
cnt++;
sm = ((sm * B % MD + z) % MD + MD) % MD;
seed();
}
private:
long long sm;
int cnt;
uint8_t data[256];
int I, J;
void swap_data(int i, int j) {
uint8_t tmp = data[i];
data[i] = data[j];
data[j] = tmp;
}
void seed() {
uint8_t key[8];
for (int i = 0; i < 4; i++) {
key[i] = (sm >> (i * 8));
}
for (int i = 0; i < 4; i++) {
key[i+4] = (cnt >> (i * 8));
}
for (int i = 0; i < 256; i++) {
data[i] = i;
}
I = J = 0;
int j = 0;
for (int i = 0; i < 256; i++) {
j = (j + data[i] + key[i%8]) % 256;
swap_data(i, j);
}
}uint8_t next() {
I = (I+1) % 256;
J = (J + data[I]) % 256;
swap_data(I, J);
return data[(data[I] + data[J]) % 256];
}
};

int m,q;
vector<pii> st,ed;
int f[maxn][maxm],g[maxn][maxm];
void addback(int p,int t){
	ed.pb({p,t});int tim=ed.size();
	for(int i=0;i<m;i++)g[tim][i]=g[tim-1][i];
	for(int i=0;i<m;i++)g[tim][(i+p)%m]=max(g[tim][(i+p)%m],g[tim-1][i]+t);
}
void rebuild(){
	for(int tim=1;tim<=ed.size();tim++){
		auto[p,t]=ed[tim-1];
		for(int i=0;i<m;i++)g[tim][i]=g[tim-1][i];
		for(int i=0;i<m;i++)g[tim][(i+p)%m]=max(g[tim][(i+p)%m],g[tim-1][i]+t);
	}
	for(int tim=1;tim<=st.size();tim++){
		auto[p,t]=st[tim-1];
		for(int i=0;i<m;i++)f[tim][i]=f[tim-1][i];
		for(int i=0;i<m;i++)f[tim][(i+p)%m]=max(f[tim][(i+p)%m],f[tim-1][i]+t);
	}
}
void rebuildfront(){
	int pos=(ed.size()+1)/2;
	for(int i=0;i<pos;i++)st.pb(ed[i]);
	reverse(st.begin(),st.end());
	reverse(ed.begin(),ed.end());
	for(int i=1;i<=pos;i++)ed.pop_back();
	reverse(ed.begin(),ed.end());
	rebuild();
}
pii popfront(){
	if(!st.size())rebuildfront();
	pii p=st.back();st.pop_back();
	return p;
}
int mx[10][maxm<<1];
int que(int l,int r){
	int k=__lg(r-l+1);
	return max(mx[k][l],mx[k][r-(1<<k)+1]);
}
int query(int l,int r){
	int ans=-inf;
	for(int i=0;i<2*m;i++)mx[0][i]=g[ed.size()][i%m];
	for(int j=1;j<10;j++){
		for(int i=0;i+(1<<j)-1<2*m;i++)mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<j-1)]);
	}
	for(int i=0;i<m;i++)ans=max(ans,f[st.size()][i]+que(l-i+m,r-i+m));
	// cout<<l<<" "<<r<<" "<<st.size()<<" "<<ed.size()<<"\n";
	return ans;
}
void work(){
	m=read();q=read();
	Crypto c;
	memset(f[0],-0x3f,sizeof(f[0]));
	memset(g[0],-0x3f,sizeof(g[0]));
	f[0][0]=g[0][0]=0;
	while(q--){
		int t=read(),w=read(),v=read(),l=read(),r=read();
		t = c.decode(t);
		w = c.decode(w);
		v = c.decode(v);
		l = c.decode(l);
		r = c.decode(r);
		if(t==1)addback(w,v);
		else popfront();
		int ans=query(l,r);
		ans=(ans<0?-1:ans);
		c.query(ans);
		printf("%lld\n",ans);
	}
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