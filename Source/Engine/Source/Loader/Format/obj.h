/* AUTHOR: 2BKBD, DATE: 2022/1/17 */
namespace anci {

#       define READ_STAGE_NONE     0
#       define READ_STAGE_VERTEX   1
#       define READ_STAGE_TEXCOORD 2
#       define READ_STAGE_NORMAL   3
#       define READ_STAGE_OBJECT   4
#       define READ_STAGE_MATERIAL 5
#       define READ_STAGE_FACE     6

        inline void load_obj_check_stage(const std::string& line, unsigned int &stage)
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
        }

        inline void load_obj_parse_line(std::string &line, unsigned int stage, attribute_t *attribute)
        {
                if (stage == READ_STAGE_VERTEX) {
                        std::vector<std::string> vertex;
                        StringUtils::split(line, " ", vertex);
                        attribute->vertices.push_back(std::stof(vertex[1]));
                        attribute->vertices.push_back(std::stof(vertex[2]));
                        attribute->vertices.push_back(std::stof(vertex[3]));
                        return;
                }

                if (stage == READ_STAGE_NORMAL) {
                        std::vector<std::string> normals;
                        StringUtils::split(line, " ", normals);
                        attribute->normals.push_back(std::stof(normals[1]));
                        attribute->normals.push_back(std::stof(normals[2]));
                        attribute->normals.push_back(std::stof(normals[3]));
                        return;
                }

                if (stage == READ_STAGE_TEXCOORD) {
                        std::vector<std::string> texCoords;
                        StringUtils::split(line, " ", texCoords);
                        attribute->normals.push_back(std::stof(texCoords[1]));
                        attribute->normals.push_back(std::stof(texCoords[2]));
                        return;
                }

                if (stage == READ_STAGE_MATERIAL) {
                        return;
                }

                if (stage == READ_STAGE_OBJECT) {
                        return;
                }

                if (stage == READ_STAGE_FACE) {
                        return;
                }
        }

        inline attribute_t *load_model_obj(const char *filename)
        {
                std::string line;
                std::ifstream file(filename, std::ios::in);

                unsigned long count = 0;
                unsigned int stage = READ_STAGE_NONE;
                attribute_t *attribute = new attribute_t();

                while(!file.eof()) {
                        /* 读取一行模型文件 */
                        std::getline(file, line);
                        /* 检查当前模型读取阶段 */
                        load_obj_check_stage(line, stage);
                        /* 解析obj文本行 */
                        load_obj_parse_line(line, stage, attribute);
                        count++;
                }

                attribute->count = count;

                file.close();
                return attribute;
        }
}