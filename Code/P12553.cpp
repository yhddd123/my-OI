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
const int maxn=2010;
const int inf=1e9;
bool mbe;

int n;
char s[maxn][3*maxn];
int val[26],bas;
mt19937 rnd(time(0));
map<int,int> mp;
int to[maxn];
int h1[maxn],h2[maxn];
vector<int> id;
void work(){
	bas=rnd()%mod;for(int i=0;i<26;i++)val[i]=rnd()%mod;
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);int m=strlen(s[i]+1);
		if(m==1)id.pb(i);
		else{
			for(int j=1;j<n;j++)h1[i]=(h1[i]*bas+val[s[i][j]-'a'])%mod;
			for(int j=2;j<=n;j++)h2[i]=(h2[i]*bas+val[s[i][j]-'a'])%mod;
			if(!mp[h1[i]])mp[h1[i]]=i;
		}
	}
	for(int i=1;i<=n;i++)if(h1[i]&&!to[i]){
		int x=i;
		while(!mp[h2[x]]){
			int u=id.back();id.pop_back();
			for(int j=1;j<=3*n;j++)s[u][j]=s[x][j+1];
			for(int j=1;j<n;j++)h1[u]=(h1[u]*bas+val[s[u][j]-'a'])%mod;
			for(int j=2;j<=n;j++)h2[u]=(h2[u]*bas+val[s[u][j]-'a'])%mod;
			if(!mp[h1[u]])mp[h1[u]]=u;
			to[x]=u;x=u;
		}
		to[x]=mp[h2[x]];
	}
	for(int u:id)to[u]=u;
	for(int i=1;i<=n;i++){
		if(h1[i])cout<<s[i][1];
		else cout<<"a";
	}
	cout<<"\n";
	for(int i=1;i<=n;i++)cout<<to[i]<<" ";cout<<"\n";
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