 make
 sudo ldconfig --verbose # So the test executeables can detect libtinyxml2
 if [ $BUILD_CORE_ONLY = OFF ]; then make test; fi
 # cd tools/
 # ./code_check.sh
 # ./abi_check.sh 4.1.0  # Check with DART 4.1.0