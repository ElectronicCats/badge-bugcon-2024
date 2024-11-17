#pragma once

#include <stdio.h>

#define UUID_LEN 16

#define EKOPARTY_STR      "EkoParty"
#define HW_HACK_STR       "`Hardware_Hacking'"
#define BIT_CANA_STR      "`A_1_bit_de_ir_en_cana'"
#define BLUE_SPACE_STR    "`Blue_Space'"
#define RED_TEAM_STR      "`Red_Team'"
#define CYB_FIN_STR       "`Cyber_Finance'"
#define HAMPING_STR       "`Hamping'"
#define BUG_BOU_SPA_STR   "`Bug_Bounty_Space'"
#define SOCIAL_ENG_STR    "`Social_Engineering'"
#define PAT_SPACE_STR     "`Patagon_Space'"
#define BLOCK_SEC_STR     "`Blockchain_Security_Space'"
#define DEV_SEC_OPS_STR   "`DevSecOps'"
#define SASO_CONF_STR     "`SASOConf'"
#define CAR_HACK_STR      "`Car_Hacking'"
#define MOB_HACK_STR      "`Mobile_Hacking'"
#define EC_STR            "`Electronic_Cats'"
#define CHICHES_ASADO_STR "`Has_llegado_al_asado'"
#define THE_BOSS_1_STR    " ES EL BOSS!!!"
#define THE_BOSS_2_STR    " ES EL BOSS!!!"
#define YWE_HACK_STR      "Yes_We_Hack!!"

#define HW_HACK_ID                                                          \
  {                                                                         \
    0xE7, 0xA3, 0x4B, 0xF1, 0x67, 0xBF, 0x41, 0xD2, 0xB5, 0x26, 0xE1, 0x58, \
        0x7D, 0xC2, 0x82, 0xC5                                              \
  }
#define BIT_CANA_ID                                                         \
  {                                                                         \
    0xB2, 0x15, 0x2E, 0xC7, 0xA8, 0x4D, 0x43, 0xD3, 0xC0, 0x11, 0xE6, 0x39, \
        0x8F, 0xD1, 0x6D, 0xAA                                              \
  }
#define BLUE_SPACE_ID                                                       \
  {                                                                         \
    0xF3, 0xB7, 0x5C, 0xC9, 0x67, 0xAA, 0x44, 0xE4, 0xA7, 0x38, 0xE9, 0x72, \
        0x2C, 0xF4, 0x5E, 0xC8                                              \
  }
#define RED_TEAM_ID                                                         \
  {                                                                         \
    0xA1, 0xC2, 0x3D, 0xE5, 0x99, 0xBF, 0x4E, 0xD8, 0xA3, 0x21, 0xF5, 0x49, \
        0x7F, 0xA9, 0xCC, 0xB3                                              \
  }
#define CYB_FIN_ID                                                          \
  {                                                                         \
    0xD7, 0xA2, 0x12, 0xC8, 0x67, 0xBF, 0x42, 0xE1, 0xA5, 0x15, 0xE6, 0x39, \
        0x8D, 0xC1, 0x79, 0xC4                                              \
  }
#define HAMPING_ID                                                          \
  {                                                                         \
    0x7F, 0xEA, 0x8B, 0xC2, 0x46, 0x9D, 0x5A, 0xE1, 0xF2, 0x14, 0xE6, 0x45, \
        0xD3, 0xB7, 0x9A, 0xF4                                              \
  }
#define BUG_BOU_SPA_ID                                                      \
  {                                                                         \
    0xC5, 0xA8, 0xBC, 0x0E, 0xE3, 0xFA, 0x4D, 0xE0, 0xB2, 0x1A, 0xF9, 0x6F, \
        0x8D, 0xC0, 0x73, 0xA1                                              \
  }
#define SOCIAL_ENG_ID                                                       \
  {                                                                         \
    0xA0, 0x3D, 0x57, 0xF5, 0x69, 0xBF, 0x20, 0xE9, 0x8C, 0x39, 0xE1, 0x5C, \
        0x2F, 0x6A, 0x91, 0x7D                                              \
  }
#define PAT_SPACE_ID                                                        \
  {                                                                         \
    0x11, 0xB9, 0x9A, 0x3F, 0x26, 0x8F, 0x43, 0xE7, 0xC4, 0x67, 0xD5, 0x92, \
        0x1E, 0xC3, 0x0D, 0x89                                              \
  }
#define BLOCK_SEC_ID                                                        \
  {                                                                         \
    0x6D, 0xE5, 0x8B, 0xBA, 0x9D, 0xA4, 0x41, 0xE0, 0xF1, 0x22, 0xC3, 0x57, \
        0xF5, 0x8A, 0x9F, 0xC8                                              \
  }
