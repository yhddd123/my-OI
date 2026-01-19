#include<bits/stdc++.h>
// #define int long long
#define mod 1000000009
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
const int maxn=155;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans;
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
unordered_map<string,int> f[maxn][maxn],g[maxn][maxn];
bool chk(string s){
	for(int i=0,j=s.size()-1;i<=j;i++,j--){
		if(s[i]!=s[j])return false;
	}
	return true;
}
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read();
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)f[i][j].clear(),g[i][j].clear();
	}
	f[1][n][""]=1;
	for(int len=n;len;len--){
		for(int i=1,j=len;j<=n;i++,j++){
			for(auto[s,v]:f[i][j]){
				// cout<<i<<" "<<j<<" "<<s<<" "<<v<<" f\n";
				for(int k=i;k<=j;k++){
					string t1=s,t2=to_string(a[j]-a[k-1]);
					while(t1.size()&&t2.size()&&t1.back()==t2.back())t1.pop_back(),t2.pop_back();
					if(t1.size()&&t2.size())continue;
					if(i==k){
						if(chk(t1+t2))inc(ans,v);
					}
					else{
						if(t2.size())inc(g[i][k-1][t2],v);
						else inc(f[i][k-1][t1],v);
					}
				}
			}
			for(auto[s,v]:g[i][j]){
				// cout<<i<<" "<<j<<" "<<s<<" "<<v<<" g\n";
				for(int k=i;k<=j;k++){
					string t1=to_string(a[k]-a[i-1]),t2=s;
					reverse(t1.begin(),t1.end());
					while(t1.size()&&t2.size()&&t1.back()==t2.back())t1.pop_back(),t2.pop_back();
					if(t1.size()&&t2.size())continue;
					if(k==j){
						if(chk(t1+t2))inc(ans,v);
					}
					else{
						if(t2.size())inc(g[k+1][j][t2],v);
						else inc(f[k+1][j][t1],v);
					}
				}
			}
			// cout<<ans<<"\n";
		}
	}
	printf("%d\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}