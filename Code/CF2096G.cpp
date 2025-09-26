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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,k,a[maxn],ss[maxn];
int pw[20];
vector<int> ask[20];
bool vis[maxn*3];
char s[20];
void work(){
	n=read();
	for(int i=1;i<20;i++)if(pw[i]>=n){k=i;break;}
	for(int i=0;i<=k;i++)ask[i].clear();
	for(int i=1;i<=n;i++)a[i]=ss[i]=0;
	for(int i=0;i<pw[k];i++)vis[i]=0;
	if(n&1)a[n]=0,vis[0]=1;
	for(int i=1,m=1;i<pw[k]&&m<n;i++)if(!vis[i]){
		int j=0;
		for(int p=0;p<k;p++){
			int v=(i/pw[p])%3;
			if(v)v=3-v;
			j+=pw[p]*v;
		}
		vis[i]=vis[j]=1;
		a[m]=i,a[m+1]=j;m+=2;
	}
	for(int i=0;i<k;i++){
		vector<int> id[3];
		for(int j=1;j<=n;j++){
			int v=(a[j]/pw[i])%3;
			id[v].pb(j);ss[j]+=v;
		}
		// cout<<id[1].size()<<" "<<id[2].size()<<"\n";
		for(int u:id[1])ask[i].pb(u);
		for(int u:id[2])ask[i].pb(u);
	}
	vector<int> id[3];
	for(int j=1;j<=n;j++)id[ss[j]%3].pb(j);
	if(id[0].size()==id[1].size()){
		for(int u:id[0])ask[k].pb(u);
		for(int u:id[1])ask[k].pb(u);
	}else if(id[0].size()==id[2].size()){
		for(int u:id[0])ask[k].pb(u);
		for(int u:id[2])ask[k].pb(u);
	}else{
		for(int u:id[1])ask[k].pb(u);
		for(int u:id[2])ask[k].pb(u);
	}
	printf("%d\n",k+1);fflush(stdout);
	for(int i=0;i<=k;i++){
		printf("%d ",ask[i].size());for(int u:ask[i])printf("%d ",u);printf("\n");fflush(stdout);
	}
	scanf("%s",s);
	int val=0,sum=0,p=0;
	for(int i=0;i<k;i++){
		if(s[i]!='?'){
			if(s[i]=='L')val+=pw[i],sum++;
			if(s[i]=='R')val+=2*pw[i],sum+=2;
		}
		else p=i;
	}
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	// cout<<val<<" "<<sum<<" "<<p<<"\n";
	if(s[k]!='?'){
		int a,b,c,v;
		if(id[0].size()==id[1].size())a=0,b=1,c=2;
		else if(id[0].size()==id[2].size())a=0,b=2,c=1;
		else a=1,b=2,c=0;
		if(s[k]=='L')v=a;
		if(s[k]=='R')v=b;
		if(s[k]=='N')v=c;
		val+=pw[p]*((v-sum%3+3)%3);
	}
	for(int i=1;i<=n;i++)if(a[i]==val){printf("%d\n",i);fflush(stdout);return ;}
	exit(0);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	pw[0]=1;for(int i=1;i<20;i++)pw[i]=pw[i-1]*3%mod;
	
	T=read();
	while(T--)work();
}