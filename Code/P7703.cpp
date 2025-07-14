#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,ans[maxn];
struct nd{
	int num;
	set<int> s1,s2;
}a[maxn];
bool cmp(nd u,nd v){return u.num<v.num;}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--){
		n=read();m=n;
		for(int i=1;i<=n;i++){
			a[i].num=read();
			a[i].s1.clear();a[i].s2.clear();
			a[i].s1.insert(i);
			ans[i]=0;
		}
		while(n){
			sort(a+1,a+n+1,cmp);
			bool fl=0;
			if(n&1)n--;
			for(int i=1;i<=n;i+=2){
				if(a[i].num==a[i+1].num){
					for(int j:a[i].s1)ans[j]=1;
					for(int j:a[i].s2)ans[j]=-1;
					for(int j:a[i+1].s1)ans[j]=-1;
					for(int j:a[i+1].s2)ans[j]=1;
					fl=1;
				}
			}
			if(fl)break;
			for(int i=1;i<=n;i+=2){
				for(int j:a[i].s1)a[i+1].s2.insert(j);
				for(int j:a[i].s2)a[i+1].s1.insert(j);
				a[i+1].num=a[i+1].num-a[i].num;
				a[i+1>>1]=a[i+1];
			}
			n>>=1;
		}
		bool fl=0;
		for(int i=1;i<=m;i++)if(ans[i]!=0)fl=1;
		if(!fl)printf("-1 ");
		else for(int i=1;i<=m;i++)printf("%lld ",ans[i]);
		printf("\n");
	}
}