#define DEV_SEC_OPS_ID                                                      \
  {                                                                         \
    0xD9, 0xE8, 0x73, 0x92, 0x4B, 0xCF, 0x48, 0xF1, 0x8C, 0x34, 0xE6, 0x2B, \
        0xA7, 0x5F, 0xB4, 0x8D                                              \
  }
#define SASO_CONF_ID                                                        \
  {                                                                         \
    0x3E, 0x72, 0x0A, 0x61, 0x8D, 0xE5, 0x43, 0xDD, 0xBF, 0xF7, 0x9C, 0x5A, \
        0xA3, 0x41, 0x8E, 0x79                                              \
  }
#define CAR_HACK_ID                                                         \
  {                                                                         \
    0x4B, 0x6E, 0xA3, 0xE1, 0x2F, 0xC6, 0x4A, 0xDA, 0xF8, 0x91, 0xE4, 0x3C, \
        0x6D, 0xF0, 0xAD, 0xA2                                              \
  }
#define MOB_HACK_ID                                                         \
  {                                                                         \
    0x7B, 0xC5, 0xD1, 0x0C, 0xD7, 0x92, 0x45, 0xC2, 0xA4, 0x2E, 0xFF, 0x8E, \
        0x7F, 0xA0, 0xE9, 0x1C                                              \
  }
#define EC_ID                                                               \
  {                                                                         \
    0x5D, 0x8A, 0xC2, 0xFB, 0x3E, 0xA1, 0x40, 0xE8, 0xD6, 0x7B, 0x1D, 0x54, \
        0xC1, 0x79, 0xB6, 0x8F                                              \
  }
#define CHICHES_ASADO_ID                                                    \
  {                                                                         \
    0x9C, 0xA4, 0xB5, 0xE8, 0x1E, 0x62, 0x48, 0xE5, 0xC7, 0x12, 0xF3, 0x6D, \
        0xA4, 0x35, 0x9C, 0x2E                                              \
  }

#define THE_BOSS_1_ID                                                       \
  {                                                                         \
    0xA4, 0xD3, 0x5E, 0xF7, 0xC1, 0x8B, 0x42, 0xE4, 0xB0, 0x29, 0xF8, 0x3C, \
        0x6A, 0x7F, 0x92, 0xC0                                              \
  }
#define THE_BOSS_2_ID                                                       \
  {                                                                         \
    0xB6, 0xC1, 0x7D, 0xE5, 0xF0, 0xA3, 0x54, 0xD8, 0xC3, 0x1E, 0xF7, 0x41, \
        0x9A, 0x2B, 0x4E, 0x8D                                              \
  }
#define YWE_HACK_ID                                                         \
  {                                                                         \
    0x6B, 0xC5, 0xD1, 0x0C, 0xD7, 0x92, 0x45, 0xC2, 0xA4, 0x2E, 0xFF, 0x8E, \
        0x7F, 0xA0, 0xE9, 0x1C                                              \
  }

typedef enum {
  EKOPARTY,
  HW_HACK,
  BIT_CANA,
  BLUE_SPACE,
  RED_TEAM,
  CYB_FIN,
  HAMPING,
  BUG_BOU_SPA,
  SOCIAL_ENG,
  PAT_SPACE,
  BLOCK_SEC,
  DEV_SEC_OPS,
  SASO_CONF,
  CAR_HACK,
  MOB_HACK,
  EC,
  CHICHES_ASADO,  // To add more villages, please insert them before this item
  THE_BOSS_1,
  THE_BOSS_2,
  YWE_HACK,
  VILLAGES_COUNT
} villages_e;

typedef struct {
  villages_e idx;
  char* name;
  uint8_t* uuid;
  uint8_t R;
  uint8_t G;
  uint8_t B;
} village_t;

