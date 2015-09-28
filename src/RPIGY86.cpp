#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <algorithm>

#include "RPIGY86.h"
#include "MPU6050.h"
#include "HMC5883L.h"
#include "MS5611.h"

using namespace v8;

#define FUNCTION_TEMPLATE_CLASS "RPiGY86"

v8::Eternal<v8::Function> RPIGY86::sFunction;

/*static*/
void RPIGY86::V8New(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    if (args.IsConstructCall())
    {
        new RPIGY86(args);
        args.GetReturnValue().Set(args.This());
    }
    else
    {
        v8::Local<v8::Function> func = RPIGY86::sGetFunction();
        v8::Local<v8::Value> newArgs[args.Length()];
        for ( int i = 0; i < args.Length(); i ++ )
        {
            newArgs[i] = args[i];
        }
        v8::Local<v8::Object> obj = func->NewInstance(Nan::GetCurrentContext(), args.Length(), newArgs).ToLocalChecked();
        args.GetReturnValue().Set(obj);
    }
}

/*static*/
void
RPIGY86::sGetMotion6(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    RPIGY86* _this = RPIGY86::Unwrap<RPIGY86>(args.Holder());
    if ( !_this )
    {
        args.GetIsolate()->ThrowException(
                v8::Exception::ReferenceError(Nan::New("not a valid RPiGY86 object").ToLocalChecked()));
    }
    if ( args.Length()  != 0 )
    {
        args.GetIsolate()->ThrowException(
                v8::Exception::SyntaxError(Nan::New("usage: getMotion6()").ToLocalChecked()));
    }
    _this->getMotion6(args);
}
/*static*/ void
RPIGY86::sGetMotion9(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    RPIGY86* _this = RPIGY86::Unwrap<RPIGY86>(args.Holder());
    if ( !_this )
    {
        args.GetIsolate()->ThrowException(
                v8::Exception::ReferenceError(Nan::New("not a valid RPiGY86 object").ToLocalChecked()));
    }

    if ( args.Length()  != 0 )
    {
        args.GetIsolate()->ThrowException(
                v8::Exception::SyntaxError(Nan::New("usage: getMotion9()").ToLocalChecked()));
    }
    _this->getMotion9(args);
}

/*static*/
v8::Local<v8::Function>
RPIGY86::sGetFunction()
{
    Nan::EscapableHandleScope scope;
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    if ( sFunction.IsEmpty() ) {
        v8::Local<v8::FunctionTemplate> ftmpl = v8::FunctionTemplate::New(isolate, RPIGY86::V8New);
        ftmpl->SetClassName(Nan::New(FUNCTION_TEMPLATE_CLASS).ToLocalChecked());
        v8::Local<v8::ObjectTemplate> otmpl = ftmpl->InstanceTemplate();
        otmpl->SetInternalFieldCount(1);
        otmpl->Set(Nan::New("getMotion6").ToLocalChecked(),
            v8::FunctionTemplate::New(isolate, sGetMotion6, v8::Local<v8::Value>(), v8::Signature::New(isolate, ftmpl)));
        otmpl->Set(Nan::New("getMotion9").ToLocalChecked(),
            v8::FunctionTemplate::New(isolate, sGetMotion9, v8::Local<v8::Value>(), v8::Signature::New(isolate, ftmpl)));
        sFunction.Set(isolate, ftmpl->GetFunction());
    }
    return scope.Escape(sFunction.Get(isolate));
}

RPIGY86::RPIGY86(const v8::FunctionCallbackInfo<v8::Value> &args)
    : mpu6050(nullptr), hmc5883l(nullptr), ms5611(nullptr)
{
    this->Wrap(args.This());
    initialize();
}

void RPIGY86::initialize()
{
    mpu6050 = new MPU6050();
    hmc5883l = new HMC5883L();
    ms5611 = new MS5611();
    mpu6050->initialize();
    mpu6050->setI2CBypassEnabled(true);
    hmc5883l->initialize();
    ms5611->begin();
}

RPIGY86::~RPIGY86()
{
    delete mpu6050;
    delete hmc5883l;
    delete ms5611;
}

void RPIGY86::getMotion6(const FunctionCallbackInfo<v8::Value> &args)
{
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    v8::Isolate* isolate = args.GetIsolate();
    mpu6050->getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    v8::Local<v8::Array> rev = v8::Array::New(isolate, 6);
    rev->Set(0, v8::Int32::New(isolate, ax));
    rev->Set(1, v8::Int32::New(isolate, ay));
    rev->Set(2, v8::Int32::New(isolate, az));
    rev->Set(3, v8::Int32::New(isolate, gx));
    rev->Set(4, v8::Int32::New(isolate, gy));
    rev->Set(5, v8::Int32::New(isolate, gz));
    args.GetReturnValue().Set(rev);
}

void RPIGY86::getMotion9(const FunctionCallbackInfo<v8::Value> &args)
{
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    int16_t mx, my, mz;

    v8::Isolate* isolate = args.GetIsolate();
    mpu6050->getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    v8::Local<v8::Array> rev = v8::Array::New(isolate, 9);
    rev->Set(0, v8::Int32::New(isolate, ax));
    rev->Set(1, v8::Int32::New(isolate, ay));
    rev->Set(2, v8::Int32::New(isolate, az));
    rev->Set(3, v8::Int32::New(isolate, gx));
    rev->Set(4, v8::Int32::New(isolate, gy));
    rev->Set(5, v8::Int32::New(isolate, gz));

    hmc5883l->getHeading(&mx, &my, &mz);
    rev->Set(6, v8::Int32::New(isolate, mx));
    rev->Set(7, v8::Int32::New(isolate, my));
    rev->Set(8, v8::Int32::New(isolate, mz));

    args.GetReturnValue().Set(rev);
}

NAN_MODULE_INIT(initialize) {
    Nan::HandleScope scope;
    Nan::Set(target, Nan::New(FUNCTION_TEMPLATE_CLASS).ToLocalChecked(),
            RPIGY86::sGetFunction());
}

NODE_MODULE(rpi_gy86, initialize)
