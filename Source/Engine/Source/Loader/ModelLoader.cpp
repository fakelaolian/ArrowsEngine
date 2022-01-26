/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "ModelLoader.h"

#include "OBJLoader.h"

namespace mloader {

std::vector<mesh_t> load_model(const char *filename)
{
        using namespace objl;
        std::vector<mesh_t> mmeshs;

        Loader loader;
        loader.LoadFile(filename);

        for (Mesh mesh : loader.LoadedMeshes) {
                mesh_t mmesh;

                /* 拷贝OBJLoader的Vertex结构体数据到mesh.vertex */
                mmesh.vertices.resize(mesh.Vertices.size());
                void *src = mesh.Vertices.data();
                void *dst = mmesh.vertices.data();
                memcpy(dst, src, mmesh.vertices.size() * sizeof(vertex_t));

                /* 拷贝OBJLoader的Indices结构体数据到mesh.indices */
                mmesh.indices.resize(mesh.Indices.size());
                src = mesh.Indices.data();
                dst = mmesh.indices.data();
                memcpy(dst, src, mmesh.indices.size() * sizeof(uint32_t));

                mmeshs.push_back(mmesh);
        }

        return mmeshs;
}

}