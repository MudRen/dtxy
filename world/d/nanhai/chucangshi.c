// Room: /d/nanhai/chucangshi

#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "������");
  set ("long", @LONG

����һ��������һЩ�����С���ӣ����⻹��һЩ������������
Ϊ����ȼ�ϵ����ɰ�ʲô�ġ�
LONG);

  set("exits", ([ /* sizeof() == 1 */
"north" : __DIR__"zoulang2",
]));
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"obj/shugan" : 2,
]));
  set("no_fight", 1);
  set("light_up", 1);
  set("no_magic", 1);

create_door("north", "С��", "south", DOOR_CLOSED);
  setup();
}
