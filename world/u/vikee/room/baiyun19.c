inherit ROOM;
#include <room.h>

void create ()
{
  set ("short", "���ƶ�");
  set ("long", @LONG

������С������ȴ������ء�
LONG);
  set("exits", ([ /* sizeof() == 3 */
  "northwest" : __DIR__"baiyun1",
  "northeast" : __DIR__"baiyun2",
  "north":      __DIR__"road1",
]));

  set("no_clean_up", 1);
  setup();
}
int clean_up()
{
      return 0;
}

