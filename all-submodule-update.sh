#!/bin/bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
TARGET_COMMIT="${1:-origin/main}"

REPOS_WITH_SUBMODULES=(
  "blender-nozzle:nozzle"
  "jit.nozzle:deps/nozzle"
  "nozzle-sokol:nozzle"
  "nozzle-TOP:libs/nozzle"
  "nozzle.rs:nozzle"
  "nozzle.swift:deps/nozzle"
  "nozzle.unity:nozzle"
  "obs-nozzle:nozzle"
  "ofxNozzle:libs/nozzle"
  "py.nozzle:libs/nozzle"
  "tcxNozzle:nozzle"
)

echo "Updating all nozzle submodules to $TARGET_COMMIT"
echo ""

for entry in "${REPOS_WITH_SUBMODULES[@]}"; do
  repo="${entry%%:*}"
  sub="${entry##*:}"
  repo_path="$REPO_ROOT/$repo"

  if [ ! -d "$repo_path/.git" ]; then
    echo "SKIP $repo (not a git repo)"
    continue
  fi

  sub_path="$repo_path/$sub"
  if [ ! -d "$sub_path/.git" ]; then
    echo "SKIP $repo (submodule $sub not found)"
    continue
  fi

  echo "=== $repo ($sub) ==="
  cd "$sub_path"
  git fetch origin 2>&1 | sed 's/^/  /'
  git checkout "$TARGET_COMMIT" 2>&1 | sed 's/^/  /'

  cd "$repo_path"
  if git diff --quiet --cached "$sub" && git diff --quiet "$sub"; then
    echo "  already up to date"
  else
    git add "$sub"
    git commit -m "chore: update nozzle submodule to $(git -C "$sub_path" log --oneline -1 --format='%h %s')"
    echo "  committed"
  fi
  echo ""
done

echo "Done. Run 'git push' in each repo to publish."
