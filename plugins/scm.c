/*  plugins/counts.c -- counts SNPs, Indels, and total number of sites.

    Copyright (C) 2013-2018 Genome Research Ltd.

    Author: Petr Danecek <pd3@sanger.ac.uk>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.  */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <htslib/vcf.h>
#include <bcftools.h>
#ifndef WITH_GUILE


/*
    This short description is used to generate the output of `bcftools plugin -l`.
*/
const char *about(void)
{
    return
        "Select variant using guile.\n";
}

/*
    Called once at startup, it initializes local variables.
    Return 1 to suppress VCF/BCF header from printing, 0 otherwise.
*/
int init(int argc, char **argv, bcf_hdr_t *in, bcf_hdr_t *out)
{
 fprintf(stderr,"GUILE IS NOT AVAILABLE\n");
    return 1;
}


/*
    Called for each VCF record. Return rec to output the line or NULL
    to suppress output.
*/
bcf1_t *process(bcf1_t *rec)
{

    return NULL;
}


/*
    Clean up.
*/
void destroy(void)
{

}

#else
#include <getopt.h>
#include <libguile.h>

typedef struct args_t {
} args_t;


/*
    This short description is used to generate the output of `bcftools plugin -l`.
*/
const char *about(void)
{
    return
        "Select variant using guile." SCM_EFFECTIVE_VERSION "\n";
}

/*
    Called once at startup, it initializes local variables.
    Return 1 to suppress VCF/BCF header from printing, 0 otherwise.
*/
int init(int argc, char **argv, bcf_hdr_t *in, bcf_hdr_t *out)
{
fprintf(stderr,"Hello 0\n");
 	args_t *args = (args_t*) calloc(1,sizeof(args_t));
    static struct option loptions[] =
    {
        {"expression",required_argument,NULL,'e'},
        {"script",required_argument,NULL,'f'},
        {NULL,0,NULL,0}
    };
    int c;
    char *script_string = NULL;
    char *script_file = NULL;
    while ((c = getopt_long(argc, argv, "e:f:",loptions,NULL)) >= 0)
    {
        switch (c)
        {
            case 'e': script_string = optarg; break;
            case 'f': script_file = optarg; break;
            case 'h':
            case '?':
            default: error("boum"); 
            	break;
        }
    }
   fprintf(stderr,"Hello 1\n");
   scm_init_guile();
   fprintf(stderr,"Hello 2\n");
   if(script_string==NULL && script_file==NULL) {
   	error("script expression/file missing"); 
    }
   else  if(script_string!=NULL && script_file!=NULL) {
   	error("script expression/file both defined"); 
    }
   else if(script_string!=NULL) {
     scm_c_eval_string(script_string);
   	}
   	else {
    abort();
   	}
   	
    return 0;



scm_shell (argc, argv);
    return 1;
}


/*
    Called for each VCF record. Return rec to output the line or NULL
    to suppress output.
*/
bcf1_t *process(bcf1_t *rec)
{



    return NULL;
}


/*
    Clean up.
*/
void destroy(void)
{

}



#endif

