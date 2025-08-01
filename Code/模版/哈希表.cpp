struct hsh_table{
	int head[maxn],tot;
	struct nd{
		int nxt;
		ull key;
		int val;
	}e[maxn];
	inline int hsh(ull u){return u%maxn;}
	bool find(ull key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return 1;
		}
		return 0;
	}
	inline int &operator[](ull key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return e[i].val;
		}
		e[++tot]={head[u],key,0};head[u]=tot;
		return e[tot].val;
	}
	void clear(){
		tot=0;
		for(int i=0;i<maxn;i++)head[i]=0;
	}
}mp;