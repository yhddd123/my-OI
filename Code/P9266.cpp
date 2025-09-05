#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=100010;
const ll inf=1e18;

int n,k;ll ans;
int to[maxn],col[maxn];
char s[maxn];
struct ds{
    int l,r,t[maxn];
    ll ans;
    ds(){l=1,r=0;}
    ll que(int ql,int qr){
        while(r<qr)r++,(s[r]==')'&&to[r]>=l)&&(ans+=(++t[col[r]]));
        while(l>ql){
            l--;
            if(s[l]=='('&&to[l]<=r)ans+=(++t[col[l]]);
        }
        while(r>qr){
            if(s[r]==')'&&to[r]>=l)ans-=(t[col[r]]--);
            r--;
        }
        while(l<ql){
            if(s[l]=='('&&to[l]<=r)ans-=(t[col[l]]--);
            l++;
        }
        return ans;
    }
}a[2];
int st[maxn],tp;
#define pii pair<ll,int>
#define fi first
#define se second
pii dp[maxn];ll w;int p[maxn];
void upd(int j,int i,int op){
	pii nw={dp[j-1].fi+a[op].que(j,i)+w,dp[j-1].se+1};
	if(nw<dp[i])dp[i]=nw,p[i]=j;
}
void sovle(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	for(int i=p[l];i<=p[r];i++)upd(i,mid,0);
	sovle(l,mid);
	for(int i=l;i<=mid;i++)upd(i,r,1);
	sovle(mid+1,r);
}
signed main(){
    scanf("%d%d%s",&n,&k,s+1);
    for(int i=1,idx=0;i<=n;i++){
        if(s[i]=='(')to[i]=n+1,st[++tp]=i;
        else if(tp){
            to[st[tp]]=i,to[i]=st[tp];
            if(col[st[tp]-1])col[st[tp]]=col[i]=col[st[tp]-1];
            else col[st[tp]]=col[i]=++idx;
            tp--;
        }
    }
    ll l=0,r=n*n;
    while(l<=r){
    	w=l+r>>1;
		for(int i=1;i<=n;i++)dp[i]={inf,0},p[i]=1;
	    upd(1,n,0);sovle(1,n);
		// cout<<w<<" "<<dp[n].fi<<" "<<dp[n].se<<"\n";
		// for(int i=1;i<=n;i++)cout<<dp[i].fi<<" "<<dp[i].se<<"\n";
    	if(dp[n].se>k)l=w+1;
    	else ans=dp[n].fi-k*w,r=w-1;
    }
    printf("%lld\n",ans);
}