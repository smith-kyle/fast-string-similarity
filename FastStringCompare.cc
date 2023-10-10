#include "functions.h"

using v8::FunctionTemplate;

// FastStringCompare.cc represents the top level of the module.
// C++ constructs that are exposed to javascript are exported here

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("computeStringSimilarity").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(computeStringSimilarity)).ToLocalChecked());

  // Passing target down to the next NAN_MODULE_INIT
  MyObject::Init(target);
}

NODE_MODULE(FastStringCompare, InitAll)
