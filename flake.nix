{
  description = "Example clang toolchain to compile solutions in this repo";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs =
    inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "aarch64-darwin"
        "x86_64-darwin"
      ];
      perSystem =
        {
          config,
          self',
          inputs',
          pkgs,
          system,
          ...
        }:
        {

          devShells = {
            default = pkgs.mkShell {
              buildInputs = [
                pkgs.clang-tools
                pkgs.clang
              ];
              shellHook = ''
                PATH="${pkgs.clang-tools}/bin:$PATH"
              '';
            };
          };
        };
    };
}
