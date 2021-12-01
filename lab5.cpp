#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "header.hpp" 
#include "sha/SHA256.h"

using namespace std;

void client(unsigned long long int N, long long int d, string outFileName){

    ofstream outf(outFileName.c_str());
    srand(time(NULL));

    unsigned long long int rnd = rand()%(int)(pow(2, 512));
    char v;
    cout << "yes or no?: ";
    string yon;
    cin >> yon;
    if(yon == "yes" || yon == "y"){
        v = '1';
    }
    else if(yon == "no" || yon == "n"){
        v = '0';
    }

    //cout << "v = " << v << " rnd = " << rnd << endl;

    //strcat(rnd, v);
    string n = to_string(rnd) + v;
    //cout << "n = " << n << endl;

    unsigned long long int r = rand();
    while(gcd(r, N) != 1){
        r = rand();
    }

    //cout << "r = " << r << endl;

    unsigned int *h = new unsigned int[32];
    long long int hh[32];
    sha256(n, h);
    string FIO;
    cout << "enter FIO, example: Petrov.P.P" << endl;
    cin >> FIO;
    outf << FIO << " " << n << " " << r << " ";

    for(int i = 0; i < 32; i++){
        hh[i] = ((h[i] % N) * (ModI(r, N, d))) % N;
        outf << hh[i] << " ";
    }

    //for(int i = 0; i < 32; i++){
    //    cout << "h' = " << hh[i] << endl;
    //}
    outf.close();
}

void clientPod(unsigned long long int N, long long int r, string inFileName, string outFileName){
    
    ifstream inf(inFileName.c_str());   
    ofstream outf(outFileName.c_str()); 
    long long int invR = Gcd(N, r); 
    while(invR < 0){
        invR = invR + N;
    }
    while(inf.good()){
        long long int sh = 0;
        inf >> sh;
        if(!inf.eof()){
            //cout << "s' = " << sh << endl;
            unsigned long long int s = ((invR % N) * (sh % N)) % N;
            outf << s << " ";
        }
    }
    inf.close();
    outf.close();
}