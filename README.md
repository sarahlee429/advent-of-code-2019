CompressionService
======

Description
-----------
Target Platform : Ubuntu 18.04.3 LTS, C++11 and Boost 1.58 compiled under GCC-7.4
Implementation of Compression service that handles
1) Ping Requests
2) Get Stats Requests
3) Reset stats Requests
4) Compress Requests

`ClientSession` contains the request/response processing. Boost `system` was used for the `asio` networking library support to handle tcp operations. `program options` used for command line argument parsing.


Class Descriptions
------------------

- `Server` - Starts service to accept clients
- `ClientSession` - Handles client requests and processes socket data, updates internal statistics
- `MsgHeader` - Handles serialization and deserialization of message headers.
- `GetstatsResonse` - Handles serialization of get stats response.
- `CompressResonse` - Handles serialization of compress response.


How to run
----------

```
./build.sh
./run.sh
```
