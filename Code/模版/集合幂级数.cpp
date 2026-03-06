inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn];
void fmt1(int *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)inc(a[j+k],a[j]);
		}
	}
}
void fmt2(int *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)inc(a[j+k],mod-a[j]);
		}
	}
}

int tf[maxn+1],tg[maxn+1],th[maxn+1],ni[maxn+1];
void xormul(int *a,int *b,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int i=0;i<=n;i++)fmt1(gg[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)tf[i]=ff[i][s];
		for(int i=0;i<=n;i++)tg[i]=gg[i][s];
		for(int i=0;i<=n;i++){
			th[i]=0;
			for(int j=0;j<=i;j++)inc(th[i],1ll*tf[j]*tg[i-j]%mod);
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)c[s]=ff[__builtin_popcount(s)][s];
}
void xorni(int *a,int *b,int n){//b=1/a
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)tf[i]=ff[i][s];
		int nif=ksm(tf[0]);
		for(int i=0;i<=n;i++){
			th[i]=1;
			for(int j=1;j<=i;j++)inc(th[i],mod-1ll*tf[j]*th[i-j]%mod);
			th[i]=1ll*th[i]*nif%mod;
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}

void xorexp(int *a,int *b,int n){//exp(a)=b
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=1ll*(mod-mod/i)*ni[mod%i]%mod;
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)th[i]=0;
		for(int i=0;i<=n;i++)tf[i]=ff[i][s];
		for(int i=0;i<=n;i++){
			if(i<n)th[i]=1ll*tf[i+1]*(i+1)%mod;
			for(int j=1;j<=i;j++)inc(th[i],1ll*tf[j]*j%mod*th[i-j]%mod*ni[i-j+1]%mod);
		}
		for(int i=1;i<=n;i++)ff[i][s]=1ll*th[i-1]*ni[i]%mod;
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	b[0]=1;for(int s=1;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
void xorln(int *a,int *b,int n){//ln(a)=b
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=1ll*(mod-mod/i)*ni[mod%i]%mod;
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)th[i]=0;
		for(int i=0;i<=n;i++)tf[i]=ff[i][s];
		for(int i=0;i<n;i++){
			th[i]=1ll*tf[i+1]*(i+1)%mod;
			for(int j=1;j<=i;j++)inc(th[i],mod-1ll*tf[j]*th[i-j]%mod);
		}
		for(int i=1;i<=n;i++)ff[i][s]=1ll*th[i-1]*ni[i]%mod;
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	b[0]=0;for(int s=1;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}

int tmp[1<<maxn];
void exp(int *a,int n){
	for(int s=0;s<(1<<n);s++)tmp[s]=a[s],a[s]=0;
	a[0]=1;for(int i=0;i<n;i++)xormul(tmp+(1<<i),a,a+(1<<i),i);
}
void mulself(int *a,int *b,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int i=0;i<=n;i++)fmt1(gg[i],1<<n);
	for(int i=0;i<=n;i++){
		fmt2(gg[i],1<<n);
		for(int s=0;s<(1<<n);s++)if(__builtin_popcount(s)==i)gg[i][s]=mod-gg[i][s],inc(gg[i][s],a[s|(1<<n)]);
		fmt1(gg[i],1<<n);
		for(int j=i+1;j<=n;j++){
			for(int s=0;s<(1<<n);s++)inc(gg[j][s],1ll*gg[i][s]*ff[j-i][s]%mod);
		}
	}
	for(int i=0;i<=n;i++)fmt2(gg[i],1<<n);
	for(int s=0;s<(1<<n);s++)b[s]=gg[__builtin_popcount(s)][s];
}
void ln(int *a,int n){
	for(int s=0;s<(1<<n);s++)tmp[s]=a[s],a[s]=0;
	for(int i=0;i<n;i++)mulself(tmp,a+(1<<i),i);
}

void xormul1(int *a,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)tf[i]=ff[i][s];
		for(int i=0;i<=n;i++)tg[i]=gg[i][s];
		for(int i=0;i<=n;i++){
			th[i]=0;
			for(int j=0;j<=i;j++)inc(th[i],1ll*tf[j]*tg[i-j]%mod);
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)inc(c[s],ff[__builtin_popcount(s)][s]);
}
int hh[maxn+1][1<<maxn];
void comp(int *a,int *b,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int j=1;j<=i;j++)b[i]=1ll*b[i]*j%mod;
	}
	for(int i=0;i<=n;i++)hh[i][0]=b[i];
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			for(int s=0;s<(1<<i-1);s++)gg[j][s]=0;
		}
		for(int s=0;s<(1<<i-1);s++)gg[__builtin_popcount(s)][s]=a[s+(1<<i-1)];
		for(int j=0;j<i;j++)fmt1(gg[j],1<<i-1);
		for(int j=1;j<=n-i+1;j++){
			xormul1(hh[j],hh[j-1]+(1<<i-1),i-1);
		}
	}
	for(int s=0;s<(1<<n);s++)c[s]=hh[0][s];
}

void xormul2(int *a,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s^((1<<n)-1)];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)tf[i]=ff[i][s];
		for(int i=0;i<=n;i++)tg[i]=gg[i][s];
		for(int i=0;i<=n;i++){
			th[i]=0;
			for(int j=0;j<=i;j++)inc(th[i],1ll*tf[j]*tg[i-j]%mod);
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)inc(c[s^((1<<n)-1)],ff[__builtin_popcount(s)][s]);
}
void comptrans(int *a,int *b,int *c,int n){
	for(int s=0;s<(1<<n);s++)hh[0][(1<<n)-1-s]=b[s];
	hh[0][(1<<n)-1]=1;
	for(int i=n;i;i--){
		for(int j=0;j<i;j++){
			for(int s=0;s<(1<<i-1);s++)gg[j][s]=0;
		}
		for(int s=0;s<(1<<i-1);s++)gg[__builtin_popcount(s)][s]=a[s+(1<<i-1)];
		for(int j=0;j<i;j++)fmt1(gg[j],1<<i-1);
		for(int j=n-i+1;j;j--){
			xormul2(hh[j-1]+(1<<i-1),hh[j],i-1);
		}
	}
	for(int i=0;i<=n;i++)c[i]=hh[i][0];
}