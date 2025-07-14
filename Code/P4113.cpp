#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=2000010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,c,m,a[maxn];
struct ask{
	int l,r,id;
	bool operator <(const ask&tmp)const{return r<tmp.r;}
}p[maxn];
int ans[maxn];
int lst[maxn],lst2[maxn];
int tree[maxn];
int lowbit(int x){return x&(-x);}
void updata(int x,int w){
	while(x<=n){
		tree[x]+=w;
		x+=lowbit(x);
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();c=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)p[i]={read()-1,read(),i};
	sort(p+1,p+m+1);
	for(int i=1,j=1;i<=n;i++){
		if(!lst[a[i]])lst[a[i]]=i;
		else{
			if(!lst2[a[i]]){
				updata(lst[a[i]],1);
				lst2[a[i]]=lst[a[i]];
				lst[a[i]]=i;
			}
			else{
				updata(lst2[a[i]],-1);
				updata(lst[a[i]],1);
				lst2[a[i]]=lst[a[i]];
				lst[a[i]]=i;
			}
		}
		while(j<=m&&p[j].r==i){
			ans[p[j].id]=query(i)-query(p[j].l);
			j++;
		}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
}
