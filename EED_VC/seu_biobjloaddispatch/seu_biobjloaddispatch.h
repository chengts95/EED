// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SEU_BIOBJLOADDISPATCH_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SEU_BIOBJLOADDISPATCH_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SEU_BIOBJLOADDISPATCH_EXPORTS
#define SEU_BIOBJLOADDISPATCH_API __declspec(dllexport)
#else
#define SEU_BIOBJLOADDISPATCH_API __declspec(dllimport)
#endif

// This class is exported from the seu_biobjloaddispatch.dll
class SEU_BIOBJLOADDISPATCH_API Cseu_biobjloaddispatch {
public:
	Cseu_biobjloaddispatch(void);
	// TODO: add your methods here.
};

extern SEU_BIOBJLOADDISPATCH_API int nseu_biobjloaddispatch;

SEU_BIOBJLOADDISPATCH_API int fnseu_biobjloaddispatch(void);
