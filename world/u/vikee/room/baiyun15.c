inherit ROOM;
#include <room.h>

void create ()
{
  set ("short", "���ƶ�");
  set ("long", @LONG

������С������ȴ������ء�
LONG);
  set("exits", ([ /* sizeof() == 3 */
  "northwest" : __DIR__"baiyun16",
  "northeast" : __DIR__"baiyun17",
  "north":      __DIR__"baiyun18",
]));

  set("no_clean_up", 1);
  setup();
}
int clean_up()
{
      return 0;
}

