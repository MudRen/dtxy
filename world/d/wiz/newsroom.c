//Created by Canoe on 2001.03.10
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",HIG "���ŷ�����" NOR);
        set("long",@LONG


��post��������!�벻Ҫ����Discard! ����ǰ������!

LONG
        );
        
        set("exits", ([ /* sizeof() == 2 */
  "down" : __DIR__"wizroom",
]));
 set("objects", ([ /* sizeof() == 2 */
//  __DIR__"obj/shu" : 1,
//  __DIR__"npc/shenling" : 1,
]));
        setup();
call_other("/obj/board/ann_b", "???");
}

