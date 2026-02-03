// Problem: CF232E Quick Tortoise
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF232E
// Memory Limit: 500 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-02-02 10:08:05
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=510;
const int maxq=600010;
const int inf=1e9;
bool mbe;

#define ull unsigned long long
ull pw[65];
struct bs{
	vector<ull> a;
	int len,n;
	void init(int _n){
		n=_n,len=(n+63)/64;a.resize(len+1);
		for(int i=0;i<len;i++)a[i]=0;
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
	void operator|=(const bs&b){
		for(int i=0;i<max(len,b.len);i++)a[i]|=b.a[i];
	}
	void operator&=(const bs&b){
		for(int i=0;i<min(len,b.len);i++)a[i]&=b.a[i];
	}
	bool any(){
		for(int i=0;i<len;i++)if(a[i])return true;
		return false;
	}
};
int n,m,q;
bool a[maxn][maxn];
char s[maxn];
bool ans[maxq];
bs pre[maxn][maxn],suf[maxn][maxn];
void sovle(int l1,int r1,int l2,int r2,vector<tuple<int,int,int,int,int>> &que){
	if(l1>r1||l2>r2||!que.size())return ;
	// if(r1-l1+1>=r2-l2+1){
		int mid=(l1+r1)/2;
		for(int i=l1;i<=mid;i++){
			for(int j=l2;j<=r2;j++)if(a[i][j])pre[i][j].init(r2-l2+1);
		}
		for(int i=mid;i<=r1;i++){
			for(int j=l2;j<=r2;j++)if(a[i][j])suf[i][j].init(r2-l2+1);
		}
		for(int j=l2;j<=r2;j++)if(a[mid][j])pre[mid][j].set1(j-l2),suf[mid][j].set1(j-l2);
		for(int i=mid;i>=l1;i--){
			for(int j=r2;j>=l2;j--)if(a[i][j]){
				if(i+1<=mid&&a[i+1][j])pre[i][j]|=pre[i+1][j];
				if(j+1<=r2&&a[i][j+1])pre[i][j]|=pre[i][j+1];
			}
		}
		for(int i=mid;i<=r1;i++){
			for(int j=l2;j<=r2;j++)if(a[i][j]){
				if(i-1>=mid&&a[i-1][j])suf[i][j]|=suf[i-1][j];
				if(j-1>=l2&&a[i][j-1])suf[i][j]|=suf[i][j-1];
			}
		}
		vector<tuple<int,int,int,int,int>> ql,qr;
		for(auto[x1,y1,x2,y2,id]:que){
			if(x1<=mid&&x2>=mid){
				bs f=pre[x1][y1]&suf[x2][y2];
				ans[id]=f.any();
			}
			else if(x2<mid)ql.pb({x1,y1,x2,y2,id});
			else qr.pb({x1,y1,x2,y2,id});
		}
		sovle(l1,mid-1,l2,r2,ql),sovle(mid+1,r1,l2,r2,qr);
	// }
	// else{
		// int mid=(l2+r2)/2;
		// for(int i=l2;i<=mid;i++){
			// for(int j=l1;j<=r1;j++)if(a[j][i])pre[i][j].init(r1-l1+1);
		// }
		// for(int i=mid;i<=r2;i++){
			// for(int j=l1;j<=r1;j++)if(a[j][i])suf[i][j].init(r1-l1+1);
		// }
		// for(int j=l1;j<=r1;j++)if(a[j][mid])pre[mid][j].set1(j-l1),suf[mid][j].set1(j-l1);
		// for(int i=mid;i>=l2;i--){
			// for(int j=r1;j>=l1;j--)if(a[j][i]){
				// if(i+1<=mid&&a[j][i+1])pre[i][j]|=pre[i+1][j];
				// if(j+1<=r1&&a[j+1][i])pre[i][j]|=pre[i][j+1];
			// }
		// }
		// for(int i=mid;i<=r2;i++){
			// for(int j=l1;j<=r1;j++)if(a[j][i]){
				// if(i-1>=mid&&a[j][i-1])suf[i][j]|=suf[i-1][j];
				// if(j-1>=l1&&a[j-1][i])suf[i][j]|=suf[i][j-1];
			// }
		// }
		// vector<tuple<int,int,int,int,int>> ql,qr;
		// for(auto[x1,y1,x2,y2,id]:que){
			// if(y1<=mid&&y2>=mid)ans[id]=(pre[y1][x1]&suf[y2][x2]).any();
			// else if(y2<mid)ql.pb({x1,y1,x2,y2,id});
			// else qr.pb({x1,y1,x2,y2,id});
		// }
		// sovle(l1,r1,l2,mid-1,ql),sovle(l1,r1,mid+1,r2,qr);
	// }
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)a[i][j]=s[j]=='.';
	}
	q=read();
	vector<tuple<int,int,int,int,int>> que;
	for(int i=1;i<=q;i++){
		int x1=read(),y1=read(),x2=read(),y2=read();
		que.pb({x1,y1,x2,y2,i});
	}
	pw[0]=1;for(int i=1;i<64;i++)pw[i]=pw[i-1]*2;
	sovle(1,n,1,m,que);
	for(int i=1;i<=q;i++)puts(ans[i]?"Yes":"No");
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