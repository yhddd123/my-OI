#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,s,ans;
int id[5],a[5];
void sovle(){
	int res=0;
	for(int i=0;i<2;i++){
		int d=a[i]/s;
		a[i]-=d*s;res+=d;
		if(a[3]>=s-a[i])++res,a[3]-=s-a[i];
		else return ;
	}
	// cout<<a[2]<<" "<<a[3]<<" "<<res<<"\n";
	if(a[2]+a[3]<s)res+=2;
	else res+=(a[2]+a[3]+s-1)/s;
	ans=min(ans,res);
}
void work(){
	n=read();m=read();s=read();
	id[0]=0,id[1]=1,id[2]=2,id[3]=3;
	ans=inf;
	do{
		for(int i=0;i<4;i++){
			if(id[i]<2)a[i]=n;
			else a[i]=m;
			// cout<<a[i]<<" ";
		}
		// cout<<"\n";
		int res=0;
		for(int i=0;i<4;i++){
			// cout<<i<<" "<<a[i]<<"\n";
			int d=a[i]/s;
			a[i]-=d*s;res+=d;
			if(a[i]){
				if(i<=3&&a[i+1]>=s-a[i])a[i+1]-=s-a[i],++res;
				else ++res;
			}
		}
		// for(int i=0;i<4;i++)cout<<id[i]<<" ";cout<<"\n";
		// cout<<res<<"\n";
		ans=min(ans,res);
	}while(next_permutation(id,id+4));
	a[0]=n,a[1]=n,a[2]=m,a[3]=m;
	sovle();
	a[0]=m,a[1]=m,a[2]=n,a[3]=n;
	sovle();
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}
