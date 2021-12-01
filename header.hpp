#ifndef LAB_5_H
#define LAB_5_H

unsigned long long int ModI(long long int a, unsigned long long int p, unsigned long long int x);
unsigned long long int Log(unsigned long long int a);
long long int gcd(long long int a, long long int b);
int Dif_Hell();
long long int Gcd(long long int a, long long int b);
unsigned long long int mul(unsigned long long int a, unsigned long long int b, unsigned long long int p);
int BabyStep_GiantStep(unsigned long long int a, unsigned long long int y, unsigned long long int p);
int Prime_rand();
bool isPrime(int p);


void client(unsigned long long int N, long long int d, std::string outFileName);
void clientPod(unsigned long long int N, long long int r, std::string inFileName, std::string outFileName);

#endif