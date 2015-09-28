#include <nan.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <algorithm>

#include "RPIGY86.h"

using namespace v8;

NAN_METHOD(GY86) {
  Nan::HandleScope scope;

  info.GetReturnValue().Set(Nan::Undefined());
}


NAN_MODULE_INIT(initialize) {
  Nan::Set(target, Nan::New("GY86").ToLocalChecked(),
          Nan::New("Test").ToLocalChecked());
}

NODE_MODULE(rpi_gy86, initialize)
