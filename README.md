### Important
Make sure you're compiling with C++20 or above.
Example args in default tasks.json:

```c++
"args": [
                "-fdiagnostics-color=always",
                "-g",
                "-std=c++23", //version specifier, necessary. not present by default
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
```