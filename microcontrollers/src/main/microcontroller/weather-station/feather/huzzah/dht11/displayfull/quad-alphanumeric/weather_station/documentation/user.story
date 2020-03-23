
FilesystemWatcher - User Story(ies) 

This project has multiple use cases as follows:

As a test driven develper,
I need a tool to watch source code files,
so that unit tests are run when production code changes
    * applies to Java, OpenSCAD, C++, etc files

As a disk qoata contstrained developer, 
I need a tool to watch files under a filesystem direcory,
so that an alert is produced if the file size limit is reached.

As a content writer,
I need a tool to watch document files,
so that I am alerted when a word count limit is reached.

Acceptance Criteria Categories:

    Quiet Periods - AC06, AC09

    RunProfileParams - AC01, AC02, AC03, AC04, AC05, AC07, AC08,

Acceptance Criteria:

01) The runtime profile is configurable via command line arguments (a list of strings).

02) The run profile is configurable via a properties file specified by a command line argument.
        * test with minimal and full profile

03) If a configuration properties file is specified with any other command line arguments, then an exception is 
    thrown and the app only prints the usage message.

04) A FilesystemWatcherRunProfile parameter is configurable that specifies its log file.

05) Every filename pattern must have a corresponding command parameter.

06) A 'quiet period' elapses before the command is executed for any given file pattern.

07) The default quiet period is 30 seconds.

08) A custom quiet period is configured for any file pattern via a command line argument or in a properties file.
        (quietPeriod=5m, quiet Period4=1m)

09) The quiet period for a file pattern is restarted if any matching file's content or last modified date
    changes.



