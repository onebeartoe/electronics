
openssl x509 -in <(openssl s_client -connect io.adafruit.com:443 -prexit 2>/dev/null) -out /tmp/example.crt

sudo keytool -importcert  -file /tmp/example.crt  -alias adafruit-io  -keystore /opt/jdk/oracle/jdk1.8.0_31/jre/lib/security/cacerts -storepass changeit
