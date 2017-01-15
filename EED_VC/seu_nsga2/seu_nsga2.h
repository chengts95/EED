// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SEU_NSGA2_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SEU_NSGA2_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SEU_NSGA2_EXPORTS
#define SEU_NSGA2_API __declspec(dllexport)
#else
#define SEU_NSGA2_API __declspec(dllimport)
#endif

// This class is exported from the seu_nsga2.dll
class SEU_NSGA2_API Cseu_nsga2 {
public:
	Cseu_nsga2(void);
	// TODO: add your methods here.
};

extern SEU_NSGA2_API int nseu_nsga2;

SEU_NSGA2_API int fnseu_nsga2(void);
