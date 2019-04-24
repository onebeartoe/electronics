
java -jar \
     -Djava.library.path=/usr/lib/jni/ \
     target/cli-0.0.1-SNAPSHOT.jar \
     --propertiesPath /home/roberto/Workspace/owner/arduino/secret.properties \
     --portName /dev/ttyACM0

printf "\n"
