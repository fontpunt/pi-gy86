var RPiGY86 = require('./index.js').RPiGY86;


var gy86 = new RPiGY86();

//var offsets = gy86.calibrateMPU6050();

////gy86.setAccelXOffset(offsets[0]);
////gy86.setAccelYOffset(offsets[1]);
////gy86.setAccelZOffset(offsets[2]);
////gy86.setGryoXOffset(offsets[3]);
////gy86.setGryoYOffset(offsets[4]);
////gy86.setGryoZOffset(offsets[5]);

gy86.setMagXOffset(-222);
gy86.setMagYOffset(74);

var data = gy86.getMotion6();
console.error(data);

console.error(gy86.getAccelRangeScale());
console.error(gy86.getGryoRangeScale());
console.error(gy86.getMagGain());
console.error(gy86.getHeading());

