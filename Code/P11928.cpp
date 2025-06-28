// Problem: P11928 [PA 2025] 子序列 / Podciągi
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11928
// Memory Limit: 1 MB
// Time Limit: 15000 ms
// Written by yhm.
// Start codeing:2025-03-27 12:50:37
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
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

int n,q;
set<int> pos[6];
char s[maxn],op[6];
struct mat{
	int e[7][7];
	mat(){mems(e,0);}
	mat operator*(const mat &tmp)const{
		mat res;
		for(int i=0;i<=6;i++){
			for(int k=0;k<=6;k++){
				for(int j=0;j<=6;j++)(res.e[i][j]+=e[i][k]*tmp.e[k][j])%=mod;
			}
		}
		return res;
	}
}tree[maxn<<2],mul[maxn<<2];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
void up(int nd,int l,int r){
	mat res;
	for(int i=0;i<6;i++){
		int lsti=*--pos[i].upper_bound(mid);
		if(lsti<l)continue;
		for(int j=0;j<6;j++){
			int lstj=*pos[j].lower_bound(mid+1);
			if(lstj>r)continue;
			if((*pos[i].lower_bound(mid+1))>=lstj&&(*--pos[j].upper_bound(mid))<=lsti){
				res.e[i][j]=1;
			}
		}
	}
	res=tree[ls]*res;res=res*tree[rs];
	for(int i=0;i<6;i++){
		if((*--pos[i].upper_bound(mid))<l){
			for(int j=0;j<6;j++)(res.e[i][j]+=tree[rs].e[i][j])%=mod;
		}
	}
	for(int j=0;j<6;j++){
		if((*pos[j].lower_bound(mid+1))>r){
			for(int i=0;i<6;i++)(res.e[i][j]+=tree[ls].e[i][j])%=mod;
		}
	}
	tree[nd]=res;
	mul[nd]=mul[ls]*mul[rs];
}
void build(int nd,int l,int r){
	if(l==r){
		tree[nd].e[s[l]-'a'][s[l]-'a']=1;
		for(int i=0;i<=6;i++)mul[nd].e[i][i]=1;
		for(int i=0;i<=6;i++)mul[nd].e[i][s[l]-'a']=1;
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd,l,r);
}
void modif(int nd,int l,int r,int p){
	if(l==r){
		mems(tree[nd].e,0);
		tree[nd].e[s[l]-'a'][s[l]-'a']=1;
		mems(mul[nd].e,0);
		for(int i=0;i<=6;i++)mul[nd].e[i][i]=1;
		for(int i=0;i<=6;i++)mul[nd].e[i][s[l]-'a']=1;
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	up(nd,l,r);
}
int calc(mat u){
	int res=0;
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++)(res+=u.e[i][j])%=mod;
	}
	return res;
}
int calc1(mat u){
	int res=0;for(int i=0;i<6;i++)(res+=u.e[6][i])%=mod;
	return res;
}
void work(){
	n=read();q=read();scanf("%s",s+1);
	for(int i=0;i<6;i++)pos[i].insert(0),pos[i].insert(n+1);
	for(int i=1;i<=n;i++)pos[s[i]-'a'].insert(i);
	build(1,1,n);
	// for(int i=0;i<6;i++){
		// for(int j=0;j<6;j++)cout<<tree[1].e[i][j]<<" ";cout<<"\n";
	// }
	// for(int i=0;i<=6;i++){
		// for(int j=0;j<=6;j++)cout<<mul[1].e[i][j]<<" ";cout<<"\n";
	// }
	printf("%lld\n",(calc1(mul[1])+mod-calc(tree[1]))%mod);
	while(q--){
		int u=read();scanf("%s",op);
		pos[s[u]-'a'].erase(u),s[u]=op[0],pos[s[u]-'a'].insert(u);
		modif(1,1,n,u);
		// cout<<calc1(mul[1])<<" "<<calc(tree[1])<<"\n";
		printf("%lld\n",(calc1(mul[1])+mod-calc(tree[1]))%mod);
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