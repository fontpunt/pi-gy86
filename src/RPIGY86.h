#ifndef RPIGY86_H_
#define RPIGY86_H_

#include <nan.h>

class MPU6050;
class HMC5883L;
class MS5611;

class RPIGY86 : public Nan::ObjectWrap {

public:
    RPIGY86(const v8::FunctionCallbackInfo<v8::Value> &args);
    ~RPIGY86();

    static v8::Local<v8::Function> sGetFunction();

private:
    /**
     * used by javascript ctro function
     */
    static void V8New(const v8::FunctionCallbackInfo<v8::Value> &args);
    /**
     * callback function for javascript function .getMotion6()
     */
    static void sGetMotion6(const v8::FunctionCallbackInfo<v8::Value> &args);
    /**
     * callback function for javascript function .getMotion9()
     */
    static void sGetMotion9(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetGryoXOffset(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetGryoYOffset(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetGryoZOffset(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetAccelXOffset(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetAccelYOffset(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetAccelZOffset(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetGryoRangeScale(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sGetGryoRangeScale(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetAccelRangeScale(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sGetAccelRangeScale(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sCalibrateMPU6050(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetMagXOffset(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetMagYOffset(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetMagZOffset(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sGetHeadingXYZ(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sGetHeading(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sSetMagGain(const v8::FunctionCallbackInfo<v8::Value> &args);
    static void sGetMagGain(const v8::FunctionCallbackInfo<v8::Value> &args);
    static v8::Eternal<v8::Function> sFunction;

    /**
     * initialize MPU6050, HMC5883L and MS6511
     */
    void initialize();

    void getMotion6(const v8::FunctionCallbackInfo<v8::Value> &args);
    void getMotion9(const v8::FunctionCallbackInfo<v8::Value> &args);
    void setAccelXOffset(int32_t offset);
    void setAccelYOffset(int32_t offset);
    void setAccelZOffset(int32_t offset);
    void setGryoXOffset(int32_t offset);
    void setGryoYOffset(int32_t offset);
    void setGryoZOffset(int32_t offset);
    void setMagXOffset(int32_t offset);
    void setMagYOffset(int32_t offset);
    void setMagZOffset(int32_t offset);
    void setGryoRangeScale(int32_t scale);
    void getGryoRangeScale(const v8::FunctionCallbackInfo<v8::Value> &args);
    void setAccelRangeScale(int32_t scale);
    void getAccelRangeScale(const v8::FunctionCallbackInfo<v8::Value> &args);
    void calibrateMPU6050(const v8::FunctionCallbackInfo<v8::Value> &args);
    void measure(int* m_ax, int* m_ay, int* m_az, int* m_gx, int* m_gy, int* m_gz);
    void getHeadingXYZ(const v8::FunctionCallbackInfo<v8::Value> &args);
    void getHeading(const v8::FunctionCallbackInfo<v8::Value> &args);
    void setMagGain(int32_t gain);
    void getMagGain(const v8::FunctionCallbackInfo<v8::Value> &args);



    MPU6050* mpu6050;
    HMC5883L* hmc5883l;
    MS5611* ms5611;
};

#endif /* RPIGY86_H_ */
