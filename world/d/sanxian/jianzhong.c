#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", CYN"��ڣ"NOR);
        set("long", @LONG

��������ɽ���Ӽ����ĵط�����˵�̿ͽ�������������������ģ�
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 2 */
  "east" : "/d/sanxian/sleep",
]));
 set("objects", ([
"/d/sanxian/npc/zhangmen" : 1,
"/d/sanxian/npc/guiguzi" : 1,
  ]) );  
        setup();
  call_other("/obj/board/jian_b", "???");
        replace_program(ROOM);
}
