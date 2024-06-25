/*
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.0 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_0.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Evan Klinger <eklinger@phash.org>                           |
   +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#include "php_pHash.h"

#if HAVE_PHASH

struct ph_mh_image_hash
{
	uint8_t *hash;
	int len;
};
struct ph_audio_hash
{
	uint32_t *hash;
	int len;
};
struct ph_video_hash
{
	ulong64 *hash;
	int len;
};
struct ph_text_hash
{
	TxtHashPoint *p;
	int count;
};
typedef Digest ph_digest_hash;
/* {{{ Resource destructors */
int le_ph_video_hash;
#if PHP_VERSION_ID >= 70000
extern "C" void ph_video_hash_dtor(zend_resource *rsrc TSRMLS_DC)
#else
extern "C" void ph_video_hash_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
#endif
{
	ph_video_hash * resource = (ph_video_hash *)(rsrc->ptr);

	if(resource)
	{
		free(resource->hash);
		free(resource);
	}
}

int le_ph_image_hash;
#if PHP_VERSION_ID >= 70000
extern "C" void ph_image_hash_dtor(zend_resource *rsrc TSRMLS_DC)
#else
extern "C" void ph_image_hash_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
#endif
{
	ulong64 * resource = (ulong64 *)(rsrc->ptr);

	if(resource)
		free(resource);
}

int le_ph_digest_hash;
#if PHP_VERSION_ID >= 70000
extern "C" void ph_digest_hash_dtor(zend_resource *rsrc TSRMLS_DC)
#else
extern "C" void ph_digest_hash_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
#endif
{
	ph_digest_hash * resource = (ph_digest_hash *)(rsrc->ptr);

	if(resource){
		free(resource);
	}
}

int le_ph_audio_hash;
#if PHP_VERSION_ID >= 70000
extern "C" void ph_audio_hash_dtor(zend_resource *rsrc TSRMLS_DC)
#else
extern "C" void ph_audio_hash_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
#endif
{
	ph_audio_hash * resource = (ph_audio_hash *)(rsrc->ptr);

	if(resource)
	{
		free(resource->hash);
		free(resource);
	}
}

int le_ph_mh_image_hash;
#if PHP_VERSION_ID >= 70000
extern "C" void ph_mh_image_hash_dtor(zend_resource *rsrc TSRMLS_DC)
#else
extern "C" void ph_mh_image_hash_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
#endif
{
	ph_mh_image_hash * resource = (ph_mh_image_hash *)(rsrc->ptr);

	if(resource)
	{
		free(resource->hash);
		free(resource);
	}
}

int le_ph_txt_hash;
#if PHP_VERSION_ID >= 70000
extern "C" void ph_txt_hash_dtor(zend_resource *rsrc TSRMLS_DC)
#else
extern "C" void ph_txt_hash_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
#endif
{
	ph_text_hash * resource = (ph_text_hash *)(rsrc->ptr);

	if(resource)
	{
		free(resource->p);
		free(resource);
	}
}

/* }}} */

/* {{{ pHash_functions[] */
zend_function_entry pHash_functions[] = {
#if HAVE_VIDEO_HASH
	PHP_FE(ph_dct_videohash    , ph_dct_videohash_arg_info)
#endif /* HAVE_VIDEO_HASH */
#if HAVE_IMAGE_HASH
	PHP_FE(ph_dct_imagehash    , ph_dct_imagehash_arg_info)
#endif /* HAVE_IMAGE_HASH */
#if HAVE_IMAGE_HASH
	PHP_FE(ph_image_digest     , ph_image_digest_arg_info)
#endif /* HAVE_IMAGE_HASH */
#if HAVE_IMAGE_HASH
	PHP_FE(ph_mh_imagehash     , ph_mh_imagehash_arg_info)
#endif /* HAVE_IMAGE_HASH */
	PHP_FE(ph_texthash         , ph_texthash_arg_info)
#if HAVE_AUDIO_HASH
	PHP_FE(ph_audiohash        , ph_audiohash_arg_info)
#endif /* HAVE_AUDIO_HASH */
#if HAVE_IMAGE_HASH
	PHP_FE(ph_image_dist       , ph_image_dist_arg_info)
#endif /* HAVE_IMAGE_HASH */
	PHP_FE(ph_compare_image    , ph_compare_image_arg_info)
#if HAVE_IMAGE_HASH
	PHP_FE(ph_dct_imagehash_to_array, ph_dct_imagehash_to_array_arg_info)
#endif /* HAVE_IMAGE_HASH */
#if HAVE_IMAGE_HASH
	PHP_FE(ph_mh_imagehash_to_array, ph_mh_imagehash_to_array_arg_info)
#endif /* HAVE_IMAGE_HASH */
#if HAVE_VIDEO_HASH
	PHP_FE(ph_video_dist       , ph_video_dist_arg_info)
#endif /* HAVE_VIDEO_HASH */
#if HAVE_AUDIO_HASH
	PHP_FE(ph_audio_dist       , ph_audio_dist_arg_info)
#endif /* HAVE_AUDIO_HASH */
	PHP_FE(ph_compare_text_hashes, ph_compare_text_hashes_arg_info)
	{ NULL, NULL, NULL }
};
/* }}} */


