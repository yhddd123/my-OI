struct SA{
int sa[maxn],rk[maxn<<1],tmp[maxn<<1],ht[maxn],cnt[maxn],id[maxn];
int st[20][maxn];
inline int que(int l,int r){
    l=rk[l],r=rk[r];
    if(l>r)swap(l,r);l++;
    int k=__lg(r-l+1);
    return min(st[k][l],st[k][r-(1<<k)+1]);
}
void init(){
	int w=26;
	for(int i=1;i<=max(n,w);i++)tmp[i]=0;
	for(int i=1;i<=n;i++)++cnt[rk[i]=s[i]-'a'+1];
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
        while(min(i+l,sa[rk[i]-1]+l)<=n&&s[i+l]==s[sa[rk[i]-1]+l])l++;
        ht[rk[i]]=l;
    }
    for(int i=1;i<=n;i++)st[0][i]=ht[i];
    for(int j=1;j<20;j++){
        for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
}
}sa;
inline int lcp(int p,int q){return sa.que(p,q);}