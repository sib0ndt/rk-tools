#ifndef _MD5_H
#define _MD5_H

#include <stddef.h>
#include <string.h>

#ifdef USE_OPENSSL

#include <openssl/evp.h>

typedef struct {
	EVP_MD_CTX *ctx;
} MD5_CTX;

static int MD5_Init(MD5_CTX *ctx)
{
	ctx->ctx = EVP_MD_CTX_new();
	if (!ctx->ctx)
		return 0;

	return EVP_DigestInit_ex(ctx->ctx, EVP_md5(), NULL);
}

static int MD5_Update(MD5_CTX *ctx, const void *input, size_t inputLen)
{
	if (!ctx->ctx)
		return 0;

	return EVP_DigestUpdate(ctx->ctx, input, inputLen);
}

static int MD5_Final(unsigned char digest[16], MD5_CTX *ctx)
{
	unsigned int digest_len = 0;
	int ok = 0;

	if (ctx->ctx)
	{
		ok = EVP_DigestFinal_ex(ctx->ctx, digest, &digest_len);
		EVP_MD_CTX_free(ctx->ctx);
		ctx->ctx = NULL;
	}

	return ok && digest_len == 16;
}

#elif defined USE_GCRYPT

#include <gcrypt.h>

typedef gcry_md_hd_t MD5_CTX;

static int MD5_Init(MD5_CTX * ctx)
{
	return gcry_md_open(ctx, GCRY_MD_MD5, 0) == 0;
}

static int MD5_Update(MD5_CTX * ctx, const void * input, size_t inputLen)
{
	gcry_md_write(*ctx, input, inputLen);
	return 1;
}

static int MD5_Final(unsigned char digest[16], MD5_CTX * ctx)
{
	memcpy(digest, gcry_md_read(*ctx, 0), 16);
	gcry_md_close(*ctx);
	return 1;
}
#else
#error "no MD5 implementation"
#endif  //USE_GCRYPT

#endif
