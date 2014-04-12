#ifndef __PROCESSBAM
#define __PROCESSBAM

typedef struct _bamInfo
{
	htsFile* bam;		/*	file pointer to the BAM file; as set in parameters->bamFile */
  	int numChrom;		/*	number of chromosomes */
	int* chromLengths;	/*	lengths of the chromosomes */
	char** chromNames;	/*	names of the chromosomes */
  	char* sampleName; 	/*	name of the sample, parsed from SM in the BAM header */
	float fragAvg;		/*	average fragment size */
  	float fragStd; 		/*	fragment size standard deviation */
	int fragMed;		/*	median of the fragment sizes */
  	int concMin; 		/*	min cutoff for concordants */
  	int concMax; 		/*	max cutoff for concordants */

	int* pos;					/*	1-based leftmost coordinate of the read */
	int* bin;					/*	bin */
	int* qual;					/*	Mapping quality */
	int* length_read_name;		/*	Length of the read name */
	int* flag;					/*	Flags */
	int* pos_mate_read;			/*	1-based leftmost coordinate of the mate read */
	int* is_reverse;			/*	True if the read maps to the reverse strand */
	int* is_mate_reverse;		/*	True if the mate of the read maps to the reverse strand */
	char** read_name;			/*	Names of the reads */
	int** length_cigar_ops;		/*	Coefficients of CIGAR operations */	
	char** cigar_ops;			/*	Characters representing CIGAR operations */
	int* length_read;			/*	Length of the read */
	int* insertion_size;		/*	Insertion Size, or better named as template length */
	char** read;				/*	The read, as string */
} bamInfo;


void loadBAM( bamInfo* inBam);
char base_as_char( int base_as_int);
void get_sample_name( bamInfo* inBam, char* header_text);
void print_read( bamInfo* inBam, int index);
void calculate_statistics( bamInfo* inBam);
int compare_size( const void* p, const void* q);

#endif
