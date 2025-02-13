_: {
  flake.hardware.keyboard.qmk.enable = true;
  perSystem = {
    config,
    pkgs,
    ...
  }: {
    overlayAttrs = {
      inherit (config.packages) default;
    };

    treefmt.programs.clang-format.enable = true;
    pre-commit.settings.hooks.clang-tidy.enable = true;

    devShells.default = pkgs.mkShell {
      shellHook = ''
        ${config.pre-commit.installationScript}
      '';
      packages = with pkgs; [
        stdenv
        gnumake
        ccls
        cmake
        clang
        pkg-config
        gdb
        valgrind
        via
        vial
        qmk
      ];
      buildInputs = config.pre-commit.settings.enabledPackages;
    };
  };
}
