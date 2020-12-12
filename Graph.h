#include<iostream>
#include<vector>
#include<deque>
using namespace std;

template <typename Tv,typename Te>class Graph{
private:
	void reset(){
		for(int i=0;i<n;i++){
			status(i)=UNDISCOVERED;dTime(i)=fTime(i)=-1;
			parent(i)=-1;priority(i)=INT_MAX;
			for(int j=0;j<n;j++){
				if(exist(i,j))status(i,j)=UNDETERMIND;
			}
		}
	}
	void BFS(int,int &);
	void DFS(int,int &);
	void BCC(int.int &,Stack<int>&);
	bool TSort(int,int &,Stack<Tv>*);
	template<typename PU>void PFS(int,PU);
public:
//顶点
	int n;
	virtual int insert(Tv const&)=0;
	virtual Tv remove(int)=0;
	virtual Tv& vertex(int)=0;
	virtual int inDegree(int)=0;
	virtual int outDegree(int)=0;
	virtual int firstNbr(int)=0;
	virtual int nextNbr(int)=0;
	virtual VStatus& status(int)=0;
	virtual int& dTime(int)=0;
	virtual int& fTime(int)=0;
	virtual int& parent(int)=0;
	virtual int& priority(int)=0;
//边
	int e;
	virtual bool exist(int,int)=0;
	virtual void insert(Te const&,int,int,int)=0;
	virtual Te remove(int,int)=0;
	virtual EStatus& status(int,int)=0;
	virtual Te& edge(int,int)=0;
	virtual int& weight(int,int)=0;
//算法
	void bfs(int);				
	void dfs(int);
	void bcc(int);
	Stack<Tv>* tSort(int);
	void prim(int);
	void dijkstra(int);
	template<typename PU>void pfs(int,PU);
}

typedef enum {UNDISCOVERED,DISCOVERED,VISITED}VStatues;

template <typename Tv>struct Vertex{
	Tv data;
	int inDegree;
	int outDegree;
	VStatues status;
	int dTime,fTime;
	int parent;
	int priority;
	Vertex(Tv const & d):
			data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),
			dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}
};

typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD}EStatus;

template <typename Te>struct Edge{
	Te data;
	int weight;
	EStatus status;
	Edge(Te const & d,int w):
			data(d),weight(w),status(UNDETERMINED){}
};

template<typename Tv,typename Te>class GraphMatrix:public Graph<Tv,Te>{
	private:
		vector<Vertex<Tv> >V;
		vector<vector<Edge<Te>*>>E;
	public:
		GraphMatrix(){n=e=0;}
		~GraphMatrix(){
			for(int j=0;j<n;j++)
				for(int k=0;k<0;k++)
						delete E[j][k];
		}
	//顶点的基本操作
	virtual Tv& vertex(int i){return V[i].data};
	virtual int inDegree(int){return V[i].inDegree;}
	virtual int outDegree(int i){return V[i].outDegree;}
	virtual VStatus& status(int i){return V[i].status};
	virtual int &dTime(int i){return V[i].dTime;}
	virtual int &fTime(int i){return V[i].fTime;}
	virtual int &parent(int i){return V[i].parent;}
	virtual int &priority(int i){return V[i].priority;}
	virtual int firstNbr(int i){return nextNbr(i,n);}
	virtual int nextNbr(int i,int j)
	{while((-1<j)&&(!exists(i,--j)));return j;}
	virtual int insert(Tv const & vertex){
		for(int j=0;j<n;j++)E[j].insert(NULL);n++;
		E.insert(vector<Edge<Te>*>(n,n,NULL));
		return V.insert(Vertex<Tv>(vertex));
	}
	virtual Tv remove(int i){
		for(int j=0;j<n;j++)
			if(exists(i,j)){delete E[i][j];V[j].inDegree--;}
		E.remove(i);n--;
		for(int j=0;j<n;j++)
			if(exists(j,i)){delete E[j][i];V[j].outDegree--;}
		Tv vBak=vertex(i);
		V.remove(i);
		return vBak;
	}
	//边的基本操作
	virtual bool exists(int i,int j){
		return (0<=i)&&(i<n)&&(0<=j)&&(j<n)
				&&E[i][j]!=NULL;
	}
	virtual Te& edge(int i,int j){return E[i][j]->data;}
	virtual EStatues& status(int i,int j){return E[i][j]->status;}
	virtual int& weight(int i,int j){return E[i][j]->weight;}
	virtual void insert(Te const& edge,int w,int i,int j){
		if(exists(i,j))return;
		E[i][j]=new Edge<Te>(edge,w);
		e++;
		V[i].outDegree++;
		V[j].inDegree++;
	}
	virtual void remove(int i,int j){
		Te eBak=edge(i,j);
		delete E[i][j];E[i][j]=NULL;
		e--;
		V[i].outDegree--;
		V[j].inDegree--;
		return eBak;
	}
}

template<typename Tv,typename Te>
void Graph<Tv,Te>::bfs(int s){
	reset();int clock=0;int v=s;
	do{
		if(UNDISCOVERD==status(v))
				BFS(v,clock);
	}while((v=(++v%n))!=s)
}

template<typename Tv,typename Te>
void Graph<Tv,Te>::BFS(int v,int &clock){
	deque<int>Q;
	status(v)=DISCOVERED;Q.push_back(v);
	while(!Q.empty()){
		int v=Q.front();Q.pop_front();dTime(v)=++clock;
		for(int u=firstNbr(v);-1<u;u=nextNbr(v,u)){
			if(UNDISCOVERED==status(u)){
				status(u)=DISCOVERED;Q.push_back(v);
				status(u,v)=TREE;parent(u)=v;
			}else{
				status(v,u)=CROSS;
			}
		}
		status(v)=VISITED;
	}
}

template<typename Tv,typename Te>
void Graph<Tv,Te>::dfs(int s){
	reset();int clock=0;int v=s;
	do{
		if(UNDISCOVERD==status(v))
			DFS(v,clock);
	}while(s!=((v=++v%n)));

}

template<typename Tv,typename Te>
void Graph<Tv,Te>::DFS(int v,int& clock){
	dTime(v)=++clock;status(v)=DISCOVERED;
	for(int u=firstNbr(v);-1<u;u=nextNbr(v,u)){
		switch(status(u)){
			case UNDISCOVERED:
				status(v,u)=TREE;parent(u)=v;DFS(u,clock);break;
			case DISCOVERED:
				status(v,u)=BACKWARD;break;
			default:
				status(v,u)=((dTime(v)<dTime(u))FORWARD:CROSS;break;
		
		}
	}

}

