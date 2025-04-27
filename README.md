# This is a test task.

It is necessary to develop a console application for finding differences in the contents of two directories.\
It receives parameters from the command line. The result of the work should be a list of files with different\
contents, as well as files that were added or deleted.

### Usage example
```
./dir_diff.exe /tmp/foo /tmp/bar
```

### Output example
```
Comparing directories "/tmp/foo" and "/tmp/bar"...

lorem.txt CHANGED
ipsum.avi CHANGED
dolor/sit/amet.bin ADDED
consectetur/adipiscing.bmp ADDED
semper/dolor.png REMOVED

Comparison finished in 1m 12s. 25 files processed, 2 changed, 2 added, 1 removed
```

### Notes
1. Implementation must be done in C++, standard version in the range from 11 to 20 inclusive.
   * It is desirable, but not necessary, to get a cross-platform solution.
   * It is desirable, but not necessary, to exclude the use of external libraries and implement the solution within the standard C++ library.
   * It is necessary to provide a solution in the form of source code, a project for MS Visual Studio, and all the necessary prerequisites for building it (in case of using non-standard libraries).
   * Optionally, a description of the discovered during development and testing problems unforeseen at the design stage, the methods of their solutions.
2. The application must process the contents of directories of arbitrary nesting.
3. The application must be able to handle files with sizes ranging from 0 B to 8 GB.
4. The contents of the files can be arbitrary: text, graphics, archives, etc.
5. The application must correctly handle access errors to the file system objects.
