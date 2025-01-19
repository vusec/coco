{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs?ref=nixos-24.11&shallow=1";
  inputs.flake-parts.url = "github:hercules-ci/flake-parts";

  outputs = inputs @ {flake-parts, ...}:
    flake-parts.lib.mkFlake {inherit inputs;} {
      flake = {
        # Put your original flake attributes here.
      };
      systems = [
        # systems for which you want to build the `perSystem` attributes
        "x86_64-linux"
        # ...
      ];
      perSystem = {
        config,
        pkgs,
        ...
      }: {
        devShells.default = pkgs.mkShell {
          env.LLVM_CONFIG = "llvm-config";

          hardeningDisable = ["all"];

          buildInputs = with pkgs; [
            (hiPrio (runCommand "clang-14" {} ''
              mkdir -p $out/bin
              ln -s ${llvmPackages_14.clang}/bin/clang $out/bin/clang-14
              ln -s ${llvmPackages_14.libllvm}/bin/opt $out/bin/opt-14
            ''))
            jq
            ccls
            (hiPrio llvmPackages_14.clang-tools)
            alejandra
            llvmPackages_14.libllvm
            llvmPackages_14.clang
            pkg-config
            bear
            gnumake
            (python3.withPackages (ps: [ps.lark ps.llvmlite]))
          ];
        };
      };
    };
}
