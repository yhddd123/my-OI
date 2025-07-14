#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=400010;
const int inf=2e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,ans;
struct nd{
	int l,r,id;
}d[maxn];
int b[maxn],l;
bool cmp(nd u,nd v){return u.l<v.l;}
bool cmp1(nd u,nd v){return u.id<v.id;}
int to[maxn][21];
int mn[maxn],id[maxn];
int get(int l,int r){
	int res=0;
	for(int i=20;i>=0;i--){
		if(d[to[l][i]].r<=r)res+=(1<<i),l=to[l][i];
	}
	return res;
}
struct node{
	int p,id;
	bool operator <(const node&tmp)const{return p<tmp.p;}
};
set<node> s;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		d[i].l=read();d[i].r=read();d[i].id=i;
		b[++l]=d[i].l;b[++l]=d[i].r;
	}
	sort(b+1,b+l+1);
	l=unique(b+1,b+l+1)-b-1;
	for(int i=1;i<=n;i++){
		d[i].l=lower_bound(b+1,b+l+1,d[i].l)-b;
		d[i].r=lower_bound(b+1,b+l+1,d[i].r)-b;
	}
	sort(d+1,d+n+1,cmp);
	d[0]={-inf,-inf,0};d[n+1]={inf,inf,n+1};
	memset(mn,0x3f,sizeof(mn));
	mn[l+1]=l+1;id[l+1]=n+1;
	for(int i=n;i>=1;i--){
		if(mn[d[i].l]>d[i].r){
			mn[d[i].l]=d[i].r;
			id[d[i].l]=d[i].id;
		}
	}
	for(int i=l;i>=1;i--){
		if(mn[i]>mn[i+1]){
			mn[i]=mn[i+1];	
			id[i]=id[i+1];
		}
	}
	to[n+1][0]=n+1;
	for(int i=1;i<=n;i++)to[d[i].id][0]=id[d[i].r+1];
	int st=n+1;for(int i=1;i<=n;i++)if(d[i].r<d[st].r)st=i;
	to[0][0]=d[st].id;
	for(int j=1;j<=20;j++){
		for(int i=0;i<=n+1;i++)to[i][j]=to[to[i][j-1]][j-1];
	}
	sort(d+1,d+n+1,cmp1);
	ans=get(0,inf-1);
	printf("%lld\n",ans);
	s.insert({-inf,0});s.insert({inf,n+1});
	for(int i=1;i<=n;i++){
		if(s.upper_bound({d[i].l,d[i].id})!=s.upper_bound({d[i].r,d[i].id}))continue;
		auto it=s.upper_bound({d[i].l,d[i].id});node r=*it;
		it--;node l=*it;
		if(get(l.id,d[i].l-1)+get(i,r.p-1)+1==get(l.id,r.p-1)){
			s.insert({d[i].l,d[i].id});s.insert({d[i].r,d[i].id});
			printf("%lld ",i);
		}
	}
}
