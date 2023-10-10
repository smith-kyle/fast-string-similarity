#include "functions.h"
#include <unordered_map>
#include <string>

using v8::Local;
using v8::Object;
using v8::String;


double computeStringSimilarityCpp(const std::string& str1, const std::string& str2) {
  std::string first = str1;
  first.erase(remove_if(first.begin(), first.end(), ::isspace), first.end());
  
  std::string second = str2;
  second.erase(remove_if(second.begin(), second.end(), ::isspace), second.end());

  if (first == second) return 1.0;
  if (first.length() < 2 || second.length() < 2) return 0.0;

  std::unordered_map<std::string, int> firstBigrams;
  
  for (size_t i = 0; i < first.length() - 1; ++i) {
    std::string bigram = first.substr(i, 2);
    firstBigrams[bigram]++;
  }

  int intersectionSize = 0;

  for (size_t i = 0; i < second.length() - 1; ++i) {
    std::string bigram = second.substr(i, 2);
    if (firstBigrams[bigram] > 0) {
      firstBigrams[bigram]--;
      intersectionSize++;
    }
  }

  return (2.0 * intersectionSize) / (first.length() + second.length() - 2);
}

NAN_METHOD(computeStringSimilarity) {
  if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsString()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  Nan::Utf8String firstArg(Nan::To<String>(info[0]).ToLocalChecked());
  Nan::Utf8String secondArg(Nan::To<String>(info[1]).ToLocalChecked());
  std::string first = std::string(*firstArg);
  std::string second = std::string(*secondArg);

  // Your string comparison logic here
  // For demonstration, returning a mock similarity score
  double similarity = computeStringSimilarityCpp(first, second);

  info.GetReturnValue().Set(Nan::New(similarity));
}

// Wrapper Impl

Nan::Persistent<v8::Function> MyObject::constructor;

NAN_MODULE_INIT(MyObject::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "plusOne", PlusOne);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("MyObject").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

MyObject::MyObject(double value) : value_(value) {
}

MyObject::~MyObject() {
}

NAN_METHOD(MyObject::New) {
  if (info.IsConstructCall()) {
    double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
    MyObject *obj = new MyObject(value);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
  }
}

NAN_METHOD(MyObject::PlusOne) {
  MyObject* obj = Nan::ObjectWrap::Unwrap<MyObject>(info.This());
  obj->value_ += 1;
  info.GetReturnValue().Set(obj->value_);
}
