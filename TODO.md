* Rename to libol (so linking is -lol ;) )
* Decryption (can just use system zlib)
	* Use system zlib
	* Make the Blowfish code less bad (use vector<uint8_t> instead of string
		* Change API to return vector instead of an out-parameter?
* Keyframe / Chunk decoding
  * Ongoing work
* Figure out if the API could be expressed in a better way (I'm new to C++!)
  * Make more C-friendly?
* Use spectator dumps instead of old replay files
* (Decoupled?) REST API client library
* Better (or any) build system
  * gyp?
  * CMake?
  * Let someone else deal with this