/* {{{ pHash_module_entry
 */
zend_module_entry pHash_module_entry = {
	STANDARD_MODULE_HEADER,
	"pHash",
	pHash_functions,
	PHP_MINIT(pHash),     /* Replace with NULL if there is nothing to do at php startup   */ 
	PHP_MSHUTDOWN(pHash), /* Replace with NULL if there is nothing to do at php shutdown  */
	PHP_RINIT(pHash),     /* Replace with NULL if there is nothing to do at request start */
	PHP_RSHUTDOWN(pHash), /* Replace with NULL if there is nothing to do at request end   */
	PHP_MINFO(pHash),
	PHP_PHASH_VERSION, 
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHASH
extern "C" {
ZEND_GET_MODULE(pHash)
} // extern "C"
#endif


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(pHash)
{
	le_ph_video_hash = zend_register_list_destructors_ex(ph_video_hash_dtor, 
						   NULL, "ph_video_hash", module_number);
	le_ph_image_hash = zend_register_list_destructors_ex(ph_image_hash_dtor, 
						   NULL, "ph_image_hash", module_number);
	le_ph_digest_hash = zend_register_list_destructors_ex(ph_digest_hash_dtor, 
						   NULL, "ph_digest_hash", module_number);
	le_ph_audio_hash = zend_register_list_destructors_ex(ph_audio_hash_dtor, 
						   NULL, "ph_audio_hash", module_number);
	le_ph_mh_image_hash = zend_register_list_destructors_ex(ph_mh_image_hash_dtor, 
						   NULL, "ph_mh_image_hash", module_number);
	le_ph_txt_hash = zend_register_list_destructors_ex(ph_txt_hash_dtor, 
						   NULL, "ph_txt_hash", module_number);

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(pHash)
{

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(pHash)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(pHash)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(pHash)
{
	php_printf("pHash\n");
	php_info_print_table_start();
	php_info_print_table_row(2, "Version",PHP_PHASH_VERSION " (beta)");
	php_info_print_table_row(2, "Released", "2013-05-14");
	php_info_print_table_row(2, "CVS Revision", "$Id: $");
	php_info_print_table_row(2, "Authors", "Evan Klinger 'eklinger@phash.org' (lead)\n");
	php_info_print_table_end();
	/* add your stuff here */

}
/* }}} */


#if HAVE_VIDEO_HASH
/* {{{ proto resource ph_video_hash ph_dct_videohash(string file)
  pHash DCT video hash */
PHP_FUNCTION(ph_dct_videohash)
{
	ph_video_hash * return_res;
#if PHP_VERSION_ID < 70000
	long return_res_id = -1;
#endif
	const char * file = NULL;
	SIZETorINT file_len = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &file, &file_len) == FAILURE) {
		return;
	}

	int len;
	ulong64 *video_hash = ph_dct_videohash(file, len);
	if(video_hash)
	{
		ph_video_hash *p = (ph_video_hash *)malloc(sizeof(ph_video_hash));
		p->hash = video_hash;
		p->len = len;
		return_res = p;

	}
	else
		RETURN_FALSE;

#if PHP_VERSION_ID >= 70000
	RETURN_RES(zend_register_resource(return_res, le_ph_video_hash));
#else
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_ph_video_hash);
#endif
}
/* }}} ph_dct_videohash */

#endif /* HAVE_VIDEO_HASH */

#if HAVE_IMAGE_HASH
/* {{{ proto resource ph_image_hash ph_dct_imagehash(string file)
  pHash DCT image hash */
