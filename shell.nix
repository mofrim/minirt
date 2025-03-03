{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  name = "minirt";

  buildInputs = with pkgs; [
    libbsd
    xorg.libXext
    xorg.libX11.dev
    qt5.qtwayland
    clang_12
    # clang12Stdenv
  ];

  shellHook = ''
    NIX11="${pkgs.xorg.libX11.dev}/include"
    QT_QPA_PLATFORM=wayland
  '';
}
