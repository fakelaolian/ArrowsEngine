/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
#include "alsl.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define RD_VTX   1
#define RD_FRAG  2
#define RD_NONE  0

void load_shader_source(const char *filename, ShaderSource *pSource)
{
        FILE *          in_file;
        struct stat     sb;
        char *          line;
        char *          vtx;
        char *          frag;
        int             vtx_alloclen;
        int             frag_alloclen;
        int             stage;

        vtx_alloclen = 1024;
        frag_alloclen = 1024;
        in_file = fopen(filename, "r");
        if (!in_file) {
                perror("fopen");
                exit(EXIT_FAILURE);
        }

        if (stat(filename, &sb) == -1) {
                perror("stat");
                exit(EXIT_FAILURE);
        }

        line = vmalloc(sb.st_size);
        vtx = vmalloc(vtx_alloclen);
        vtx[0] = '\0';
        frag = vmalloc(vtx_alloclen);
        frag[0] = '\0';

        while (fscanf(in_file, "%[^\n] ", line) != EOF) {
                if (strncmp(line, "#version", 8) == 0) {
                        strcat(vtx, line);
                        strcat(vtx, "\n");
                        strcat(frag, line);
                        strcat(frag, "\n");
                        continue;
                }

                if (strcmp(line, "#vtx") == 0) {
                        stage = RD_VTX;
                        continue;
                }

                if (strcmp(line, "#end") == 0) {
                        stage = RD_NONE;
                        continue;
                }

                if (strcmp(line, "#frag") == 0) {
                        stage = RD_FRAG;
                        continue;
                }

                if (stage == RD_VTX) {
                        if ((strlen(vtx) + strlen(line)) > vtx_alloclen) {
                                vtx_alloclen += vtx_alloclen;
                                vtx = vrealloc(vtx, vtx_alloclen);
                        }
                        strcat(vtx, line);
                        strcat(vtx, "\n");
                        continue;
                }

                if (stage == RD_FRAG) {
                        if ((strlen(frag) + strlen(line)) > frag_alloclen) {
                                frag_alloclen += frag_alloclen;
                                frag = vrealloc(frag, frag_alloclen);
                        }
                        strcat(frag, line);
                        strcat(frag, "\n");
                        continue;
                }
        }

        pSource->vtx = vtx;
        pSource->frag = frag;

        vfree(line);
        fclose(in_file);

}

void free_shader_source(ShaderSource *pSource)
{
        vfree(pSource->vtx);
        vfree(pSource->frag);
}