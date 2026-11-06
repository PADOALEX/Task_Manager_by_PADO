# Priority task manager

[![C++ CI](https://github.com/PADOALEX/Task_Manager_by_PADO/actions/workflows/ci.yml/badge.svg)](https://github.com/PADOALEX/Task_Manager_by_PADO/actions/workflows/ci.yml)

A small C++17 console exercise for pending tasks, priority execution, editing and text-file persistence. HIGH tasks execute before MEDIUM and LOW, with insertion order preserved within each priority.

One collection is the source of truth for listing, editing, execution and saving. Executed tasks are removed and do not return after restarting. Both startup and save use `tasks.txt` in the current directory. Invalid or incomplete records fail before replacing the in-memory collection or overwriting the input file.

## Build and test

On Windows, install Visual Studio with Desktop development with C++, CMake 3.20+ and Python 3.12+:

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
.\build\Release\app.exe
```

The Visual Studio solution remains available. With a single-configuration generator, use `-DCMAKE_BUILD_TYPE=Release` and run `build/app.exe`. CTest drives the actual executable in temporary directories and verifies priority, edits, save/reload, completed-task removal, malformed records and EOF.

## Storage and limits

Each pending task uses three lines: priority (`HIGH`, `MEDIUM`, `LOW`), title and description. Titles must be nonempty; fields are single-line. The legacy `aboba.txt` startup mismatch is removed; existing records already saved in `tasks.txt` retain their format. The console interface now uses English prompts. This single-user exercise has no database, authentication, concurrent writers or crash-safe storage.
