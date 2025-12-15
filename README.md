# Tic Tac Toe

Example Tic Tac Toe solver based on cpp-devenv template and using GitHub Actions.

## Build System

- **Overview:** The repository uses a thin `Makefile` to prepare tooling and dependencies, and hands off actual compilation and testing to CMake. You can either drive everything with the Make targets or run CMake directly.

### Quick Start
- Get going fast with the common local flow:

```bash
make prepare-tools
cmake -S . -B work/build
cmake --build work/build
ctest --test-dir work/build --output-on-failure
make style-check-clang
```

### Using Make (recommended)
- **Prepare tools:** sets up a Python venv, installs required Python packages, and builds a minimal local Boost.

```bash
make prepare-tools
```

- **Configure CMake:** generates the build system under `work/build/`.

```bash
cmake -S . -B work/build
```

- **Build:** compiles the project via the CMake-generated build files.

```bash
cmake --build work/build
```

- **Test:** runs tests via CTest in the CMake build tree.

```bash
ctest --test-dir work/build --output-on-failure
```

- **Style checks:** run clang-format in check mode or format mode (clang-format is provided by the venv step).

```bash
make style-check-clang
make style-format-clang
```

- **Clean:** removes the venv and `work/` artifacts. Use `dev-clean` for a deeper git-clean while preserving VS Code settings.

```bash
make clean
make dev-clean
```

### Using CMake directly
- **Configure:** `cmake -S . -B work/build`
- **Build:** `cmake --build work/build`
- **Test:** `ctest --test-dir work/build --output-on-failure`

### Notes
- **Boost:** The `prepare-tools` target builds a minimal Boost into `boost/` and exports `BOOST_ROOTDIR` for CMake to find headers/libs. If you have system Boost installed, you can skip `make boost` and let CMake find your system installation.
- **Artifacts:** All CMake outputs are placed under `work/build/`. Executables like the game and test runners appear in that tree.
- **Help:** See available Make targets via `make help`.

## CI/CD

- **Platform:** GitHub Actions with Ubuntu 24.04 runners.
- **Workflows:**
	- **Build & Test:** [build-test.yml](.github/workflows/build-test.yml)
		- Triggers: push to `main`, pull requests (open/reopen/synchronize/ready_for_review), and `merge_group` checks.
		- Steps: checkout (with submodules), Python setup, install CMake/Ninja, create venv (`make venv`), cache/build Boost (`make boost` if cache miss), CMake configure (`-G Ninja`), build, and run `ctest`.
		- Status: posts commit status via `myrotvorets/set-commit-status-action` using context `build-test-status`.
		- Caching: caches `boost/` keyed by `${{ runner.os }}-boost-${{ env.BOOST_VERSION }}`.
	- **Style Checks:** [style-checks.yml](.github/workflows/style-checks.yml)
		- Triggers: push to `main` and pull requests (open/reopen/synchronize/ready_for_review).
		- Steps: checkout (with submodules), Python setup, venv (`make venv`), run `make style-check-clang`.
		- Status: posts commit status via `myrotvorets/set-commit-status-action` using context `style-check-status`.

- **Conventions:** Both workflows enforce single-run per ref via `concurrency` to cancel in-progress duplicates. They use the repository-local `boost/` directory with `BOOST_ROOT` set so builds are reproducible.

- **Local parity:** The local commands in the Build System section mirror CI steps: configure, build, test, and style checks. If local `make style-check-clang` fails due to `clang-format` availability, re-create the venv (`rm -rf venv && make venv`) to ensure `requirements.txt` is applied.

