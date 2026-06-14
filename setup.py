from os import system
import os.path
import sys

def curl_download(url, output_path):
    if not os.path.exists(output_path):
        print(f"downloading {url} to {output_path}...")
        cmd(f"curl -L {url} -o {output_path}")
    else:
        print(f"{output_path} already exists, skipping download.")
def wget_download(url, output_path):
    if not os.path.exists(output_path):
        print(f"downloading {url} to {output_path}...")
        cmd(f"wget -O {output_path} {url}")
    else:
        print(f"{output_path} already exists, skipping download.")
def submake(directory, num_jobs=4, target=None):
    cmd(f"cd {directory} && make -j{num_jobs} {target if target else ''}")
    
def cmd(command):
    val = system(command)
    if val != 0:
        print(f"command failed: {command}")
        exit(val)
def install_assimp():
    if not os.path.exists("lib/assimp"):
        print("creating lib/assimp directory...")
        os.makedirs("lib/assimp")
    if os.path.exists("lib/assimp/build/bin/libassimp.so.6.0.5"):
        print("assimp already installed.")
        return
    curl_download("https://github.com/assimp/assimp/archive/refs/tags/v6.0.5.zip", "lib/assimp/assimp.zip")
    print("installing assimp...")
    cmd("unzip -o lib/assimp/assimp.zip -d lib/assimp")
    cmd("mv -n lib/assimp/assimp-6.0.5/* lib/assimp")
    print("bulding assimp...")
    cmd("cd lib/assimp && cmake CMakeLists.txt -B build -DASSIMP_WARNINGS_AS_ERRORS=OFF")
    submake("lib/assimp/build")
    print("assimp Install complete.")
    
def install_freetype():
    if not os.path.exists("lib/ft2"):
        print("creating lib/ft2 directory...")
        os.makedirs("lib/ft2")
    if os.path.exists("lib/ft2/objs/.libs/libfreetype.so.6.20.6"):
        print("freetype already installed.")
        return
    wget_download("https://download.savannah.gnu.org/releases/freetype/freetype-2.14.3.tar.gz", "lib/ft2/ft2.tar.gz")
    print("installing freetype...")
    cmd("tar -xvzf lib/ft2/ft2.tar.gz -C lib/ft2")
    cmd("mv -n lib/ft2/freetype-2.14.3/* lib/ft2")
    print("building freetype...")
    submake("lib/ft2")
    submake("lib/ft2", target="library")
    print("freetype Install complete.")
    
def install_glad():
    if not os.path.exists("lib/glad"):
        print("creating lib/glad directory...")
        os.makedirs("lib/glad")
    if os.path.exists("lib/glad/build/src/gl.c"):
        print("glad already installed.")
        return
    wget_download("https://github.com/Dav1dde/glad/archive/refs/heads/glad2.zip", "lib/glad/glad.zip")
    print("installing glad...")
    cmd("unzip -o lib/glad/glad.zip -d lib/glad")
    cmd("mv -n lib/glad/glad-glad2/* lib/glad")
    print("bulding glad...")
    cmd("python -m venv lib/glad/venv")
    cmd("lib/glad/venv/bin/pip install -r lib/glad/requirements.txt")
    cmd("cd lib/glad && venv/bin/python -m glad --out-path=build --api=gl:core=4.3 c --loader")
    print("glad Install complete.")
    
def install_glfw():
    if not os.path.exists("lib/glfw"):
        print("creating lib/glfw directory...")
        os.makedirs("lib/glfw")
    if os.path.exists("lib/glfw/build/src/libglfw.so.3.4"):
        print("glfw already installed.")
        return
    curl_download("https://api.github.com/repos/glfw/glfw/releases/tags/3.4", "lib/glfw/assets.json")
    print("installing glfw...")
    cmd("python download_json.py lib/glfw/assets.json")
    if sys.platform == 'win32':
        print("win32 not implemented")
        exit(-1)
    if sys.platform == 'win64':
        print("win32 not implemented")
        exit(-1)
    if sys.platform == 'linux':
        cmd("unzip -o lib/glfw/glfw-3.4.zip -d lib/glfw/")
        cmd("mv -n lib/glfw/glfw-3.4/* lib/glfw/")
        cmd("rm -rf lib/glfw/glfw-3.4")
        print("prebuilding glfw...")
        cmd("cd lib/glfw && cmake -B build -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=ON -D GLFW_BUILD_EXAMPLES=OFF -D GLFW_BUILD_TESTS=OFF -D GLFW_BUILD_DOCS=OFF")
        print("bulding glfw...")
        submake("lib/glfw/build")
    if sys.platform == 'darwin':
        print("win32 not implemented")
        exit(-1)
    print("glfw Install complete.")

