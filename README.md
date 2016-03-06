this uses https://github.com/OpenKinect/libfreenect/ library,
copy the folder to library folder, then add this subdirectory to library CMakeLists.txt


```
...
add_subdirectory(KinectDemo) #name of this directory inside parentheses
``` 

folder scheme:

```
libfreenect/
* KinectDemo/
*   CMakeLists.txt
*   sourcefiles...
* other-directories/
* CMakeLists.txt
```
