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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int x,y,z;
struct SA{
int sa[maxn],rk[maxn<<1],tmp[maxn<<1],ht[maxn],cnt[maxn],id[maxn];
int st[20][maxn];
inline int que(int l,int r){
    l=rk[l],r=rk[r];
    if(l>r)swap(l,r);l++;
    int k=__lg(r-l+1);
    return min(st[k][l],st[k][r-(1<<k)+1]);
}
void init(int *a,int n){
	int w=z;
	for(int i=1;i<=max(n,w);i++)tmp[i]=0;
	for(int i=1;i<=n;i++)++cnt[rk[i]=a[i]];
	for(int i=1;i<=w;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i;i--)sa[cnt[rk[i]]--]=i;
	for(int i=1;i<=w;i++)cnt[i]=0;
    for(int len=1;len<n;len<<=1){
    	int cur=0;for(int i=n-len+1;i<=n;i++)id[++cur]=i;
    	for(int i=1;i<=n;i++)if(sa[i]>len)id[++cur]=sa[i]-len;
    	for(int i=1;i<=n;i++)cnt[tmp[i]=rk[i]]++;
    	for(int i=1;i<=w;i++)cnt[i]+=cnt[i-1];
    	for(int i=n;i;i--)sa[cnt[rk[id[i]]]--]=id[i];
    	for(int i=1;i<=w;i++)cnt[i]=0;
    	int p=0;
        for(int i=1;i<=n;i++){
            if(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+len]==tmp[sa[i-1]+len])rk[sa[i]]=p;
            else rk[sa[i]]=++p;
        }
        w=p;
        if(w==n)break;
    }
    ht[1]=0;
    for(int i=1,l=0;i<=n;i++){
        if(rk[i]==1)continue;
        if(l)l--;
        while(max(i+l,sa[rk[i]-1]+l)<=n&&a[i+l]==a[sa[rk[i]-1]+l])l++;
        ht[rk[i]]=l;
    }
    for(int i=1;i<=n;i++)st[0][i]=ht[i];
    for(int j=1;j<20;j++){
        for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
}
}sa;
inline int lcp(int p,int q){
	if(p>y||q>y)return 0;
	return sa.que(p,q);}
