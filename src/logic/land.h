#include <psp-include.h>
#include <logic/utils.h>

#define CHUNK_SIZE 32

typedef enum
{
    CTYPE_FOREST,
    CTYPE_DESERT,
} chunk_type;

typedef struct
{
    chunk_type type;
} chunk_t;

typedef struct
{
    int row_cnt;
    int col_cnt;
    chunk_t *chunks;
    SDL_Texture *texture;
} land_t;

chunk_t *chunk_at(land_t *land, int row, int col)
{
    return land->chunks + row * land->col_cnt + col;
}

int init_land(land_t *land, int row_cnt, int col_cnt)
{
    land->row_cnt = row_cnt;
    land->col_cnt = col_cnt;
    land->chunks = malloc(row_cnt * col_cnt);
    if (!land->chunks)
        return -1;

    for (int cnt = 0; cnt < row_cnt * col_cnt; cnt++)
        land->chunks[cnt].type = CTYPE_DESERT;

    return 0;
}

SDL_Rect create_quad(int angle, int x, int y, int tile_size)
{
    int screen_x;
    int screen_y;

    switch (angle)
    {
    case 0: // No rotation
        screen_x = x * tile_size;
        screen_y = y * tile_size;
        break;

    case 45: // Isometric projection
        screen_x = (x - y) * tile_size / 2;
        screen_y = (x + y) * tile_size / 2;
        break;

    case 90: // 90-degree rotation
        screen_x = -y * tile_size;
        screen_y = x * tile_size;
        break;

    case 135: // 135-degree rotation (isometric + rotation)
        screen_x = -(x - y) * tile_size / 2;
        screen_y = (x + y) * tile_size / 2;
        break;

    case 180: // 180-degree flip
        screen_x = -x * tile_size;
        screen_y = -y * tile_size;
        break;

    default: // Fallback (no rotation)
        screen_x = x * tile_size;
        screen_y = y * tile_size;
        break;
    }

    return (SDL_Rect){screen_x, screen_y, tile_size, tile_size};
}

sprite_t draw_land(land_t *land, int angle)
{
    SDL_SetRenderTarget(app_renderer(app), land->texture);
    for (int row = 0; row < land->row_cnt; row++)
        for (int col = 0; col < land->col_cnt; col++)
        {
            SDL_Texture *texture;
            if (chunk_at(land, row, col)->type == CTYPE_FOREST)
                texture = resources.turf;
            if (chunk_at(land, row, col)->type == CTYPE_DESERT)
                texture = resources.desert_turf;

            SDL_Rect quad = create_quad(angle, col, row, CHUNK_SIZE);
            SDL_RenderCopy(app_renderer(app), texture, NULL, &quad);
        }
    SDL_SetRenderTarget(app_renderer(app), NULL);

    return (sprite_t){
        .width = app.width,
        .height = app.height,
        .x = 0,
        .y = 0,
        .texture = land->texture,
    };
}