PHP_FUNCTION(ph_dct_imagehash)
{
	ulong64 * return_res;
#if PHP_VERSION_ID < 70000
	long return_res_id = -1;
#endif

	const char * file = NULL;
	int file_len = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &file, &file_len) == FAILURE) {
		return;
	}

	ulong64 *hash = (ulong64 *)malloc(sizeof(ulong64));
	int ret = ph_dct_imagehash(file, *hash);
	if(ret != 0)
	{
		free(hash);
		RETURN_FALSE;
	}
	else
		return_res = hash;
#if PHP_VERSION_ID >= 70000
	RETURN_RES(zend_register_resource(return_res, le_ph_image_hash));
#else
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_ph_image_hash);
#endif
}
/* }}} ph_dct_imagehash */

#endif /* HAVE_IMAGE_HASH */

#if HAVE_IMAGE_HASH
/* {{{ proto resource ph_digest_hash ph_image_digest(string file)
  pHash Radial image digest */
PHP_FUNCTION(ph_image_digest)
{
	ph_digest_hash * return_res;
#if PHP_VERSION_ID < 70000
	long return_res_id = -1;
#endif

	const char * file = NULL;
	int file_len = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &file, &file_len) == FAILURE) {
		return;
	}

	double sigma = 1.0;
	double gamma = 1.0;
	long angles = 180;

	ph_digest_hash *digest = (ph_digest_hash *)malloc(sizeof(ph_digest_hash));
	int ret = ph_image_digest(file, sigma, gamma, *digest, angles);
	if(ret != 0)
	{
		free(digest);
		RETURN_FALSE;
	}
	else
	{
		return_res = digest;
	}

#if PHP_VERSION_ID >= 70000
	RETURN_RES(zend_register_resource(return_res, le_ph_digest_hash));
#else
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_ph_digest_hash);
#endif
}
/* }}} ph_image_digest */

#endif /* HAVE_IMAGE_HASH */

#if HAVE_IMAGE_HASH
/* {{{ proto resource ph_mh_image_hash ph_mh_imagehash(string file, float alpha=2.0, float level=1.0)
  Fixed Length MH image hash */
PHP_FUNCTION(ph_mh_imagehash)
{
	ph_mh_image_hash * return_res;
#if PHP_VERSION_ID < 70000
	long return_res_id = -1;
#endif

	const char * file = NULL;
	int file_len = 0;
	double alpha = 2.0;
	double level = 1.0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|dd", &file, &file_len, &alpha, &level) == FAILURE) {
		return;
	}

	int num = 0;
	uint8_t *hash = ph_mh_imagehash(file, num, alpha, level);
	if (hash)
	{
		ph_mh_image_hash *h = (ph_mh_image_hash *)malloc(sizeof(ph_mh_image_hash));
		h->hash = hash;
		h->len = num;
		return_res = h;
	}
	else
		RETURN_FALSE;

#if PHP_VERSION_ID >= 70000
	RETURN_RES(zend_register_resource(return_res, le_ph_mh_image_hash));
#else
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_ph_mh_image_hash);
#endif
}
/* }}} ph_mh_imagehash */

#endif /* HAVE_IMAGE_HASH */

/* {{{ proto resource ph_txt_hash ph_texthash(string file)
  pHash cyclic text hash */
PHP_FUNCTION(ph_texthash)
{
	ph_text_hash * return_res;
#if PHP_VERSION_ID < 70000
	long return_res_id = -1;
#endif

	const char * file = NULL;
	int file_len = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &file, &file_len) == FAILURE) {
		return;
	}

	int num;
	TxtHashPoint *txtHash = ph_texthash(file, &num);
	if(txtHash)
	{
		ph_text_hash *h = (ph_text_hash *)malloc(sizeof(ph_text_hash));
		h->p = txtHash;
		h->count = num;
		return_res = h;
	}
	else
		RETURN_FALSE;

#if PHP_VERSION_ID >= 70000
	RETURN_RES(zend_register_resource(return_res, le_ph_txt_hash));
#else
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_ph_txt_hash);
#endif
}
/* }}} ph_texthash */


#if HAVE_AUDIO_HASH
/* {{{ proto resource ph_audio_hash ph_audiohash(string file, int sample_rate=5512, int channels=1)
  pHash audio hash */
