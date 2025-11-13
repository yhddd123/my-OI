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
const int inf=1e9;
bool mbe;

int n,ans;
int a[2][maxn];
int st0[maxn],tp0,st1[maxn],tp1;
void work(){
	n=read();
	for(int i=1;i<=2*n;i++){
		int u=read(),v=read();
		if(1<=u&&u<=n){
			if(v<=1)a[0][u]++,ans+=1-v;
			else a[1][u]++,ans+=v-2;
		}
		else if(v<=1){
			if(u<=0)a[0][1]++,ans+=1-u+1-v;
			else a[0][n]++,ans+=u-n+1-v;
		}
		else{
			if(u<=0)a[1][1]++,ans+=1-u+v-2;
			else a[1][n]++,ans+=u-n+v-2;
		}
	}
	for(int i=1;i<=n;i++){
		if(!a[0][i])st0[++tp0]=i;
		if(!a[1][i])st1[++tp1]=i;
		while(a[0][i]>1&&tp0)a[0][i]--,ans+=i-st0[tp0--];
		while(a[1][i]>1&&tp1)a[1][i]--,ans+=i-st1[tp1--];
		while(a[0][i]>1&&tp1)a[0][i]--,ans+=i-st1[tp1--]+1;
		while(a[1][i]>1&&tp0)a[1][i]--,ans+=i-st0[tp0--]+1;
		if(a[0][i]>1)a[0][i+1]+=a[0][i]-1,ans+=a[0][i]-1,a[0][i]=1;
		if(a[1][i]>1)a[1][i+1]+=a[1][i]-1,ans+=a[1][i]-1,a[1][i]=1;
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("bad.in","r",stdin);
	// freopen("bad.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}