#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
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

int ans;
mt19937 rnd(time(0));
int pw[2][maxn],val[2][26],bas[2],mod[2];
struct node{
int n;
char s[maxn];
int f[2][maxn],g[2][maxn];
void hsh(){
	for(int j=0;j<2;j++){
	    for(int i=1;i<=n;i++)f[j][i]=(f[j][i-1]*bas[j]+val[j][s[i]-'A'])%mod[j];
	    for(int i=n;i;i--)g[j][i]=(g[j][i+1]*bas[j]+val[j][s[i]-'A'])%mod[j];
	}
}
pii que1(int l,int r){return {(f[0][r]-f[0][l-1]*pw[0][r-l+1]%mod[0]+mod[0])%mod[0],(f[1][r]-f[1][l-1]*pw[1][r-l+1]%mod[1]+mod[1])%mod[1]};}
pii que2(int l,int r){return {(g[0][l]-g[0][r+1]*pw[0][r-l+1]%mod[0]+mod[0])%mod[0],(g[1][l]-g[1][r+1]*pw[1][r-l+1]%mod[1]+mod[1])%mod[1]};}
map<pii,int> mp;int idx;
void add(int l,int r){
	pii v=que1(l,r);
    int lst=0;
    while(l<=r){
        pii v=que1(l,r);
        if(mp[v]){
            e[lst].pb(mp[v]);
            break;
        }
        mp[v]=++idx;
        e[lst].pb(idx),lst=idx;
        l++,r--;
    }
    dp[mp[v]]++;
}
vector<int> e[maxn];
int d[maxn];
queue<int> q;
int dp[maxn];
void init(){
    scanf("%s",s+1);n=strlen(s+1);
    hsh();
    for(int i=1;i<=n;i++){
        int l=2,r=min(i,n-i+1),res=l-1;
        while(l<=r){
            int mid=l+r>>1;
            if(que1(i-mid+1,i)==que2(i,i+mid-1))res=mid,l=mid+1;
            else r=mid-1;
        }
        add(i-res+1,i+res-1);
        if(i==n||s[i]!=s[i+1])continue;
        l=2,r=min(i,n-i),res=l-1;
        while(l<=r){
            int mid=l+r>>1;
            if(que1(i-mid+1,i)==que2(i+1,i+mid))res=mid,l=mid+1;
            else r=mid-1;
        }
        add(i-res+1,i+res);
    }
    for(int u=0;u<=idx;u++){
    	for(int v:e[u])d[v]++;
    }
    q.push(0);
    while(!q.empty()){
    	int u=q.front();q.pop();
    	for(int v:e[u]){
    		d[v]--;dp[v]+=dp[u];
    		if(!d[v])q.push(v);
    	}
    }
    // for(int i=1;i<=idx;i++)cout<<dp[i]<<" ";cout<<"\n";
}
}s1,s2;
void work(){
	mod[0]=998244353,mod[1]=1000000007;
	for(int j=0;j<2;j++){
		bas[j]=rnd()%mod[j];for(int i=0;i<26;i++)val[j][i]=rnd()%mod[j];
	    pw[j][0]=1;for(int i=1;i<maxn;i++)pw[j][i]=pw[j][i-1]*bas[j]%mod[j];
	}
    s1.init();s2.init();
    for(auto[v,p]:s1.mp)ans+=s1.dp[p]*s2.dp[s2.mp[v]];
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}