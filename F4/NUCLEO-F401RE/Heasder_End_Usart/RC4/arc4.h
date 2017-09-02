/**
 * \file arc4.h
 */
#ifndef XYSSL_ARC4_H
#define XYSSL_ARC4_H
#include "sys.h"
/**
 * \brief          ARC4 context structure
 */
typedef struct
{
    int x;                      /*!< permutation index */
    int y;                      /*!< permutation index */
    unsigned char m[256];       /*!< permutation table */
}
arc4_context;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          ARC4 key schedule
 *
 * \param ctx      ARC4 context to be initialized
 * \param key      the secret key
 * \param keylen   length of the key
 */
void arc4_setup( arc4_context *ctx, unsigned char *key, int keylen );

/**
 * \brief          ARC4 cipher function
 *
 * \param ctx      ARC4 context
 * \param buf      buffer to be processed
 * \param buflen   amount of data in buf
 */
void arc4_crypt( arc4_context *ctx, unsigned char *buf, int buflen );

/*
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 */
int arc4_self_test( int verbose );


void Arc4Decrypt(uint8_t *textBuf, uint32_t strLength,uint8_t *key);
void Arc4Crypt(uint8_t *textBuf,uint32_t hexLength,uint8_t *key);
#ifdef __cplusplus
}
#endif

#endif /* arc4.h */
