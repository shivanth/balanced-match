#include <node_api.h>
#include <assert.h>
#include<string>
#include<vector>
#include<iostream>

std::vector<size_t> range(std::string a,std::string b,std::string c);

#define DECLARE_NAPI_METHOD(name, func)             \
        { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value balanced(napi_env env, napi_callback_info info){
        napi_status status;
        size_t argc = 3;
        napi_value args[3];
        status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
        assert(status == napi_ok);

        if (argc < 3) {
                napi_throw_error(env,NULL, "Wrong number of arguments");
                return nullptr;
        }

        napi_valuetype valuetype0;
        status = napi_typeof(env, args[0], &valuetype0);
        if(status != napi_ok){
                napi_throw_error(env,NULL, "Expected String");
                return nullptr;
        }

        napi_valuetype valuetype1;
        status = napi_typeof(env, args[1], &valuetype1);
        if(status != napi_ok){
                napi_throw_error(env,NULL, "Expected String");
                return nullptr;
        }

        napi_valuetype valuetype2;
        status = napi_typeof(env, args[2], &valuetype2);
        if(status != napi_ok){
                napi_throw_error(env,NULL, "Expected String");
                return nullptr;
        }

        if (valuetype0 != napi_string || valuetype1 != napi_string || valuetype2 != napi_string){
                napi_throw(env,NULL);
        }

        //get c++ values of arguements
        size_t size1, size2,size3;
        size_t written;
        status = napi_get_value_string_utf8(env, args[0], NULL, 0, &size1);
        char * _arg1 = new char[size1 + 1];
        status = napi_get_value_string_utf8(env,args[0],_arg1,size1 + 1, &written);
        std::string arg1(_arg1);
        status = napi_get_value_string_utf8(env, args[1], NULL, 0, &size2);
        char * _arg2 = new char[size2 + 1];
        status = napi_get_value_string_utf8(env,args[1],_arg2,size2 + 1, &written);
        std::string arg2(_arg2);
        status = napi_get_value_string_utf8(env, args[2], NULL, 0, &size3);
        char * _arg3 = new char[size3 + 1];
        status = napi_get_value_string_utf8(env,args[2],_arg3,size3 + 1, &written);
        std::string arg3(_arg3);
        //find the first match indexes
        std::vector<size_t> r = range(arg1,arg2,arg3);

        napi_value pos1 = NULL;
        napi_value pos2 = NULL;


        if(r.size() == 2){
                status = napi_create_int32(env,r[0],&pos1);
                status = napi_create_int32(env,r[1],&pos2);
        }
        else{
                return NULL;//undefined
        }

        napi_value pre;
        napi_value body;
        napi_value post;
        napi_value ret;

        //find the pre , body and post of the match using the ranges
        napi_create_string_utf8(env,arg3.substr(0,r[0]).c_str(),r[0],&pre);
        napi_create_string_utf8(env,arg3.substr(r[0] + size1, r[1] ).c_str(),r[1] - size2 - r[0] ,&body);
        napi_create_string_utf8(env,arg3.substr(r[1] + 1, size3 - (r[1] + size2 - 1)).c_str(),size3 - (r[1] + size2),&post);
        status = napi_create_object(env, &ret);

        // create the return object
        napi_set_named_property(env, ret, "start", pos1);
        napi_set_named_property(env, ret, "end", pos2);
        napi_set_named_property(env, ret, "pre", pre);
        napi_set_named_property(env, ret, "body", body);
        napi_set_named_property(env, ret, "post", post);

        return ret;


}

std::vector<size_t> range(std::string a,std::string b,std::string c){
        std::cout<<a<<" "<<b<<" "<<c<<std::endl;
        std::string::size_type pos1 = c.find(a);
        std::string::size_type pos2 = c.find(b,pos1);
        std::string::size_type i = pos1;
        std::string::size_type beg, left, right;
        std::vector<std::string::size_type> result;
        std::cout<<pos1<<" "<<pos2<<std::endl;
        bool done = false;
        std::cout<<i<<std::endl<<std::flush;
        if(pos1 != std::string::npos && pos2 != std::string::npos){

                std::vector<std::string::size_type> begs;
                left = a.size();

                while(i != std::string::npos && !done){

                        if(i == pos1){
                                begs.push_back(i);
                                pos1 = c.find(a, i+1);
                        }
                        else if (begs.size() == 1){
                                result.clear();
                                result.push_back(begs.back());
                                result.push_back(pos2);
                                begs.pop_back();
                                done = true;
                        }
                        else{
                                beg = begs.back();
                                begs.pop_back();
                                if(beg < left){
                                        left = beg;
                                        right = pos2;
                                }
                        }
                        i = pos1 < pos2 && pos1 !=std::string::npos ? pos1 : pos2;


                }
                if (begs.size()) {
                        result.clear();
                        result.push_back(left);
                        result.push_back(right);
                }
        }
        return result;
}






void Init(napi_env env, napi_value exports, napi_value module, void* priv) {
        napi_status status;
        napi_property_descriptor balancedDescriptor = DECLARE_NAPI_METHOD("balanced", balanced);
        status = napi_define_properties(env, exports, 1, &balancedDescriptor);
        assert(status == napi_ok);
}

NAPI_MODULE(addon, Init);
