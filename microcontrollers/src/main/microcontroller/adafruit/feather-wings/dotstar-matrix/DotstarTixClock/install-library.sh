
# update this Arduino library path value to the correct path, if needed
ARDUINO_LIBRARY_DIRECTORY=~/Arduino/libraries/

echo "arduino libary path is:"
echo $ARDUINO_LIBRARY_DIRECTORY

TARGET=`pwd`
echo "target:"
echo $TARGET

ln -s $TARGET $ARDUINO_LIBRARY_DIRECTORY
