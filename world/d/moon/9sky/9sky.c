#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "����֮��");
  set ("long", @LONG

�������̫����ĵ����ˣ�̫��Ҳ��������ת�����½���ȥ����
����ռ��ޱ��޼ʣ����������쳣��
LONG);

  set("objects", ([ /* sizeof() == 1*/ 
//  __DIR__"npc/hunter" : 2,
]));

  set("outdoors", 1);
  
set("objects", ([
                __DIR__"npc/sun" : 1,
       ]) );

  setup();
}