PHP_FUNCTION(ph_audiohash)
{
	ph_audio_hash * return_res;
#if PHP_VERSION_ID < 70000
	long return_res_id = -1;
#endif

	const char * file = NULL;
	int file_len = 0;
	long sample_rate = 5512;
	long channels = 1;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", &file, &file_len, &sample_rate, &channels) == FAILURE) {
		return;
	}

	int n;
	float *audiobuf = ph_readaudio(file, sample_rate, channels, NULL, n);
	if(audiobuf)
	{
		int nb_frames;
		uint32_t *hash = ph_audiohash(audiobuf, n, sample_rate, nb_frames);
		free(audiobuf);

		if(hash)
		{
			ph_audio_hash *h = (ph_audio_hash *)malloc(sizeof(ph_audio_hash));
			h->hash = hash;
			h->len = nb_frames;

			return_res = h;
		}
		else
			RETURN_FALSE;
	}
	else
		RETURN_FALSE;

#if PHP_VERSION_ID >= 70000
	RETURN_RES(zend_register_resource(return_res, le_ph_audio_hash));
#else
	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_ph_audio_hash);
#endif
}
/* }}} ph_audiohash */

#endif /* HAVE_AUDIO_HASH */

#if HAVE_IMAGE_HASH
/* {{{ proto float ph_image_dist(resource ph_image_hash h1,resource ph_image_hash h2)
  pHash image distance. */
PHP_FUNCTION(ph_image_dist)
{
	zval * h1_res = NULL;
	int h1_resid = -1;
	ulong64 * h1;
	zval * h2_res = NULL;
	int h2_resid = -1;
	ulong64 * h2;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &h1_res, &h2_res) == FAILURE) {
		return;
	}

#if PHP_VERSION_ID >= 70000
	if ((h1 = (ulong64 *)zend_fetch_resource2(Z_RES_P(h1_res), "ph_image_hash", h1_resid, le_ph_image_hash)) == NULL) {
		RETURN_FALSE;
	}
	if ((h2 = (ulong64 *)zend_fetch_resource2(Z_RES_P(h2_res), "ph_image_hash", h2_resid, le_ph_image_hash)) == NULL) {
		RETURN_FALSE;
	}
#else
	ZEND_FETCH_RESOURCE(h1, ulong64 *, &h1_res, h1_resid, "ph_image_hash", le_ph_image_hash);
	ZEND_FETCH_RESOURCE(h2, ulong64 *, &h2_res, h2_resid, "ph_image_hash", le_ph_image_hash);
#endif


	if(h1 && h2)
	{
		int dist = ph_hamming_distance(*h1, *h2);
		RETURN_DOUBLE(dist);
	}
	else
		RETURN_DOUBLE(-1);
}
/* }}} ph_image_dist */

#endif /* HAVE_IMAGE_HASH */

/* {{{ proto double ph_compare_image(resource ph_digest_hash a, resource ph_digest_hash b)
  Compare two image digest */
PHP_FUNCTION(ph_compare_image)
{
	zval * a_res = NULL;
	int a_resid = -1;
	ph_digest_hash * a;
	zval * b_res = NULL;
	int b_resid = -1;
	ph_digest_hash * b;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &a_res, &b_res) == FAILURE) {
		return;
	}
#if PHP_VERSION_ID >= 70000
	if ((a = (ph_digest_hash *)zend_fetch_resource2(Z_RES_P(a_res), "ph_digest_hash", a_resid, le_ph_digest_hash)) == NULL) {
		RETURN_FALSE;
	}
	if ((b = (ph_digest_hash *)zend_fetch_resource2(Z_RES_P(b_res), "ph_digest_hash", b_resid, le_ph_digest_hash)) == NULL) {
		RETURN_FALSE;
	}
#else
	ZEND_FETCH_RESOURCE(a, ph_digest_hash *, &a_res, a_resid, "ph_digest_hash", le_ph_digest_hash);
	ZEND_FETCH_RESOURCE(b, ph_digest_hash *, &b_res, b_resid, "ph_digest_hash", le_ph_digest_hash);
#endif


	if(a && b)
	{
		double threshold=0.9;
		double *ps=(double *)malloc(sizeof(double));
		double similar=0;

		ph_crosscorr(*a, *b, *ps, threshold);
		similar=*ps; free(ps);
		RETURN_DOUBLE(similar);
	}
	else
		RETURN_FALSE;
}
/* }}} ph_compare_image */


#if HAVE_IMAGE_HASH
/* {{{ proto array ph_dct_imagehash_to_array(resource ph_image_hash h)
  Conversion of DCT pHash image hash to 8-bytes array. */
