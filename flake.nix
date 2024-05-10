{
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-23.11";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = {...} @ inputs:
    inputs.utils.lib.eachDefaultSystem (system: let
      pkgs = import inputs.nixpkgs {inherit system;};
    in {
      devShell = pkgs.mkShell {
        packages = with pkgs; [
          cmake
          emscripten

          ninja
          python3

          SDL2
        ];

        CMAKE_TOOLCHAIN_FILE = "${pkgs.emscripten}/share/emscripten/cmake/Modules/Platform/Emscripten.cmake";

        # Emscripten will try to write to the cache in nix store, copy it here so it's writable
        shellHook = ''
          export EM_CACHE=$(git rev-parse --show-toplevel)/.em_cache
          ls $EM_CACHE 2>/dev/null | exit
          cp -r ${pkgs.emscripten}/share/emscripten/cache $EM_CACHE
          chmod u+rwx -R $EM_CACHE
        '';
      };

      formatter = pkgs.alejandra;
    });
}
