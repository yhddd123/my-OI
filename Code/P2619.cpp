#include<bits/stdc++.h>
#define int long long
#define y1 _y1
#define mod 19260817
using namespace std;
const int maxn=100010;

int n,m,num;
struct nd{
	int x,y,val,col;
	bool operator <(const nd &tmp)const{
		if(val==tmp.val)return col<tmp.col;
		return val<tmp.val;
	}
}e[maxn];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int l,r,mid,ans;
int sum,cnt,tmp;
bool check(int x){
	for(int i=1;i<=m;i++)if(!e[i].col)e[i].val+=x;
	for(int i=1;i<=n;i++)f[i]=i;
	sum=cnt=tmp=0;
	sort(e+1,e+m+1);
	for(int i=1;i<=m;i++){
		int xx=fd(e[i].x),yy=fd(e[i].y);
		if(xx!=yy){
			++cnt;f[xx]=yy;
			if(!e[i].col)++tmp;
			sum+=e[i].val;
		}
		if(cnt==n)break;
	}
	for(int i=1;i<=m;i++)if(!e[i].col)e[i].val-=x;
	if(tmp>=num)return true;
	return false;
}
void sovle(){
	cin>>n>>m>>num;
	for(int i=1;i<=m;i++){
		cin>>e[i].x>>e[i].y>>e[i].val>>e[i].col;
		e[i].x++;e[i].y++;
	}
	l=-110;r=110;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			l=mid+1;
			ans=sum-mid*num;
		}
		else r=mid-1;
	}
	cout<<ans<<"\n";
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	T=1;
	while(T--)sovle();
}

