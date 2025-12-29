-- example script to declare functions of the plugin
-- Firebird 5.0.3

CREATE FUNCTION GetCurrentTimestampUTC() RETURNS TIMESTAMP EXTERNAL NAME 'FbQe!GetCurrentTimestampUTC' ENGINE UDR;
