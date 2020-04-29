#include <bits/stdc++.h>
using namespace std;
#define ST          first
#define ND          second
#define PB          push_back
#define MKP         make_pair
#define LWBND		lower_bound
#define UPBND		upper_bound
#define FOR(i,a,b)  for(int i=(a);i<=(b);++i)
#define FORS(i,a,b) for(int i=(a);i<(b);++i)
#define ALL(x)      x.begin(),x.end()
#define SZ(x)       ((int)(x).size())
#define MOD         1000000007 //998244353
#define MAXN        200005
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<PII> VPII;
const int INF=0x3f3f3f3f;

typedef struct T{
    int key,priority;
    T *left,*right;
    T(){
        key=0;
        priority=0;
        left=nullptr;
        right=nullptr;
    }
    T(int key,int priority, T* left, T* right){
        this->key=key;
        this->priority=priority;
        this->left=left;
        this->right=right;
    }
}T;

T* nil=new T();

class Treap{
    T* rad;
public:
    Treap(){
        rad = nil;
    }
    Treap(int key, int priority){
        rad = new T(key,priority,nil, nil);
    }
    Treap(int key, int priority,T* left,T* right){
        rad = new T(key,priority,left,right);
    }

    T* getRoot(){
        return this->rad;
    }

    bool search(int key){
        T* it=rad;
        while(it->key != key && it != nil)
        {
            if(it->key > key)
                it = it->left;
            else    
                it = it->right;
        }
        if (it==nil)
            return false;
        else
            return true;
    }
    void rotateLeft(T* &node){
        T* lft = node->left;
        node -> left = lft -> right;
        lft -> right = node;
        node = lft;
    }
    void rotateRight(T* &node){
        T* rght = node->right;
        node -> right = rght -> left;
        rght -> left = node;
        node = rght;
    }
    void balance(T* &node){
        if(node->right->priority > node->priority)
            this->rotateRight(node);
        if(node->left->priority > node->priority)
            this->rotateLeft(node);
    }
    void insert(T* &node,int key, int priority)//done recursivly cause we can have T* &node, can we achieve this iteratively?
    {
        if(node == nil){
            node = new T(key,priority,nil,nil);
            return;
        }
        if (node->key > key)
            insert(node->left, key, priority);
        if (node->key <= key)
            insert(node->right, key, priority);

        balance(node);//this way is easier
    }
    void insert(int key, int priority){
        this->insert(rad,key,priority);
        //T* it=rad;
        //while(it != nil){
            //if(it->key > key)
                //it = it->left;
            //else 
                //it = it->right;
        //}
        // tried multiple ways of changing it, but couldn't get it:(
        //it = &(*it); //??? Does this work??
        //T** newNode = &it; //??? Does this work??
        //it = new T(key, priority, nil, nil);

        //we need recursiveness to balance?? No pointer towards father, I guess I could've done a balance(T* &node, int key, int priority) that would balance recursivly
        //but no reason for extra work when we can do it all with recursiveness
    }
    void erase(T* &node,int key,int& ok){
        if( node == nil)
            return;

        if(node->key > key)
            erase(node->left, key,ok);
        else if(node->key < key)
            erase(node->right, key,ok);
        else{
            if(node->left == nil && node->right==nil)
            {
                delete node;
                node = nil;
                ok=1;
            }
            else{
                if(node->left->priority > node->right->priority)
                {
                    this->rotateLeft(node);
                    erase(node->right ,key,ok);
                }
                else
                {
                    this->rotateRight(node);
                    erase(node->left,key,ok);
                }
            }
        }
    }
    int erase(int key){
        int ok=0;
        erase(this->rad,key,ok);
        return ok;
    }
    //after a split the main treap will be empty;
    friend void split(Treap& trp, Treap& trpleft, Treap& trpright,int key){
        trp.insert(key,INT_MAX);
        trpleft.rad=trp.rad->left;
        trpright.rad=trp.rad->right;
        delete trp.rad;
        trp.rad=nil;
    }
    //after join the 2 left& rights are nill(empty)
    friend void join(Treap &trp, Treap &trpleft, Treap &trpright,int key){
        trp.rad = new T(key, 0, trpleft.rad, trpright.rad);
        trp.erase(key);
        trpleft.rad=nil;
        trpright.rad=nil;
    }

