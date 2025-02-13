{
  description = "shared flake-parts template";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-parts.url = "github:hercules-ci/flake-parts";

    git-hooks-nix = {
      url = "github:cachix/git-hooks.nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    treefmt-nix.url = "github:numtide/treefmt-nix";
  };

  outputs = inputs @ {
    flake-parts,
    git-hooks-nix,
    treefmt-nix,
    ...
  }:
    flake-parts.lib.mkFlake {inherit inputs;} {
      systems = [
        "x86_64-linux"
        "aarch64-darwin"
        "aarch64-linux"
      ];

      imports = [
        git-hooks-nix.flakeModule
        treefmt-nix.flakeModule
        flake-parts.flakeModules.easyOverlay
        ./flake-module.nix
      ];

      perSystem = {config, ...}: {
        treefmt.settings.global = {
          on-unmatched = "debug";
          excludes = [
            ".git"
            "*.lock"
            ".gitignore"
          ];
        };

        pre-commit.settings.hooks.treefmt = {
          enable = true;
          packageOverrides.treefmt = config.treefmt.build.wrapper;
        };
      };
    };
}
