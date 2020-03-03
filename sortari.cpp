#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define st first
#define nd second
#define pb push_back
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define FORS(i,a,b) for(int i=(a);i<(b);++i)
#define PII pair<int,int>
#define VI vector<int>
#define VPII vector<PII>
#define all(x) x.begin(),b.end()
#define SZ(x) ((int)(x).size())
#define ll long long
#define MOD 1000000 //998244353
const int inf=0x3f3f3f3f;
#define maxn 500005
 
///buckets of bytes
#define maxb 8
#define bucket 0xFF //255,a byte aka bits 0-7(8 bits)
#define total_bytes (sizeof(v[1]))
#define get_byte(x) ((x>>(byte*8))&bucket)
 
const int million=1e6;
int n,gvals,gbase;
 
//The program and tester
void printer(int* v);
bool verifier(int* v);
void tester(int n,int base,int vals,string x);
int transformer(const string& sName);
void gettingTests(const string& sName,int* vec, int n, int base,int vals);

/// BUBBLE SORT
/// 40pct on infoarena(educationala sortare prin comparare)
void bubbleSort(int* v);

/// COUNT SORT 
/// 20pct on infoarena
void countSort(int* v);

/// RADIX SORT
/// 100pcts on infoarena(715ms)
void countByteSort(int byte,int* v);
void radixSort(int* v);


/// QUICK SORT
/// 40 pcts?
void quickSort(int* v,int st, int dr);

/// MERGE SORT
/// 100 on infoaren(452ms)
void mergexd(int* v,int l, int m, int r);
void mergeSort(int* v,int l,int r);

int main()
{
    //Setting the output to fixed and 6 decimals
    cout<<fixed<<setprecision(6);

    //First test
    n=100;
    gvals=500;
    gbase=0;
    tester(n,gbase,gvals,"First");

    n=1000;
    gvals=2000000;
    gbase=0;
    tester(n,gbase,gvals,"Second");

    n=500000;
    gvals=500;
    gbase=50;
    tester(n,gbase,gvals,"Third");

    n=1000000;
    gvals=500000;
    gbase=200000;
    tester(n,gbase,gvals,"Fourth");

    n=10;
    gvals=20;
    gbase=0;
    tester(n,gbase,gvals,"Fifth");

    n=333333;
    gvals=333333;
    gbase=222222;
    tester(n,gbase,gvals,"Sixth");

    n=2000000;
    gvals=1000000000;
    gbase=0;
    tester(n,gbase,gvals,"Seventh");

/*    n=4000000;
    gvals=5000000;
    gbase=0;
    tester(n,gbase,gvals,"Seventh");
    */

}

void tester(int n,int base,int vals,string x){
    //creating the vector and generating values
    auto f = [base,vals]() -> int{
        return base+rand()%vals;
    };
    int* vec =  new int[n]{0};
    generate(vec,vec+n,f);

    //printing the initial
    cout<<x<<" test has "<<n<<" elements\n";
    cout<<"Ranging from "<<base<<"-"<<vals <<"\n";
    //BUBBLE SORT limited at 100k (500k takes too much time)
    if(n<100000)
        gettingTests("bubble",vec,n,base,vals);

    //COUNT SORT limited at 1M memory
    if(vals<1000000)
        gettingTests("count",vec,n,base,vals);

    //RADIX SORT
    gettingTests("radix",vec,n,base,vals);

    //QUICK SORT
    gettingTests("quick",vec,n,base,vals);

    //MERGE SORT
    gettingTests("merge",vec,n,base,vals);

    //predefined one
    gettingTests("predef",vec,n,base,vals);

    //deleting the vec
    delete[] vec;
    cout<<'\n';
}