PHP_FUNCTION(ph_dct_imagehash_to_array)
{
	zval * h_res = NULL;
	int h_resid = -1;
	ulong64 * h;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &h_res) == FAILURE) {
		return;
	}
#if PHP_VERSION_ID >= 70000
	if ((h = (ulong64 *)zend_fetch_resource2(Z_RES_P(h_res), "ph_image_hash", h_resid, le_ph_image_hash)) == NULL) {
		RETURN_FALSE;
	}
#else
	ZEND_FETCH_RESOURCE(h, ulong64 *, &h_res, h_resid, "ph_image_hash", le_ph_image_hash);
#endif


	array_init(return_value);

	if (h)
	{
		array_init(return_value);
		uint8_t *p = (uint8_t*) h;
		for (int i = 0; i < sizeof(ulong64) / sizeof(uint8_t); i++)
		{
			add_next_index_long(return_value, *(p + i));
		}
	}
	else
	{
		RETURN_FALSE;
	}
}
/* }}} ph_dct_imagehash_to_array */

#endif /* HAVE_IMAGE_HASH */

#if HAVE_IMAGE_HASH
/* {{{ proto array ph_mh_imagehash_to_array(resource ph_mh_image_hash h)
  Conversion of fixed Length MH image hash to 72-bytes array. */
PHP_FUNCTION(ph_mh_imagehash_to_array)
{
	zval * h_res = NULL;
	int h_resid = -1;
	ph_mh_image_hash * h;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &h_res) == FAILURE) {
		return;
	}
#if PHP_VERSION_ID >= 70000
	if ((h = (ph_mh_image_hash *)zend_fetch_resource2(Z_RES_P(h_res), "ph_mh_image_hash", h_resid, le_ph_mh_image_hash)) == NULL) {
		RETURN_FALSE;
	}
#else
	ZEND_FETCH_RESOURCE(h, ph_mh_image_hash *, &h_res, h_resid, "ph_mh_image_hash", le_ph_mh_image_hash);
#endif


	array_init(return_value);

	if (h)
	{
		array_init(return_value);
		for (int i = 0; i < h->len; i++)
		{
			add_next_index_long(return_value, *(h->hash + i));
		}
	}
	else
	{
		RETURN_FALSE;
	}
}
/* }}} ph_mh_imagehash_to_array */

#endif /* HAVE_IMAGE_HASH */

#if HAVE_VIDEO_HASH
/* {{{ proto float ph_video_dist(resource ph_video_hash h1,resource ph_video_hash h2, int thresh=21)
  pHash video distance. */
PHP_FUNCTION(ph_video_dist)
{
	zval * h1_res = NULL;
	int h1_resid = -1;
	ph_video_hash * h1;
	zval * h2_res = NULL;
	int h2_resid = -1;
	ph_video_hash * h2;

	zppLONG thresh = 21;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr|l", &h1_res, &h2_res, &thresh) == FAILURE) {
		return;
	}

#if PHP_VERSION_ID >= 70000
	if ((h1 = (ph_video_hash *)zend_fetch_resource2(Z_RES_P(h1_res), "ph_video_hash", h1_resid, le_ph_video_hash)) == NULL) {
		RETURN_FALSE;
	}
	if ((h2 = (ph_video_hash *)zend_fetch_resource2(Z_RES_P(h2_res), "ph_video_hash", h2_resid, le_ph_video_hash)) == NULL) {
		RETURN_FALSE;
	}
#else
	ZEND_FETCH_RESOURCE(h1, ph_video_hash *, &h1_res, h1_resid, "ph_video_hash", le_ph_video_hash);
	ZEND_FETCH_RESOURCE(h2, ph_video_hash *, &h2_res, h2_resid, "ph_video_hash", le_ph_video_hash);
#endif


	if(h1 && h2)
	{
		double sim = ph_dct_videohash_dist(h1->hash, h1->len, h2->hash, h2->len, thresh);
		RETURN_DOUBLE(sim);
	}
	else
		RETURN_DOUBLE(-1);
}
/* }}} ph_video_dist */

#endif /* HAVE_VIDEO_HASH */

#if HAVE_AUDIO_HASH
/* {{{ proto float ph_audio_dist(resource ph_audio_hash h1,resource ph_audio_hash h2,
		int block_size=256, float thresh=0.30)
  pHash audio distance. */
