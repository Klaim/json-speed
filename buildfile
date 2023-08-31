# Glue buildfile that "pulls" all the packages in the project.
#
import pkgs = [dir_paths] $process.run_regex(\
  cat $src_root/packages.manifest, '\s*location\s*:\s*(\S+)\s*', '\1')

./: $pkgs

define workspace: alias

# platform_file = "build2-configs/windows.options"
# info "platform_file = '$platform_file'"
install_config = "config.install.root=$src_root/install"
common_options = "--options-file=$src_root/build2-configs/common.options"
# platform_options = "--options-file=$src_root/build2-configs/$platform_file"

msvc_debug_config = $src_root/build2-configs/msvc-debug.config
msvc_release_config = $src_root/build2-configs/msvc-release.config
clang_debug_config = $src_root/build2-configs/clang-debug.config
clang_release_config = $src_root/build2-configs/clang-release.config

msvc_release_out = $src_root/build-msvc-release/
msvc_debug_out = $src_root/build-msvc-debug/
clang_release_out = $src_root/build-clang-release/
clang_debug_out = $src_root/build-clang-debug/
build_dirs = $msvc_release_out $msvc_debug_out $clang_release_out $clang_debug_out

workspace{init} :
{{
  diag bdep $src_root
  bdep init --empty
  bdep config create @msvc        -d $src_root/ $msvc_release_out   cc $common_options config.config.load=$msvc_release_config   $install_config/msvc-release
  bdep config create @clang       -d $src_root/ $clang_release_out  cc $common_options config.config.load=$clang_release_config  $install_config/clang-release
  bdep config create @msvc-debug  -d $src_root/ $msvc_debug_out     cc $common_options config.config.load=$msvc_debug_config     $install_config/msvc-debug
  bdep config create @clang-debug -d $src_root/ $clang_debug_out    cc $common_options config.config.load=$clang_debug_config    $install_config/clang-debug
  bdep init --all
}}

workspace{install} :
{{
  diag b $src_root
  b install: $msvc_release_out/readjson-nlohmann/
  b install: $msvc_debug_out/readjson-nlohmann/
  b install: $clang_release_out/readjson-nlohmann/
  b install: $clang_debug_out/readjson-nlohmann/

  b install: $msvc_release_out/readjson-simdjson/
  b install: $msvc_debug_out/readjson-simdjson/
  b install: $clang_release_out/readjson-simdjson/
  b install: $clang_debug_out/readjson-simdjson/
}}

workspace{clear} :
{{
  rm -rf $build_dirs
  rm -rf $src_root/.bdep
}}
