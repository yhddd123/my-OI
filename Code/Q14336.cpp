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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans;
set<int> s;
int mx[19][maxn];
int que(int l,int r){
	int k=__lg(r-l+1);
	return max(mx[k][l],mx[k][r-(1<<k)+1]);
}
void work(){
	n=read();ans=n-1;
	for(int i=1;i<=n;i++)a[read()]=i;
	for(int i=1;i<=n;i++)mx[0][i]=a[i];
	for(int j=1;j<=18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++){
		s.insert(i);
		int p=i,v=a[i];
		while(1){
			int l=1,r=p-1,res=0;
			while(l<=r){
				int mid=l+r>>1;
				if(que(mid,p-1)>v)res=mid,l=mid+1;
				else r=mid-1;
			}
			p=res;
			auto it=s.upper_bound(p);
			if(it==s.begin())break;
			s.erase(--it);
		}
		ans=min(ans,n-(int)s.size());
	}
	printf("%d\n",ans);
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