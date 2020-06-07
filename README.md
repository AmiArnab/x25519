### Plain C++ Implementation of Curve25519 (x25519) Scalar Multiplication

------

This a plain C++ implementation of Daniel J. Bernstein's [Curve25519][1] Scalar Multiplication. This C++ program uses GNU GMP library for underlying arithmetic. Use the following command compile.

```bash
g++ x25519.cpp -std=c++17 -lgmpxx -lgmp -o x25519
```

[1]: https://link.springer.com/chapter/10.1007/11745853_14 "Bernstein, D.J., 2006, April. Curve25519: new Diffie-Hellman speed records. In International Workshop on Public Key Cryptography (pp. 207-228). Springer, Berlin, Heidelberg."

