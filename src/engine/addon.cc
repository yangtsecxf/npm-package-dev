#include <node_api.h>
#include "../common.h"
#include "EngineInterfaceMgr/EngineInterfaceMgr.h"
#include "EngineInterfaceMgr/IEngine.h"

napi_value Random(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 2;
	napi_value argv[2];
	status = napi_get_cb_info(env, info, &argc, argv, 0, 0);
	if (status != napi_ok || argc < 2)
	{
		const napi_extended_error_info* result = new napi_extended_error_info;
		napi_status sts = napi_get_last_error_info(env, &result);
		napi_throw_type_error(env, nullptr, result->error_message);
		status = napi_get_undefined(env, argv);
	}

	EngineInterfaceMgr oMgr;
	IEngine* pIEngine = oMgr.GetEngine();
	if (nullptr != pIEngine)
	{
		// get int m, n
		int m,n = 0;
		NAPI_CALL(env, napi_get_value_int32(env, argv[0], &m));
		NAPI_CALL(env, napi_get_value_int32(env, argv[1], &n));

		// get random number r
		int r = pIEngine->random(m, n);

		// r to string
		char buffer[64] = { 0 };
		_itoa_s(r, buffer, 64, 10);
		size_t len = strlen(buffer);

		// string to rt
		napi_value rt;
		NAPI_CALL(env, napi_create_string_utf8(env, buffer, len, &rt));

		return rt;
	}

	return argv[0];
}

napi_value Echo(napi_env env, napi_callback_info info)
{
    napi_status status;

    size_t argc = 1;
    napi_value argv[1];
    status = napi_get_cb_info(env, info, &argc, argv, 0, 0);
    if(status != napi_ok || argc < 1)
    {
        const napi_extended_error_info* result = new napi_extended_error_info;
        napi_status sts = napi_get_last_error_info(env, &result);

        napi_throw_type_error(env, nullptr, result->error_message);
        status = napi_get_undefined(env, argv);
    }

    return argv[0];
}

napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc = DECLARE_NAPI_PROPERTY("echo", Echo);
    NAPI_CALL(env, napi_define_properties(env, exports, 1, & desc));

	desc = DECLARE_NAPI_PROPERTY("random", Random);
	NAPI_CALL(env, napi_define_properties(env, exports, 1, &desc));

    return exports;
}

NAPI_MODULE(addon, Init)
