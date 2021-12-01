#include<stdlib.h>
#include<iostream>
#include<math.h>

using namespace std;


long long int gcd(long long int a, long long int b)
{
    return b ? gcd(b, a%b) : a;
}

unsigned long long int Log(unsigned long long int a)
{
    if(a != 0){
        return (log(a) / log(2)) + 1;
    }else{
        return 0;
    }
}

bool isPrime(int p)
{
   if (p<=1) return false;
     
   int b=(int)pow(p,0.5); 
    
   for(int i=2;i<=b;++i)
   {
      if ((p%i)==0) return false;        
   }     
     
   return true;  
     
}


int Prime_rand()
{
    int x;
  
    do{
        x=rand()%(int)(pow(10, 5));//%(int)(pow(2,1024));// + 1000;
    }while(isPrime(x)==false);
        
    return x;
}

unsigned long long int ModI(long long int a, unsigned long long int p, unsigned long long int x){

    unsigned long long int res = 1;
    unsigned long long int n;

    n = Log(x);
    //cout << "n = " << n << endl;
    int last_bit;
    unsigned long long int arr_last_bit[n];

    //cout << endl << "Binary form is:" << endl;
    for(int i = 0; i < n, x!=0; i++){
        
        last_bit=x&1;
        //cout<<last_bit;
        x=x>>1;    
        
        arr_last_bit[i] = last_bit; 
    }

    for(int i = 0; i < n; i++){
        if(arr_last_bit[i] == 1){
            res = ((res % p) * (a % p)) % p;
        }
        a = ((a % p) * (a % p)) % p;
    }

    return res;
/*
    unsigned long long res;

    for(res = 1; x; x >>= 1)
    {
        if (x & 1)
            res = ((res % p) * (a % p)) % p;
        a = ((a % p) * (a % p)) % p;
    }

    return res;
*/
}

unsigned long long int mul(unsigned long long int a, unsigned long long int b, unsigned long long int p)
{
    unsigned long long int res = ModI((a * b), p, 1);
    return res;
}

int Dif_Hell(){

    srand(time(NULL));

    unsigned long long int X[2];
    unsigned long long int Y[2];
    unsigned long long int Z[2];

    X[0] = rand()%999;
    X[1] = rand()%999;

    int q = Prime_rand();
    unsigned long long int p = 2 * q + 1;
    unsigned long long int g = 0;

    while((g < 1) || (g > (p - 1)) || ((ModI(g, p, q)) == 1)){
        g = Prime_rand();
    }
    //cout << "p = " << p << " q = " << q << " g = " << g << endl; 

    Y[0] = ModI(g, p, X[0]);
    Y[1] = ModI(g, p, X[1]);

    Z[0] = ModI(Y[0], p, X[1]);
    Z[1] = ModI(Y[1], p, X[0]);

    cout << "x[0] = " << X[0] << " x[1] = " << X[1] << endl;
    cout << "y[0] = " << Y[0] << " y[1] = " << Y[1] << endl;
    cout << "Zab = " <<  Z[0] << "  Zba = " << Z[1] << endl;

    if(Z[0] == Z[1]){
        cout << "Shared secret key received" << endl;
    }

    return 0;
}

long long int Gcd(long long int a, long long int b){
    //ax+by=gcd(a,b)
    
    long long int U[3]{a, 1, 0};
    long long int V[3]{b, 0, 1};
    long long int T[3];

    unsigned long long int q;
    int it = 0;
    while(V[0] != 0){
        //cout << it << " iteration" << endl;
        for(int i = 0; i < 3; i++){
            q = U[0] / V[0];
            T[i] = U[i] - q * V[i]; 
        }
        for(int i = 0; i < 3; i++){
            //cout << "U[" << i << "] = " << U[i] << "\t" << "V[" << i << "] = " << V[i] << "\t" << "T[" << i << "] = " << T[i] << endl; 
            U[i] = V[i];
            V[i] = T[i];
        }
    
        //cout << "q = " << q << endl;
        it++;
    }
    
    //cout << "RES: " << a << " * " << U[1] << " + " << b <<  " * " << U[2] << " = " << U[0] << endl; 
    //cout << "gcd(" << a << ", " << b << ") = " << U[0] << ", x = " << U[1] << ", y = " << U[2] << endl;
    return U[2];
}

int BabyStep_GiantStep(unsigned long long int a, unsigned long long int y, unsigned long long int p){
    
    //int p;
    //p = Prime_rand();
    //p = 23;
    /*do{
        a = rand()%100;
        y = rand()%100;
    }while((a > p) && (y > p));
    */
    cout << "p = " << p << endl;
    
    int i,j;
    int x, m, k;
    m = k = sqrt(p) + 1;
    cout << "m = " << m << " k = " << k << endl;
    
    unsigned long long int firstrow[m];
    unsigned long long int secondrow[m];

    for(j = 1; j < k; j++){
        secondrow[j] = ModI(a, p, (m * j));
        cout << "secondrow[" << j << "] = " << secondrow[j] << endl;
        for(i = 0; i < m; i++){
            firstrow[i] = (long long int)(pow(a, i) * y) % p;
            cout << "firstrow[" << i << "] = " << firstrow[i] << endl;
            
            if(firstrow[i] == secondrow[j]){
                x = j * m - i;
                if(ModI(a, p, x) == y){
                    cout << "RES: " << a << "^" << x << " mod " << p << " = " << y << endl;
                }
                else{
                    cout << "no solution" << endl;
                }
                return x;
            
            }
            
        }   

    }

    return 0;
}

