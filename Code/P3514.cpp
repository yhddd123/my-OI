#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=2000010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],sum;
char c[maxn];
int val,mx;
int l[maxn],r[maxn];
void work(){
	n=read();m=read();
	scanf("%s",c+1);
	for(int i=1;i<=n;i++){
		if(c[i]=='T')a[i]=2;
		else a[i]=1;
		sum+=a[i];
	}
	val=sum;
	for(int i=1;i<=n;i++){
		val-=a[i];
		if(a[i]==1){
			mx=val;
			l[mx]=i+1;r[mx]=n;
			break;
		}
	}
	val=sum;
	for(int i=n;i>=1;i--){
		val-=a[i];
		if(a[i]==1){
			if(mx<val)mx=val,l[mx]=1,r[mx]=i-1;
			break;
		}
	}
	l[sum]=1;r[sum]=n;
	for(int i=sum;i>=2;i-=2){
		if(a[l[i]]==2)l[i-2]=l[i]+1,r[i-2]=r[i];
		else if(a[r[i]]==2)r[i-2]=r[i]-1,l[i-2]=l[i];
		else l[i-2]=l[i]+1,r[i-2]=r[i]-1;
	}
	for(int i=mx;i>=2;i-=2){
		if(a[l[i]]==2)l[i-2]=l[i]+1,r[i-2]=r[i];
		else if(a[r[i]]==2)r[i-2]=r[i]-1,l[i-2]=l[i];
		else l[i-2]=l[i]+1,r[i-2]=r[i]-1;
	}
	while(m--){
		int u=read();
		if(!l[u])printf("NIE\n");
		else printf("%lld %lld\n",l[u],r[u]);
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
