#include <kernel.h>
#include <stdint.h>

#include "external/gsKit/include/gsKit.h"
#include "external/gsKit/include/dmaKit.h"

GSGLOBAL *settings = NULL;
const uint64_t CLEAR_COLOR = GS_SETREG_RGBAQ(0x00, 0x00, 0x3f, 0x80, 0x00);

typedef struct TRIANGLE_VERTEX_DATA
{
    float x __attribute__ ((packed));
    float y __attribute__ ((packed));
    int32_t z __attribute__ ((packed));
} VertexData;

void InitScreenSettings()
{
    settings = gsKit_init_global();
    settings->PrimAlphaEnable = GS_SETTING_ON;

    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    gsKit_set_primalpha(settings, GS_SETREG_ALPHA(0, 1, 0, 1, 0), 0);

    gsKit_set_clamp(settings, GS_CMODE_REPEAT);
    gsKit_vram_clear(settings);
    gsKit_init_screen(settings);
    gsKit_mode_switch(settings, GS_ONESHOT);
}

void FlipScreen(GSGLOBAL *gsGlobal)
{
    gsKit_queue_exec(gsGlobal);
    gsKit_sync_flip(gsGlobal);
}

///////////////////////////////////////////////////////////////////////////////////
/// Explanation about the coordinates:
///     The coordinate system starts at (0, 0) as usual,
///     however it does not start in the center of the screen like OpenGL,
///     rather in the top-left. So all coordinates passed into the prim
///     functions of gsKit expect these coordinates.
///////////////////////////////////////////////////////////////////////////////////

/**
 * Draws a rectangle on the screen given a starting coordinates, width, height, zOffset and color.
 */
void DrawRectangle(float startX, float startY, float width, float height, int zOffset, uint64_t color)
{
    gsKit_prim_sprite(settings, startX, startY,
                      startX + width, startY + height,
                      zOffset, color);
}

/**
 * Draws a triangle on the screen given the vertex coordinates and color.
 */
void DrawTriangle(const VertexData *v1, const VertexData *v2, const VertexData *v3, uint64_t color)
{
    gsKit_prim_triangle_3d(settings,
                           (float) v1->x, (float) v1->y, v1->z,
                           (float) v2->x, (float) v2->y, v2->z,
                           (float) v3->x, (float) v3->y, v3->z,
                           color);
}

/**
 * Draws a line on the screen given a vertex coordinates for the start of the line and it's end and color.
 */
void DrawLine(const VertexData *startPoint, const VertexData *endPoint, uint64_t color)
{
    gsKit_prim_line_3d(settings,
                       startPoint->x, startPoint->y, startPoint->z,
                       endPoint->x, endPoint->y, endPoint->z,
                       color);
}

/**
 * Draws a point on the screen given the coordinates and color.
 */
void DrawPoint(const VertexData *point, uint64_t color)
{
    gsKit_prim_point(settings, point->x, point->y, point->z, color);
}

int main(void)
{
    InitScreenSettings();

    const float rectW = 300;
    const float rectH = 200;
    const float rectX = (float) settings->Width / 2.0f - rectW / 2.0f;
    const float rectY = (float) settings->Height / 2.0f - rectH / 2.0f;

    const VertexData v1 = {.x = rectX + rectW / 2.0f, .y = rectY, .z = 0};
    const VertexData v2 = {.x = rectX + rectW, .y = (rectY + rectH), .z = 0};
    const VertexData v3 = {.x = rectX, .y = (rectY + rectH), .z = 0};
    const VertexData v4 = {.x = (float) settings->Width / 2.0f, .y = (float) settings->Height / 2.0f, .z = 0};

    while (1)
    {
        gsKit_clear(settings, CLEAR_COLOR);

        DrawRectangle(rectX, rectY, rectW, rectH, 0,
                      GS_SETREG_RGBAQ(127, 127, 127, 0x80, 0));
        DrawTriangle(&v1, &v2, &v3, GS_SETREG_RGBAQ(0, 96, 24, 0x80, 0));

        DrawLine(&v1, &v3, GS_SETREG_RGBAQ(127, 0, 0, 0x80, 0));
        DrawPoint(&v4, GS_SETREG_RGBAQ(0, 0, 255, 0x80, 0));

        FlipScreen(settings);
    }

    return 0;
}