def install_glm():
    if not os.path.exists("lib/glm"):
        print("creating lib/glm directory...")
        os.makedirs("lib/glm")
    if os.path.exists("lib/glm/build/glm/libglm.so"):
        print("glm already installed.")
        return
    curl_download("https://api.github.com/repos/g-truc/glm/releases/tags/1.0.2", "lib/glm/assets.json")
    print("installing glm...")
    cmd("python download_json.py lib/glm/assets.json")
    cmd("unzip -o lib/glm/glm-1.0.2.zip -d lib")
    print("building glm...")
    cmd("cd lib/glm && cmake -B build -DGLM_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=ON")
    submake("lib/glm/build")
    print("glm install complete.")

def install_resource_manager():
    if not os.path.exists("lib/resource-manager"):
        print("creating lib/resource-manager directory...")
        os.makedirs("lib/resource-manager")
    if os.path.exists("lib/resource-manager/bin/libresourcemanager.so"):
        print("resource-manager already installed.")
        return
    curl_download("https://github.com/davidporras31/Resource-Manager/archive/refs/heads/main.zip", "lib/resource-manager/resource-manager.zip")
    print("installing resource-manager...")
    cmd("unzip -o lib/resource-manager/resource-manager.zip -d lib/resource-manager")
    cmd("mv -n lib/resource-manager/Resource-Manager-main/* lib/resource-manager")
    cmd("rm -rf lib/resource-manager/Resource-Manager-main")
    print("building resource-manager...")
    submake("lib/resource-manager", target="BUILD_SHARED_LIBS=ON")
    print("resource-manager install complete.")

def install_shader_precompiler():
    if not os.path.exists("lib/shader-precompiler"):
        print("creating lib/shader-precompiler directory...")
        os.makedirs("lib/shader-precompiler")
    if os.path.exists("lib/shader-precompiler/ShaderPrecompiler.h"):
        print("shader-precompiler already installed.")
        return
    curl_download("https://github.com/davidporras31/shader-precompiler/archive/refs/heads/main.zip", "lib/shader-precompiler/shader-precompiler.zip")
    print("installing shader-precompiler...")
    cmd("unzip -o lib/shader-precompiler/shader-precompiler.zip -d lib/shader-precompiler")
    cmd("mv -n lib/shader-precompiler/shader-precompiler-main/* lib/shader-precompiler")
    cmd("rm -rf lib/shader-precompiler/shader-precompiler-main")
    print("shader-precompiler install complete.")

def install_stb():
    if not os.path.exists("lib/stb"):
        print("creating lib/stb directory...")
        os.makedirs("lib/stb")
    if os.path.exists("lib/stb/stb/stb_image.h"):
        print("stb already installed.")
        return
    curl_download("https://github.com/nothings/stb/archive/refs/heads/master.zip", "lib/stb/stb.zip")
    print("installing stb...")
    cmd("unzip -o lib/stb/stb.zip -d lib/stb")
    cmd("mkdir -p lib/stb/stb")
    cmd("mv -n lib/stb/stb-master/* lib/stb/stb")
    cmd("rm -rf lib/stb/stb-master")
    print("stb Install complete.")

def main():
    print("installing dependencies...")
    if not os.path.exists("lib"):
        print("creating lib directory...")
        os.makedirs("lib")
    install_assimp()
    install_freetype()
    install_glad()
    install_glfw()
    install_glm()
    install_resource_manager()
    install_shader_precompiler()
    install_stb()

if __name__ == "__main__":
    main()