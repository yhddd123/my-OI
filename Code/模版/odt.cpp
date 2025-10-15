struct node{
	int l,r,c;
	bool operator<(const node&tmp)const{return r<tmp.l;}
};
struct odt{
	set<node> s;
	void split(int p){
		auto it=s.lower_bound({p,p,0});
		if((*it).r>p){
			auto[l,r,c]=*it;
			s.erase(it);
			s.insert({l,p,c}),s.insert({p+1,r,c});
		}
	}
	void ins(int l,int r,int c){
		split(l-1),split(r);
		auto it=s.lower_bound({l,l,0});
		while((*it).r<=r)it=s.erase(it);
		while((*it).c==c)r=(*it).r,it=s.erase(it);
		it--;while((*it).c==c)l=(*it).l,it=s.erase(it),it--;
		s.insert({l,r,c});
	}
	node que(int p){
		auto it=s.lower_bound({p,p,0});
		return (*it);
	}
};