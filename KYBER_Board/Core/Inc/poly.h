#ifndef POLY_H
#define POLY_H

#include <stdint.h>
#include "params.h"

/*
 * Elements of R_q = Z_q[X]/(X^n + 1). Represents polynomial
 * coeffs[0] + X*coeffs[1] + X^2*coeffs[2] + ... + X^{n-1}*coeffs[n-1]
 */
typedef struct{
  int16_t coeffs[KYBER_N];
} poly;

#define poly_decompress KYBER_NAMESPACE(poly_decompress)
void poly_decompress(poly *r, const uint8_t a[KYBER_POLYCOMPRESSEDBYTES]);

#define poly_frombytes KYBER_NAMESPACE(poly_frombytes)
void poly_frombytes(poly *r, const uint8_t a[KYBER_POLYBYTES]);

#define poly_tomsg KYBER_NAMESPACE(poly_tomsg)
void poly_tomsg(uint8_t msg[KYBER_INDCPA_MSGBYTES], const poly *r);

#define poly_ntt KYBER_NAMESPACE(poly_ntt)
void poly_ntt(poly *r);

#define poly_invntt_tomont KYBER_NAMESPACE(poly_invntt_tomont)
void poly_invntt_tomont(poly *r);

#define poly_basemul_montgomery KYBER_NAMESPACE(poly_basemul_montgomery)
void poly_basemul_montgomery(poly *r, const poly *a, const poly *b);

#define poly_reduce KYBER_NAMESPACE(poly_reduce)
void poly_reduce(poly *r);

#define poly_add KYBER_NAMESPACE(poly_add)
void poly_add(poly *r, const poly *a, const poly *b);

#define poly_sub KYBER_NAMESPACE(poly_sub)
void poly_sub(poly *r, const poly *a, const poly *b);

#endif