PHP_FUNCTION(ph_audio_dist)
{
	zval * h1_res = NULL;
	int h1_resid = -1;
	ph_audio_hash * h1;
	zval * h2_res = NULL;
	int h2_resid = -1;
	ph_audio_hash * h2;

	zppLONG block_size = 256;
	double thresh = 0.30;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr|ld", &h1_res, &h2_res, &block_size, &thresh) == FAILURE) {
		return;
	}
#if PHP_VERSION_ID >= 70000
	if ((h1 = (ph_audio_hash *)zend_fetch_resource2(Z_RES_P(h1_res), "ph_audio_hash", h1_resid, le_ph_audio_hash)) == NULL) {
		RETURN_FALSE;
	}
	if ((h2 = (ph_audio_hash *)zend_fetch_resource2(Z_RES_P(h2_res), "ph_audio_hash", h2_resid, le_ph_audio_hash)) == NULL) {
		RETURN_FALSE;
	}
#else
	ZEND_FETCH_RESOURCE(h1, ph_audio_hash *, &h1_res, h1_resid, "ph_audio_hash", le_ph_audio_hash);
	ZEND_FETCH_RESOURCE(h2, ph_audio_hash *, &h2_res, h2_resid, "ph_audio_hash", le_ph_audio_hash);
#endif


	if(h1 && h2)
	{
		int Nc;
		double *cs = ph_audio_distance_ber(h1->hash, h1->len, h2->hash, h2->len,
				thresh, block_size, Nc);
		if(cs)
		{
			double max_cs = 0.0;
			for (int i = 0; i < Nc; ++i)
			{
				if (cs[i] > max_cs)
				{
					max_cs = cs[i];
				}
			}
			free(cs);
			RETURN_DOUBLE(max_cs);
		}
		else
			RETURN_DOUBLE(-1);
	}
	else
		RETURN_DOUBLE(-1);
}
/* }}} ph_audio_dist */

#endif /* HAVE_AUDIO_HASH */

/* {{{ proto array ph_compare_text_hashes(resource ph_txt_hash h1,resource ph_txt_hash h2)
  pHash text distance. */
PHP_FUNCTION(ph_compare_text_hashes)
{
	zval * h1_res = NULL;
	int h1_resid = -1;
	ph_text_hash * h1;
	zval * h2_res = NULL;
	int h2_resid = -1;
	ph_text_hash * h2;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &h1_res, &h2_res) == FAILURE) {
		return;
	}
#if PHP_VERSION_ID >= 70000
	if ((h1 = (ph_text_hash *)zend_fetch_resource2(Z_RES_P(h1_res), "ph_txt_hash", h1_resid, le_ph_txt_hash)) == NULL) {
		RETURN_FALSE;
	}
	if ((h2 = (ph_text_hash *)zend_fetch_resource2(Z_RES_P(h2_res), "ph_txt_hash", h2_resid, le_ph_txt_hash)) == NULL) {
		RETURN_FALSE;
	}
#else
	ZEND_FETCH_RESOURCE(h1, ph_text_hash *, &h1_res, h1_resid, "ph_txt_hash", le_ph_txt_hash);
	ZEND_FETCH_RESOURCE(h2, ph_text_hash *, &h2_res, h2_resid, "ph_txt_hash", le_ph_txt_hash);
#endif


	array_init(return_value);

	if(h1 && h2)
	{
		int count = 0;
		TxtMatch *m = ph_compare_text_hashes(h1->p, h1->count, h2->p, h2->count, &count);
		if(m)
		{
			for(int i = 0; i < count; ++i)
			{
#if PHP_VERSION_ID >= 70000
				zval array;
				array_init(&array);
				add_assoc_long(&array, "begin", m[i].first_index);
				add_assoc_long(&array, "end", m[i].second_index);
				add_assoc_long(&array, "length", m[i].length);
				add_next_index_zval(return_value, &array);
#else
				zval *array;
				MAKE_STD_ZVAL(array);
				array_init(array);
				add_assoc_long(array, "begin", m[i].first_index);
				add_assoc_long(array, "end", m[i].second_index);
				add_assoc_long(array, "length", m[i].length);
				add_next_index_zval(return_value, array);
#endif
			}
			free(m);
		}
		else
			RETURN_FALSE;

	}
	else
		RETURN_FALSE;
}
/* }}} ph_compare_text_hashes */

#endif /* HAVE_PHASH */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