void gettingTests(const string& sName,int* vec, int n, int base,int vals){
    auto start=high_resolution_clock::now();
    auto stop=high_resolution_clock::now();
    int *vec2=new int[n];
    memcpy(vec2,vec,n*sizeof(int));
    float timer;
    int typeS=transformer(sName);

    if(typeS==transformer("bubble")){
        //BUBBLE SORT
        //start & stop are for the execution time
        start=high_resolution_clock::now();
        bubbleSort(vec2);
        stop=high_resolution_clock::now();
        timer=float(duration_cast<microseconds>(stop-start).count())/float(million);

        //printing the time
        cout<<"Bubble Sort: "<<timer<<"s\n";
    }else if(typeS==transformer("count"))
    {
        //COUNT SORT
        //start & stop are for the execution time
        start=high_resolution_clock::now();
        countSort(vec2);
        stop=high_resolution_clock::now();
        timer=float(duration_cast<microseconds>(stop-start).count())/float(million);

        //printing the time
        cout<<"Count Sort : "<<timer<<"s\n";
    }else if(typeS==transformer("radix"))
    {
        //RADIX SORT
        //start & stop are for the execution time
        start=high_resolution_clock::now();
        radixSort(vec2);
        stop=high_resolution_clock::now();
        timer=float(duration_cast<microseconds>(stop-start).count())/float(million);

        //printing the time
        cout<<"Radix Sort : "<<timer<<"s\n";
    }else if(typeS==transformer("quick"))
    {
        //QUICK SORT
        //start & stop are for the execution time
        start=high_resolution_clock::now();
        quickSort(vec2,0,n);
        stop=high_resolution_clock::now();
        timer=float(duration_cast<microseconds>(stop-start).count())/float(million);

        //printing the time
        cout<<"Quick Sort : "<<timer<<"s\n";
    }else if(typeS==transformer("merge"))
    {
        //MERGE SORT
        start=high_resolution_clock::now();
        mergeSort(vec2,0,n);
        stop=high_resolution_clock::now();
        timer=float(duration_cast<microseconds>(stop-start).count())/float(million);

        //printing the time
        cout<<"Merge Sort : "<<timer<<"s\n";
    }else if(typeS==transformer("predef"))
    {
        //MERGE SORT
        start=high_resolution_clock::now();
        sort(vec2,vec2+n);
        stop=high_resolution_clock::now();
        timer=float(duration_cast<microseconds>(stop-start).count())/float(million);

        //printing the time
        cout<<"Predef Sort: "<<timer<<"s\n";
    }
    delete[] vec2;

}
int transformer(const string& sName){
    int sum=0,j=1;
    for (auto it : sName){
        sum+=(it-'a')*j;
        j*=5;
    }
    return sum;
}


void printer(int* v){
    FORS(i,0,n)
        cout<<v[i]<<'\n';
}

bool verifier(int *v){
    int *a=new int[n];
    memcpy(a,v,sizeof(int)*n);
    sort(a,a+n);
    FORS(i,0,n)
        if(a[i]!=v[i]){
            delete[] a;
            return 0;
        }
    delete[] a;
    return 1;
}

/// BUBBLE SORT
/// 40pct on infoarena
void bubbleSort(int* v)
{
    FORS(i,0,n-1)
        FORS(j,0,n-i-1)
        if(v[j]>v[j+1])
            swap(v[j],v[j+1]);
}

/// COUNT SORT 
/// 20pct on infoarena
void countSort(int* v)
{
    int maxi=0;
    FORS(i,0,n)
        if(v[i]>maxi)
            maxi=v[i];
    int freq[maxi+2];
    memset(freq,0,sizeof(freq));
    FORS(i,0,n)
        freq[v[i]]++;
    int j=0;
    FOR(i,0,maxi)
        while(freq[i]){
            v[j++]=i;
            --freq[i];
        }
}


/// RADIX SORT
/// 100pcts on infoarena(715ms)
void countByteSort(int byte,int *v)
{
    int count[1<<maxb];
    int index[1<<maxb];
    int aux[n+5];
    //int *aux=new int[n];
    index[0]=0;
    memset(count,0,sizeof(count));

    FORS(i,0,n)
        count[get_byte(v[i])]++;
    FORS(i,1,(1<<maxb))
        index[i]=index[i-1]+count[i-1];
    FORS(i,0,n)
        aux[index[get_byte(v[i])]++]=v[i];
    FORS(i,0,n)
        v[i]=aux[i];
    //return aux;
}

void radixSort(int* v)
{
    for(unsigned int bit=0;bit<total_bytes;++bit)
        countByteSort(bit,v);
    //v=countSort(bit,v);
}

/// QUICK SORT
/// 40 pcts?
void quickSort(int* v,int st, int dr){
    if(st<dr){
        int i=st, aux;
        int rad=v[dr];
        for(int j=st;j<dr;j++)
            if(v[j]<rad){
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
                i+=1;
            }
        v[dr]=v[i];
        v[i]=rad;
        quickSort(v,st,i-1);
        quickSort(v,i+1,dr);
    }
}
/// MERGE SORT
/// 100 on infoaren(452ms)
void mergexd(int* v,int l, int m, int r){
    int n1,n2,i,j,k;
    n1=m-l+1; // the length of the left side till middle
    n2=r-m; //length of right side
    int la[n1],ra[n2]; //create the temporary arrays
    for(int i=0;i<n1;i++)
        la[i]=v[l+i]; //initialize left array
    for(int i=0;i<n2;i++)
        ra[i]=v[m+i+1]; //initialize right array
    i=0;j=0; //index of temporaries arrays
    k=l;//index of official array
    while(i<n1&&j<n2){
        if(la[i]<ra[j]){
            v[k]=la[i];
            i++;
        }else{
            v[k]=ra[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        v[k]=la[i];
        i++;k++;
    }
    while(j<n2){
        v[k]=ra[j];
        j++;k++;
    }
}
void mergeSort(int* v,int l,int r){
    if(l<r){
        int m=(l+r)/2;
        mergeSort(v,l,m);
        mergeSort(v,m+1,r);
        mergexd(v,l,m,r);
    }
}
