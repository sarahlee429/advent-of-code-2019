CompressionService
======

Description
-----------
Implementation of Compression service that handles
1) Ping Requests
2) Get Stats Requests
3) Reset stats requests
4) Compress requests

Platform
-----------
Ubuntu 18.04.3 LTS, C++11 and Boost 1.58 compiled under GCC-7.4

Class Descriptions
------------------

- `Server` - Starts service to accept clients
- `ClientSession` - Handles client requests and processes socket data, updates internal statistics
- `MsgHeader` - Handles serialization and deserialization of message headers.
- `Trie.java` - The data structure that holds information for NGrams language model. The Trie implementation has been altered from traditional character Trie to fit the tasks of this project better.
- `TrieNode.java` - A node class used to construct the Trie.
- `TrieTest.java` - A JUnit test for testing Trie implementation.
- `Unigrams.java` - Implementation of unigrams and the related smoothing features. The classes contains `WORD_MARKER` that specifies end of a word. It can be changed by the user.

How to run
----------

