{ pkgs }: {
    deps = [
        # Compiling tools
        pkgs.gnumake
        pkgs.gcc

        # Mandatory native graphics development dep
        pkgs.xorg.libX11

        # actual libraries the program uses
        ## font rendering
        pkgs.freetype
        pkgs.ftgl

        ## OpenGL GFX libs
        pkgs.libglvnd
        pkgs.libglvnd.dev
        pkgs.libGLU
        pkgs.libGLU.dev
        pkgs.glfw2
        pkgs.glm
    ];
  env = {
    LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
      "deps"
      pkgs.libglvnd
      pkgs.glfw2
      pkgs.glm
      pkgs.libGLU
      pkgs.freetype
      pkgs.ftgl
      pkgs.xorg.libX11
    ];
  };
}