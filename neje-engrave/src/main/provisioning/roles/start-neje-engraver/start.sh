
whoami

pwd

cd /opt/onebeartoe/neje-engrave

pwd

java -jar payara-micro-5.181.jar neje-engrave-0.0.1-SNAPSHOT.war > out.text 2>&1 &

echo $! > pid