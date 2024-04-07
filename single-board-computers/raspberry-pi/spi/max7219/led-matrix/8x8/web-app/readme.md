


Debugging in Netbeans

    Some of this was used to debug in netbeans

        https://stackoverflow.com/a/41633184/803890


    Be sure to use the instructions values for Spring Boot version 2.x

        Execute Goals:
            spring-boot:run


        Set Properties:
            spring-boot.run.jvmArguments=-Xdebug -Xrunjdwp:transport=dt_socket,server=n,address=${jpda.address}
            jpda.listen=true

        