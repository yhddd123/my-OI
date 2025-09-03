#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
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
const int maxn=1000010;
const int inf=1e9;

int n,m,q;
char s[maxn],t[maxn];
int lnk[maxn],len[maxn];
int a[maxn][26];
int p=1,cur=1;
void insert(int c){
    int nd=++cur;
    len[nd]=len[p]+1;
    while(p&&!a[p][c])a[p][c]=nd,nd=lnk[nd];
    if(c==2)cout<<p<<"\n";
    if(!p){lnk[p=nd]=1;return ;}
    int q=a[p][c];
    if(len[p]+1==len[q])lnk[nd]=q;
    else{
        int cl=++cur;
        len[cl]=len[p]+1,lnk[cl]=lnk[q];
        memcpy(a[cl],a[q],sizeof(a[q]));
        lnk[nd]=lnk[q]=cl;
        while(p&&a[p][c]==q)a[p][c]=cl,p=lnk[p];
    }
    p=nd;
}
void go(int &p,int c,int &l){
	while(1){
		if(a[p][c]){
			p=a[p][c],l++;
			break;
		}
		if(!l)break;
		l--;
		if(l==len[lnk[p]])p=lnk[p];
	}
}
int nxt[maxn];
bool vis[maxn];
int sum[maxn];
int pos[maxn];
void work(){
    n=read();m=read();q=read();scanf("%s%s",s+1,t+1);
    while(cur){
        memset(a[cur],0,sizeof(a[cur]));
        lnk[cur]=len[cur]=0,cur--;
    }
    p=cur=1;
    for(int i=1;i<=n;i++)insert(s[i]-'a');
    for(int i=1,p=1,l=0;i<=m;i++){
        go(p,t[i]-'a',l);
        pos[i]=i-l+1;
    }
    for(int i=1;i<=n;i++)cout<<pos[i]<<" ";cout<<"\n";
}

int T;
signed main(){
    freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}