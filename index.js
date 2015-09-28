exports.RPiGY86 = require('./lib/binding/rpi_gy86').RPiGY86;
exports.HMC5883L = { 
    GAIN_1370 : 0,  // 0.73 mG/LSb
    GAIN_1090 : 1,  // 0.92 mG/LSb
    GAIN_820  : 2,  // 1.22 mG/LSb
    GAIN_660  : 3,  // 1.52  mG/LSb
    GAIN_440  : 4,  // 2.27  mG/LSb
    GAIN_390  : 5,  // 2.56 mG/LSb
    GAIN_330  : 6,  // 3.03 mG/LSb
    GAIN_230  : 7 };// 4.35 mG/LSb

exports.MPU6050 = {
    GYRO :  { FS_250 : 0,  //  131   LSB/°/s
              FS_500 : 1,  //   65.5 LSB/°/s
              FS_1000: 2,  //   32.8 LSB/°/s
              FS_2000: 3 },//   16.4 LSB/°/s
    ACCEL : { FS_2   : 0,  //  16384 LSB/g
              FS_4   : 1,  //   8192 LSB/g
              FS_8   : 2,  //   4096 LSB/g
              FS_16  : 3 } //   2048 LSB/g
};