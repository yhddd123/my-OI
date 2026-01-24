// Problem: P14256 平局（draw）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14256
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-24 18:54:26
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
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
const int maxn=3010;
const int inf=1e9;
bool mbe;

int n;
char s[maxn];
namespace automation{
	int f[110][110][3];
	int op(int u,int v){return (u==(v+1)%3?u:v);}
	map<vector<int>,int> mp;
	int calc(vector<int> a){
		if(mp.find(a)!=mp.end())return mp[a];
		int n=a.size();
		for(int i=1;i<=n;i++){
			for(int c=0;c<3;c++)f[i][i][c]=-inf;
			f[i][i][a[i-1]]=0;
		}
		for(int len=2;len<=n;len++){
			for(int i=1,j=len;j<=n;i++,j++){
				for(int c=0;c<3;c++)f[i][j][c]=-inf;
				for(int k=i;k<j;k++){
					for(int c1=0;c1<3;c1++){
						for(int c2=0;c2<3;c2++)f[i][j][op(c1,c2)]=max(f[i][j][op(c1,c2)],f[i][k][c1]+f[k+1][j][c2]+(c1==c2));
					}
				}
			}
		}
		int ans=0;for(int c=0;c<3;c++)ans=max(ans,f[1][n][c]);
		return mp[a]=ans;
	}
	struct node{
		vector<int> sta;
		pii son[3];
		int val;
	}dft[maxn*6];
	int pw[8]={1,3,9,27,81,243,729,6561};
	bool operator==(node u,node v){
		for(int s=0;s<pw[6];s++){
			vector<int> a=u.sta,b=v.sta;
			for(int i=0;i<6;i++)a.pb((s/pw[i])%3),b.pb((s/pw[i])%3);
			if(calc(a)-u.val!=calc(b)-v.val)return false;
		}
		return true;
	}
	int idx;
	void build(int T){
		int lst=0;
		while(T--){
			int tmp=idx;
			for(int i=lst;i<=tmp;i++){
				for(int j=0;j<3;j++){
					node nw=dft[i];
					nw.sta.pb(j);nw.val=calc(nw.sta);
					int p=-1;
					for(int k=0;k<=idx;k++)if(nw==dft[k]){p=k;break;}
					if(p==-1)dft[++idx]=nw,p=idx;
					dft[i].son[j]={p,nw.val-dft[i].val};
				}
			}
			lst=tmp+1;
		}
	}
	int id(int i){
		if(i<=3)return i-1;
		return i+2;
	}
	void init(int N){
		for(int i=1;i<=3;i++)dft[i-1]=dft[i];
		for(int i=idx;i>=4;i--)dft[i+2]=dft[i];
		idx+=2;
		for(int i=0;i<=idx;i++){
			for(int j=0;j<3;j++)dft[i].son[j].fi=id(dft[i].son[j].fi);
		}
		// for(int i=0;i<=idx;i++)if(i<3||i>=6){
			// cout<<i<<" ";
			// for(int j=0;j<3;j++)cout<<dft[i].son[j].fi<<" "<<dft[i].son[j].se<<" ";cout<<"\n";
			// for(int v:dft[i].sta)cout<<v;cout<<"\n";
		// }
		for(int i=30;i<=N;i++){
			dft[i]=dft[i-18];
			for(int j=0;j<3;j++)dft[i].son[j].fi+=18;
		}
	}
}
using automation::dft;
int f[2][maxn*6],g[2][maxn*6],cur;
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	automation::build(6);
	n=read();scanf("%s",s+1);
	automation::init(n*6);
	for(int i=0;i<=2;i++)if((s[1]-'0')&(1<<i))f[1][i]=1;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=n*6;j++)f[i&1][j]=g[i&1][j]=0;
		int val=s[i]-'0';
		for(int j=0;j<=n*6;j++)if(f[(i&1)^1][j]||g[(i&1)^1][j]){
			// cout<<i<<" "<<j<<" "<<f[(i&1)^1][j]<<" "<<g[(i&1)^1][j]<<"\n";
			for(int c=0;c<3;c++)if(val&(1<<c)){
				inc(f[i&1][dft[j].son[c].fi],f[(i&1)^1][j]);
				inc(g[i&1][dft[j].son[c].fi],g[(i&1)^1][j]);
				if(dft[j].son[c].se)inc(g[i&1][dft[j].son[c].fi],f[(i&1)^1][j]);
			}
		}
	}
	int ans=0;for(int i=0;i<=n*6;i++)inc(ans,g[n&1][i]);
	printf("%lld\n",ans);
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