#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ӭ���Ʒ�");
        set("long", 
"���ϵ�ʯ�Ʒ�����֪��ʲôʱ���޽���\n"+
"ʯ�������ۣ�����̨��ȴһ����Ⱦ��\n"+
"�ߴ���Ʒ���������ţ�\n"+
HIG"    ��      ɽ      ��      ��  \n"NOR
);
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"square",
  "southdown" : __DIR__"path1",
]));

        set("objects",([
        __DIR__"npc/zhike" : 2,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xx" );

        setup();
  call_other("/obj/board/sword_b", "???");
        replace_program(ROOM);
}
