# Tic Tac Toe

C++17 tic-tac-toe game and solver built on the [cpp-devenv](https://github.com/kbrunham/cpp-devenv) template. Setup, build, test, and CI details live in [README.md](README.md).

## Repository layout

| Path | Purpose |
|------|---------|
| `src/` | Game logic (`GAME_BOARD`, `GAME_MOVE`, `GAME_ENV`, utilities) |
| `main.cpp` | CLI entry point (cxxopts, plog logging) |
| `test/` | GoogleTest unit tests |
| `extern/` | Git submodules (googletest, cxxopts, plog, backward-cpp, cmake_helpers) |
| `boost/` | Local minimal Boost build (created by `make boost`; gitignored) |
| `work/build/` | CMake build tree (gitignored) |

## Setup, build, and test

Follow [README.md — Build System](README.md#build-system) for the full workflow. Minimum steps:

1. `make dev-update` — initialize submodules
2. `make prepare-tools` — Python venv + local Boost 1.86
3. Configure, build, and test under `work/build/` (see README Quick Start)

Executables: `./work/build/main` (game), `./work/build/main_test1` (tests).

Dev container: Ubuntu 24.04 C++ image (`.devcontainer/`). Run setup after the container starts. Honor `http_proxy` / `https_proxy` when set (surfaced via `devcontainer.json`).

## Style

Formatting uses `.clang-format` (Microsoft-based style). Run `make style-check-clang` before proposing changes and `make style-format-clang` to auto-format. See [README.md](README.md#build-system) for details.

## Make targets

| Target | Description |
|--------|-------------|
| `make prepare-tools` | `venv` + `boost` |
| `make venv` | Python venv with `clang-format` |
| `make boost` | Download and build minimal Boost into `boost/` |
| `make dev-update` | `git submodule update --init --recursive` |
| `make clean` | Remove `venv/` and `work/` |
| `make dev-clean` | Deep `git clean` (preserves `.vscode/`) |
| `make help` | List Make targets |

## Dependencies

- **C++17** (required)
- **Boost 1.86** — filesystem and regex, static link; built locally or via `BOOST_ROOT`
- **Submodules** — GoogleTest, cxxopts, plog, backward-cpp, cmake_helpers

## Planned work

See [TODO.md](TODO.md) for tracked TODO items in the codebase.

## Code conventions

- Match existing style: `enum class` and class names in `SCREAMING_SNAKE` (e.g. `GAME_PLAYER`, `GAME_BOARD`).
- Use `CMN_ASSERT` from `src/cmn.h` for internal assertions.
- Keep changes minimal; avoid one-letter variable names.
- Do not add license or copyright headers to source files.
- Avoid inline comments unless requested; prefer clear code and existing Doxygen-style block comments where already used.

## CI/CD

See [README.md — CI/CD](README.md#cicd). Workflows in `.github/workflows/`:

- **build-test.yml** — submodules, venv, cached Boost, Ninja build, CTest (`build-test-status`)
- **style-checks.yml** — `make style-check-clang` (`style-check-status`)

## Change management

- Branch from `main`; open PRs rather than pushing directly to protected branches.
- Include summary, rationale, and validation steps in PRs.
- Run local build, tests, and `make style-check-clang` before requesting review; CI must pass.
- Code owner: `@kalen` (see `.github/CODEOWNERS`).

## Troubleshooting

- **Submodules missing / CMake can't find extern:** `make dev-update`
- **Boost not found:** `make boost` or set `BOOST_ROOT` to a system install (CMake default: `./boost`)
- **`clang-format` missing:** `rm -rf venv && make venv`
- **Network/proxy issues:** ensure `http_proxy` / `https_proxy` are set
- **Dev container `BASH_FUNC_*` export error:** usually caused by exported shell functions (e.g. custom `mcd`) in the host `~/.bashrc` being passed into the container; unset or remove `export -f` for those functions on the host

## Prohibited actions

- No force pushes to shared branches.
- No unrelated large refactors without explicit request.
- No secrets or tokens committed to the repo.
