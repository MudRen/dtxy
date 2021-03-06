// by snowcat jan 22 1998

#include <ansi.h>
#include <quest.c>

// the quest format is the following mapping:
// daoxing :     type     name     id            object         amount
//--------------------------------------------------------------------
//  1000   : ({ "find",  "????",   "mi ji" ,     "",             "1" }), 
//  5000   : ({ "give",  "????",   "zai min" ,   "????(silver)", "5" }), 
// 12000   : ({ "kill",  "?׹Ǿ?", "baigu jing", "",             "3" });
 
//??һ?????ţ??ȼ????????????ӣ??????׹Ǿ?????????????

mapping quests_furniture = ([
      50 : ({ "find", "?˵?",         "blade",              "", "1" }),
     110 : ({ "find", "??̳??",       "tanzi",              "", "1" }),
     120 : ({ "find", "??ƿ",         "youping",            "", "1" }),
     130 : ({ "find", "????",         "bag",                "", "1" }),
     140 : ({ "find", "????",         "fan he",             "", "1" }),
     210 : ({ "find", "??ɨ??",       "broom",              "", "1" }),
     220 : ({ "find", "ѩ????",       "snowglass",          "", "1" }),
     330 : ({ "find", "????",         "ruler",              "", "1" }),
    1100 : ({ "find", "??̺",         "gua tan",            "", "1" }),
    1200 : ({ "find", "????",         "xi hu",              "", "1" }),
    1300 : ({ "find", "????",         "xi wan",             "", "1" }),
    1400 : ({ "find", "??ľб????",   "yi zi",              "", "1" }),
    1500 : ({ "find", "?ο?ľ??",     "zhuo zi",            "", "1" }),
    2000 : ({ "find", "ԡ??",         "yu jin",             "", "1" }),
    3000 : ({ "find", "ˮ??",         "shui guan",          "", "1" }),
    4100 : ({ "find", "?ͺ?«",       "you hulu",           "", "1" }),
    4200 : ({ "find", "????Ͳ",       "qingzhu tong",       "", "1" }),
    5100 : ({ "find", "??¨",         "zhu lou",            "", "1" }),
    5200 : ({ "find", "ˮ?ƹ?",       "jiu guan",           "", "1" }),
    5300 : ({ "find", "?????Ͼƺ?",   "jiu hu",             "", "1" }),
    5400 : ({ "find", "?״ɻ???",     "hua pen",            "", "1" }),
    5500 : ({ "find", "??ʯ??ƿ",     "hua ping",           "", "1" }),
    5600 : ({ "find", "?̻?????",     "zhu lan",            "", "1" }),
    5700 : ({ "find", "ϸ????¨",     "zhu lou",            "", "1" }),
    5800 : ({ "find", "??ҩյ",       "yin yaozhan",        "", "1" }),
    5850 : ({ "find", "?ײ?",         "bai bu",             "", "1" }),
    5900 : ({ "find", "????",         "hua bu",             "", "1" }),

    6000 : ({ "find", "?ɻ???",       "deng long",          "", "1" }),
    6100 : ({ "find", "??????",       "deng long",          "", "1" }),
    6150 : ({ "find", "ѩ????",       "deng long",          "", "1" }),
    6200 : ({ "find", "?ۻ???",       "deng long",          "", "1" }),
    6250 : ({ "find", "÷????",       "deng long",          "", "1" }),
    6300 : ({ "find", "??????",       "deng long",          "", "1" }),
    6350 : ({ "find", "??????",       "deng long",          "", "1" }),
    6400 : ({ "find", "??????",       "deng long",          "", "1" }),
    6450 : ({ "find", "??????",       "deng long",          "", "1" }),
    6500 : ({ "find", "???õ?",       "deng long",          "", "1" }),
    6550 : ({ "find", "??????",       "deng long",          "", "1" }),
    6600 : ({ "find", "??????",       "deng long",          "", "1" }),
    6650 : ({ "find", "??????",       "deng long",          "", "1" }),
    6700 : ({ "find", "??????",       "deng long",          "", "1" }),
    6750 : ({ "find", "??????",       "deng long",          "", "1" }),
    6800 : ({ "find", "?λõ?",       "deng long",          "", "1" }),
    6850 : ({ "find", "??????",       "deng long",          "", "1" }),
    6900 : ({ "find", "??????",       "deng long",          "", "1" }),
    6950 : ({ "find", "?ɺ׵?",       "deng long",          "", "1" }),

    7000 : ({ "find", "???????ֳ???", "chair",              "", "1" }),
    7001 : ({ "find", "????????????", "chair",              "", "1" }),
    7002 : ({ "find", "???濿??????", "chair",              "", "1" }),
    7003 : ({ "find", "???濿??????", "chair",              "", "1" }),
    7004 : ({ "find", "???泤??",     "chair",              "", "1" }),
    7005 : ({ "find", "????????",     "chair",              "", "1" }),
    7006 : ({ "find", "??????????",   "chair",              "", "1" }),
    7007 : ({ "find", "??????????",   "chair",              "", "1" }),
    7008 : ({ "find", "?????۵?????", "chair",              "", "1" }),
    7009 : ({ "find", "?????۵?????", "chair",              "", "1" }),
    7010 : ({ "find", "???氲?ֳ???", "chair",              "", "1" }),
    7011 : ({ "find", "???氲??????", "chair",              "", "1" }),

    7100 : ({ "find", "???????ֳ???", "chair",              "", "1" }),
    7101 : ({ "find", "????????????", "chair",              "", "1" }),
    7102 : ({ "find", "???濿??????", "chair",              "", "1" }),
    7103 : ({ "find", "???濿??????", "chair",              "", "1" }),
    7104 : ({ "find", "???泤??",     "chair",              "", "1" }),
    7105 : ({ "find", "????????",     "chair",              "", "1" }),
    7106 : ({ "find", "??????????",   "chair",              "", "1" }),
    7107 : ({ "find", "??????????",   "chair",              "", "1" }),
    7108 : ({ "find", "?????۵?????", "chair",              "", "1" }),
    7109 : ({ "find", "?????۵?????", "chair",              "", "1" }),
    7110 : ({ "find", "???氲?ֳ???", "chair",              "", "1" }),
    7111 : ({ "find", "???氲??????", "chair",              "", "1" }),

    7200 : ({ "find", "???޷??ֳ???", "chair",              "", "1" }),
    7201 : ({ "find", "???޷???????", "chair",              "", "1" }),
    7202 : ({ "find", "???޿???????", "chair",              "", "1" }),
    7203 : ({ "find", "???޿???????", "chair",              "", "1" }),
    7204 : ({ "find", "???޳???",     "chair",              "", "1" }),
    7205 : ({ "find", "????????",     "chair",              "", "1" }),
    7206 : ({ "find", "???޴?????",   "chair",              "", "1" }),
    7207 : ({ "find", "???޴?????",   "chair",              "", "1" }),
    7208 : ({ "find", "?????۵?????", "chair",              "", "1" }),
    7209 : ({ "find", "?????۵?????", "chair",              "", "1" }),
    7210 : ({ "find", "???ް??ֳ???", "chair",              "", "1" }),
    7211 : ({ "find", "???ް???????", "chair",              "", "1" }),

    7300 : ({ "find", "˿?????ֳ???", "chair",              "", "1" }),
    7301 : ({ "find", "˿??????????", "chair",              "", "1" }),
    7302 : ({ "find", "˿?忿??????", "chair",              "", "1" }),
    7303 : ({ "find", "˿?忿??????", "chair",              "", "1" }),
    7304 : ({ "find", "˿?峤??",     "chair",              "", "1" }),
    7305 : ({ "find", "˿??????",     "chair",              "", "1" }),
    7306 : ({ "find", "˿????????",   "chair",              "", "1" }),
    7307 : ({ "find", "˿????????",   "chair",              "", "1" }),
    7308 : ({ "find", "˿???۵?????", "chair",              "", "1" }),
    7309 : ({ "find", "˿???۵?????", "chair",              "", "1" }),
    7310 : ({ "find", "˿?尲?ֳ???", "chair",              "", "1" }),
    7311 : ({ "find", "˿?尲??????", "chair",              "", "1" }),

    8001 : ({ "find", "??ľ??",       "table",              "", "1" }),
    8002 : ({ "find", "Сľ??",       "table",              "", "1" }),
    8003 : ({ "find", "??ľ??",       "table",              "", "1" }),
    8004 : ({ "find", "??ľ??",       "table",              "", "1" }),
    8005 : ({ "find", "Բľ??",       "table",              "", "1" }),
    8006 : ({ "find", "????ľ??",     "table",              "", "1" }),
    8007 : ({ "find", "????ľ??",     "table",              "", "1" }),
    8008 : ({ "find", "????ľ??",     "table",              "", "1" }),
    8011 : ({ "find", "??????",       "table",              "", "1" }),
    8012 : ({ "find", "С????",       "table",              "", "1" }),
    8013 : ({ "find", "??????",       "table",              "", "1" }),
    8014 : ({ "find", "??????",       "table",              "", "1" }),
    8015 : ({ "find", "Բ????",       "table",              "", "1" }),
    8016 : ({ "find", "????????",     "table",              "", "1" }),
    8017 : ({ "find", "????????",     "table",              "", "1" }),
    8018 : ({ "find", "????????",     "table",              "", "1" }),
    8021 : ({ "find", "????????",     "table",              "", "1" }),
    8022 : ({ "find", "С??????",     "table",              "", "1" }),
    8023 : ({ "find", "????????",     "table",              "", "1" }),
    8024 : ({ "find", "????????",     "table",              "", "1" }),
    8025 : ({ "find", "Բ??????",     "table",              "", "1" }),
    8026 : ({ "find", "??????????",   "table",              "", "1" }),
    8027 : ({ "find", "??????????",   "table",              "", "1" }),
    8028 : ({ "find", "??????????",   "table",              "", "1" }),
    8031 : ({ "find", "???޽???",     "table",              "", "1" }),
    8032 : ({ "find", "С?޽???",     "table",              "", "1" }),
    8033 : ({ "find", "???޽???",     "table",              "", "1" }),
    8034 : ({ "find", "???޽???",     "table",              "", "1" }),
    8035 : ({ "find", "Բ?޽???",     "table",              "", "1" }),
    8036 : ({ "find", "?????޽???",   "table",              "", "1" }),
    8037 : ({ "find", "?????޽???",   "table",              "", "1" }),
    8038 : ({ "find", "?????޽???",   "table",              "", "1" }),

    9000 : ({ "find", "??Ƥ",         "shou pi",            "", "1" }),

   25000 : ({ "find", "??ƿ",         "jingping",           "", "1" }),

   30000 : ({ "find", "??????",       "mallet",             "", "1" }),
   35000 : ({ "find", HIC"????ϻ"NOR, "camera",             "", "1" }),

   45000 : ({ "find", "????????",     "panzi",              "", "1" }),
  200000 : ({ "find", "??Կ??",       "tie yaoshi",         "", "1" }),
 1800000 : ({ "find", "?ƽ?ϻ??",     "xiazi",              "", "1" }),
]);


