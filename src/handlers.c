#ifndef H_HANDLERS

#include <os_io_seproxyhal.h>
#include <stdlib.h>

#include "handlers.h"
#include "getVersion.h"
#include "getExtendedPublicKey.h"
#include "runTests.h"
#include "attestUtxo.h"
#include "attestKey.h"
#include "state.h"
#include "errors.h"
#include "deriveAddress.h"

// The APDU protocol uses a single-byte instruction code (INS) to specify
// which command should be executed. We'll use this code to dispatch on a
// table of function pointers.

enum {
	// 0x0* - app status calls
	INS_GET_VERSION       = 0x00,

	// 0x1* - public-key/address related
	INS_GET_PUB_KEY       = 0x10,
	INS_DERIVE_ADDRESS    = 0x11,

	// 0x2* - signing-transaction related
	INS_ATTEST_UTXO       = 0x20,

	#ifdef DEVEL
	// 0xF* - debug_mode related
	INS_RUN_TESTS         = 0xF0,
	// 0xF1 reserved for INS_SET_HEADLESS_INTERACTION
	// session key used for attestation
	INS_GET_ATTEST_KEY    = 0xF2,
	INS_SET_ATTEST_KEY    = 0xF3,

	#endif
};


handler_fn_t* lookupHandler(uint8_t ins)
{
	switch (ins) {

	case INS_GET_VERSION:
		return getVersion_handleAPDU;

	case INS_GET_PUB_KEY:
		return getExtendedPublicKey_handleAPDU;
	case INS_DERIVE_ADDRESS:
		return deriveAddress_handleAPDU;

	case INS_ATTEST_UTXO:
		return handle_attestUtxo;

// *INDENT-OFF* astyle has problems with #define inside switch
#ifdef DEVEL
	case INS_RUN_TESTS:
		return handleRunTests;

	case INS_GET_ATTEST_KEY:
		return handleGetAttestKey;

	case INS_SET_ATTEST_KEY:
		return handleSetAttestKey;
#endif
// *INDENT-ON*

	default:
		return NULL;
	}
}

#endif
