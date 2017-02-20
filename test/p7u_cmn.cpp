
#include "p7u_cmn.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "hef_str.h"
#include "hef_data.h"
#include "hef_assert.h"

char             szP7zWcxFile[128] = "p7z_usr.wcx";
bool             bShowDebug = 0;
//char           szDirCharABfr[2] = { '\\', 0, }; // '\\' => 0x5C
std::string*     DebugLogFile = 0;
std::string*     SelfWcxFile = 0;
std::string*     Str7zSoFile = 0;
int              uGlobArcExcCalbRefc = 0;

void wcxi_DebugString( const char* inp )
{
	if(bShowDebug){
		printf("%s: %s\n", szP7zWcxFile, inp );
		if( DebugLogFile && !DebugLogFile->empty() ){
			std::string str;
			str = hf_strftime2( "%H:%M:%S ", 0 );
			str += inp;
			str += "\n";
			hf_PutFileBytes( DebugLogFile->c_str(), str.c_str(), -1, EPFBF_APPEND );
		}
	}
}
void wcxi_ConvU64To2xU32( uint64_t inp, uint32_t* uLow, uint32_t* uHi )
{
	*uLow = (uint32_t)( inp & 0xFFFFFFFF );
	*uHi = (uint32_t)( (inp >> 32) & 0xFFFFFFFF );
}




