#ifdef WITH_GUILE



#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <getopt.h>
#include <math.h>
#include <inttypes.h>
#include <htslib/hts.h>
#include <htslib/vcf.h>
#include <libguile.h>
#include "bcftools.h"


typedef struct
{
bcf_hdr_t *hdr;
bcf1_t *rec;
SCM proc;
}
args_t;

static args_t *args = NULL;

const char *version(void)
{
    return "with guile " SCM_EFFECTIVE_VERSION "\n";
}

const char *about(void)
{
    return "with guile " SCM_EFFECTIVE_VERSION "\n";
}

const char *usage(void)
{
    return "TODO";
}

static SCM chrom_wrapper() {
    return SCM_BOOL_T;
    }

int init(int argc, char **argv, bcf_hdr_t *in, bcf_hdr_t *out)
{
    char* script_string = NULL;
    args = (args_t*) calloc(1,sizeof(args_t));
    args->hdr = in;
    static struct option loptions[] =
    {
        {"expression",required_argument,NULL,'e'},
        {NULL,0,NULL,0}
    };
    opterr = 0;
    int c;
    while ((c = getopt_long(argc, argv, "e:",loptions,NULL)) >= 0)
    {
        switch (c)
        {
            case 'e': script_string = optarg; break;
            default:
                error("boum");
                break;
        }
    }
    if(script_string==NULL) {
        error("undefined script\n");
        }
    scm_init_guile();
    SCM v = scm_c_eval_string(script_string);
    args->proc = scm_c_lookup ("filter-variant");
    if(scm_is_null(args->proc)) {
        error("cannot find filter-variant in script.\n");
        }
    scm_c_define_gsubr ("chrom", 0, 0, 0, chrom_wrapper);
    return 0;
}


bcf1_t *process(bcf1_t *rec)
{
    args->rec = rec;
    SCM ret= scm_call_0 (args->proc);
    if(scm_is_false_or_nil(ret)) return NULL;
    return rec;
}

void destroy(void)
{
    free(args);
}



#else

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <htslib/hts.h>
#include <htslib/vcf.h>
#include "bcftools.h"

const char *about(void)
{
    return "not implemented\n";
}

const char *usage(void)
{
    return "TODO";
}

int init(int argc, char **argv, bcf_hdr_t *in, bcf_hdr_t *out)
{
   abort();
    return 0;
}


bcf1_t *process(bcf1_t *rec)
{
    abort();
    return rec;
}

void destroy(void)
{

}



#endif

