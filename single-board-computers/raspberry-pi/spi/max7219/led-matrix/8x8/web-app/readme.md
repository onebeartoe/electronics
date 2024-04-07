

This Project Uses a Raspberry Pi Model B

and

depends on Pi4J version 1.2

    Pi4J version 3.2 was tried but SPI did not seem to work with a Model B 

        and gave the following error with version 3.2

            UnsatisfiedLinkError = libpi4j-pigpio.so


Debugging in Netbeans

    Some of this was used to debug in netbeans

        https://stackoverflow.com/a/41633184/803890


    Be sure to use the instructions values for Spring Boot version 2.x

        Execute Goals:
            spring-boot:run


        Set Properties:
            spring-boot.run.jvmArguments=-Xdebug -Xrunjdwp:transport=dt_socket,server=n,address=${jpda.address}
            jpda.listen=true

        