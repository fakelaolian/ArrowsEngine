/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "ModelLoader.h"

#include "OBJLoader.h"

namespace arosloader {

std::vector<mesh_t> load_model(const char *filename, std::vector<mesh_t> &mmeshs)
{
        using namespace objl;

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

                /* 拷贝材质 */
                mmesh.material.ns     = mesh.MeshMaterial.Ns;
                mmesh.material.ka[0]  = mesh.MeshMaterial.Ka.X;
                mmesh.material.ka[1]  = mesh.MeshMaterial.Ka.Y;
                mmesh.material.ka[2]  = mesh.MeshMaterial.Ka.Z;
                mmesh.material.kd[0]  = mesh.MeshMaterial.Kd.X;
                mmesh.material.kd[1]  = mesh.MeshMaterial.Kd.Y;
                mmesh.material.kd[2]  = mesh.MeshMaterial.Kd.Z;
                mmesh.material.ks[0]  = mesh.MeshMaterial.Ks.X;
                mmesh.material.ks[1]  = mesh.MeshMaterial.Ks.Y;
                mmesh.material.ks[2]  = mesh.MeshMaterial.Ks.Z;
                mmesh.material.ni     = mesh.MeshMaterial.Ni;
                mmesh.material.d      = mesh.MeshMaterial.d;
                mmesh.material.illum  = mesh.MeshMaterial.illum;
                mmesh.material.map_kd = mesh.MeshMaterial.map_Kd;
                mmesh.material.map_bump = mesh.MeshMaterial.map_bump;
                mmesh.material.map_ks = mesh.MeshMaterial.map_Ks;

                mmesh.name            = mesh.MeshName;

                mmeshs.push_back(mmesh);
        }

        return mmeshs;
}

}