#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=150010;
const int inf=1e15;
bool mbe;

int n,a[3][maxn],ans;
int b[maxn],c[maxn],val[maxn][3][3];
int f[3][3][maxn];
pii vl[maxn*3],vr[maxn*3];int nl,nr;
int lsh[maxn*3],len;
#define lb(x) (x&(-x))
int c1[maxn*3],c2[maxn*3];
void upd(int x,int w){
	while(x<=len)c1[x]++,c2[x]+=w,x+=lb(x);
}
int que1(int x){
	int res=0;
	while(x)res+=c1[x],x-=lb(x);
	return res;
}
int que2(int x){
	int res=0;
	while(x)res+=c2[x],x-=lb(x);
	return res;
}
void clr(){
	for(int i=1;i<=len;i++)c1[i]=c2[i]=0;
}
void calc(){
	sort(vl+1,vl+nl+1,[&](pii u,pii v){return u.fi<v.fi;});
	sort(vr+1,vr+nr+1,[&](pii u,pii v){return u.fi<v.fi;});
	len=0;
	for(int i=1;i<=nl;i++)lsh[++len]=vl[i].fi-vl[i].se;
	for(int i=1;i<=nr;i++)lsh[++len]=vr[i].fi-vr[i].se;
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	clr();
	for(int i=nl,j=1;i;i--){
		while(j<=nr&&vl[i].fi+vr[j].fi<0){
			int p=lower_bound(lsh+1,lsh+len+1,vr[j].fi-vr[j].se)-lsh;
			upd(p,vr[j].fi%mod);
			j++;
		}
		int p=upper_bound(lsh+1,lsh+len+1,-(vl[i].fi-vl[i].se))-lsh-1;
		(ans+=vl[i].fi%mod*que1(p)+que2(p))%=mod;
	}
	for(int i=1;i<=nl;i++)swap(vl[i].fi,vl[i].se);
	for(int i=1;i<=nr;i++)swap(vr[i].fi,vr[i].se);
	sort(vl+1,vl+nl+1,[&](pii u,pii v){return u.fi<v.fi;});
	sort(vr+1,vr+nr+1,[&](pii u,pii v){return u.fi<v.fi;});
	len=0;
	for(int i=1;i<=nl;i++)lsh[++len]=vl[i].fi-vl[i].se;
	for(int i=1;i<=nr;i++)lsh[++len]=vr[i].fi-vr[i].se;
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	clr();
	for(int i=nl,j=1;i;i--){
		while(j<=nr&&vl[i].fi+vr[j].fi<0){
			int p=lower_bound(lsh+1,lsh+len+1,vr[j].fi-vr[j].se)-lsh;
			upd(p,vr[j].fi%mod);
			j++;
		}
		int p=lower_bound(lsh+1,lsh+len+1,-(vl[i].fi-vl[i].se))-lsh-1;
		(ans+=vl[i].fi%mod*que1(p)+que2(p))%=mod;
	}
}
void sovle(int l,int r){
	if(l==r){
		(ans+=val[l][0][1]+val[l][0][2]+val[l][1][2])%=mod;
		return ;
	}
	int mid=l+r>>1;
	sovle(l,mid),sovle(mid+1,r);
	for(int o=0;o<=2;o++){
		for(int j=0;j<=2;j++){
			for(int i=l;i<=r;i++)f[o][j][i]=inf;
		}
		for(int o1=0;o1<=2;o1++)f[o][o1][mid]=val[mid][o][o1];
		for(int i=mid-1;i>=l;i--){
			for(int o1=0;o1<=2;o1++){
				for(int o2=0;o2<=2;o2++){
					f[o][o2][i]=min(f[o][o2][i],f[o][o1][i+1]+val[i][o1][o2]);
				}
			}
		}
		for(int o1=0;o1<=2;o1++)f[o][o1][mid+1]=val[mid+1][o][o1];
		for(int i=mid+2;i<=r;i++){
			for(int o1=0;o1<=2;o1++){
				for(int o2=0;o2<=2;o2++){
					f[o][o2][i]=min(f[o][o2][i],f[o][o1][i-1]+val[i][o1][o2]);
				}
			}
		}
	}
	nl=nr=0;
	for(int j=0;j<=2;j++){
		for(int i=l;i<=mid;i++){
			(ans+=f[0][j][i]%mod*(r-mid)*3)%=mod;
			vl[++nl]={f[1][j][i]-f[0][j][i],f[2][j][i]-f[0][j][i]};
		}
	}
	for(int j=0;j<=2;j++){
		for(int i=mid+1;i<=r;i++){
			(ans+=f[0][j][i]%mod*(mid-l+1)*3)%=mod;
			vr[++nr]={f[1][j][i]-f[0][j][i],f[2][j][i]-f[0][j][i]};
		}
	}
	// for(int i=l;i<=mid;i++){
		// for(int o1=0;o1<=2;o1++){
			// for(int j=mid+1;j<=r;j++){
				// for(int o2=0;o2<=2;o2++){
					// int res=min({f[0][o1][i]+f[0][o2][j],f[1][o1][i]+f[1][o2][j],f[2][o1][i]+f[2][o2][j]});
					// // cout<<i<<" "<<o1<<" "<<j<<" "<<o2<<" "<<res<<"\n";
					// (ans+=res)%=mod;
				// }
			// }	
		// }
	// }
	calc();
	// cout<<l<<" "<<r<<" "<<ans<<endl;
}
void work(){
	read();n=read();
	for(int i=0;i<=2;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();
	}
	b[1]=c[n]=inf;
	for(int i=2;i<=n;i++)b[i]=min(b[i-1],a[1][i-1])+a[0][i-1]+a[2][i-1];
	for(int i=n-1;i;i--)c[i]=min(c[i+1],a[1][i+1])+a[0][i+1]+a[2][i+1];
	for(int i=1;i<=n;i++){
		for(int j=0;j<=2;j++)val[i][j][j]=a[j][i];
		val[i][0][1]=val[i][1][0]=a[0][i]+a[1][i];
		val[i][1][2]=val[i][2][1]=a[1][i]+a[2][i];
		val[i][0][2]=val[i][2][0]=a[0][i]+a[2][i]+min({a[1][i],b[i],c[i]});
	}
	// cout<<val[2][0][2]<<"\n";
	sovle(1,n);
	ans%=mod,ans+=mod,ans%=mod;
	printf("%lld\n",ans*2%mod);
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