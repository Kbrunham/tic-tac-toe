make# Agent Instructions

Purpose: This file guides automation agents (CI, bots, local assistants) interacting with this repository to operate safely and consistently.

## Operating Principles
- Be safe: avoid destructive actions (no `git reset --hard`, no force-push) unless explicitly requested by the user.
- Be concise: prefer minimal, targeted changes; keep diffs focused.
- Be reproducible: use documented build and test commands; rely on local `boost/` when possible.
- Respect style: run style checks before proposing changes.
- Preserve history: open PRs from branches; never commit directly to protected branches.

## Environment
- OS: Ubuntu 24.04 (locally in dev container and CI runners).
- Proxies: honor environment variables `http_proxy` and `https_proxy` if present. Dev container surfaces these via `.devcontainer/devcontainer.json`.
- Python venv: use `venv` at repository root created by `make venv`.

## Build & Test
- Configure:
  - `cmake -S . -B work/build`
- Build:
  - `cmake --build work/build`
- Test:
  - `ctest --test-dir work/build --output-on-failure`

## Make Targets
- Tooling: `make prepare-tools` (sets up venv and builds minimal Boost).
- Style:
  - Check: `make style-check-clang`
  - Format: `make style-format-clang`
- Clean:
  - Local: `make clean` (removes `venv` and `work/`).
  - Deep: `make dev-clean` (git clean with safe excludes).
- Submodules: `make dev-update`.

## CI/CD Reference
- Workflows live in `.github/workflows/`:
  - `build-test.yml`: CMake+Ninja build and CTest, caches `boost/`.
  - `style-checks.yml`: runs clang-format check.
- Both use concurrency to cancel duplicate runs and post commit statuses via `myrotvorets/set-commit-status-action`.

## Change Management
- Branching: create feature branches off the current default working branch.
- PRs: ensure PRs include a summary, rationale, and validation steps.
- Tests: run local tests and style checks; CI must pass.

## File and Code Guidelines
- Keep changes minimal and aligned with existing code style.
- Avoid one-letter variable names.
- Do not add license or copyright headers.
- Avoid inline comments unless explicitly requested; use clear code.

## Troubleshooting
- If `clang-format` fails to execute from venv, recreate venv:
  - `rm -rf venv && make venv`
- If Boost is missing, run `make boost` or ensure system Boost is discoverable.
- For network constraints, ensure `http_proxy`/`https_proxy` are correctly set in your environment.

## Prohibited Actions
- No force pushes to shared branches.
- No modifying unrelated files or large-scale refactors without explicit request.
- No external secrets or tokens committed to the repo.

## Contact
- For questions or edge cases, open an issue or draft PR describing the proposal and constraints.