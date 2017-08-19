#include <node_api.h>
#include <assert.h>
#include<string>

napi_value balanced(napi_env env, napi_callback_info info){
        napi_status status;
        size_t argc = 3;
        napi_value args[3];
        status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
        assert(status == napi_ok);

        if (argc < 3) {
                napi_throw_type_error(env, "Wrong number of arguments");
                return nullptr;
        }

        napi_valuetype valuetype0;
        status = napi_typeof(env, args[0], &valuetype0);
        assert(status == napi_ok);

        napi_valuetype valuetype1;
        status = napi_typeof(env, args[1], &valuetype1);
        assert(status == napi_ok);

        napi_valuetype valuetype2;
        status = napi_typeof(env, args[2], &valuetype2);
        assert(status == napi_ok);

        if (valuetype0 != napi_object || valuetype1 != napi_string || valuetype2 != napi_string){
                napi_throw(env,NULL);
        }

}
