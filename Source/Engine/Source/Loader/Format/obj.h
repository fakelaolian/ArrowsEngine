/* AUTHOR: 2BKBD, DATE: 2022/1/17 */
namespace anci {

#       define READ_STAGE_NONE     0
#       define READ_STAGE_VERTEX   1
#       define READ_STAGE_TEXCOORD 2
#       define READ_STAGE_NORMAL   3
#       define READ_STAGE_OBJECT   4
#       define READ_STAGE_MATERIAL 5
#       define READ_STAGE_FACE     6
#       define READ_STAGE_USEMAT   7
#       define READ_STAGE_SMOOTH   8

        struct AllVtx {
                std::vector<float> vertices;
                std::vector<float> texcoords;
                std::vector<float> normals;
        };

        struct Vtxface {
                std::vector<int> faces;
        };

        inline void load_obj_check_stage(const std::string& line, unsigned int &stage, int& objectIndex)
        {
                if (line.rfind("v ") == 0) {
                        stage = READ_STAGE_VERTEX;
                        return;
                }

                if (line.rfind("vt ") == 0) {
                        stage = READ_STAGE_TEXCOORD;
                        return;
                }

                if (line.rfind("vn ") == 0) {
                        stage = READ_STAGE_NORMAL;
                        return;
                }

                if (line.rfind("f ") == 0) {
                        stage = READ_STAGE_FACE;
                        return;
                }

                if (line.rfind("usemtl ") == 0) {
                        stage = READ_STAGE_USEMAT;
                        return;
                }

                if (line.rfind("o ") == 0) {
                        stage = READ_STAGE_OBJECT;
                        objectIndex++;
                        return;
                }

                if (line.rfind("s ") == 0) {
                        stage = READ_STAGE_SMOOTH;
                        return;
                }

                if (line.rfind("#") == 0) {
                        stage = READ_STAGE_NONE;
                        return;
                }
        }

        inline void load_obj_parse_line(std::string &line, unsigned int stage, Vtxface &vtxFaces, AllVtx& vtxs)
        {
                if (stage == READ_STAGE_VERTEX) {
                        std::vector<std::string> vertex;
                        StringUtils::split(line, " ", vertex);
                        vtxs.vertices.push_back(std::stof(vertex[1]));
                        vtxs.vertices.push_back(std::stof(vertex[2]));
                        vtxs.vertices.push_back(std::stof(vertex[3]));
                        return;
                }

                if (stage == READ_STAGE_NORMAL) {
                        std::vector<std::string> normals;
                        StringUtils::split(line, " ", normals);
                        vtxs.normals.push_back(std::stof(normals[1]));
                        vtxs.normals.push_back(std::stof(normals[2]));
                        vtxs.normals.push_back(std::stof(normals[3]));
                        return;
                }

                if (stage == READ_STAGE_TEXCOORD) {
                        std::vector<std::string> texCoords;
                        StringUtils::split(line, " ", texCoords);
                        vtxs.texcoords.push_back(std::stof(texCoords[1]));
                        vtxs.texcoords.push_back(std::stof(texCoords[2]));
                        return;
                }

                if (stage == READ_STAGE_FACE) {
                        std::vector<std::string> faces;
                        StringUtils::split(line, " ", faces);

                        std::vector<std::string> face;
                        for (int i = 1; i < faces.size(); i++) {
                                face.clear();
                                StringUtils::split(faces[i], "/", face);
                                vtxFaces.faces.push_back(std::stoi(face[0]));
                                vtxFaces.faces.push_back(std::stoi(face[1]));
                                vtxFaces.faces.push_back(std::stoi(face[2]));
                        }

                        return;
                }

                if (stage == READ_STAGE_MATERIAL) {
                        return;
                }
        }

        inline attribute_t *load_model_obj(const char *filename)
        {
                std::string line;
                std::ifstream file(filename, std::ios::in);

                unsigned int stage = READ_STAGE_NONE;

                AllVtx allVtx;
                attribute_t *attribute = new attribute_t();

                int objectIndex = -1;
                std::vector<Vtxface> vtxFaces{10};

                while(!file.eof()) {
                        /* 读取一行模型文件 */
                        std::getline(file, line);
                        /* 检查当前模型读取阶段 */
                        load_obj_check_stage(line, stage, objectIndex);
                        /* 解析obj文本行 */
                        load_obj_parse_line(line, stage, vtxFaces[objectIndex], allVtx);
                }

                allVtx.vertices.insert(allVtx.vertices.begin(), 0);
                allVtx.texcoords.insert(allVtx.texcoords.begin(), 0);
                allVtx.normals.insert(allVtx.normals.begin(), 0);

                for (int i = 0; i < (objectIndex + 1); i++) {
                        std::vector<int>& face = vtxFaces[i].faces;

                        for (int j = 0; j < face.size(); j++) {
                                int vtxIdx = face[j + 0] * 3;
                                int texcIdx = face[j + 1] * 2;
                                int normIdx = face[j + 2] * 3;

                                mesh_t mesh;
                                vertex_t vertex;

                                vertex.pos[0] = allVtx.vertices[vtxIdx - 2];
                                vertex.pos[1] = allVtx.vertices[vtxIdx - 1];
                                vertex.pos[2] = allVtx.vertices[vtxIdx - 0];

                                vertex.uv[0] = allVtx.texcoords[texcIdx - 1];
                                vertex.uv[1] = allVtx.texcoords[texcIdx - 0];

                                vertex.normal[0] = allVtx.normals[normIdx - 2];
                                vertex.normal[1] = allVtx.normals[normIdx - 1];
                                vertex.normal[2] = allVtx.normals[normIdx - 0];

                                mesh.vertices.push_back(vertex);
                                attribute->meshs.push_back(mesh);

                                j += 2;
                        }

                }

                file.close();
                return attribute;
        }

        void free_model_obj(attribute_t * attribute)
        { delete attribute; }
}