    int getHeight(T* node){
        if (node == nil)
            return 0;
        return 1+max(getHeight(node->left),getHeight(node->right));
    }
    void printGivenLevel(ostream&out, T* node,int level){
        if(node==nil || level<1)
            return;
        if(level==1)
            out<<left<<setw(10)<<node->priority<<' '<<node->key<<'\n';
        else{
            printGivenLevel(out,node->right, level-1);
            printGivenLevel(out,node-> left, level-1);
        }

    }
    void getKthKey(T* node,int& cnt,int& ans){
        if(ans==INT_MIN){
            if (node == nil) return;
            getKthKey(node->left,cnt,ans);
            cnt--;
            if(cnt==0) 
                ans=node->key;
            getKthKey(node->right,cnt,ans);
        }

        
    }
    int getKthKey(int key){
        int ans=INT_MIN;
        getKthKey(this->rad,key,ans);
        if(ans==INT_MIN)
        {
            cout<<"Nu exista cheie";
            return -1;
        }
        else
            return ans;
    }
    int getMax(){
        T* it=this->rad;
        while (it->right!=nil)
            it=it->right;
        return it->key;
    }
    int getMin(){
        T* it=this->rad;
        while (it->left!=nil)
            it=it->left;
        return it->key;
    }
    int successor(int key){
        int sol=-1;
        if(key>this->getMax()){
            return -1;
        }
        T* it = this->rad;
        while(it->key != key && it!=nil){
            if(it-> key > key){
                sol = it->key;
                it = it->left;
            }else
                it = it->right;
        }
        if(it->key == key)
            return key;
        if(it!=nil && it->right != nil)
        {
            it=it->right;
            while(it->left!=nil)
                it = it->left;
            sol=it->key;
        }
        return sol;
    }
    int predecessor(int key){
        int sol=-1;
        if(key < this->getMin()){
            return -1;
        }
        T* it = this->rad;
        while(it->key != key && it!=nil){
            if(it->key < key){
                sol=it->key;
                it = it->right;
            }
            else
                it = it->left;
        }
        if(it->key == key)
            return key;
        if(it!= nil && it->left != nil)
        {
            it=it->left;
            while(it->right != nil)
                it=it->right;
            sol=it->key;
        }
        return sol;

    }
    void inordine(ostream& out,T* node){
        if (node == nil) return;
        inordine(out,node->left);
        out<<left<<setw(10)<<node->key<<' '<<node->priority<<'\n';
        inordine(out,node->right);
    }
    void inordineLimited(T* node,int X,int Y){
        if (node == nil) return;
        inordineLimited(node->left,X,Y);
        if(node->key <=Y && node->key>=X)
            cout<<node->key<<' ';
        inordineLimited(node->right,X,Y);
    }
    Treap& operator=(const Treap& cpy){
        if(this!= &cpy){
            delete this->rad;
            this->rad = cpy.rad;
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, Treap& mytrp){
        out<<"Inordine, aka BST order print:\n";
        out<<setw(10)<<"key"<<" priority\n";
        mytrp.inordine(out,mytrp.rad);
        out<<"Level print, aka Heap ordered\n";
        int hght=mytrp.getHeight(mytrp.rad);
        out<<setw(10)<<"priority"<<" key\n";
        FOR(i,1,hght)
            mytrp.printGivenLevel(out,mytrp.rad,i);
        return out;
    }
    friend istream& operator>>(istream& in, Treap& mytrp){
        int key,priority;
        cout<<"Enter key and priority: ";
        in>>key>>priority;
        mytrp.insert(key,priority);
        return in;
    }
};


int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("abce.in","r",stdin);
    freopen("abce.out","w",stdout);
    int tip,x,y,cnt,ok,n;
    Treap myTreap;
    cin>>n;
    //80 de punce pe infoarena
    //Daca as fi avut acces la teste, as fi putut da debug
    //Dar din pacate sunt private :(
    FOR(i,1,n)
    {
        cin>>tip;
        cin>>x;
        switch(tip){
            case 1:
                myTreap.insert(x,rand()+1);
                break;
            case 2:
                cnt=0;
                ok=myTreap.erase(x);
                /*while(1){
                    ok=myTreap.erase(x);
                    cnt++;
                    if(!ok)
                        break;
                }*/
                //cout<<cnt<<'\n';
                break;
            case 3:
                if(myTreap.search(x))
                    cout<<1;
                else
                    cout<<0;
                cout<<'\n';
                break;
            case 4:
                cout<<myTreap.predecessor(x)<<'\n';
                break;
            case 5:
                cout<<myTreap.successor(x)<<'\n';
                break;
            case 6:
                cin>>y;
                myTreap.inordineLimited(myTreap.getRoot(),x,y);
                cout<<'\n';
                break;
            default:
                return 0;
        }
    }
}
