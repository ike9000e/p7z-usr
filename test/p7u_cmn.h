
#ifndef _P7U_CMN_H_
#define _P7U_CMN_H_
#include <string>
#include <vector>
#include <stdint.h>

namespace hef{}
using namespace hef;

extern bool             bShowDebug;
extern std::string*     DebugLogFile;
extern std::string*     SelfWcxFile;
extern std::string*     Str7zSoFile;
extern char             szP7zWcxFile[128];
extern int              uGlobArcExcCalbRefc;

void wcxi_DebugString( const char* );
void wcxi_ConvU64To2xU32( uint64_t inp, uint32_t* uLow, uint32_t* uHi );

class IProcRelay{
public:
	/// Set percentage positions durning DCMD files extract process.
	/// Return value 0 indicates user cancel via DCMD GUI.
	virtual bool iprSetFilePercentage( const char* szFilename, float fPercentage ) = 0;
	virtual bool iprSetTotalPercentage( const char* szFilename, float fPercentage ) = 0;
	//
	struct SMsgBox{
		const char* capt, *msg;
		bool bOkAccepted;
		int flags3; // fe. 0x10 = red error icon.
		SMsgBox() : capt(""), msg(""), bOkAccepted(0), flags3(0) {}
	};
	struct SPrompt : SMsgBox{
		std::string strIoVal; ///< input|output value for|from prompt edit field.
	};
	/// Returns true if prompt box was available and was displayed.
	/// Value 'bOkAccepted' gets set to 1 if ok button was pressed.
	virtual bool iprPromptBox( SPrompt& inp ) = 0;
	virtual bool iprMessageBox( SMsgBox& inp ) = 0;
	//
	virtual bool iprTryGetOrAskArcFNPassword( const char* szArcFnm, std::string* outp ) = 0;
	virtual bool iprRemoveArcFNPassword( const char* szArcFnm ) = 0;
};

#endif //_P7U_CMN_H_
