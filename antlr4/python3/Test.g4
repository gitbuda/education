grammar Test;                   // Define a grammar called Tests
startTest : 'test' ID ( ID )* ; // Match keyword test followed by one or more identifiers.
ID : [a-z]+ ;                   // Match lower-case identifiers.
WS : [ \t\r\n]+ -> skip ;       // Skip spaces, tabs, newlines, \r (Windows).
