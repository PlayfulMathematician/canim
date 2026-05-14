{
  description = "canim development shell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";

      pkgs = import nixpkgs {
        inherit system;
      };
    in {
      devShells.${system}.default =
        (pkgs.mkShell.override { stdenv = pkgs.gccStdenv; }) {
          nativeBuildInputs = with pkgs; [
            cmake
            ninja
            pkg-config
            gcc
            gdb
            git
            curl
            zip
            unzip
            gnutar
            perl
            python3
          ];

          buildInputs = with pkgs; [
            SDL2
            libglvnd
            libglvnd.dev
            mesa
            xorg.libX11
            xorg.libXext
            xorg.libXrandr
            xorg.libXcursor
            xorg.libXinerama
            xorg.libXi
          ];

          shellHook = ''
            export VCPKG_ROOT="$PWD/.tools/vcpkg"
            export PATH="$VCPKG_ROOT:$PATH"

            export CC="$(command -v gcc)"
            export CXX="$(command -v g++)"

            export PYTHON3="$(command -v python3)"
            export Python3_EXECUTABLE="$PYTHON3"

            export VCPKG_BINARY_SOURCES=clear

            echo "VCPKG_ROOT=$VCPKG_ROOT"
            echo "CC=$CC"
            echo "CXX=$CXX"
            echo "PYTHON3=$PYTHON3"
          '';
        };
    };
}
