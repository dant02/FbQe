:: %1 expecting value debug or release

SC QUERY FirebirdServerDefaultInstance | FIND "STOPPED"
IF NOT ERRORLEVEL 1 GOTO restart

ECHO "STOP the service..."
SC STOP FirebirdServerDefaultInstance
ECHO "Waiting for service to stop..."

:loop
SC QUERY FirebirdServerDefaultInstance | FIND "STOPPED"
IF ERRORLEVEL 1 (
  TIMEOUT 3 /nobreak
  GOTO loop
)

:restart
ECHO "Service is stopped."
ECHO "Starting service..."
SC START FirebirdServerDefaultInstance

XCOPY x64\%1\fbqe.dll c:\fb\plugins\udr /Y