const uint8_t hw_hack_id[UUID_LEN] = HW_HACK_ID;
const uint8_t bit_cana_id[UUID_LEN] = BIT_CANA_ID;
const uint8_t blue_space_id[UUID_LEN] = BLUE_SPACE_ID;
const uint8_t red_team_id[UUID_LEN] = RED_TEAM_ID;
const uint8_t cyb_fin_id[UUID_LEN] = CYB_FIN_ID;
const uint8_t hamping_id[UUID_LEN] = HAMPING_ID;
const uint8_t bug_bou_spa_id[UUID_LEN] = BUG_BOU_SPA_ID;
const uint8_t social_eng_id[UUID_LEN] = SOCIAL_ENG_ID;
const uint8_t pat_space_id[UUID_LEN] = PAT_SPACE_ID;
const uint8_t block_sec_id[UUID_LEN] = BLOCK_SEC_ID;
const uint8_t dev_sec_ops_id[UUID_LEN] = DEV_SEC_OPS_ID;
const uint8_t saso_conf_id[UUID_LEN] = SASO_CONF_ID;
const uint8_t car_hack_id[UUID_LEN] = CAR_HACK_ID;
const uint8_t mob_hack_id[UUID_LEN] = MOB_HACK_ID;
const uint8_t ec_id[UUID_LEN] = EC_ID;
const uint8_t chiches_asado_id[UUID_LEN] = CHICHES_ASADO_ID;
const uint8_t the_boss_1_id[UUID_LEN] = THE_BOSS_1_ID;
const uint8_t the_boss_2_id[UUID_LEN] = THE_BOSS_2_ID;
const uint8_t ywe_hack_id[UUID_LEN] = YWE_HACK_ID;

const village_t villages[] = {
    {.idx = EKOPARTY,
     .name = EKOPARTY_STR,
     .uuid = NULL,
     .R = 0,
     .G = 0,
     .B = 0},
    {.idx = HW_HACK,
     .name = HW_HACK_STR,
     .uuid = hw_hack_id,
     .R = 17,
     .G = 85,
     .B = 204},
    {.idx = BIT_CANA,
     .name = BIT_CANA_STR,
     .uuid = bit_cana_id,
     .R = 0,
     .G = 255,
     .B = 255},
    {.idx = BLUE_SPACE,
     .name = BLUE_SPACE_STR,
     .uuid = blue_space_id,
     .R = 11,
     .G = 84,
     .B = 148},
    {.idx = RED_TEAM,
     .name = RED_TEAM_STR,
     .uuid = red_team_id,
     .R = 255,
     .G = 0,
     .B = 0},
    {.idx = CYB_FIN,
     .name = CYB_FIN_STR,
     .uuid = cyb_fin_id,
     .R = 255,
     .G = 0,
     .B = 255},
    {.idx = HAMPING,
     .name = HAMPING_STR,
     .uuid = hamping_id,
     .R = 144,
     .G = 87,
     .B = 35},
    {.idx = BUG_BOU_SPA,
     .name = BUG_BOU_SPA_STR,
     .uuid = bug_bou_spa_id,
     .R = 111,
     .G = 8,
     .B = 220},
    {.idx = SOCIAL_ENG,
     .name = SOCIAL_ENG_STR,
     .uuid = social_eng_id,
     .R = 208,
     .G = 218,
     .B = 26},
    {.idx = PAT_SPACE,
     .name = PAT_SPACE_STR,
     .uuid = pat_space_id,
     .R = 107,
     .G = 155,
     .B = 230},
    {.idx = BLOCK_SEC,
     .name = BLOCK_SEC_STR,
     .uuid = block_sec_id,
     .R = 74,
     .G = 134,
     .B = 232},
    {.idx = DEV_SEC_OPS,
     .name = DEV_SEC_OPS_STR,
     .uuid = dev_sec_ops_id,
     .R = 230,
     .G = 145,
     .B = 56},
    {.idx = SASO_CONF,
     .name = SASO_CONF_STR,
     .uuid = saso_conf_id,
     .R = 255,
     .G = 255,
     .B = 0},
    {.idx = CAR_HACK,
     .name = CAR_HACK_STR,
     .uuid = car_hack_id,
     .R = 255,
     .G = 10,
     .B = 10},
    {.idx = MOB_HACK,
     .name = MOB_HACK_STR,
     .uuid = mob_hack_id,
     .R = 109,
     .G = 157,
     .B = 235},
    {.idx = EC, .name = EC_STR, .uuid = ec_id, .R = 106, .G = 168, .B = 79},
    {.idx = CHICHES_ASADO,
     .name = CHICHES_ASADO_STR,
     .uuid = chiches_asado_id,
     .R = 255,
     .G = 255,
     .B = 255},
    {.idx = THE_BOSS_1,
     .name = THE_BOSS_1_STR,
     .uuid = the_boss_1_id,
     .R = 255,
     .G = 0,
     .B = 0},
    {.idx = THE_BOSS_2,
     .name = THE_BOSS_2_STR,
     .uuid = the_boss_2_id,
     .R = 255,
     .G = 0,
     .B = 0},
    {.idx = YWE_HACK,
     .name = YWE_HACK_STR,
     .uuid = ywe_hack_id,
     .R = 255,
     .G = 93,
     .B = 18}};

void villages_begin();

village_t* villages_get_current_village();