int a[maxn],b[maxn],c[maxn];
int t[maxn],nxt[maxn];
int pw[maxn],bas,val[maxn];
int ans[maxn],res[maxn];
int suf[maxn];
bool calc(){
	nxt[0]=-1;
	for(int i=2,j=0;i<=y;i++){
		while(j&&b[i]!=b[j+1])j=nxt[j];
		if(b[i]==b[j+1])j++;
		nxt[i]=j;
	}
	// for(int i=y+1;i<=maxn-10;i++)b[i]=0;
	sa.init(b,y);
	int p=0;
	for(int i=1,h1=0,h2=0;i<=y&&i<=x;i++){
		h1=(h1*bas+val[b[i]])%mod;
		h2=(h2+val[a[x-i+1]]*pw[i-1])%mod;
		// cout<<h1<<" "<<h2<<" "<<val[b[i]]<<" "<<val[a[x-i+1]]<<"\n";
		if(h1==h2)p=i;
	}
	int l=0,r=y,res=y+1;
	auto chk=[&](int p){
		for(int i=1;i<=z;i++)t[i]=0;
		for(int i=1;i<=z;i++)t[c[i]]++;
		for(int i=1;i<=x;i++)t[a[i]]--;
		for(int i=p+1;i<=y;i++)t[b[i]]--;
		for(int i=1;i<=z;i++)if(t[i]<0)return 0;
		return 1;
	};
	while(l<=r){
		int mid=l+r>>1;
		if(chk(mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	// cout<<p<<" "<<res<<endl;
	if(p<res)return 0;
	auto getmn=[&](int l,int r){
		int mn=b[l];for(int i=l+1;i<=r;i++)mn=min(mn,b[i]);
		return mn;
	};
	auto cmp=[&](int p,int q){
		int l=lcp(p,q);
		if(q+l-1==y)return false;
		return a[1]<getmn(p,q-1)&&b[p+l]<b[q+l];
	};
	int nw=p;p=nxt[p];
	while(p&&p>=res){
		if(cmp(p+1,nw+1))nw=p;
		p=nxt[p];
	}
	for(int i=1;i<=z;i++)t[i]=0;
	for(int i=1;i<=z;i++)t[c[i]]++;
	for(int i=1;i<=x;i++)t[a[i]]--;
	for(int i=nw+1;i<=y;i++)t[b[i]]--;
	int pp=0;for(int i=1;i<a[1];i++){
		for(int j=1;j<=t[i];j++)ans[++pp]=i;
	}
	bool fl1=0,fl2=0;
	for(int i=1;i<=x;i++)if(a[i]!=a[1]&&!fl1)fl1=1,fl2=(a[i]<a[1]);
	for(int i=nw+1;i<=y;i++)if(b[i]!=a[1]&&!fl1)fl1=1,fl2=(b[i]<a[1]);
	if(!fl2){
		for(int j=1;j<=t[a[1]];j++)ans[++pp]=a[1];
	}
	for(int i=1;i<=x;i++)ans[++pp]=a[i];
	for(int i=nw+1;i<=y;i++)ans[++pp]=b[i];
	if(fl2){
		for(int j=1;j<=t[a[1]];j++)ans[++pp]=a[1];
	}
	for(int i=a[1]+1;i<=z;i++){
		for(int j=1;j<=t[i];j++)ans[++pp]=i;
	}
	// cout<<x<<" "<<y<<"\n";
	// for(int i=1;i<=y;i++)cout<<sa.sa[i]<<" ";cout<<"\n";
	// for(int i=1;i<=y;i++)cout<<sa.ht[i]<<" ";cout<<"\n";
	// for(int i=1;i<=z;i++)cout<<ans[i]<<" ";cout<<"\n";
	return 1;
}
bool chk1(){
	int h1=0;for(int i=1;i<=x;i++)h1=(h1*bas+val[a[i]])%mod;
	int h2=0;for(int i=1;i<=x;i++)h2=(h2*bas+val[b[i]])%mod;
	bool fl=(h1==h2);
	for(int i=x+1;i<=y;i++){
		h2=(h2*bas+val[b[i]])%mod;
		(h2+=mod-val[b[i-x]]*pw[x]%mod)%=mod;
		if(h1==h2)fl=1;
	}
	if(!fl)return 0;
	int pp=0;
	for(int i=1;i<b[1];i++){
		for(int j=1;j<=t[i];j++)ans[++pp]=i;
	}
	bool fl1=0,fl2=0;
	for(int i=1;i<=y;i++)if(b[i]!=b[1]&&!fl1)fl1=1,fl2=(b[i]<b[1]);
	if(!fl2){
		for(int j=1;j<=t[b[1]];j++)ans[++pp]=b[1];
	}
	for(int i=1;i<=y;i++)ans[++pp]=b[i];
	if(fl2){
		for(int j=1;j<=t[b[1]];j++)ans[++pp]=b[1];
	}
	for(int i=b[1]+1;i<=z;i++){
		for(int j=1;j<=t[i];j++)ans[++pp]=i;
	}
	// for(int i=1;i<=z;i++)cout<<ans[i]<<" ";cout<<"\n";
	return 1;
}
bool chk2(){
	for(int i=1;i<=z;i++)t[i]=0;
	for(int i=1;i<=z;i++)t[c[i]]++;
	for(int i=1;i<=x;i++)t[a[i]]--;
	for(int i=1;i<=y;i++)t[b[i]]--;
	for(int i=1;i<=z;i++)if(t[i]<0)return 0;
	bool fl=0;for(int i=1;i<=x;i++){
		if(a[i]>b[i]){fl=1;break;}
		if(a[i]<b[i])break;
	}
	if(fl){
		for(int i=1;i<=max(x,y);i++)swap(a[i],b[i]);
		swap(x,y);
	}
	int pp=0;
		for(int i=1;i<a[1];i++){
			for(int j=1;j<=t[i];j++)ans[++pp]=i;
		}
		
	bool fl1=0,fl2=0,fl3=0;
	for(int i=1;i<=x;i++)if(a[i]!=a[1]&&!fl1)fl1=1,fl2=(a[i]<a[1]);
	if(!(a[1]==b[1]&&!fl1)&&!fl2){
		fl3=1;
		for(int j=1;j<=t[a[1]];j++)ans[++pp]=a[1];
	}
	for(int i=1;i<=x;i++)ans[++pp]=a[i];
	// cout<<x<<" "<<y<<"\n";
	// cout<<fl1<<" "<<fl2<<"\n";
	if(!(a[1]==b[1])&&fl2){
		fl3=1;
		for(int j=1;j<=t[a[1]];j++)ans[++pp]=a[1];
	}
		for(int i=a[1]+(fl3);i<b[1];i++){
			for(int j=1;j<=t[i];j++)ans[++pp]=i;
		}
		
		fl1=0,fl2=0;
	for(int i=1;i<=y;i++)if(b[i]!=b[1]&&!fl1)fl1=1,fl2=(b[i]<b[1]);
	if(!(a[1]==b[1]&&fl3)&&!fl2){
		for(int j=1;j<=t[b[1]];j++)ans[++pp]=b[1];
	}
	for(int i=1;i<=y;i++)ans[++pp]=b[i];
	if(!(a[1]==b[1]&&fl3)&&fl2){
		for(int j=1;j<=t[b[1]];j++)ans[++pp]=b[1];
	}
		for(int i=b[1]+1;i<=z;i++){
			for(int j=1;j<=t[i];j++)ans[++pp]=i;
		}
	// for(int i=1;i<=z;i++)cout<<ans[i]<<" ";cout<<"\n";
	return 1;
}
bool flag;
void upd(){
	if(!flag){
		for(int i=1;i<=z;i++)res[i]=ans[i];
	}
	else{
		bool fl=0;
		for(int i=1;i<=z;i++){
			if(ans[i]<res[i]){fl=1;break;}
			if(ans[i]>res[i])break;
		}
		if(fl){
			for(int i=1;i<=z;i++)swap(ans[i],res[i]);
		}
	}
	flag=1;
}
void work(){
	x=read(),y=read(),z=read();
	for(int i=1;i<=x;i++)a[i]=read();
	for(int i=1;i<=y;i++)b[i]=read();
	for(int i=1;i<=z;i++)c[i]=read();
	for(int i=1;i<=z;i++)t[i]=0;
	for(int i=1;i<=z;i++)t[c[i]]++;
	for(int i=1;i<=y;i++)t[b[i]]--;
	for(int i=1;i<=z;i++)if(t[i]<0){puts("-1");return ;}
	flag=0;
	if(chk1())upd();
	if(chk2())upd();
	if(calc())upd();
	for(int i=1;i<=max(x,y);i++)swap(a[i],b[i]);
	swap(x,y);
	if(calc())upd();
	if(!flag){puts("-1");return ;}
	for(int i=1;i<=z;i++)printf("%d ",res[i]);puts("");
}
mt19937 rnd(time(0));

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int n=maxn-10;
	bas=rnd()%mod;pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas%mod;
	for(int i=1;i<=n;i++)val[i]=rnd()%mod;
	
	int T=read();
	while(T--)work();
}