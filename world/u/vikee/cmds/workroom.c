#include <ansi.h>
inherit ROOM;
void create()
{
    set("short", "ɽ��Сͤ");
    set("long", 
"������һҶ֪�﹤���ĵط�:\n\n"
HIY "           ���ɪɪ\n"
    "           ��ҶƮƮ\n\n"
HIG "��������:vikee@hanwang.com.cn / vikee@263.net\n\n" NOR
);
        set("exits", ([
            "down" :"/d/city/kezhan.c",
        ]));
        replace_program(ROOM);
}
