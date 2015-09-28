{
  'conditions': [
    ['OS=="linux"', {
      'targets': [

        {
          'target_name': 'rpi_gy86',
          'sources': ['./src/RPIGY86.cpp'],
          'dependencies': ['rpi_libgy86'],
          'include_dirs': ['<!(node -e "require(\'nan\')")']
        },

        {
          'target_name': 'rpi_libgy86',
          'type': 'static_library',
          'sources': [
            './src/I2Cdev/I2Cdev.cpp',
            './src/MPU6050/MPU6050.cpp',
            './src/HMC5883L/HMC5883L.cpp',
            './src/MS5611/MS5611.cpp',
          ],
          'include_dirs': ['./include'],
          'cflags': ['-O2', '-Wall']
        },

        {
          'target_name':'action_after_build',
          'type': 'none',
          'dependencies': ['rpi_gy86'],
          'copies': [{
            'destination': './lib/binding/',
            'files': [
              '<(PRODUCT_DIR)/rpi_gy86.node'
            ]
          }]
        }
      ]
    }, { # OS != linux
      'targets': [{
        'target_name': 'rpi-gy86',
        'actions': [{
          'action_name': 'not_supported_msg',
          'inputs': [],
          'outputs': [ '--nothing-being-built--' ],
          'action': ['true'],
          'message': '**** YOU ARE INSTALLING THIS MODULE ON AN UNSUPPORTED PLATFORM ****'
        }]
      }]
    }]
  ]
}
