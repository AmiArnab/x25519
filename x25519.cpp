#include <iostream>
#include <gmpxx.h>

using namespace std;

mpz_class Prime = mpz_class{"57896044618658097711785492504343953926634992332820282019728792003956564819949",10};//2^255-19
mpz_class InvExp = mpz_class{"57896044618658097711785492504343953926634992332820282019728792003956564819947",10};//2^255-19-2

int DoubleAndAdd(mpz_class &P4x,mpz_class &P4z,mpz_class &P5x,mpz_class &P5z, mpz_class P2x,mpz_class P2z,mpz_class P3x,mpz_class P3z,mpz_class X1){

    mpz_class a24(121666);

    mpz_class T0(0);
    mpz_class T1(0);
    mpz_class T2(0);
    mpz_class T3(0);
    mpz_class T4(0);
    mpz_class T5(0);

    T0 = P2x + P2z;
    mpz_mod(T0.get_mpz_t(),T0.get_mpz_t(),Prime.get_mpz_t());

    T1 = P2x - P2z;
    mpz_mod(T1.get_mpz_t(),T1.get_mpz_t(),Prime.get_mpz_t());

    T3 = T1 * T1;
    mpz_mod(T3.get_mpz_t(),T3.get_mpz_t(),Prime.get_mpz_t());

    T4 = T0 * T0;
    mpz_mod(T4.get_mpz_t(),T4.get_mpz_t(),Prime.get_mpz_t());

    T2  = P3x + P3z;
    mpz_mod(T2.get_mpz_t(),T2.get_mpz_t(),Prime.get_mpz_t());

    T1 = T2 * T1;
    mpz_mod(T1.get_mpz_t(),T1.get_mpz_t(),Prime.get_mpz_t());

    P4x = T4 * T3;
    mpz_mod(P4x.get_mpz_t(),P4x.get_mpz_t(),Prime.get_mpz_t());

    T2 = P3x - P3z;
    mpz_mod(T2.get_mpz_t(),T2.get_mpz_t(),Prime.get_mpz_t());

    T0 = T2 * T0;
    mpz_mod(T0.get_mpz_t(),T0.get_mpz_t(),Prime.get_mpz_t());

    T2 = T4 - T3;
    mpz_mod(T2.get_mpz_t(),T2.get_mpz_t(),Prime.get_mpz_t());

    T4 = a24 * T2;
    mpz_mod(T4.get_mpz_t(),T4.get_mpz_t(),Prime.get_mpz_t());

    T5 = T0 + T1;
    mpz_mod(T5.get_mpz_t(),T5.get_mpz_t(),Prime.get_mpz_t());

    T0 = T0 - T1;
    mpz_mod(T0.get_mpz_t(),T0.get_mpz_t(),Prime.get_mpz_t());

    P5x = T5 * T5;
    mpz_mod(P5x.get_mpz_t(),P5x.get_mpz_t(),Prime.get_mpz_t());

    T0 = T0 * T0;
    mpz_mod(T0.get_mpz_t(),T0.get_mpz_t(),Prime.get_mpz_t());

    T4 = T3 + T4;
    mpz_mod(T4.get_mpz_t(),T4.get_mpz_t(),Prime.get_mpz_t());

    P4z = T2 * T4;
    mpz_mod(P4z.get_mpz_t(),P4z.get_mpz_t(),Prime.get_mpz_t());

    P5z = X1 * T0;
    mpz_mod(P5z.get_mpz_t(),P5z.get_mpz_t(),Prime.get_mpz_t());

    return 0;
}

int ScalarMult(mpz_class &prod, mpz_class sca, mpz_class base){

    size_t scalen = mpz_sizeinbase(sca.get_mpz_t(),2)-1;
    mpz_class pc = base;
    mpz_class p1x = base;
    mpz_class p1z("1",10);
    mpz_class p2x("1",10);
    mpz_class p2z("0",10);

    mpz_class p3x;
    mpz_class p3z;
    mpz_class p4x;
    mpz_class p4z;

    while(scalen > 0){
        if(mpz_tstbit(sca.get_mpz_t(),scalen)) DoubleAndAdd(p1x,p1z,p2x,p2z,p1x,p1z,p2x,p2z,pc);
        else DoubleAndAdd(p2x,p2z,p1x,p1z,p2x,p2z,p1x,p1z,pc);
        scalen--;
    }

    if(mpz_tstbit(sca.get_mpz_t(),0)) DoubleAndAdd(p1x,p1z,p2x,p2z,p1x,p1z,p2x,p2z,pc);
    else DoubleAndAdd(p2x,p2z,p1x,p1z,p2x,p2z,p1x,p1z,pc);

    mpz_powm(p2z.get_mpz_t(),p2z.get_mpz_t(),InvExp.get_mpz_t(),Prime.get_mpz_t());
    p2x = p2x * p2z;
    mpz_mod(prod.get_mpz_t(),p2x.get_mpz_t(),Prime.get_mpz_t());
    return 0;
}

int main()
{
    mpz_class prod;
    mpz_class base("9",10);
    mpz_class sca("7237005577332262213973186563042994240857116359379907606001950938285454250990",10);

    ScalarMult(prod,sca,base);

    //Should get 9 as output
    cout << prod << endl;

    return 0;
}
