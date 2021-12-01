#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cstring>
#include <fstream>
#include "header.hpp" 
#include "sha/SHA256.h"

using namespace std;

int main(){
    
    srand(time(NULL));

    unsigned long long int q = Prime_rand();
    unsigned long long int p = Prime_rand();
    //unsigned long long int q = 33;
    //unsigned long long int p = 23;
    unsigned long long int N = p * q;
    unsigned long long int yN = (p - 1) * (q - 1);
    //unsigned long long int x = rand()%(p - 2) + 2;
    //unsigned long long int x = 7;
    unsigned long long int c = yN;
    long long int d = Gcd(yN, c);
    
    while((gcd((c * d), yN) != 1) || (gcd(c, yN) != 1) || (c > yN)){
        c = rand();
        d = Gcd(yN, c);
        if(d < 0){
            d = d + yN;
        }
    }


    //cout << "yn = " << yN << " c = " << c << endl;
    //cout << "D = " << d << " C = " << c << " Q = " << q << " P = " << p << " N = " << N << " y(n) = " << yN << endl;


    client(N, d, "test.txt");
    ifstream inf("test.txt");
    string FIO;
    inf >> FIO;
    
    inf.seekg(FIO.length(), ios_base::beg);
    string n;
    inf >> n;

    inf.seekg((FIO.length() + n.length()), ios_base::beg);
    int vote;
    inf >> vote;

    inf.seekg((FIO.length() + n.length() + 1), ios_base::beg);
    unsigned long long int r;
    inf >> r;

    inf.close();

    //cout << FIO << " " << n << " " << r << " " << z << endl;

    ifstream infFIO("FIOlist.txt");
    ofstream outFIO("FIOlist.txt", ios_base::app);
    cout << FIO << endl;
    while(infFIO.good()){
        string FIOlist;
        infFIO >> FIOlist;
        if(!outFIO.eof()){
            if(FIOlist == FIO){
                cout << "ERROR: you already voted" << endl;
                return 0;                
            }  
        }
    }
    outFIO << FIO << " ";
    infFIO.close();
    outFIO.close();

    ifstream infS("test.txt");
    ofstream outfS("alisa.txt");
    infS.seekg((FIO.length() + n.length() + string(n).length() + 2), ios_base::beg);
    while(infS.good()){
        long long int h = 0;
        infS >> h;
        if(!outfS.eof()){
            //cout << h << endl;
            long long int sh = ModI(h, N, c);
            outfS << sh << " ";
        }
    }

    infS.close();
    outfS.close();

    clientPod(N, r, "alisa.txt", "res.txt");

    unsigned int *h = new unsigned int[32];
    sha256(n, h);

    ifstream infres("res.txt");
    long long int check[32];
    int i = 0;
    while(infres.good()){
        long long int s;
        infres >> s;
        if(!infres.eof()){
            check[i] = ModI(s, N, d);
            i++;
        }
    }

    for(int i = 0; i < 32; i++){
        //cout << check[i] << endl;
        if(h[i] != check[i]){
            cout << "error" << endl;
            return 0;
        }
    }
    

    ofstream outBull("bulletin.txt", ios_base::app);
    if(vote == 0){
        outBull << "no\n";
    }
    else if(vote == 1){
        outBull << "yes\n";
    }
    return 0;

}